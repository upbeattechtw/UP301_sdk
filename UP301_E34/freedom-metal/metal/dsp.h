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
#ifndef METAL_DSP_H
#define METAL_DSP_H

#define UPT_DSP_DOT_PROD_MODE  0x09
#define UPT_DSP_SQUARE_ROOT_MODE  0x10

#include <stdint.h>

enum { UPT_DSP_RFFT_MODE, UPT_DSP_IRFFT_MODE };

typedef enum enum_dsp_device {
    NAON_UDL_1_2_DSP = 0, /**< NAON UDL module. */
} enum_dsp_device_Type;

/*!
 * @brief dsp return error code.
 * @ingroup UP301_Metal constructors & destructors
 */
typedef enum enum_dsp_status{
    E_DSP_SUCCESS,       //Success.
    E_DSP_INVINIT,       //Initial fail or resource is unavailable.
    E_DSP_INVPARA,       //Invalid function parameter/argument.
    E_DSP_ERROR,         //Unspecific error.
} enum_dsp_retcode_Type;

/**
 * @brief Instance structure for the upt DSP function.
 */
typedef struct {
  uint32_t length; /**< length of the operation */

  uint32_t dim; /**< dimension of the vector for dot product mode */

  uint8_t dsp_ifftFlag;     /**< flag that selects FFT/IFFT
                         - ifftFlag=UPT_DSP_RFFT_MODE: RFFT
                         - ifftFlag=UPT_DSP_IRFFT_MODE: IRFFT
                         */
  uint8_t spectrumFlag; /**< flag that indicates spectrum calculation */
} upt_dsp_config_Type;

/**
 * @brief Handle for a ADC engine
 */
typedef struct metal_dsp {
    const struct metal_dsp_vtable *vtable;
} metal_dsp_Type;

struct metal_dsp_vtable {
	enum_dsp_retcode_Type (*fft_disable_irq)(metal_dsp_Type *dsp);

	enum_dsp_retcode_Type (*fft_enable_irq)(metal_dsp_Type *dsp);

	enum_dsp_retcode_Type (*fft_clear_irq)(metal_dsp_Type *dsp);

	enum_dsp_retcode_Type (*rfft_q15)(
			    metal_dsp_Type *dsp,
				const upt_dsp_config_Type *cfg,
				int16_t *pSrc, int16_t *pDst,
		        int32_t *sfDst);

	enum_dsp_retcode_Type (*dot_prod_q15)(
			metal_dsp_Type *dsp,
			const upt_dsp_config_Type *cfg,
			const int16_t *pSrcA,
	        const int16_t *pSrcB,
			int16_t *pDst, int32_t *sfDst);

	enum_dsp_retcode_Type  (*dot_prod_q31)(
			metal_dsp_Type *dsp,
			const upt_dsp_config_Type *cfg,
			const int32_t *pSrcA,
	        const int32_t *pSrcB,
			int32_t *pDst,
			int32_t *sfDst);

	enum_dsp_retcode_Type (*sqrt_q15)(
			metal_dsp_Type *dsp,
			int16_t *pSrc,
			int16_t *pDst,
			int16_t *pScale,
			int32_t length);

	enum_dsp_retcode_Type (*sqrt_q31)(
			metal_dsp_Type *dsp,
			int32_t *pSrc,
			int32_t *pDst,
			int32_t *pScale,
			int32_t length);

	enum_dsp_retcode_Type (*spectrum_q15)(
			metal_dsp_Type *dsp,
			int16_t *pSrc,
			int32_t *pMagnitude,
			int32_t *pScale,
			int32_t length);

	enum_dsp_retcode_Type (*spectrum_q31)(
			metal_dsp_Type *dsp,
			int32_t *pSrc,
			int32_t *pMagnitude,
			int32_t *pScale,
			int32_t length);

	enum_dsp_retcode_Type (*rfft_q31)(
			metal_dsp_Type *dsp,
			const upt_dsp_config_Type *cfg,
			int32_t *pSrc, int32_t *pDst,
			int32_t *sfDst);

};


/**
 * @brief Get a handle for a DSP.
 * @param device_num The index of the desired DSP engine.
 * @return A handle to the DSP, or NULL if the engine does not exist.
 */
__inline__ metal_dsp_Type *upt_dsp_get_device(enum_dsp_device_Type device_num);



__inline__ enum_dsp_retcode_Type upt_dsp_fft_disable_irq(metal_dsp_Type *dsp) {
    return dsp->vtable->fft_disable_irq(dsp);

}

__inline__ enum_dsp_retcode_Type upt_dsp_fft_enable_irq(metal_dsp_Type *dsp) {
    return dsp->vtable->fft_enable_irq(dsp);
}

