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

#ifndef UPT_METAL_DRIVERS_GPIO_H
#define UPT_METAL_DRIVERS_GPIO_H
#include "metal/compiler.h"
#include "metal/io.h"
#include "metal/gpio.h"
#include "upt_rtcm_gpio.h"

struct __metal_driver_vtable_up_gpio {
    const struct __metal_gpio_vtable gpio;
};

__METAL_DECLARE_VTABLE(__metal_driver_vtable_up_gpio)

struct __metal_driver_up_gpio {
	metal_gpio_Type gpio;
};

#define __upt_metal_driver_rtcm_gpio_init upt_rtcm_gpio_init
#define __upt_metal_driver_rtcm_gpio_set_bit upt_rtcm_gpio_set_bit
#define __upt_metal_driver_rtcm_gpio_get_bit upt_rtcm_gpio_get_bit
#define __upt_metal_driver_rtcm_gpio_set_direction upt_rtcm_gpio_set_direction
#define __upt_metal_driver_rtcm_gpio_get_direction upt_rtcm_gpio_get_direction
#define __upt_metal_driver_rtcm_gpio_output_toggle upt_rtcm_gpio_output_toggle
#define __upt_metal_driver_rtcm_gpio_config_interrupt upt_rtcm_gpio_config_interrupt
#define __upt_metal_driver_rtcm_gpio_raw_status upt_rtcm_gpio_raw_status
#define __upt_metal_driver_rtcm_gpio_status upt_rtcm_gpio_status
#define __upt_metal_driver_rtcm_gpio_clear_interrupt upt_rtcm_gpio_clear_interrupt
#define __upt_metal_driver_rtcm_gpio_interrupt_enable upt_rtcm_gpio_interrupt_enable
#define __upt_metal_driver_rtcm_gpio_interrupt_disable upt_rtcm_gpio_interrupt_disable
#define __upt_metal_driver_rtcm_gpio_set_bit_S_L_R upt_rtcm_gpio_set_bit_S_L_R
#define __upt_metal_driver_rtcm_gpio_S_L_R_output_enable upt_rtcm_gpio_S_L_R_output_enable
#define __upt_metal_driver_rtcm_gpio_S_L_R_output_disable upt_rtcm_gpio_S_L_R_output_disable

#endif /* UPT_METAL_DRIVERS_GPIO_H */
