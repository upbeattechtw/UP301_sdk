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
#include <sys/times.h>

#include "metal/cpu.h"
#include "metal/timer.h"

/* v * num / den while avoiding overflow
 *
 * Modulus on unsigned values is defined as:
 *
 *	v % den = v - (v / den) * den
 *	v = v % den + (v / den) * den
 *
 * This lets us break the computation down as follows:
 *
 *	r = (v * num) / den
 *	  = ((v % den + (v / den) * den) * num) / den
 *	  = ((v % den) * num) / den + ((v / den) * den) * num / den
 *	  = ((v % den) * num) / den + ((v / den) * num
 *
 * As long as num * den fits in 64 bits, then this computation will fit
 * in 64 bits. CLOCKS_PER_SEC is defined as 1,000,000, so we just need
 * timebase to be less than about 4,000,000,000,000 (4 trillion).
 */

static inline uint64_t muldiv(uint64_t v, uint64_t num, uint64_t den) {
    return (((v % den) * num) / den) + ((v / den) * num);
}

/* Timing information for current process. From
   newlib/libc/include/sys/times.h the tms struct fields are as follows:

   - clock_t tms_utime  : user clock ticks
   - clock_t tms_stime  : system clock ticks
   - clock_t tms_cutime : children's user clock ticks
   - clock_t tms_cstime : children's system clock ticks

   Since maven does not currently support processes we set both of the
   children's times to zero. Eventually we might want to separately
   account for user vs system time, but for now we just return the total
   number of cycles since starting the program.  */
clock_t _times(struct tms *buf) {
	uint64_t mcc;
	uint64_t timebase;
	uint32_t hartid = metal_cpu_get_current_hartid();

    metal_timer_get_timebase_frequency(hartid, &timebase);
    metal_timer_get_cyclecount(hartid, &mcc);

    /*
     * Convert from native resolution to published resolution.
     *
     * Truncating this to 64 bits works because a change of 'c' in
     * cyclecount will change the return value by
     * c * CLOCKS_PER_SEC / timebase, so applications will see
     * time marching forward.
     */
    mcc = muldiv(mcc, CLOCKS_PER_SEC, timebase);

    buf->tms_stime = 0;
    buf->tms_cutime = 0;
    buf->tms_cstime = 0;
    return buf->tms_utime = mcc;
}

extern __typeof(_times) times __attribute__((__weak__, __alias__("_times")));