/**
 * @brief Clear IRQ
 * @param None
 * @return None
 */
__inline__ enum_dsp_retcode_Type upt_dsp_fft_clear_irq(metal_dsp_Type *dsp) {
    return dsp->vtable->fft_clear_irq(dsp);
}

/**
 * @brief 16-bit real number FFT/IFFT
 * @details For n point real input 16-bit FFT, n=32/64/128/512/1024
 *           - cfg->length = n
 *           - cfg->ifftFlag = UPT_DSP_RFFT_MODE
 *           - pSrc: int16_t input array of (n) counts of real number
 *           - pDst: int16_t output array of (n/2+1) counts of complex number
 *              - pDst[0]: real_0
 *              - pDst[1]: imag_0
 *              - pDst[2]: real_1
 *              - pDst[3]: imag_1
 *              ...
 *              - pDst[n]: real_{n/2}
 *              - pDst[n+1]: imag_{n/2}
 *          For n point output 16-bit IFFT, n=32/64/128/512/1024
 *           - cfg->length = n
 *           - cfg->ifftFlag = UPT_DSP_IRFFT_MODE
 *           - pSrc: int16_t input array of (n/2+1) counts of complex number
 *              - pSrc[0]: real_0
 *              - pSrc[1]: imag_0
 *              - pSrc[2]: real_1
 *              - pSrc[3]: imag_1
 *              ...
 *              - pSrc[n]: real_{n/2}
 *              - pSrc[n+1]: imag_{n/2}
 *           - pDst: int16_t output array of (n) counts of real number
 * @param cfg configuration parameter
 * @param pSrc int16_t input array
 * @param pDst int16_t output array
 * @param sfDst output scale factor
 *          For q15 input format, scale factor indicates the output format as
 *          - 0: q15
 *          - 1: q1.14
 *          - 2: q2.13
 *          - 3: q3.12
 *          ...
 * @return 0 for sucess, others for error
 */

__inline__ enum_dsp_retcode_Type upt_dsp_rfft_q15(metal_dsp_Type *dsp,const upt_dsp_config_Type *cfg,
								 int16_t *pSrc, int16_t *pDst,int32_t *sfDst) {

					return dsp->vtable->rfft_q15(dsp,cfg,pSrc,pDst,sfDst);

}

/**
 * @brief 32-bit real number FFT/IFFT
 * @details For n point real input 32-bit FFT, n=32/64/128/512/1024
 *           - cfg->length = n
 *           - cfg->ifftFlag = UPT_DSP_RFFT_MODE
 *           - pSrc: int32_t input array of (n) counts of real number
 *           - pDst: int32_t output array of (n/2+1) counts of complex number
 *              - pDst[0]: real_0
 *              - pDst[1]: imag_0
 *              - pDst[2]: real_1
 *              - pDst[3]: imag_1
 *              ...
 *              - pDst[n]: real_{n/2}
 *              - pDst[n+1]: imag_{n/2}
 *          For n point output 32-bit IFFT, n=32/64/128/512/1024
 *           - cfg->length = n
 *           - cfg->ifftFlag = UPT_DSP_IRFFT_MODE
 *           - pSrc: int32_t input array of (n/2+1) counts of complex number
 *              - pSrc[0]: real_0
 *              - pSrc[1]: imag_0
 *              - pSrc[2]: real_1
 *              - pSrc[3]: imag_1
 *              ...
 *              - pSrc[n]: real_{n/2}
 *              - pSrc[n+1]: imag_{n/2}
 *           - pDst: int32_t output array of (n) counts of real number
 * @param cfg configuration parameter
 * @param pSrc int32_t input array
 * @param pDst int32_t output array
 * @param sfDst output scale factor
 *          For q31 input format, scale factor indicates the output format as
 *          - 0: q31
 *          - 1: q1.30
 *          - 2: q2.29
 *          - 3: q3.28
 *          ...
 * @return 0 for sucess, others for error
 */
__inline__ enum_dsp_retcode_Type upt_dsp_rfft_q31(metal_dsp_Type *dsp,const upt_dsp_config_Type *cfg,
								 int32_t *pSrc, int32_t *pDst,int32_t *sfDst) {
					return dsp->vtable->rfft_q31(dsp,cfg,pSrc,pDst,sfDst);
}

