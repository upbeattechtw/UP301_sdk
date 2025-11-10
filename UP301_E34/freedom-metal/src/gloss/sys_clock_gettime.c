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

#define _POSIX_MONOTONIC_CLOCK 200809L
#define _POSIX_TIMERS
#include <errno.h>
#include <time.h>

#include "metal.h"
#include "metal/drivers/riscv_cpu.h"

#ifdef MTIME_RATE_HZ_DEF
#undef MTIME_RATE_HZ
#define MTIME_RATE_HZ MTIME_RATE_HZ_DEF
#endif /* MTIME_RATE_HZ_DEF */

#ifndef MTIME_RATE_HZ
#define MTIME_RATE_HZ 32768
#endif /* MTIME_RATE_HZ */

#if !defined(mtime_interrupt_controller) &&                                    \
    defined(__METAL_DT_RISCV_CLINT0_HANDLE)
#define mtime_interrupt_controller __METAL_DT_RISCV_CLINT0_HANDLE
#endif /* !defined(mtime_interrupt_controller) && defined(__METAL_DT_RISCV_CLINT0_HANDLE) */

#if !defined(mtime_interrupt_controller) &&                                    \
    defined(__METAL_DT_SIFIVE_CLIC0_HANDLE)
#define mtime_interrupt_controller __METAL_DT_SIFIVE_CLIC0_HANDLE
#endif /* !defined(mtime_interrupt_controller) && defined(__METAL_DT_SIFIVE_CLIC0_HANDLE) */

#ifndef UPT_GET_F_CPU_HZ
#define UPT_GET_F_CPU_HZ                                                       \
  (11059200 *                                                                  \
   (1 + *(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS +        \
                                   METAL_UP_SCU_GCRG0 + GCRG_PLLFREQ1))) /     \
      (1 + (*(volatile unsigned int *)(METAL_UP_SCU_20000000_BASE_ADDRESS +    \
                                       METAL_UP_SCU_GCRG0 + GCRG_ODIVCH0) &    \
            0xFF))
#endif

int clock_getres(clockid_t clk_id, struct timespec *res) {
    switch (clk_id) {
    case CLOCK_REALTIME:
    case CLOCK_MONOTONIC:
        unsigned long long f_cpu_hz = UPT_GET_F_CPU_HZ;
        res->tv_sec = 0;
        res->tv_nsec = f_cpu_hz / MTIME_RATE_HZ;
        return 0;
    default:
        errno = EINVAL;
        return -1;
    }
}

int clock_gettime(clockid_t clk_id, struct timespec *tp) {
    uint64_t ticks;

    switch (clk_id) {
    case CLOCK_REALTIME:
    case CLOCK_MONOTONIC:
        unsigned long long f_cpu_hz = UPT_GET_F_CPU_HZ;
        mtime_interrupt_controller->vtable->command_request(
            mtime_interrupt_controller, METAL_TIMER_MTIME_GET, &ticks);
        tp->tv_sec = ticks / MTIME_RATE_HZ;
        tp->tv_nsec = ((ticks % (MTIME_RATE_HZ)) * f_cpu_hz) / MTIME_RATE_HZ;
        return 0;
    default:
        errno = EINVAL;
        return -1;
    }
}

int clock_settime(clockid_t clk_id, const struct timespec *tp) {
    errno = EINVAL;
    return -1;
}

uint64_t upt_gettime_us_64() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * (uint64_t) 1000000 + ts.tv_nsec / 1000;
}