// -----------------------------------------------------------------------------
// Copyright (c) 2022 Think Silicon S.A.
/*
 * Copyright (C) 2025 UpbeatTech Inc. All Rights Reserved
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * This file contains code derived from software originally developed by Think Silicon S.A.
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

/*******************************************************************************
 * Copyright (c) 2022 Think Silicon S.A.
 *
   Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this header file and/or associated documentation files to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the
 * Materials, and to permit persons to whom the Materials are furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Materials.
 *
 * MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS
 * NEMAGFX API. THE UNMODIFIED, NORMATIVE VERSIONS OF THINK-SILICON NEMAGFX
 * SPECIFICATIONS AND HEADER INFORMATION ARE LOCATED AT:
 *   https://think-silicon.com/products/software/nemagfx-api
 *
 *  The software is provided 'as is', without warranty of any kind, express or
 *  implied, including but not limited to the warranties of merchantability,
 *  fitness for a particular purpose and noninfringement. In no event shall
 *  Think Silicon S.A. be liable for any claim, damages or other liability, whether
 *  in an action of contract, tort or otherwise, arising from, out of or in
 *  connection with the software or the use or other dealings in the software.
 ******************************************************************************/

#ifndef NEMA_RINGBUFFER_H__
#define NEMA_RINGBUFFER_H__

#include "nema_sys_defs.h"
#include "nema_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------
//@function nema_rb_submit_cmdlist
//@brief Enqueue a Command List to the Ring Buffer for execution
//@param nema_buffer_t *bo desc: Pointer to the buffer object of the Command List
//@param uint32_t size desc: Size of the populated Command List
//@return int desc: Return submission id
//--------------------------------------------------
/** \private */
int32_t nema_rb_submit_cmdlist(nema_buffer_t *bo, int size);

int32_t nema_rb_submit_cmdlist2(uintptr_t base_phys, int size);

void nema_rb_reset(void);

//--------------------------------------------------
//@function nema_rb_inline_cmd
//@brief Enqueue a Command to the Ring Buffer for execution
//@param uint32_t reg desc: Hardware Register to be written
//@param uint32_t data desc: Data to be written
//--------------------------------------------------
/** \private */
void nema_rb_inline_cmd(uint32_t reg, uint32_t data);

/** \private */
void nema_rb_force_flush(void);

/** \private */
void nema_rb_submit_cl_id(int cl_id);

#ifdef __cplusplus
}
#endif

#endif
