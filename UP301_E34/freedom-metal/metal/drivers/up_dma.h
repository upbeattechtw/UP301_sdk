/*
 * Copyright (C) 2025 UpbeatTech Inc. All Rights Reserved
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
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

#ifndef METAL__DRIVERS__UP_DMA_H
#define METAL__DRIVERS__UP_DMA_H
#include "metal/compiler.h"
#include "metal/dma.h"
#include "metal/io.h"

struct __metal_driver_vtable_up_dma {
    const struct __metal_dma_vtable dma;
};

__METAL_DECLARE_VTABLE(__metal_driver_vtable_up_dma);

struct __metal_driver_up_dma {
    metal_dma_Type dma;
};

#endif /* METAL__DRIVERS__UP_DMA_H */
