// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "iree/base/api.h"
#include "iree/hal/api.h"

namespace {
extern const iree_hal_semaphore_vtable_t iree_hal_d3d12_semaphore_vtable;
}  // namespace

void iree_hal_d3d12_semaphore_destroy(iree_hal_semaphore_t* semaphore) {
}

iree_status_t iree_hal_d3d12_semaphore_query(
    iree_hal_semaphore_t* semaphore,
    uint64_t* out_value) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_semaphore_signal(
    iree_hal_semaphore_t* semaphore,
    uint64_t new_value) {
  assert(false);
  return iree_ok_status();
}

void iree_hal_d3d12_semaphore_fail(
    iree_hal_semaphore_t* semaphore,
    iree_status_t status) {
  assert(false);
}

iree_status_t iree_hal_d3d12_semaphore_wait(
    iree_hal_semaphore_t* semaphore,
    uint64_t value,
    iree_timeout_t timeout) {
  assert(false);
  return iree_ok_status();
}

namespace {
const iree_hal_semaphore_vtable_t iree_hal_d3d12_semaphore_vtable = {
    /*.destroy =*/ iree_hal_d3d12_semaphore_destroy,
    /*.query =*/ iree_hal_d3d12_semaphore_query,
    /*.signal =*/ iree_hal_d3d12_semaphore_signal,
    /*.fail =*/ iree_hal_d3d12_semaphore_fail,
    /*.wait =*/ iree_hal_d3d12_semaphore_wait,
};
}  // namespace
