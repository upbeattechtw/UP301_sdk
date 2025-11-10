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

#ifndef __SEGGER_LIBC__
#include <sys/time.h>
#include <sys/times.h>
#endif /* __SEGGER_LIBC__ */

#include "metal.h"
#include "metal/cpu.h"
#include "metal/timer.h"

#if defined(__METAL_DT_MAX_HARTS)
/*!
 * @brief implementation serves as a small shim that interfaces with the first
 * timer on a system.
 * @return enum_timer_retcode_Type error call.
 *  */
enum_timer_retcode_Type metal_timer_get_cyclecount(uint32_t hartid, uint64_t *mcc) {
    struct metal_cpu *cpu = metal_cpu_get(hartid);

    if (cpu) {
        *mcc = metal_cpu_get_timer(cpu);
        return E_TIMER_SUCCESS;
    }
    return E_TIMER_ERROR;
}

enum_timer_retcode_Type metal_timer_get_timebase_frequency(uint32_t hartid,
										    uint64_t *timebase) {
    struct metal_cpu *cpu = metal_cpu_get(hartid);

    if (cpu) {
        *timebase = metal_cpu_get_timebase(cpu);
        return E_TIMER_SUCCESS;
    }
    return E_TIMER_ERROR;
}

uint32_t metal_timer_get_machine_time(uint32_t hartid) {
    struct metal_cpu *cpu = metal_cpu_get(hartid);

    if (cpu) {
        return metal_cpu_get_mtime(cpu);
    }
    return 0;
}

int32_t metal_timer_set_machine_time(uint32_t hartid, uint64_t time) {
    struct metal_cpu *cpu = metal_cpu_get(hartid);

    if (cpu) {
        return metal_cpu_set_mtimecmp(cpu, time);
    }
    return -1;
}

#else

/* This implementation of gettimeofday doesn't actually do anything, it's just
 * there to provide a shim and return 0 so we can ensure that everything can
 * link to _gettimeofday.
 */
uint32_t nop_cyclecount(uint32_t id, uint64_t *c)
    __attribute__((section(".text.metal.nop.cyclecount")));
uint32_t nop_cyclecount(uint32_t id, uint64_t *c) { return -1; }
uint32_t nop_timebase(uint64_t *t)
    __attribute__((section(".text.metal.nop.timebase")));
uint32_t nop_timebase(uint64_t *t) { return -1; }
uint32_t nop_tick(uint32_t second) __attribute__((section(".text.metal.nop.tick")));
uint32_t nop_tick(uint32_t second) { return -1; }
enum_timer_retcode_Type metal_timer_get_cyclecount(uint32_t hartid, uint64_t *c)
    __attribute__((weak, alias("nop_cyclecount"))) {
#pragma message(                                                               \
    "There is no default timer device, metal_timer_get_cyclecount() will always return cyclecount -1.")
}
enum_timer_retcode_Type metal_timer_get_timebase_frequency(uint32_t hartid, uint64_t *t)
    __attribute__((weak, alias("nop_timebase"))) {
#pragma message(                                                               \
    "There is no default timer device, metal_timer_get_timebase_frequency() will always return timebase -1.")
}
int32_t metal_timer_set_tick(uint32_t hartid, uint32_t second)
	__attribute__((weak, alias("nop_tick"))) {
#pragma message(                                                               \
    "There is no default timer device, metal_timer_set_tick) will always return -1.")
}

#endif /* defined(__METAL_DT_MAX_HARTS) */
