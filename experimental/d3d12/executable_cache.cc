// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "experimental/d3d12/executable_cache.h"

#include "iree/base/api.h"
#include "iree/hal/api.h"

extern iree_hal_executable_cache_vtable_t
    iree_hal_d3d12_executable_cache_vtable;

iree_status_t iree_hal_d3d12_executable_cache_initialize(
    iree_allocator_t host_allocator,
    iree_hal_executable_cache_t** out_executable_cache) {
  iree_hal_d3d12_executable_cache_t* executable_cache = nullptr;
  IREE_RETURN_IF_ERROR(iree_allocator_malloc(
      host_allocator, sizeof(*executable_cache), (void**)&executable_cache));
  memset(executable_cache, 0, sizeof(*executable_cache));
  iree_hal_resource_initialize(&iree_hal_d3d12_executable_cache_vtable,
                               &executable_cache->resource);

  *out_executable_cache = (iree_hal_executable_cache_t*)executable_cache;
  return iree_ok_status();
}

void iree_hal_d3d12_nop_executable_cache_destroy(
    iree_hal_executable_cache_t* base_executable_cache) {
  iree_hal_d3d12_executable_cache_t* executable_cache =
      iree_hal_d3d12_executable_cache_cast(base_executable_cache);
  iree_allocator_t host_allocator = executable_cache->host_allocator;
  iree_allocator_free(host_allocator, executable_cache);
}

bool iree_hal_d3d12_nop_executable_cache_can_prepare_format(
    iree_hal_executable_cache_t* executable_cache,
    iree_hal_executable_caching_mode_t caching_mode,
    iree_string_view_t executable_format) {
  return iree_string_view_equal(executable_format,
                                iree_make_cstring_view("SPVE"));
}

iree_status_t iree_hal_d3d12_nop_executable_cache_prepare_executable(
    iree_hal_executable_cache_t* executable_cache,
    const iree_hal_executable_params_t* executable_params,
    iree_hal_executable_t** out_executable) {
  assert(false);
  return iree_ok_status();
}

iree_hal_executable_cache_vtable_t iree_hal_d3d12_executable_cache_vtable = {
    /*.destroy =*/iree_hal_d3d12_nop_executable_cache_destroy,
    /*.can_prepare_format =*/
    iree_hal_d3d12_nop_executable_cache_can_prepare_format,
    /*.prepare_executable =*/
    iree_hal_d3d12_nop_executable_cache_prepare_executable,
};
