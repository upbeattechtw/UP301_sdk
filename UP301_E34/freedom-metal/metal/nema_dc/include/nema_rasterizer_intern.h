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

#ifndef NEMA_RASTERIZER_INTERN_H__
#define NEMA_RASTERIZER_INTERN_H__

#ifdef __cplusplus
extern "C" {
#endif

// Drawing Engine Primitives
//-----------------------------------------------------------------------------------------------------------------------
#define DRAW_LINE         (0x01U)
#define DRAW_BOX          (0x02U)
#define DRAW_TRIANGLE     (0x04U)
#define DRAW_QUAD         (0x05U)
#define GL_DRAW_LINE      (0x21U)
#define GL_DRAW_BOX       (0x22U)
#define GL_DRAW_PIXEL     (0x23U)
#define GL_DRAW_TRIANGLE  (0x24U)
#define GL_DRAW_QUAD      (0x25U)

#define RAST_AA_E3          (0x00800000U)  //(1U<<23)
#define RAST_AA_E2          (0x01000000U)  //(1U<<24)
#define RAST_AA_E1          (0x02000000U)  //(1U<<25)
#define RAST_AA_E0          (0x04000000U)  //(1U<<26)
#define RAST_AA_MASK        (RAST_AA_E0 | RAST_AA_E1 | RAST_AA_E2 | RAST_AA_E3)
#define RAST_GRAD           (0x08000000U)  //(1U<<27)
#define RAST_SETUP_CULL_CW  (0x10000000U)  //(1U<<28)
#define RAST_SETUP_CULL_CCW (0x20000000U)  //(1U<<29)
#define RAST_TILE           (0x40000000U)  //(1U<<30)

/** \brief Enables MSAA per edge
 *
 * \param aa A combination of the flags RAST_AA_E0, RAST_AA_E1, RAST_AA_E2, RAST_AA_E3
 * \return previous AA flags (may be ignored)
 *
 */
uint32_t nema_enable_aa_flags(uint32_t aa);

/** \brief Enables an additional clipping rectangle
 *
 * \param x Clip Window top-left x coordinate
 * \param y Clip Window minimum y
 * \param w Clip Window width
 * \param h Clip Window height
 *
 */
void nema_set_clip2(int32_t x, int32_t y, uint32_t w, uint32_t h);

/** \brief Returns if clip2 is supported in the hardware
 *
 * \return returns 1 if clip2 is supported otherwise returns 0
 *
 */
int nema_supports_clip2(void);

/** \brief Returns the number of steps required to draw a full circle
 *
 * \param r Radius
 * \return returns the number of steps
 *
 */
int calculate_steps_from_radius(float r);


#ifdef __cplusplus
}
#endif

#endif //NEMA_RASTERIZER_INTERN_H__
