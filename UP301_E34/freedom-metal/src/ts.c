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

#include <stddef.h>

#include "metal.h"
#include "metal/ts.h"


extern inline enum_ts_retcode_Type upt_ts_enable(metal_ts_Type *ts, bool enable);

extern inline enum_ts_retcode_Type upt_ts_measure(metal_ts_Type *ts);

extern inline int16_t upt_ts_read_temp(metal_ts_Type *ts);

extern inline enum_ts_retcode_Type upt_ts_measure_async(metal_ts_Type *ts, bool enable);

extern __inline__ uint32_t upt_ts_get_status(metal_ts_Type *ts);

extern __inline__ enum_ts_retcode_Type upt_ts_clear_status(metal_ts_Type *ts);


metal_ts_Type *upt_ts_get_device(enum_ts_device_Type device_num) {
#ifdef __METAL_DT_MAX_TSS
    if (device_num < __METAL_DT_MAX_TSS) {
        return (metal_ts_Type *)__metal_ts_table[device_num];
    }
#endif
    return NULL;
}
