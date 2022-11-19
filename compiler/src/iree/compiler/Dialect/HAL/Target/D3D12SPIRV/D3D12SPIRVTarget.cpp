// Copyright 2020 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "iree/compiler/Dialect/HAL/Target/D3D12SPIRV/D3D12SPIRVTarget.h"

#include "iree/compiler/Codegen/Dialect/IREECodegenDialect.h"
#include "iree/compiler/Codegen/Passes.h"
#include "iree/compiler/Dialect/HAL/Target/D3D12SPIRV/SPIRVToHLSL.h"
#include "iree/compiler/Dialect/HAL/Target/TargetRegistry.h"
#include "iree/compiler/Utils/FlatbufferUtils.h"
#include "iree/schemas/d3d12_executable_def_builder.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/GPU/IR/GPUDialect.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/SPIRV/IR/SPIRVDialect.h"
#include "mlir/Dialect/SPIRV/IR/SPIRVOps.h"
#include "mlir/Dialect/SPIRV/IR/TargetAndABI.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
#include "mlir/Target/SPIRV/Serialization.h"

namespace mlir {
namespace iree_compiler {
namespace IREE {
namespace HAL {

// TODO(vsytch): provide a proper target environment for D3D12.
static spirv::TargetEnvAttr getD3D12TargetEnv(MLIRContext *context) {
  auto triple = spirv::VerCapExtAttr::get(
      spirv::Version::V_1_0, {spirv::Capability::Shader},
      {spirv::Extension::SPV_KHR_storage_buffer_storage_class}, context);
  // TODO(vsytch): pretend to be Vulkan until MLIR learns about a D3D12 SPIRV dialect.
  return spirv::TargetEnvAttr::get(
      triple, spirv::getDefaultResourceLimits(context),
      spirv::ClientAPI::Vulkan, spirv::Vendor::Unknown,
      spirv::DeviceType::Unknown, spirv::TargetEnvAttr::kUnknownDeviceID);
}

class D3D12SPIRVTargetBackend : public TargetBackend {
 public:
  D3D12SPIRVTargetBackend() = default;

  // NOTE: we could vary this based on the options such as 'd3d12-v2'.
  std::string name() const override { return "d3d12"; }

  void getDependentDialects(DialectRegistry &registry) const override {
    registry.insert<IREE::Codegen::IREECodegenDialect, spirv::SPIRVDialect,
                    gpu::GPUDialect>();
  }

  IREE::HAL::DeviceTargetAttr getDefaultDeviceTarget(
      MLIRContext *context) const override {
    Builder b(context);
    SmallVector<NamedAttribute> configItems;

    // Indicates that the runtime HAL driver operates only in the legacy
    // synchronous mode.
    configItems.emplace_back(b.getStringAttr("legacy_sync"), b.getUnitAttr());

    configItems.emplace_back(b.getStringAttr("executable_targets"),
                             getExecutableTargets(context));

    auto configAttr = b.getDictionaryAttr(configItems);
    return IREE::HAL::DeviceTargetAttr::get(
        context, b.getStringAttr(deviceID()), configAttr);
  }

  void buildTranslationPassPipeline(IREE::HAL::ExecutableVariantOp variantOp,
                                    OpPassManager &passManager) override {
    // For now we disable translation if the variant has external object files.
    // We could instead perform linking with those objects (if they're Metal
    // archives, etc).
    if (variantOp.isExternal()) return;

    buildSPIRVCodegenPassPipeline(passManager, /*enableFastMath=*/false);
  }


