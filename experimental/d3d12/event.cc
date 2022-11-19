// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "iree/base/api.h"
#include "iree/hal/api.h"

namespace {
extern const iree_hal_event_vtable_t iree_hal_d3d12_event_vtable;
}  // namespace

void iree_hal_d3d12_event_destroy(iree_hal_event_t* event) {
  assert(false);
}

namespace {
const iree_hal_event_vtable_t iree_hal_d3d12_event_vtable = {
    /*.destroy =*/ iree_hal_d3d12_event_destroy,
};
}  // namespace
