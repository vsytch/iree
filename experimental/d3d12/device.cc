// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "experimental/d3d12/device.h"

#include "experimental/d3d12/driver.h"
#include "experimental/d3d12/executable_cache.h"

IREE_API_EXPORT iree_status_t iree_hal_d3d12_device_initialize(
    iree_hal_driver_t* base_driver, iree_hal_device_id_t device_id,
    iree_allocator_t host_allocator, iree_hal_device_t** out_device) {
  iree_hal_d3d12_driver_t* driver = iree_hal_d3d12_driver_cast(base_driver);
  if (device_id >= driver->adapters.size()) {
    return iree_make_status(IREE_STATUS_UNKNOWN);
  }

  iree_hal_d3d12_device_t* device = nullptr;
  iree_host_size_t total_size = sizeof(*device) + sizeof("d3d12");
  IREE_RETURN_IF_ERROR(
      iree_allocator_malloc(host_allocator, total_size, (void**)&device));
  memset(device, 0, total_size);
  iree_hal_resource_initialize(&iree_hal_d3d12_device_vtable,
                               &device->resource);
  device->driver = base_driver;
  iree_hal_driver_retain(device->driver);
  device->host_allocator = host_allocator;
  device->name = iree_make_cstring_view("d3d12");

  D3D12_RETURN_IF_ERROR(D3D12CreateDevice(driver->adapters[device_id].get(),
                                          D3D_FEATURE_LEVEL_12_0,
                                          IID_PPV_ARGS(&device->device)));

  *out_device = (iree_hal_device_t*)device;
  return iree_ok_status();
}

void iree_hal_d3d12_device_destroy(iree_hal_device_t* device) { assert(false); }

iree_string_view_t iree_hal_d3d12_device_id(iree_hal_device_t* device) {
  assert(false);
  return iree_string_view_t{};
}

iree_allocator_t iree_hal_d3d12_device_host_allocator(
    iree_hal_device_t* device) {
  assert(false);
  return iree_allocator_t{};
}

iree_hal_allocator_t* iree_hal_d3d12_device_allocator(
    iree_hal_device_t* device) {
  assert(false);
  return nullptr;
}

iree_status_t iree_hal_d3d12_device_trim(iree_hal_device_t* device) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_device_create_channel(
    iree_hal_device_t* device, iree_hal_queue_affinity_t queue_affinity,
    iree_hal_channel_params_t params, iree_hal_channel_t** out_channel) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_device_query_i64(iree_hal_device_t* device,
                                              iree_string_view_t category,
                                              iree_string_view_t key,
                                              int64_t* out_value) {
  *out_value = 0;

  if (iree_string_view_equal(category,
                             iree_make_cstring_view("hal.executable.format"))) {
    *out_value =
        iree_string_view_equal(key, iree_make_cstring_view("d3d12-hlsl-fb"))
            ? 1
            : 0;
    return iree_ok_status();
  }

  return iree_make_status(
      IREE_STATUS_NOT_FOUND,
      "unknown device configuration key value '%.*s :: %.*s'",
      (int)category.size, category.data, (int)key.size, key.data);
}

iree_status_t iree_hal_d3d12_device_create_command_buffer(
    iree_hal_device_t* device, iree_hal_command_buffer_mode_t mode,
    iree_hal_command_category_t command_categories,
    iree_hal_queue_affinity_t queue_affinity, iree_host_size_t binding_capacity,
    iree_hal_command_buffer_t** out_command_buffer) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_device_create_descriptor_set_layout(
    iree_hal_device_t* device, iree_hal_descriptor_set_layout_flags_t flags,
    iree_host_size_t binding_count,
    const iree_hal_descriptor_set_layout_binding_t* bindings,
    iree_hal_descriptor_set_layout_t** out_descriptor_set_layout) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_device_create_event(iree_hal_device_t* device,
                                                 iree_hal_event_t** out_event) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_device_create_executable_cache(
    iree_hal_device_t* base_device, iree_string_view_t identifier,
    iree_loop_t loop, iree_hal_executable_cache_t** out_executable_cache) {
  iree_hal_d3d12_device_t* device = iree_hal_d3d12_device_cast(base_device);
  return iree_hal_d3d12_executable_cache_initialize(device->host_allocator,
                                                    out_executable_cache);
}

