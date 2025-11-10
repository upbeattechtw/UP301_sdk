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
#include "metal.h"
#include "metal/cpu.h"

metal_cpu_Type *metal_cpu_get(uint32_t hartid) {
    if (hartid < __METAL_DT_MAX_HARTS) {
        return (metal_cpu_Type *)__metal_cpu_table[hartid];
    }
    return NULL;
}

uint32_t metal_cpu_get_current_hartid() {
#ifdef __riscv
    uint32_t mhartid;
    __asm__ volatile("csrr %0, mhartid" : "=r"(mhartid));
    return mhartid;
#endif
}

uint32_t metal_cpu_get_num_harts() { return __METAL_DT_MAX_HARTS; }

extern __inline__ uint64_t metal_cpu_get_timer(metal_cpu_Type *cpu);

extern __inline__ uint64_t metal_cpu_get_timebase(metal_cpu_Type *cpu);

extern __inline__ uint64_t metal_cpu_get_mtime(metal_cpu_Type *cpu) {
    return cpu->vtable->mtime_get(cpu);
}

extern __inline__ int32_t 
metal_cpu_set_mtimecmp(metal_cpu_Type *cpu, uint64_t time);

extern __inline__ metal_interrupt_Type *
metal_cpu_timer_interrupt_controller(metal_cpu_Type *cpu);

extern __inline__ uint32_t metal_cpu_timer_get_interrupt_id(metal_cpu_Type *cpu);

extern __inline__ metal_interrupt_Type *
metal_cpu_software_interrupt_controller(metal_cpu_Type *cpu);

extern __inline__ uint32_t
metal_cpu_software_get_interrupt_id(metal_cpu_Type *cpu);

extern __inline__ int32_t metal_cpu_software_set_ipi(metal_cpu_Type *cpu,
                                                 uint32_t hartid);

extern __inline__ int32_t metal_cpu_software_clear_ipi(metal_cpu_Type *cpu,
                                                   uint32_t hartid);

extern __inline__ uint32_t metal_cpu_get_msip(metal_cpu_Type *cpu, uint32_t hartid);

extern __inline__ metal_interrupt_Type *
metal_cpu_interrupt_controller(metal_cpu_Type *cpu);

extern __inline__ int32_t
metal_cpu_exception_register(metal_cpu_Type *cpu, uint32_t ecode,
                             metal_exception_handler_t handler);

extern __inline__ uint32_t metal_cpu_get_instruction_length(metal_cpu_Type *cpu,
                                                       uintptr_t epc);

extern __inline__ uintptr_t metal_cpu_get_exception_pc(metal_cpu_Type *cpu);

extern __inline__ uint32_t metal_cpu_set_exception_pc(metal_cpu_Type *cpu,
                                                 uintptr_t epc);

extern __inline__ struct metal_buserror *
metal_cpu_get_buserror(metal_cpu_Type *cpu);
