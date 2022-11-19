// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "iree/base/api.h"
#include "iree/hal/api.h"

namespace {
extern const iree_hal_allocator_vtable_t iree_hal_d3d12_allocator_vtable;
}  // namespace

void iree_hal_d3d12_allocator_destroy(iree_hal_allocator_t* IREE_RESTRICT allocator) {
}

iree_allocator_t iree_hal_d3d12_allocator_host_allocator(
    const iree_hal_allocator_t* IREE_RESTRICT allocator) {
  assert(false);
  return iree_allocator_t{};
}

iree_status_t iree_hal_d3d12_allocator_trim(
    iree_hal_allocator_t* IREE_RESTRICT allocator) {
  assert(false);
  return iree_ok_status();
}

void iree_hal_d3d12_allocator_query_statistics(
    iree_hal_allocator_t* IREE_RESTRICT allocator,
    iree_hal_allocator_statistics_t* IREE_RESTRICT out_statistics) {
  assert(false);
}

iree_hal_buffer_compatibility_t iree_hal_d3d12_allocator_query_compatibility(
    iree_hal_allocator_t* IREE_RESTRICT allocator,
    const iree_hal_buffer_params_t* IREE_RESTRICT params,
    iree_device_size_t allocation_size) {
  assert(false);
  return iree_hal_buffer_compatibility_t{};
}

iree_status_t iree_hal_d3d12_allocator_allocate_buffer(
    iree_hal_allocator_t* IREE_RESTRICT allocator,
    const iree_hal_buffer_params_t* IREE_RESTRICT params,
    iree_device_size_t allocation_size, iree_const_byte_span_t initial_data,
    iree_hal_buffer_t** IREE_RESTRICT out_buffer) {
  assert(false);
  return iree_ok_status();
}

void iree_hal_d3d12_allocator_deallocate_buffer(
    iree_hal_allocator_t* IREE_RESTRICT allocator,
    iree_hal_buffer_t* IREE_RESTRICT buffer) {
  assert(false);
}

iree_status_t iree_hal_d3d12_allocator_import_buffer(
    iree_hal_allocator_t* IREE_RESTRICT allocator,
    const iree_hal_buffer_params_t* IREE_RESTRICT params,
    iree_hal_external_buffer_t* IREE_RESTRICT external_buffer,
    iree_hal_buffer_release_callback_t release_callback,
    iree_hal_buffer_t** IREE_RESTRICT out_buffer) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_allocator_export_buffer(
    iree_hal_allocator_t* IREE_RESTRICT allocator,
    iree_hal_buffer_t* IREE_RESTRICT buffer,
    iree_hal_external_buffer_type_t requested_type,
    iree_hal_external_buffer_flags_t requested_flags,
    iree_hal_external_buffer_t* IREE_RESTRICT out_external_buffer) {
  assert(false);
  return iree_ok_status();
}

namespace {
const iree_hal_allocator_vtable_t iree_hal_d3d12_allocator_vtable = {
    /*.destroy =*/ iree_hal_d3d12_allocator_destroy,
    /*.host_allocator =*/ iree_hal_d3d12_allocator_host_allocator,
    /*.trim =*/ iree_hal_d3d12_allocator_trim,
    /*.query_statistics =*/ iree_hal_d3d12_allocator_query_statistics,
    /*.query_compatibility =*/ iree_hal_d3d12_allocator_query_compatibility,
    /*.allocate_buffer =*/ iree_hal_d3d12_allocator_allocate_buffer,
    /*.deallocate_buffer =*/ iree_hal_d3d12_allocator_deallocate_buffer,
    /*.import_buffer =*/ iree_hal_d3d12_allocator_import_buffer,
    /*.export_buffer =*/ iree_hal_d3d12_allocator_export_buffer,
};
}  // namespace
