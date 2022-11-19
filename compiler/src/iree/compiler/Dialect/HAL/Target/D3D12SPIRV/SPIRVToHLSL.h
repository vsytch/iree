// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef IREE_COMPILER_DIALECT_HAL_TARGET_D3D12SPIRV_SPIRVTOHLSL_H_
#define IREE_COMPILER_DIALECT_HAL_TARGET_D3D12SPIRV_SPIRVTOHLSL_H_

#include <array>
#include <string>

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/StringRef.h"
#include "mlir/Support/LLVM.h"

namespace mlir {
namespace iree_compiler {

struct D3D12Shader {
  std::string source;
  struct ThreadGroupSize {
    uint32_t x;
    uint32_t y;
    uint32_t z;
  } threadgroupSize;
};

// Cross compiles SPIR-V into High Level Shading Language source code for the
// compute shader with |entryPoint|. Returns llvm::None on failure.
llvm::Optional<D3D12Shader> crossCompileSPIRVToHLSL(
    llvm::ArrayRef<uint32_t> spvBinary, StringRef entryPoint);

}  // namespace iree_compiler
}  // namespace mlir

#endif  // IREE_COMPILER_DIALECT_HAL_TARGET_D3D12SPIRV_SPIRVTOHLSL_H_