/**
 * @brief 16-bit real number vector dot product
 * @details For n points, m-dimension vector dot product, m=1~512
 *           - cfg->length = n
 *           - cfg->dim = m
 *           - pSrcA: int16_t input array of (n*m) counts of real number
 *              - pSrcA[0]: A0_0
 *              - pSrcA[1]: A0_1
 *                ...
 *              - pSrcA[m-1]: A0_{m-1}
 *              - pSrcA[m]: A1_0
 *              - pSrcA[m+1]: A1_1
 *                ...
 *              - pSrcA[2*m-1]: A1_{m-1}
 *                ...
 *              - pSrcA[(n-1)*m]: A{n-1}_0
 *              - pSrcA[(n-1)*m+1]: A{n-1}_1
 *                ...
 *              - pSrcA[n*m - 1]: A{n-1}_{m-1}
 *           - pSrcB: int16_t input array of (n*m) counts of real number
 *              - pSrcB[0]: B0_0
 *              - pSrcB[1]: B0_1
 *                ...
 *              - pSrcB[m-1]: B0_{m-1}
 *              - pSrcB[m]: B1_0
 *              - pSrcB[m+1]: B1_1
 *                ...
 *              - pSrcB[2*m-1]: B1_{m-1}
 *                ...
 *              - pSrcB[(n-1)*m]: B{n-1}_0
 *              - pSrcB[(n-1)*m+1]: B{n-1}_1
 *                ...
 *              - pSrcB[n*m - 1]: B{n-1}_{m-1}
 *           - pDst: int16_t output array of (n) counts of real number
 *              - pDst[0] = A0_0*B0_0 + A0_1*B0_1 + ... + A0_{m-1}*B0_{m-1}
 *              - pDst[1] = A1_0*B1_0 + A1_1*B1_1 + ... + A1_{m-1}*B1_{m-1}
 *                ...
 *              - pDst[n-1] = A{n-1}_0*B{n-1}_0 + A{n-1}_1*B{n-1}_1 + ... +
 *                             A{n-1}_{m-1}*B{n-1}_{m-1}
 *           - sfDst: output scale factor
 *                For q15 input format, scale factor indicates the output format
 *                as
 *                - 0: q15
 *                - 1: q1.14
 *                - 2: q2.13
 *                - 3: q3.12
 *                ...
 * @param cfg configuration parameter
 * @param pSrcA int16_t input array of source A
 * @param pSrcB int16_t input array of source B
 *              If pSrcB is NULL and the vector dimension (m) is 2, then
 *              the conjugate dot product of pSrcA will be conducted.
 * @param pDst int16_t output array
 * @param sfDst output scale factor
 *          For q15 input format, scale factor indicates the output format as
 *          - 0: q15
 *          - 1: q1.14
 *          - 2: q2.13
 *          - 3: q3.12
 *          ...
 * @return 0 for sucess, others for error
 */
__inline__ enum_dsp_retcode_Type upt_dsp_dot_prod_q15(metal_dsp_Type *dsp,
							 const upt_dsp_config_Type *cfg, const int16_t *pSrcA,
							 const int16_t *pSrcB, int16_t *pDst, int32_t *sfDst) {

					return dsp->vtable->dot_prod_q15(dsp,cfg,pSrcA,pSrcB,pDst,sfDst);

}

/**
 * @brief 32-bit real number vector dot product
 * @details For n points, m-dimension vector dot product, m=1~3
 *           - cfg->length = n
 *           - cfg->dim = m
 *           - pSrcA: int32_t input array of (n*m) counts of real number
 *              - pSrcA[0]: A0_0
 *              - pSrcA[1]: A0_1
 *                ...
 *              - pSrcA[m-1]: A0_{m-1}
 *              - pSrcA[m]: A1_0
 *              - pSrcA[m+1]: A1_1
 *                ...
 *              - pSrcA[2*m-1]: A1_{m-1}
 *                ...
 *              - pSrcA[(n-1)*m]: A{n-1}_0
 *              - pSrcA[(n-1)*m+1]: A{n-1}_1
 *                ...
 *              - pSrcA[n*m - 1]: A{n-1}_{m-1}
 *           - pSrcB: int32_t input array of (n*m) counts of real number
 *              - pSrcB[0]: B0_0
 *              - pSrcB[1]: B0_1
 *                ...
 *              - pSrcB[m-1]: B0_{m-1}
 *              - pSrcB[m]: B1_0
 *              - pSrcB[m+1]: B1_1
 *                ...
 *              - pSrcB[2*m-1]: B1_{m-1}
 *                ...
 *              - pSrcB[(n-1)*m]: B{n-1}_0
 *              - pSrcB[(n-1)*m+1]: B{n-1}_1
 *                ...
 *              - pSrcB[n*m - 1]: B{n-1}_{m-1}
 *           - pDst: int32_t output array of (n) counts of real number
 *              - pDst[0] = A0_0*B0_0 + A0_1*B0_1 + ... + A0_{m-1}*B0_{m-1}
 *              - pDst[1] = A1_0*B1_0 + A1_1*B1_1 + ... + A1_{m-1}*B1_{m-1}
 *                ...
 *              - pDst[n-1] = A{n-1}_0*B{n-1}_0 + A{n-1}_1*B{n-1}_1 + ... +
 *                             A{n-1}_{m-1}*B{n-1}_{m-1}
 *           - sfDst: output scale factor
 *                For q31 input format, scale factor indicates the output format
 *                as
 *                - 0: q31
 *                - 1: q1.30
 *                - 2: q2.29
 *                - 3: q3.28
 *                ...
 * @param cfg configuration parameter
 * @param pSrcA int32_t input array of source A
 * @param pSrcB int32_t input array of source B
 *              If pSrcB is NULL and the vector dimension (m) is 2, then
 *              the conjugate dot product of pSrcA will be conducted.
 * @param pDst int32_t output array
 * @param sfDst output scale factor
 *          For q31 input format, scale factor indicates the output format as
 *          - 0: q31
 *          - 1: q1.30
 *          - 2: q2.29
 *          - 3: q3.28
 *          ...
 * @return 0 for sucess, others for error
 */
