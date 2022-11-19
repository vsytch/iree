// Copyright 2020 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "iree/compiler/Dialect/HAL/Target/D3D12SPIRV/SPIRVToHLSL.h"

#include <vector>

#include "llvm/ADT/STLExtras.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

// Disable exception handling in favor of assertions.
#define SPIRV_CROSS_EXCEPTIONS_TO_ASSERTIONS
#include "third_party/spirv_cross/spirv_hlsl.hpp"

#define DEBUG_TYPE "spirv-to-hlsl"

namespace mlir {
namespace iree_compiler {

namespace {
class SPIRVToHLSLCompiler : public SPIRV_CROSS_NAMESPACE::CompilerHLSL {
 public:
  using CompilerHLSL::CompilerHLSL;

  D3D12Shader::ThreadGroupSize getWorkgroupSizeForEntryPoint(
      StringRef entryName) {
    const auto& entryPoint = get_entry_point(
        entryName.str(), spv::ExecutionModel::ExecutionModelGLCompute);
    const auto& workgroupSize = entryPoint.workgroup_size;
    // TODO(vsytch): support specialization constant.
    if (workgroupSize.constant != 0) return {0, 0, 0};
    return {workgroupSize.x, workgroupSize.y, workgroupSize.z};
  }

  // A struct containing a resource descriptor's information.
  struct Descriptor {
    uint32_t set;
    uint32_t binding;

    Descriptor(uint32_t s, uint32_t b) : set(s), binding(b) {}

    friend bool operator<(const Descriptor& l, const Descriptor& r) {
      return std::tie(l.set, l.binding) < std::tie(r.set, r.binding);
    }
  };

  // Returns all all resource buffer descriptors' set and binding number pairs
  // in increasing order.
  std::vector<Descriptor> getBufferSetBindingPairs() {
    std::vector<Descriptor> descriptors;

    // Iterate over all variables in the SPIR-V blob.
    ir.for_each_typed_id<SPIRV_CROSS_NAMESPACE::SPIRVariable>(
        [&](uint32_t id, SPIRV_CROSS_NAMESPACE::SPIRVariable& var) {
          auto storage = var.storage;
          switch (storage) {
              // Non-interface variables. We don't care.
            case spv::StorageClassFunction:
            case spv::StorageClassPrivate:
            case spv::StorageClassWorkgroup:
              // Builtin variables. We don't care either.
            case spv::StorageClassInput:
              return;
            default:
              break;
          }
          if (storage == spv::StorageClassUniform ||
              storage == spv::StorageClassStorageBuffer) {
            uint32_t setNo = get_decoration(id, spv::DecorationDescriptorSet);
            uint32_t bindingNo = get_decoration(id, spv::DecorationBinding);
            descriptors.emplace_back(setNo, bindingNo);
            return;
          }
          // TODO(antiagainst): push constant
          assert(false && "unspported storage class in SPIRVToHLSLCompiler");
        });

    llvm::sort(descriptors);
    return descriptors;
  }

  Options getCompilationOptions() {
    // TODO(vsytch): fill out the following according to the D3D12 GPU
    // family.
    return SPIRVToHLSLCompiler::Options{};
  }
};
}  // namespace

llvm::Optional<D3D12Shader> crossCompileSPIRVToHLSL(
    llvm::ArrayRef<uint32_t> spvBinary, StringRef entryPoint) {
  SPIRVToHLSLCompiler spvCrossCompiler(spvBinary.data(), spvBinary.size());

  // All spirv-cross operations work on the current entry point. It should be
  // set right after the cross compiler construction.
  spvCrossCompiler.set_entry_point(
      entryPoint.str(), spv::ExecutionModel::ExecutionModelGLCompute);

  // Explicitly set the argument buffer index for each SPIR-V resource variable.
  auto descriptors = spvCrossCompiler.getBufferSetBindingPairs();
  for (const auto& descriptor : descriptors) {
    if (descriptor.set != 0) {
      assert(false &&
             "multiple descriptor set unimplemented in SPIRVToHLSLCompiler");
    }

    SPIRV_CROSS_NAMESPACE::HLSLResourceBinding binding = {};
    binding.stage = spv::ExecutionModelGLCompute;
    binding.desc_set = descriptor.set;
    binding.binding = descriptor.binding;
    // TODO(vsytch): We only interact with buffers in IREE.
    binding.uav = {0, descriptor.binding};

    spvCrossCompiler.add_hlsl_resource_binding(binding);
  }

  auto spvCrossOptions = spvCrossCompiler.getCompilationOptions();
  spvCrossCompiler.set_hlsl_options(spvCrossOptions);

  std::string hlslSource = spvCrossCompiler.compile();
  LLVM_DEBUG(llvm::dbgs()
             << "Cross compiled High Level Shading Language source code:\n-----\n"
             << hlslSource << "\n-----\n");

  auto workgroupSize =
      spvCrossCompiler.getWorkgroupSizeForEntryPoint(entryPoint);
  if (!workgroupSize.x || !workgroupSize.y || !workgroupSize.z) {
    return llvm::None;
  }
  return D3D12Shader{std::move(hlslSource), workgroupSize};
}

}  // namespace iree_compiler
}  // namespace mlir
