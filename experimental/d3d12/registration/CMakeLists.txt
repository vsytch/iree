# Copyright 2022 The IREE Authors
#
# Licensed under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

iree_add_all_subdirs()

iree_cc_library(
  NAME
    registration
  HDRS
    "driver_module.h"
  SRCS
    "driver_module.cc"
  DEPS
    iree::base
    iree::base::core_headers
    iree::base::tracing
    iree::experimental::d3d12
    iree::hal
  DEFINES
    "IREE_HAVE_HAL_EXPERIMENTAL_D3D12_DRIVER_MODULE=1"
  PUBLIC
)