__inline__ enum_dsp_retcode_Type upt_dsp_dot_prod_q31(metal_dsp_Type *dsp,
						   const upt_dsp_config_Type *cfg, const int32_t *pSrcA,
		                   const int32_t *pSrcB, int32_t *pDst, int32_t *sfDst){

					return dsp->vtable->dot_prod_q31(dsp,cfg,pSrcA,pSrcB,pDst,sfDst);

}



/**
 * @brief 16-bit square root of real number
 * @details For n point real input, n = 1 ~ 1024
 *          - pSrc: int16_t input array of (n) counts of real number
 *          - pDst: int32_t output array of (n) counts of real number, where
 *                  pDst[i] is the square root of the pSrc[i]
 *          - length: n
 * @param pSrc int16_t input array
 * @param pDst int32_t output array
 * @param pScale input the scale facotr for the pSrc; output the scale factor
 *               for the pDst
 * @param length pSrc and pDst array length
 * @return 0 for sucess, others for error
 */
__inline__ enum_dsp_retcode_Type upt_dsp_sqrt_q15(metal_dsp_Type *dsp,
		                              int16_t *pSrc, int16_t *pDst,
									  int16_t *pScale, int32_t length){

					return dsp->vtable->sqrt_q15(dsp,pSrc,pDst,pScale,length);

}

/**
 * @brief 32-bit square root of real number
 * @details For n point real input, n = 1 ~ 1024
 *          - pSrc: int32_t input array of (n) counts of real number
 *          - pDst: int32_t output array of (n) counts of real number, where
 *                  pDst[i] is the square root of the pSrc[i]
 *          - length: n
 * @param pSrc int32_t input array
 * @param pDst int32_t output array
 * @param pScale input the scale facotr for the pSrc; output the scale factor
 *               for the pDst
 * @param length pSrc and pDst array length
 * @return 0 for sucess, others for error
 */
__inline__ enum_dsp_retcode_Type upt_dsp_sqrt_q31(metal_dsp_Type *dsp,
		                             int32_t *pSrc, int32_t *pDst,
									 int32_t *pScale, int32_t length){

					return dsp->vtable->sqrt_q31(dsp,pSrc,pDst,pScale,length);

}

/**
 * @brief 16-bit real spectrum analysis
 * @param pSrc input/buffer array of length (n+2). Only the first (n) counts
 * store the real input.
 * @param pMagnitude output array of length (n/2+1) of the spectrum magnitude
 * @param pScale the scale factor for spectrum magnitude output
 * @param length (n) count of pSrc real input, n=32/64/128/512/1024
 */
__inline__ enum_dsp_retcode_Type upt_dsp_spectrum_q15(metal_dsp_Type *dsp,
		                          int16_t *pSrc, int32_t *pMagnitude, int32_t *pScale,
				                  int32_t length){

					return dsp->vtable->spectrum_q15(dsp,pSrc,pMagnitude,pScale,length);

}



/**
 * @brief 32-bit real spectrum analysis
 * @param pSrc input/buffer array of length (n+2). Only the first (n) counts
 * store the real input.
 * @param pMagnitude output array of length (n/2+1) of the spectrum magnitude
 * @param pScale the scale factor for spectrum magnitude output
 * @param length (n) count of pSrc real input, n=32/64/128/512/1024
 */
__inline__ enum_dsp_retcode_Type upt_dsp_spectrum_q31(metal_dsp_Type *dsp,
									int32_t *pSrc, int32_t *pMagnitude, int32_t *pScale,
									int32_t length){

					return dsp->vtable->spectrum_q31(dsp,pSrc,pMagnitude,pScale,length);

}


#endif /* METAL_DSP_H */
