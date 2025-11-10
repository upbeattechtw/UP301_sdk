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

#ifndef METAL_DRIVERS_UP_TS_H
#define METAL_DRIVERS_UP_TS_H
#include "metal/compiler.h"
#include "metal/io.h"
#include "metal/ts.h"

struct __metal_driver_vtable_up_ts {
    const struct metal_ts_vtable ts;
};

struct __metal_driver_up_ts;

__METAL_DECLARE_VTABLE(__metal_driver_vtable_up_ts)

struct __metal_driver_up_ts {
    const metal_ts_Type ts;
};

#endif
