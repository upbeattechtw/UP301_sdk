/*
 * Copyright (C) 2025 UpbeatTech Inc. All Rights Reserved
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * This file contains code derived from software originally developed by SiFive, Inc.
 * Copyright 2018 SiFive, Inc
 * SPDX-License-Identifier: Apache-2.0
 *
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX short identifier: Apache-2.0
 */
#include <string.h>

#include "metal.h"
#include "metal/interrupt.h"

metal_interrupt_Type *
metal_interrupt_get_controller(metal_intr_cntrl_Type cntrl, uint32_t id) {
    switch (cntrl) {
    case METAL_CPU_CONTROLLER:
        break;
    case METAL_CLINT_CONTROLLER:
#ifdef __METAL_DT_RISCV_CLINT0_HANDLE
        return __METAL_DT_RISCV_CLINT0_HANDLE;
#endif
        break;
    case METAL_CLIC_CONTROLLER:
#ifdef __METAL_DT_SIFIVE_CLIC0_HANDLE
        return __METAL_DT_SIFIVE_CLIC0_HANDLE;
#endif
        break;
    case METAL_PLIC_CONTROLLER:
#ifdef __METAL_DT_RISCV_PLIC0_HANDLE
        return __METAL_DT_RISCV_PLIC0_HANDLE;
#endif
        break;
    }
    return NULL;
}

extern __inline__ void metal_interrupt_init(metal_interrupt_Type *controller);

extern __inline__ int32_t
metal_interrupt_set_vector_mode(metal_interrupt_Type *controller,
                                metal_vector_mode_Type mode);
extern __inline__ metal_vector_mode_Type
metal_interrupt_get_vector_mode(metal_interrupt_Type *controller);

extern __inline__ int32_t
metal_interrupt_set_privilege(metal_interrupt_Type *controller,
                              metal_intr_priv_mode_Type mode);
extern __inline__ metal_intr_priv_mode_Type
metal_interrupt_get_privilege(metal_interrupt_Type *controller);

extern __inline__ uint32_t
metal_interrupt_set_threshold(metal_interrupt_Type *controller,
                              uint32_t level);
extern __inline__ uint32_t
metal_interrupt_get_threshold(metal_interrupt_Type *controller);

extern __inline__ uint32_t
metal_interrupt_get_priority(metal_interrupt_Type *controller, uint32_t id);

extern __inline__ int32_t
metal_interrupt_set_priority(metal_interrupt_Type *controller, uint32_t id,
                             uint32_t priority);

extern __inline__ int32_t
metal_interrupt_set_preemptive_level(metal_interrupt_Type *controller, uint32_t id,
                                     uint32_t level);

extern __inline__ uint32_t
metal_interrupt_get_preemptive_level(metal_interrupt_Type *controller,
                                     uint32_t id);

extern __inline__ int32_t metal_interrupt_clear(metal_interrupt_Type *controller,
                                            uint32_t id);

extern __inline__ int32_t metal_interrupt_set(metal_interrupt_Type *controller,
                                          uint32_t id);

extern __inline__ int32_t
metal_interrupt_register_handler(metal_interrupt_Type *controller, uint32_t id,
                                 metal_interrupt_handler_t handler, void *priv);

extern __inline__ int32_t metal_interrupt_register_vector_handler(
    metal_interrupt_Type *controller, uint32_t id,
    metal_interrupt_vector_handler_t handler, void *priv_data);

extern __inline__ int32_t metal_interrupt_enable(metal_interrupt_Type *controller,
                                             uint32_t id);

extern __inline__ int32_t
metal_interrupt_disable(metal_interrupt_Type *controller, uint32_t id);

extern __inline__ int32_t
metal_interrupt_vector_enable(metal_interrupt_Type *controller, uint32_t id);

extern __inline__ int32_t
metal_interrupt_vector_disable(metal_interrupt_Type *controller, uint32_t id);

extern __inline__ int32_t
_metal_interrupt_command_request(metal_interrupt_Type *controller, uint32_t cmd,
                                 void *data);

extern __inline__ metal_affinity_Type
metal_interrupt_affinity_enable(metal_interrupt_Type *controller,
                                metal_affinity_Type bitmask, uint32_t id);

extern __inline__ metal_affinity_Type
metal_interrupt_affinity_disable(metal_interrupt_Type *controller,
                                 metal_affinity_Type bitmask, uint32_t id);

extern __inline__ metal_affinity_Type
metal_interrupt_affinity_set_threshold(metal_interrupt_Type *controller,
                                       metal_affinity_Type bitmask,
                                       uint32_t level);
extern __inline__ uint32_t
metal_interrupt_affinity_get_threshold(metal_interrupt_Type *controller,
                                       uint32_t contextid);
