// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef IREE_HAL_DRIVERS_D3D12_UTIL_STATUS_H_
#define IREE_HAL_DRIVERS_D3D12_UTIL_STATUS_H_

#include "iree/base/api.h"

#include <winrt/base.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#define D3D12_RESULT_TO_STATUS(expr, ...) \
  iree_hal_d3d12_result_to_status((expr), __FILE__, __LINE__)

#define D3D12_RETURN_IF_ERROR(expr, ...) \
  IREE_RETURN_IF_ERROR(               \
      iree_hal_d3d12_result_to_status((expr), __FILE__, __LINE__))

#define D3D12_CHECK_OK(expr) \
  IREE_CHECK_OK(iree_hal_d3d12_result_to_status((expr), __FILE__, __LINE__))

iree_status_t iree_hal_d3d12_result_to_status(
    HRESULT result,
    const char* file,
    uint32_t line);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // IREE_HAL_DRIVERS_D3D12_UTIL_STATUS_H_