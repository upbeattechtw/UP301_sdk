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
#include "metal/rtc.h"

extern inline enum_rtc_retcode_Type upt_rtc_init(metal_rtc_Type *rtc);

extern inline enum_rtc_retcode_Type upt_rtc_set_time(metal_rtc_Type *rtc, rtc_real_time_info_Type *realtime);

extern inline enum_rtc_retcode_Type upt_rtc_get_time(metal_rtc_Type *rtc, rtc_real_time_info_Type *realtime);

extern inline enum_rtc_retcode_Type upt_rtc_set_alarm(metal_rtc_Type *rtc, rtc_alarm_time_info_Type *alatime);

extern inline enum_rtc_retcode_Type upt_rtc_get_alarm(metal_rtc_Type *rtc, rtc_alarm_time_info_Type *alatime);

extern inline enum_rtc_retcode_Type upt_rtc_enable(metal_rtc_Type *rtc, bool enable);

extern inline enum_rtc_retcode_Type upt_rtc_isr_enable(metal_rtc_Type *rtc, bool enable);

extern inline uint32_t upt_rtc_get_status(metal_rtc_Type *rtc);

extern inline enum_rtc_retcode_Type upt_rtc_clear_status(metal_rtc_Type *rtc);

metal_rtc_Type *upt_rtc_get_device(enum_rtc_device_Type device_num) {
#if __METAL_DT_MAX_RTCS > 0
    if (device_num > __METAL_DT_MAX_RTCS) {
        return NULL;
    }
#endif
    return (metal_rtc_Type *)__metal_rtc_table[device_num];
}
