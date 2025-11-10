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
#include "metal/pwm.h"

extern __inline__ enum_pwm_retcode_Type upt_pwm_set_output_timing(metal_pwm_Type *pwm,
										 	 	 uint8_t pwm_ch,
												 uint32_t base_clock,
												 uint32_t phase,
												 uint32_t duty,
												 uint32_t pulse);

extern __inline__ enum_pwm_retcode_Type upt_pwm_trigger(metal_pwm_Type *pwm, uint8_t pwm_ch, uint32_t count);

extern __inline__ enum_pwm_retcode_Type upt_pwm_enable(metal_pwm_Type *pwm, uint8_t pwm_ch, metal_pwm_run_mode_Type enable);

extern __inline__ enum_pwm_retcode_Type upt_pwm_isr_enable(metal_pwm_Type *pwm, uint8_t pwm_ch, metal_pwm_interrupt_Type enable);

extern __inline__ uint32_t upt_pwm_get_status(metal_pwm_Type *pwm, uint8_t pwm_ch);

extern __inline__ enum_pwm_retcode_Type upt_pwm_clear_status(metal_pwm_Type *pwm, uint8_t pwm_ch);

metal_pwm_Type *upt_pwm_get_device(enum_pwm_device_Type device_num) {
#if __METAL_DT_MAX_PWMS > 0
    if (device_num < __METAL_DT_MAX_PWMS) {
        return (metal_pwm_Type *)__metal_pwm_table[device_num];
    }
#endif

    return NULL;
}
