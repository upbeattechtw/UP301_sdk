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
#include <sys/types.h>

#include "metal/scrub.h"


/* brk is handled entirely within the C library.  This limits METAL programs
 * that use the C library to be disallowed from dynamically allocating memory
 * without talking to the C library, but that sounds like a sane way to go
 * about it.  Note that there is no error checking anywhere in this file, users
 * will simply get the relevant error when actually trying to use the memory
 * that's been allocated. 
 */
extern char metal_segment_heap_target_start;
extern char metal_segment_heap_target_end;
static char *__brk = &metal_segment_heap_target_start;

#ifdef _PICOLIBC__
#define _brk brk
#define _sbrk sbrk
#endif /* _PICOLIBC__ */

int _brk(void *addr) {
    __brk = addr;
    return 0;
}

char *_sbrk(ptrdiff_t incr) {
    char *old = __brk;

    /* If __heap_size == 0, we can't allocate memory on the heap */
    if (&metal_segment_heap_target_start == &metal_segment_heap_target_end) {
        return (void *)-1;
    }

    /* Don't move the break past the end of the heap */
    if ((__brk + incr) < &metal_segment_heap_target_end) {
        __brk += incr;
    }
    else {
        __brk = &metal_segment_heap_target_end;
        return (void *)-1;
    }
    /* Scrub out allocated memory to avoid spurious ECC errors */
    metal_mem_scrub(old, incr);

    return old;
}
