// Copyright 2022 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "iree/base/api.h"
#include "iree/hal/api.h"

namespace {
extern const iree_hal_command_buffer_vtable_t
    iree_hal_d3d12_command_buffer_vtable;
}  // namespace

void iree_hal_d3d12_command_buffer_destroy(
    iree_hal_command_buffer_t* command_buffer) {}

void* iree_hal_d3d12_command_buffer_dyn_cast(
    iree_hal_command_buffer_t* command_buffer, const void* vtable) {
  assert(false);
  return nullptr;
}

iree_status_t iree_hal_d3d12_command_buffer_begin(
    iree_hal_command_buffer_t* command_buffer) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_end(
    iree_hal_command_buffer_t* command_buffer) {
  assert(false);
  return iree_ok_status();
}

void iree_hal_d3d12_command_buffer_begin_debug_group(
    iree_hal_command_buffer_t* command_buffer, iree_string_view_t label,
    iree_hal_label_color_t label_color,
    const iree_hal_label_location_t* location) {
  assert(false);
}

void iree_hal_d3d12_command_buffer_end_debug_group(
    iree_hal_command_buffer_t* command_buffer) {
  assert(false);
}

iree_status_t iree_hal_d3d12_command_buffer_execution_barrier(
    iree_hal_command_buffer_t* command_buffer,
    iree_hal_execution_stage_t source_stage_mask,
    iree_hal_execution_stage_t target_stage_mask,
    iree_hal_execution_barrier_flags_t flags,
    iree_host_size_t memory_barrier_count,
    const iree_hal_memory_barrier_t* memory_barriers,
    iree_host_size_t buffer_barrier_count,
    const iree_hal_buffer_barrier_t* buffer_barriers) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_signal_event(
    iree_hal_command_buffer_t* command_buffer, iree_hal_event_t* event,
    iree_hal_execution_stage_t source_stage_mask) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_reset_event(
    iree_hal_command_buffer_t* command_buffer, iree_hal_event_t* event,
    iree_hal_execution_stage_t source_stage_mask) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_wait_events(
    iree_hal_command_buffer_t* command_buffer, iree_host_size_t event_count,
    const iree_hal_event_t** events,
    iree_hal_execution_stage_t source_stage_mask,
    iree_hal_execution_stage_t target_stage_mask,
    iree_host_size_t memory_barrier_count,
    const iree_hal_memory_barrier_t* memory_barriers,
    iree_host_size_t buffer_barrier_count,
    const iree_hal_buffer_barrier_t* buffer_barriers) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_discard_buffer(
    iree_hal_command_buffer_t* command_buffer, iree_hal_buffer_t* buffer) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_fill_buffer(
    iree_hal_command_buffer_t* command_buffer, iree_hal_buffer_t* target_buffer,
    iree_device_size_t target_offset, iree_device_size_t length,
    const void* pattern, iree_host_size_t pattern_length) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_update_buffer(
    iree_hal_command_buffer_t* command_buffer, const void* source_buffer,
    iree_host_size_t source_offset, iree_hal_buffer_t* target_buffer,
    iree_device_size_t target_offset, iree_device_size_t length) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_copy_buffer(
    iree_hal_command_buffer_t* command_buffer, iree_hal_buffer_t* source_buffer,
    iree_device_size_t source_offset, iree_hal_buffer_t* target_buffer,
    iree_device_size_t target_offset, iree_device_size_t length) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_collective(
    iree_hal_command_buffer_t* command_buffer, iree_hal_channel_t* channel,
    iree_hal_collective_op_t op, uint32_t param,
    iree_hal_buffer_binding_t send_binding,
    iree_hal_buffer_binding_t recv_binding, iree_device_size_t element_count) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_push_constants(
    iree_hal_command_buffer_t* command_buffer,
    iree_hal_pipeline_layout_t* pipeline_layout, iree_host_size_t offset,
    const void* values, iree_host_size_t values_length) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_push_descriptor_set(
    iree_hal_command_buffer_t* command_buffer,
    iree_hal_pipeline_layout_t* pipeline_layout, uint32_t set,
    iree_host_size_t binding_count,
    const iree_hal_descriptor_set_binding_t* bindings) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_dispatch(
    iree_hal_command_buffer_t* command_buffer,
    iree_hal_executable_t* executable, int32_t entry_point,
    uint32_t workgroup_x, uint32_t workgroup_y, uint32_t workgroup_z) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_dispatch_indirect(
    iree_hal_command_buffer_t* command_buffer,
    iree_hal_executable_t* executable, int32_t entry_point,
    iree_hal_buffer_t* workgroups_buffer,
    iree_device_size_t workgroups_offset) {
  assert(false);
  return iree_ok_status();
}

iree_status_t iree_hal_d3d12_command_buffer_execute_commands(
    iree_hal_command_buffer_t* command_buffer,
    iree_hal_command_buffer_t* commands,
    iree_hal_buffer_binding_table_t binding_table) {
  assert(false);
  return iree_ok_status();
}

namespace {
const iree_hal_command_buffer_vtable_t iree_hal_d3d12_command_buffer_vtable = {
    /*.destroy =*/iree_hal_d3d12_command_buffer_destroy,
    /*.dyn_cast =*/iree_hal_d3d12_command_buffer_dyn_cast,
    /*.begin =*/iree_hal_d3d12_command_buffer_begin,
    /*.end =*/iree_hal_d3d12_command_buffer_end,
    /*.begin_debug_group =*/
    iree_hal_d3d12_command_buffer_begin_debug_group,
    /*.end_debug_group =*/iree_hal_d3d12_command_buffer_end_debug_group,
    /*.execution_barrier =*/
    iree_hal_d3d12_command_buffer_execution_barrier,
    /*.signal_event =*/iree_hal_d3d12_command_buffer_signal_event,
    /*.reset_event =*/iree_hal_d3d12_command_buffer_reset_event,
    /*.wait_events =*/iree_hal_d3d12_command_buffer_wait_events,
    /*.discard_buffer =*/iree_hal_d3d12_command_buffer_discard_buffer,
    /*.fill_buffer =*/iree_hal_d3d12_command_buffer_fill_buffer,
    /*.update_buffer =*/iree_hal_d3d12_command_buffer_update_buffer,
    /*.copy_buffer =*/iree_hal_d3d12_command_buffer_copy_buffer,
    /*.collective=*/iree_hal_d3d12_command_buffer_collective,
    /*.push_constants =*/iree_hal_d3d12_command_buffer_push_constants,
    /*.push_descriptor_set =*/
    iree_hal_d3d12_command_buffer_push_descriptor_set,
    /*.dispatch =*/iree_hal_d3d12_command_buffer_dispatch,
    /*.dispatch_indirect =*/
    iree_hal_d3d12_command_buffer_dispatch_indirect,
    /*.execute_commands =*/
    iree_hal_d3d12_command_buffer_execute_commands,
};
}  // namespace
