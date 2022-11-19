// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "experimental/d3d12/util/status.h"

IREE_API_EXPORT iree_status_t iree_hal_d3d12_result_to_status(
    HRESULT result,
    const char* file,
    uint32_t line) {
  if (IREE_LIKELY(SUCCEEDED(result))) {
    return iree_ok_status();
  }

  // We got a failure, extract the error message.
  winrt::hresult_error error{result};
  // Painfully convert UTF-16 to ASCII.
  std::wstring_view wmessage = error.message();
  std::string message(wmessage.cbegin(), wmessage.cend());
  return iree_make_status_with_location(file, line, IREE_STATUS_UNKNOWN, message.c_str());
}

