// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef IREE_EXPERIMENTAL_D3D12_EXECUTABLE_CACHE_H_
#define IREE_EXPERIMENTAL_D3D12_EXECUTABLE_CACHE_H_

#include "iree/base/api.h"
#include "iree/hal/api.h"

#ifdef __cplusplus
extern iree_hal_executable_cache_vtable_t
    iree_hal_d3d12_executable_cache_vtable;

struct iree_hal_d3d12_executable_cache_t {
  iree_hal_resource_t resource;
  iree_allocator_t host_allocator;
};

inline iree_hal_d3d12_executable_cache_t* iree_hal_d3d12_executable_cache_cast(
    iree_hal_executable_cache_t* base_value) {
  IREE_HAL_ASSERT_TYPE(base_value, &iree_hal_d3d12_executable_cache_vtable);
  return (iree_hal_d3d12_executable_cache_t*)base_value;
}

extern "C" {
#endif  // __cplusplus

iree_status_t iree_hal_d3d12_executable_cache_initialize(
    iree_allocator_t host_allocator,
    iree_hal_executable_cache_t** out_executable_cache);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // IREE_EXPERIMENTAL_D3D12_EXECUTABLE_CACHE_H_