  LogicalResult serializeExecutable(const SerializationOptions &options,
                                    IREE::HAL::ExecutableVariantOp variantOp,
                                    OpBuilder &executableBuilder) override {
    ModuleOp innerModuleOp = variantOp.getInnerModule();
    auto spvModuleOp = *innerModuleOp.getOps<spirv::ModuleOp>().begin();

    // The runtime use ordinals instead of names but Metal requires function
    // names for constructing pipeline states. Get an ordered list of the entry
    // point names.
    SmallVector<StringRef, 8> entryPointNames;
    spvModuleOp.walk([&](spirv::EntryPointOp exportOp) {
      entryPointNames.push_back(exportOp.getFn());
    });

    // 1. Serialize the spirv::ModuleOp into binary format.
    SmallVector<uint32_t, 0> spvBinary;
    if (failed(spirv::serialize(spvModuleOp, spvBinary))) {
      return variantOp.emitError() << "failed to serialize spirv.module";
    }
    if (!options.dumpIntermediatesPath.empty()) {
      dumpDataToPath<uint32_t>(options.dumpIntermediatesPath,
                               options.dumpBaseName, variantOp.getName(),
                               ".spv", spvBinary);
    }

    // 2. Cross compile SPIR-V to HLSL source code.
    llvm::SmallVector<D3D12Shader, 2> hlslShaders;
    for (const auto &entryPoint : entryPointNames) {
      llvm::Optional<D3D12Shader> hlslShader = crossCompileSPIRVToHLSL(
          // We can use ArrayRef here given spvBinary reserves 0 bytes on stack.
          llvm::makeArrayRef(spvBinary.data(), spvBinary.size()), entryPoint);
      if (!hlslShader) {
        return variantOp.emitError()
               << "failed to cross compile SPIR-V to D3D12 shader";
      }
      hlslShaders.push_back(std::move(*hlslShader));
    }

    // 3. Compile MSL to MTLLibrary.
    // TODO(antiagainst): provide the option to compile the shaders into a
    // library and embed in the FlatBuffer. Metal provides APIs for compiling
    // shader sources into a MTLLibrary at run-time, but does not provie
    // a way to serialize the generated MTLLibrary. The only way available is
    // to use command-line tools like `metal` and `metallib`. Likely we need
    // to invoke them in C++.

    if (!options.dumpBinariesPath.empty()) {
      for (auto shader : llvm::enumerate(hlslShaders)) {
        dumpDataToPath(
            options.dumpBinariesPath, options.dumpBaseName,
            (variantOp.getName() + std::to_string(shader.index())).str(),
            ".hlsl", shader.value().source);
      }
    }

    // 4. Pack the MTLLibrary and metadata into a FlatBuffer.
    FlatbufferBuilder builder;
    iree_D3D12ExecutableDef_start_as_root(builder);

    auto shaderSourcesRef = builder.createStringVec(llvm::map_range(
        hlslShaders, [&](const D3D12Shader &shader) { return shader.source; }));

    iree_D3D12ThreadgroupSize_vec_start(builder);
    for (auto &shader : hlslShaders) {
      iree_D3D12ThreadgroupSize_vec_push_create(
          builder, shader.threadgroupSize.x, shader.threadgroupSize.y,
          shader.threadgroupSize.z);
    }
    auto threadgroupSizesRef = iree_D3D12ThreadgroupSize_vec_end(builder);

    auto entryPointNamesRef = builder.createStringVec(entryPointNames);

    iree_D3D12ExecutableDef_entry_points_add(builder, entryPointNamesRef);
    iree_D3D12ExecutableDef_threadgroup_sizes_add(builder, threadgroupSizesRef);
    iree_D3D12ExecutableDef_shader_sources_add(builder, shaderSourcesRef);
    iree_D3D12ExecutableDef_end_as_root(builder);

    // 5. Add the binary data to the target executable.
    auto binaryOp = executableBuilder.create<IREE::HAL::ExecutableBinaryOp>(
        variantOp.getLoc(), variantOp.getSymName(),
        variantOp.getTarget().getFormat(),
        builder.getBufferAttr(executableBuilder.getContext()));
    binaryOp.setMimeTypeAttr(
        executableBuilder.getStringAttr("application/x-flatbuffers"));

    return success();
  }

 private:
  ArrayAttr getExecutableTargets(MLIRContext *context) const {
    SmallVector<Attribute> targetAttrs;
    // If we had multiple target environments we would generate one target attr
    // per environment, with each setting its own environment attribute.
    targetAttrs.push_back(
        getExecutableTarget(context, getD3D12TargetEnv(context)));
    return ArrayAttr::get(context, targetAttrs);
  }

  IREE::HAL::ExecutableTargetAttr getExecutableTarget(
      MLIRContext *context, spirv::TargetEnvAttr targetEnv) const {
    Builder b(context);
    SmallVector<NamedAttribute> configItems;

    configItems.emplace_back(b.getStringAttr(spirv::getTargetEnvAttrName()),
                             targetEnv);

    auto configAttr = b.getDictionaryAttr(configItems);
    return IREE::HAL::ExecutableTargetAttr::get(
        context, b.getStringAttr("d3d12"), b.getStringAttr("d3d12-hlsl-fb"),
        configAttr);
  }
};

void registerD3D12SPIRVTargetBackends() {
  auto backendFactory = [=]() {
    return std::make_shared<D3D12SPIRVTargetBackend>();
  };
  // #hal.device.target<"d3d12", ...
  static TargetBackendRegistration registration0("d3d12", backendFactory);
  // #hal.executable.target<"d3d12-spirv", ...
  static TargetBackendRegistration registration1("d3d12-spirv", backendFactory);
}

}  // namespace HAL
}  // namespace IREE
}  // namespace iree_compiler
}  // namespace mlir
