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


#ifndef NEMADC_HAL_H__
#define NEMADC_HAL_H__

#include "nema_sys_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \brief Initialize system. Implementor defined. Called in nemadc_init()
 *
 * \return 0 if no errors occurred
 * \see nema_init()
 *
 */
int32_t nemadc_sys_init(void);


/** \brief Wait for VSYNC
 *
 *
 */
void nemadc_wait_vsync(void);

/** \brief Read Hardware register
 *
 * \param reg Register to read
 * \return Value read from the register
 * \see nema_reg_write
 *
 */
uint32_t nemadc_reg_read(uint32_t reg);

/** \brief Write Hardware Register
 *
 * \param reg Register to write
 * \param value Value to be written
 * \see nema_reg_read()
 *
 */
void nemadc_reg_write(uint32_t reg, uint32_t value);

#ifdef __cplusplus
}
#endif

#endif
