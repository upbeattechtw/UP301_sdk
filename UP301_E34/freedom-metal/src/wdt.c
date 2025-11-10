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

#include "metal.h"
#include "metal/wdt.h"

extern __inline__ enum_wdt_retcode_Type upt_wdt_init(metal_wdt_Type *wdt, uint32_t nLoad);

extern __inline__ enum_wdt_retcode_Type upt_wdt_enable(metal_wdt_Type *wdt, bool enable);

extern __inline__ enum_wdt_retcode_Type upt_wdt_isr_enable(metal_wdt_Type *wdt, bool enable);

extern __inline__ enum_wdt_retcode_Type upt_wdt_kick(metal_wdt_Type *wdt);

extern __inline__ uint32_t upt_wdt_get_count(metal_wdt_Type *wdt);

extern __inline__ enum_wdt_retcode_Type upt_wdt_set_count(metal_wdt_Type *wdt, uint32_t nLoad);

metal_wdt_Type *upt_wdt_get_device(enum_wdt_device_Type device_num) {
#if __METAL_DT_MAX_WDTS > 0
    if (device_num < __METAL_DT_MAX_WDTS) {
        return (metal_wdt_Type *)__metal_wdt_table[device_num];
    }
#endif
    return NULL;
}
