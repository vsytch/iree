iree_add_all_subdirs()

iree_cc_library(
  NAME
    status
  HDRS
    "status.h"
  SRCS
    "status.cc"
  DEPS
    iree::base
    iree::base::core_headers
  PUBLIC
)