iree_status_t iree_hal_d3d12_device_create_pipeline_layout(
    iree_hal_device_t* device, iree_host_size_t push_constants,
    iree_host_size_t set_layout_count,
    iree_hal_descriptor_set_layout_t* const* set_layouts,
    iree_hal_pipeline_layout_t** out_pipeline_layout) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_device_create_semaphore(
    iree_hal_device_t* device, uint64_t initial_value,
    iree_hal_semaphore_t** out_semaphore) {
  assert(false);
  return iree_ok_status();
}

iree_hal_semaphore_compatibility_t
iree_hal_d3d12_device_query_semaphore_compatibility(
    iree_hal_device_t* device, iree_hal_semaphore_t* semaphore) {
  assert(false);
  return iree_hal_semaphore_compatibility_t{};
}

iree_status_t iree_hal_d3d12_device_transfer_range(
    iree_hal_device_t* device, iree_hal_transfer_buffer_t source,
    iree_device_size_t source_offset, iree_hal_transfer_buffer_t target,
    iree_device_size_t target_offset, iree_device_size_t data_length,
    iree_hal_transfer_buffer_flags_t flags, iree_timeout_t timeout) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_device_queue_alloca(
    iree_hal_device_t* device, iree_hal_queue_affinity_t queue_affinity,
    const iree_hal_semaphore_list_t wait_semaphore_list,
    const iree_hal_semaphore_list_t signal_semaphore_list,
    iree_hal_allocator_pool_t pool, iree_hal_buffer_params_t params,
    iree_device_size_t allocation_size,
    iree_hal_buffer_t** IREE_RESTRICT out_buffer) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_device_queue_dealloca(
    iree_hal_device_t* device, iree_hal_queue_affinity_t queue_affinity,
    const iree_hal_semaphore_list_t wait_semaphore_list,
    const iree_hal_semaphore_list_t signal_semaphore_list,
    iree_hal_buffer_t* buffer) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_device_queue_execute(
    iree_hal_device_t* device, iree_hal_queue_affinity_t queue_affinity,
    const iree_hal_semaphore_list_t wait_semaphore_list,
    const iree_hal_semaphore_list_t signal_semaphore_list,
    iree_host_size_t command_buffer_count,
    iree_hal_command_buffer_t* const* command_buffers) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_device_queue_flush(
    iree_hal_device_t* device, iree_hal_queue_affinity_t queue_affinity) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_device_wait_semaphores(
    iree_hal_device_t* device, iree_hal_wait_mode_t wait_mode,
    const iree_hal_semaphore_list_t semaphore_list, iree_timeout_t timeout) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_device_profiling_begin(
    iree_hal_device_t* device,
    const iree_hal_device_profiling_options_t* options) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_device_profiling_end(iree_hal_device_t* device) {
  assert(false);
  return iree_ok_status();
}

iree_hal_device_vtable_t iree_hal_d3d12_device_vtable = {
    /*.destroy =*/iree_hal_d3d12_device_destroy,
    /*.id =*/iree_hal_d3d12_device_id,
    /*.host_allocator =*/iree_hal_d3d12_device_host_allocator,
    /*.device_allocator =*/iree_hal_d3d12_device_allocator,
    /*.trim =*/iree_hal_d3d12_device_trim,
    /*.query_i64 =*/iree_hal_d3d12_device_query_i64,
    /*.create_channel=*/iree_hal_d3d12_device_create_channel,
    /*.create_command_buffer =*/iree_hal_d3d12_device_create_command_buffer,
    /*.create_descriptor_set_layout =*/
    iree_hal_d3d12_device_create_descriptor_set_layout,
    /*.create_event =*/iree_hal_d3d12_device_create_event,
    /*.create_executable_cache =*/iree_hal_d3d12_device_create_executable_cache,
    /*.create_pipeline_layout =*/iree_hal_d3d12_device_create_pipeline_layout,
    /*.create_semaphore =*/iree_hal_d3d12_device_create_semaphore,
    /*.query_semaphore_compatibility =*/
    iree_hal_d3d12_device_query_semaphore_compatibility,
    /*.transfer_range =*/iree_hal_d3d12_device_transfer_range,
    /*.queue_alloca =*/iree_hal_d3d12_device_queue_alloca,
    /*.queue_dealloca =*/iree_hal_d3d12_device_queue_dealloca,
    /*.queue_execute =*/iree_hal_d3d12_device_queue_execute,
    /*.queue_flush =*/iree_hal_d3d12_device_queue_flush,
    /*.wait_semaphores =*/iree_hal_d3d12_device_wait_semaphores,
    /*.profiling_begin =*/iree_hal_d3d12_device_profiling_begin,
    /*.profiling_end =*/iree_hal_d3d12_device_profiling_end,
};
