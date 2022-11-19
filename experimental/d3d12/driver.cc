// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "experimental/d3d12/device.h"
#include "experimental/d3d12/driver.h"


IREE_API_EXPORT iree_status_t iree_hal_d3d12_driver_initialize(
    iree_string_view_t driver_name,
    iree_allocator_t host_allocator,
    iree_hal_driver_t** out_driver) {
  iree_hal_d3d12_driver_t* driver = nullptr;
  iree_host_size_t total_size = sizeof(*driver) + driver_name.size;
  IREE_RETURN_IF_ERROR(iree_allocator_malloc(host_allocator, total_size, (void**)&driver));
  iree_hal_resource_initialize(&iree_hal_d3d12_driver_vtable,
                               &driver->resource);
  driver->host_allocator = host_allocator;
  iree_string_view_append_to_buffer(
      driver_name, &driver->name,
      (char*)driver + total_size - driver_name.size);

  uint32_t flags = 0;
#if !defined(NDEBUG)
  {
    winrt::com_ptr<ID3D12Debug6> debug_controller;
    D3D12_RETURN_IF_ERROR(D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller)));

    winrt::com_ptr<IDXGIInfoQueue> info_queue;
    D3D12_RETURN_IF_ERROR(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&info_queue)));

    D3D12_RETURN_IF_ERROR(info_queue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true));
    D3D12_RETURN_IF_ERROR(info_queue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true));

    flags = DXGI_CREATE_FACTORY_DEBUG;
  }
#endif
  winrt::com_ptr<IDXGIFactory6> factory;
  D3D12_RETURN_IF_ERROR(CreateDXGIFactory2(flags, IID_PPV_ARGS(&factory)));

  winrt::com_ptr<IDXGIAdapter4> adapter;
  // Find all the devices that supports D3D12.
  for (
      uint32_t idx = 0;
      SUCCEEDED(factory->EnumAdapterByGpuPreference(
          idx, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter)));
      idx++) {
    DXGI_ADAPTER_DESC3 desc;
    D3D12_RETURN_IF_ERROR(adapter->GetDesc3(&desc));

    // Skip the Basic Render Driver adapter.
    if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
      continue;
    }

    // Check if the adapter supports D3D12, but don't initialize it.
    if (SUCCEEDED(D3D12CreateDevice(adapter.get(), D3D_FEATURE_LEVEL_12_0, _uuidof(ID3D12Device), nullptr))) {
      driver->adapters.push_back(std::move(adapter));
    }
  }

  if (driver->adapters.size() == 0) {
    return iree_make_status(IREE_STATUS_UNKNOWN);
  }

  *out_driver = (iree_hal_driver_t*)driver;
  return iree_ok_status();
}

void iree_hal_d3d12_driver_destroy(iree_hal_driver_t* driver) {
  assert(false);
}

iree_status_t iree_hal_d3d12_driver_query_available_devices(
    iree_hal_driver_t* driver,
    iree_allocator_t host_allocator,
    iree_host_size_t* out_device_info_count,
    iree_hal_device_info_t** out_device_infos) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_driver_dump_device_info(
    iree_hal_driver_t* driver,
    iree_hal_device_id_t device_id,
    iree_string_builder_t* builder) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_driver_create_device_by_id(
    iree_hal_driver_t* base_driver,
    iree_hal_device_id_t device_id,
    iree_host_size_t param_count,
    const iree_string_pair_t* params,
    iree_allocator_t host_allocator,
    iree_hal_device_t** out_device) {
  IREE_RETURN_IF_ERROR(iree_hal_d3d12_device_initialize(base_driver, device_id, host_allocator, out_device));
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_driver_create_device_by_path(
    iree_hal_driver_t* driver,
    iree_string_view_t driver_name,
    iree_string_view_t device_path,
    iree_host_size_t param_count,
    const iree_string_pair_t* params,
    iree_allocator_t host_allocator,
    iree_hal_device_t** out_device) {
  assert(false);
  return iree_ok_status();
}

iree_hal_driver_vtable_t iree_hal_d3d12_driver_vtable = {
    /*.destroy =*/ iree_hal_d3d12_driver_destroy,
    /*.query_available_devices =*/ iree_hal_d3d12_driver_query_available_devices,
    /*.dump_device_info =*/ iree_hal_d3d12_driver_dump_device_info,
    /*.create_device_by_id =*/ iree_hal_d3d12_driver_create_device_by_id,
    /*.create_device_by_path =*/ iree_hal_d3d12_driver_create_device_by_path,
};
