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
#include "metal/dsp.h"

extern __inline__ enum_dsp_retcode_Type upt_dsp_fft_disable_irq(metal_dsp_Type *dsp);
extern __inline__ enum_dsp_retcode_Type upt_dsp_fft_enable_irq(metal_dsp_Type *dsp);
extern __inline__ enum_dsp_retcode_Type upt_dsp_fft_clear_irq(metal_dsp_Type *dsp);
extern __inline__ enum_dsp_retcode_Type upt_dsp_rfft_q15(metal_dsp_Type *dsp,const upt_dsp_config_Type *cfg,
												 int16_t *pSrc, int16_t *pDst,int32_t *sfDst);

extern __inline__ enum_dsp_retcode_Type upt_dsp_rfft_q31(metal_dsp_Type *dsp,const upt_dsp_config_Type *cfg,
												 int32_t *pSrc, int32_t *pDst,int32_t *sfDst);

extern __inline__ enum_dsp_retcode_Type upt_dsp_dot_prod_q15(metal_dsp_Type *dsp,
		 	 	 	 	 	 	 	 	 	 	 const upt_dsp_config_Type *cfg, const int16_t *pSrcA,
												 const int16_t *pSrcB, int16_t *pDst, int32_t *sfDst);

extern __inline__ enum_dsp_retcode_Type upt_dsp_dot_prod_q31(metal_dsp_Type *dsp,
												 const upt_dsp_config_Type *cfg, const int32_t *pSrcA,
											  	 const int32_t *pSrcB, int32_t *pDst, int32_t *sfDst);
extern __inline__ enum_dsp_retcode_Type upt_dsp_sqrt_q15(metal_dsp_Type *dsp,
												 int16_t *pSrc, int16_t *pDst,
												 int16_t *pScale, int32_t length);

extern __inline__ enum_dsp_retcode_Type upt_dsp_sqrt_q31(metal_dsp_Type *dsp,
												 int32_t *pSrc, int32_t *pDst,
												 int32_t *pScale, int32_t length);
extern __inline__ enum_dsp_retcode_Type upt_dsp_spectrum_q15(metal_dsp_Type *dsp,
												 int16_t *pSrc, int32_t *pMagnitude, int32_t *pScale,
												 int32_t length);


extern __inline__ enum_dsp_retcode_Type upt_dsp_spectrum_q31(metal_dsp_Type *dsp,
												 int32_t *pSrc, int32_t *pMagnitude, int32_t *pScale,
												 int32_t length);

metal_dsp_Type *upt_dsp_get_device(enum_dsp_device_Type device_num) {
#if __METAL_DT_MAX_DSPS > 0
    if (device_num < __METAL_DT_MAX_DSPS) {
        return (metal_dsp_Type *)__metal_dsp_table[device_num];
    }
#endif

    return NULL;
}

