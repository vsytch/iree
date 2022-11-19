// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "iree/base/api.h"
#include "iree/hal/api.h"

namespace {
extern const iree_hal_pipeline_layout_vtable_t
    iree_hal_d3d12_pipeline_layout_vtable;
}

void iree_hal_d3d12_pipeline_layout_destroy(
    iree_hal_pipeline_layout_t* pipeline_layout) {
  assert(false);
}

namespace {
const iree_hal_pipeline_layout_vtable_t
    iree_hal_d3d12_pipeline_layout_vtable = {
        /*.destroy =*/ iree_hal_d3d12_pipeline_layout_destroy,
};
}  // namespace
