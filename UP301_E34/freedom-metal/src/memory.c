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
#include "metal/memory.h"

struct metal_memory *metal_get_memory_from_address(const uintptr_t address) {
    for (int i = 0; i < __METAL_DT_MAX_MEMORIES; i++) {
        struct metal_memory *mem = __metal_memory_table[i];

        uintptr_t lower_bound = metal_memory_get_base_address(mem);
        uintptr_t upper_bound = lower_bound + (metal_memory_get_size(mem) - 1);

        if (upper_bound < lower_bound) {
            /* overflow detected this memory range is ignored */
            continue;
        }

        if ((address >= lower_bound) && (address <= upper_bound)) {
            return mem;
        }
    }

    return NULL;
}

extern __inline__ uintptr_t
metal_memory_get_base_address(const struct metal_memory *memory);
extern __inline__ size_t
metal_memory_get_size(const struct metal_memory *memory);
extern __inline__ int
metal_memory_supports_atomics(const struct metal_memory *memory);
extern __inline__ int
metal_memory_is_cachable(const struct metal_memory *memory);
