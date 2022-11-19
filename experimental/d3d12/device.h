// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef IREE_EXPERIMENTAL_D3D12_DEVICE_H_
#define IREE_EXPERIMENTAL_D3D12_DEVICE_H_

#include "experimental/d3d12/util/status.h"
#include "iree/base/api.h"
#include "iree/hal/api.h"

#include <d3d12.h>
#include <winrt/base.h>

#ifdef __cplusplus
extern iree_hal_device_vtable_t iree_hal_d3d12_device_vtable;

struct iree_hal_d3d12_device_t {
  iree_hal_resource_t resource;
  iree_hal_driver_t* driver;
  iree_allocator_t host_allocator;
  iree_string_view_t name;

  winrt::com_ptr<ID3D12Device> device;
};

inline iree_hal_d3d12_device_t* iree_hal_d3d12_device_cast(
    iree_hal_device_t* base_value) {
  IREE_HAL_ASSERT_TYPE(base_value, &iree_hal_d3d12_device_vtable);
  return (iree_hal_d3d12_device_t*)base_value;
}

extern "C" {
#endif  // __cplusplus

iree_status_t iree_hal_d3d12_device_initialize(
    iree_hal_driver_t* driver,
    iree_hal_device_id_t device_id,
    iree_allocator_t host_allocator,
    iree_hal_device_t** out_device);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // IREE_EXPERIMENTAL_D3D12_DEVICE_H_
