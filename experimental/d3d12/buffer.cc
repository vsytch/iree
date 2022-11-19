// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "iree/base/api.h"
#include "iree/hal/api.h"

namespace {
extern const iree_hal_buffer_vtable_t iree_hal_d3d12_buffer_vtable;
}  // namespace

void iree_hal_d3d12_buffer_recycle(iree_hal_buffer_t* buffer) {
}

void iree_hal_d3d12_buffer_destroy(iree_hal_buffer_t* buffer) {
}

iree_status_t iree_hal_d3d12_buffer_map_range(
    iree_hal_buffer_t* buffer,
    iree_hal_mapping_mode_t mapping_mode,
    iree_hal_memory_access_t memory_access,
    iree_device_size_t local_byte_offset,
    iree_device_size_t local_byte_length,
    iree_hal_buffer_mapping_t* mapping) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_buffer_unmap_range(
    iree_hal_buffer_t* buffer,
    iree_device_size_t local_byte_offset,
    iree_device_size_t local_byte_length,
    iree_hal_buffer_mapping_t* mapping) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_buffer_invalidate_range(
    iree_hal_buffer_t* buffer,
    iree_device_size_t local_byte_offset,
    iree_device_size_t local_byte_length) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_buffer_flush_range(
    iree_hal_buffer_t* buffer,
    iree_device_size_t local_byte_offset,
    iree_device_size_t local_byte_length) {
  assert(false);
  return iree_ok_status();
}

namespace {
const iree_hal_buffer_vtable_t iree_hal_d3d12_buffer_vtable = {
    /*.recycle =*/ iree_hal_d3d12_buffer_recycle,
    /*.destroy =*/ iree_hal_d3d12_buffer_destroy,
    /*.map_range =*/ iree_hal_d3d12_buffer_map_range,
    /*.unmap_range =*/ iree_hal_d3d12_buffer_unmap_range,
    /*.invalidate_range =*/ iree_hal_d3d12_buffer_invalidate_range,
    /*.flush_range =*/ iree_hal_d3d12_buffer_flush_range,
};
}  // namespace
