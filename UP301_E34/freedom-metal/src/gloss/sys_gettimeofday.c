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

#include <errno.h>
#include <sys/time.h>

#include "metal/timer.h"

int _gettimeofday(struct timeval *tp, void *tzp) {
    uint32_t rv;
    uint64_t mcc, timebase;
    rv = metal_timer_get_cyclecount(0, &mcc);
    if (rv != 0) {
        return -1;
    }
    rv = metal_timer_get_timebase_frequency(0, &timebase);
    if (rv != 0) {
        return -1;
    }
    tp->tv_sec = mcc / timebase;
    tp->tv_usec = mcc % timebase * 1000000 / timebase;
    return 0;
}

extern __typeof(_gettimeofday) gettimeofday
    __attribute__((__weak__, __alias__("_gettimeofday")));
