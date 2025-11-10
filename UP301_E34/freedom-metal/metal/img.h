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

/**
 * @file  img.h
 * @brief API for image input module
 */
#ifndef METAL_IMG_H
#define METAL_IMG_H

#include <stdint.h>
#include <stdbool.h>

typedef enum enum_img_device {
	UDL_1_3 = 0,
} enum_img_device_Type;


typedef enum enum_img_int_flags {
	img_frame_end = 0,
	img_frame_begin,
    img_rx_busy
} enum_img_int_flags_Type;

typedef enum enum_img_intr_mode {
	intr_everyframe	= 0,
	intr_requireframe,
} enum_img_intr_mode_Type;

typedef enum enum_img_intr_frame_begin_mode {
	high_until_clear = 0,
	posedge,
} enum_img_intr_frame_begin_mode_Type;

typedef struct upt_img_config{
    bool pclk_edge;
    uint16_t y_pos_skip;
    bool vsync_pol;
    uint16_t x_pos_skip;
    bool hsync_pol;
    uint16_t line_num;
    uint16_t byte_num;
    uint16_t sram_byte_access;
    bool leading_zero;
    uint16_t frame_per_trigger;
    // downsampling settings 
    uint16_t frame_rcv;
    uint16_t frame_skip;
    uint16_t line_rcv;
    uint16_t line_skip;
    uint16_t byte_rcv;
    uint16_t byte_skip;
    uint32_t begin_addr;
    enum_img_intr_mode_Type interrupt_mode;
    enum_img_intr_frame_begin_mode_Type frame_begin_interrupt_mode;

} upt_img_config_Type;

/**
 * @brief IMG return error code.
 * @ingroup UP301_Controller_IMG
 */
typedef enum enum_img_retcode{
    E_IMG_SUCCESS,     // Success.
	E_IMG_INVINIT,	 	// Initial fail or resource is unavailable.
	E_IMG_INVPARA,	 	// Invalid function parameter/argument.
    E_IMG_ERROR,     	// Unspecific error.
} enum_img_retcode_Type;

#define IMG_FRAME_END     (0x1U << 8)
#define IMG_FRAME_BEGIN   (0x1U << 24)

typedef struct metal_img {
    const struct metal_img_vtable *vtable;
} metal_img_Type;

struct metal_img_vtable {
    enum_img_retcode_Type (*init)(metal_img_Type *img, upt_img_config_Type *config);
    enum_img_retcode_Type (*start)(metal_img_Type *img, bool enable);
    enum_img_retcode_Type (*interrupt_enable)(metal_img_Type *img, uint32_t enable_evt);
    enum_img_retcode_Type (*status)(metal_img_Type *img, enum_img_int_flags_Type check);
    uint32_t (*status_all)(metal_img_Type *img);
    void (*status_clear)(metal_img_Type *img);
};

metal_img_Type *upt_img_get_device(enum_img_device_Type device_num);

__inline__ enum_img_retcode_Type upt_img_init(metal_img_Type *img, upt_img_config_Type *config) {
    return img->vtable->init(img, config);
}
__inline__ enum_img_retcode_Type upt_img_enable(metal_img_Type *img, bool enable) {
    return img->vtable->start(img, enable);
}
__inline__ uint32_t upt_img_check_status(metal_img_Type *img, enum_img_int_flags_Type check) {
    return img->vtable->status(img, check);
}
__inline__ uint32_t upt_img_get_status(metal_img_Type *img) {
	return img->vtable->status_all(img);
}
__inline__ void upt_img_clear_status(metal_img_Type *img) {
    img->vtable->status_clear(img);
}
__inline__ enum_img_retcode_Type upt_img_isr_enable(metal_img_Type *img, uint32_t enable_evt) {
    return img->vtable->interrupt_enable(img, enable_evt);
}
#endif
