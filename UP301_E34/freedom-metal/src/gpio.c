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
#include "metal/gpio.h"

extern __inline__ enum_gpio_retcode_Type upt_gpio_init(metal_gpio_Type *gpio);

extern __inline__ enum_gpio_retcode_Type upt_gpio_set_bit(metal_gpio_Type *gpio, uint32_t pin, enum_gpio_value_Type value);

extern __inline__ enum_gpio_value_Type upt_gpio_get_bit(metal_gpio_Type *gpio, uint32_t pin);

extern __inline__ enum_gpio_retcode_Type upt_gpio_set_direction(metal_gpio_Type *gpio, uint32_t pin, enum_gpio_dir_Type direction);

extern __inline__ enum_gpio_dir_Type upt_gpio_get_direction(metal_gpio_Type *gpio, uint32_t pin);

extern __inline__ enum_gpio_retcode_Type upt_gpio_output_toggle(metal_gpio_Type *gpio, uint32_t pin);

extern __inline__ enum_gpio_retcode_Type upt_gpio_isr_enable(metal_gpio_Type *gpio, uint32_t pin, enum_gpio_tri_Type intr_type);

extern __inline__ uint32_t upt_gpio_get_raw_status(metal_gpio_Type *gpio, uint32_t pin);

extern __inline__ uint32_t upt_gpio_get_status(metal_gpio_Type *gpio, uint32_t pin);

extern __inline__ enum_gpio_retcode_Type upt_gpio_clear_status(metal_gpio_Type *gpio, uint32_t pin);

extern __inline__ enum_gpio_retcode_Type upt_gpio_rtcm_set_bit_S_L_R(metal_gpio_Type *gpio, uint32_t pin, enum_gpio_value_Type value);

extern __inline__ enum_gpio_retcode_Type upt_gpio_rtcm_S_L_R_output_enable(metal_gpio_Type *gpio, uint32_t pin, bool enable);

metal_gpio_Type *upt_gpio_get_device(enum_gpio_device_Type device_num) {
#if __METAL_DT_MAX_GTIMERS > 0
    if (device_num > __METAL_DT_MAX_GPIOS) {
        return NULL;
    }
#endif
    return (metal_gpio_Type *)__metal_gpio_table[device_num];
}
