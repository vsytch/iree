// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef IREE_EXPERIMENTAL_D3D12_DRIVER_H_
#define IREE_EXPERIMENTAL_D3D12_DRIVER_H_

#include "experimental/d3d12/util/status.h"
#include "iree/base/api.h"
#include "iree/hal/api.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#if !defined(NDEBUG)
#include <dxgidebug.h>
#endif
#include <winrt/base.h>

#include <vector>

#ifdef __cplusplus
extern iree_hal_driver_vtable_t iree_hal_d3d12_driver_vtable;

struct iree_hal_d3d12_driver_t {
  iree_hal_resource_t resource;
  iree_allocator_t host_allocator;
  iree_string_view_t name;

  std::vector<winrt::com_ptr<IDXGIAdapter4>> adapters;
};

inline iree_hal_d3d12_driver_t* iree_hal_d3d12_driver_cast(
    iree_hal_driver_t* base_value) {
  IREE_HAL_ASSERT_TYPE(base_value, &iree_hal_d3d12_driver_vtable);
  return (iree_hal_d3d12_driver_t*)base_value;
}

extern "C" {
#endif  // __cplusplus

iree_status_t iree_hal_d3d12_driver_initialize(
    iree_string_view_t driver_name,
    iree_allocator_t host_allocator,
    iree_hal_driver_t** driver);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // IREE_EXPERIMENTAL_D3D12_DRIVER_H_
