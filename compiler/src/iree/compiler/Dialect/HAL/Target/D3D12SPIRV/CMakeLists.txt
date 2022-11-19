if(NOT IREE_TARGET_BACKEND_D3D12_SPIRV)
  return()
endif()

iree_add_all_subdirs()

iree_cc_library(
  NAME
    D3D12SPIRV
  HDRS
    "D3D12SPIRVTarget.h"
  SRCS
    "D3D12SPIRVTarget.cpp"
  DEPS
    ::SPIRVToHLSL
    MLIRAffineDialect
    MLIRGPUOps
    MLIRLinalgDialect
    MLIRSPIRVDialect
    MLIRSPIRVSerialization
    MLIRVectorDialect
    iree::compiler::Codegen::Common
    iree::compiler::Codegen::Dialect::IREECodegenDialect
    iree::compiler::Codegen::PassHeaders
    iree::compiler::Codegen::SPIRV
    iree::compiler::Codegen::Utils
    iree::compiler::Dialect::HAL::Target
    iree::compiler::Utils
    iree::schemas::d3d12_executable_def_c_fbs
  PUBLIC
)

iree_cc_library(
  NAME
    SPIRVToHLSL
  HDRS
    "SPIRVToHLSL.h"
  SRCS
    "SPIRVToHLSL.cpp"
  DEPS
    LLVMSupport
    MLIRSupport
    spirv-cross-hlsl
  PUBLIC
)

