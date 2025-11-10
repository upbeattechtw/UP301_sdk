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
 * @file  pdm.h
 * @brief API for Pulse Density Modulation for Digital Microphone
 */
#ifndef METAL__PDM_H
#define METAL__PDM_H
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Device number of PDM device
 * @ingroup UP301_Controller_PDM
 */
enum pdm_sel {
	NAON_PDM_0		= 0,
	NAON_PDM_1
};

/***************************************************************************/
/* -------------+----------------------------------------------------------+
 *  MCLK(MHz)   +   CKO(MHz)  +  Fs    +   OSR   +  Data bit  +  USE CASE  +
 *--------------+-------------+--------+---------+------------+------------+
 *    12.288    +    3.072    +  48    +    64   +     24     +   CASE_1   +
 *--------------+-------------+------------------+------------+------------+
 *    12.288    +    1.536    +  16    +    96   +     24     +   CASE_3   +
 *--------------+----------------------+---------+------------+------------+
 *    24.576    +    6.144    +  96    +    64   +     24     +   CASE_5   +
 *--------------+-------------+--------+---------+------------+------------+
 *    12.288    +    1.536    +  24    +    64   +     24     +   CASE_6   +
 *--------------+-------------+--------+---------+------------+------------+
 *    12.288    +    1.024    +  16    +    64   +     16     +   CASE_2   +
 *--------------+-------------+--------+---------+------------+------------+
 *    12.288    +    0.768    +  16    +    48   +     16     +   CASE_4   +
 *--------------+-------------+--------+---------+------------+------------+
 *    12.288    +    3.072    +  96    +    32   +     24     +   CASE_7   +
 *--------------+-------------+--------+---------+------------+------------+
 *    12.288    +    1.536    +  48    +    32   +     24     +   CASE_8   +
 *--------------+-------------+--------+---------+------------+------------+
 ****************************************************************************/

/**
 * @brief PCM_CLK, Sample Rate and PDM_CKO Conversion vs. Performance
 * @ingroup UP301_Controller_PDM
 */
typedef enum enum_pdm_case_Type {
	pdm_case_1		= 0,
	pdm_case_2,
	pdm_case_3,
	pdm_case_4,
	pdm_case_5,
	pdm_case_6,
	pdm_case_7,
	pdm_case_8
}enum_pdm_case_Type;

/*!
 * @brief pdm return error code.
 * @ingroup UP301_Metal constructors & destructors
 */
typedef enum enum_pdm_status{
    E_PDM_SUCCESS,       //Success.
    E_PDM_INVINIT,       //Initial fail or resource is unavailable.
    E_PDM_INVPARA,       //Invalid function parameter/argument.
    E_PDM_ERROR,         //Unspecific error.
} enum_pdm_retcode_Type;

/**
 * @brief Audio channels
 * @ingroup UP301_Controller_PDM
 */
typedef enum enum_pdm_ch_sel_Type {
	pdm_channel_disable		= 0,
	pdm_channel_nomo_left,
	pdm_channel_nomo_right,
	pdm_chennel_stereo
}enum_pdm_ch_sel_Type;

/**
 * @brief Set bust length to PDM
 * @ingroup UP301_Controller_PDM
 */
typedef enum enum_pdm_brt_len_Type {
	pdm_word_1		= 0,
	pdm_word_4,
	pdm_word_8,
	pdm_word_16
}enum_pdm_brt_len_Type;

/**
 * @brief Set FIFO watermark level to PDM
 * @ingroup UP301_Controller_PDM
 */
typedef enum enum_pdm_watermark_Type {
	pdm_watermark_none = 0
}enum_pdm_watermark_Type;

/**
 * @brief PDM event flags
 * @ingroup UP301_Controller_PDM
 */
typedef enum enum_pdm_int_flags_Type {
	pdm_dma0_int	= 0,
	pdm_dma1_int,
	pdm_fifo_overflow
}enum_pdm_int_flags_Type;

/**
 * @brief PDM data precision
 * @ingroup UP301_Controller_PDM
 */
typedef enum enum_pdm_format_Type {
	pcm_wlen_16bit 		= 0,
	pcm_wlen_18bit,
	pcm_wlen_20bit,
	pcm_wlen_24bit
}enum_pdm_format_Type;

/** @brief Interrupt status: return value of upt_pdm_get_status() */
#define pdm_ffovf_int_reg 						(0x1U << 0)
/** @brief Interrupt status: return value of upt_pdm_get_status() */
#define pdm_dma0_int_reg 						(0x1U << 2)
/** @brief Interrupt status: return value of upt_pdm_get_status() */
#define pdm_dma1_int_reg 						(0x1U << 3)

struct metal_pdm_config {
	// PDM channel enable
	enum_pdm_ch_sel_Type pdm_channel;
    // PCM data length
	enum_pdm_format_Type data_wlen;
    // PDM DMAC transfer total size in word(32-bit)
    uint32_t total_size;
    // PDM DMAC block size in word(32_bit)
    uint32_t block_size;
    // PDM DMAC burst length
    enum_pdm_brt_len_Type burst_len;
    // @brief PDM DMAC destination address 0
    uint32_t dst_addr0;
    // PDM DMAC destination address 1
    uint32_t dst_addr1;
    // PDM I2S slave active bit
    uint32_t i2s_active;
    // Left/Right channel swap enable
    uint32_t lr_swap;
    // PDM PGA gain left value 0x8 = 0dB, 1.5dB/step
    int32_t pga_left;
    // PDM PGA gain right value 0x8 = 0dB, 1.5dB/step
    int32_t pga_right;
    // PDM conversion use case type
    enum_pdm_case_Type usecase;
};

struct metal_pdm;
struct metal_pdm_vtable {
	enum_pdm_retcode_Type (*cfg)(struct metal_pdm *pdm, struct metal_pdm_config *pdm_config);
	enum_pdm_retcode_Type (*core_enable)(struct metal_pdm *pdm, int32_t enable);
	enum_pdm_retcode_Type (*dmac_enable)(struct metal_pdm *pdm, int32_t enable);
    int32_t (*status)(struct metal_pdm *pdm, enum_pdm_int_flags_Type check);
    enum_pdm_retcode_Type (*status_clear)(struct metal_pdm *pdm, enum_pdm_int_flags_Type check);
    uint32_t (*status_all)(struct metal_pdm *pdm);
    enum_pdm_retcode_Type (*status_clear_all)(struct metal_pdm *pdm);
    enum_pdm_retcode_Type (*interrupt_enable)(struct metal_pdm *pdm, int32_t enable);
	enum_pdm_retcode_Type (*set_dma_adr)(struct metal_pdm *pdm, uint32_t dma_number, uint32_t adr);
};

/**
 * @brief A handle for a PDM device
 */
struct metal_pdm {
    const struct metal_pdm_vtable *vtable;
};

/**
 * @brief Get a handle for a PDM device
 * @param[in] device_num The index of the desired PDM device
 * @return A handle to the PDM device, or NULL if the device does not exist
 */
struct metal_pdm *upt_pdm_get_device(uint32_t device_num);

/**
 * @brief Initialize PDM Hardware
 * @param[in] pdm The PDM handle
 * @param[in] pdm_config Configurations of a PDM
 * @remarks No return value
 */
__inline__ enum_pdm_retcode_Type upt_pdm_config(struct metal_pdm *pdm, struct metal_pdm_config *pdm_config) {
	                 pdm->vtable->cfg(pdm, pdm_config);
                     return E_PDM_SUCCESS;
}

/**
 * @brief Enable PDM core
 * @param[in] pdm c
 * @param[in] enable Enable/Disable PDM engine
 * @remarks No return value
 */
__inline__ enum_pdm_retcode_Type upt_pdm_enable(struct metal_pdm *pdm, bool enable) {
	                 pdm->vtable->core_enable(pdm, enable);
                     return E_PDM_SUCCESS;
}

/**
 * @brief Enable/Disable PDM interrupt
 * @param[in] pdm The handle for the PDM device
 * @param[in] enable Enable/Disable PDM interrupt ISR
 * @remarks No return value
 */
__inline__ enum_pdm_retcode_Type upt_pdm_isr_enable(struct metal_pdm *pdm, bool enable) {
	          pdm->vtable->interrupt_enable(pdm, enable);
	          return E_PDM_SUCCESS;
}

/**
 * @brief Enable/Disable PDM DMA control
 * @param[in] pdm The PDM handle
 * @param[in] enable Enable/Disable PDM DMA control
 * @remarks No return value
 */
__inline__ enum_pdm_retcode_Type upt_pdm_dma_enable(struct metal_pdm *pdm, bool enable) {
	         pdm->vtable->dmac_enable(pdm, enable);
	         return E_PDM_SUCCESS;
}

/**
 * @brief Set DMA watermark of PDM
 * @param[in] pdm The PDM handle
 * @param[in] watermark Threshold of DMA request
 * @remarks No return value
 */
__inline__ void upt_pdm_set_watermark(struct metal_pdm *pdm, enum_pdm_watermark_Type watermark) {
	/* No need to implement on this IP */
}

/**
 * @brief Get all status of PDM
 * @param[in] pdm The PDM handle
 * @return status of PDM
 */
__inline__ uint32_t upt_pdm_get_status(struct metal_pdm *pdm) {
	return pdm->vtable->status_all(pdm);
}

/**
 * @brief Clear all PDM status
 * @param[in] pdm The PDM handle
 * @remarks No return value
 */
__inline__ enum_pdm_retcode_Type upt_pdm_clear_status(struct metal_pdm *pdm) {
	pdm->vtable->status_clear_all(pdm);
	return E_PDM_SUCCESS;
}

/**
 * @brief Check specific status of PDM
 * @param[in] pdm The PDM handle
 * @param[in] check The status will be checked
 * @return status of PDM
 */
__inline__ uint32_t upt_pdm_check_status(struct metal_pdm *pdm, enum_pdm_int_flags_Type check) {
	return pdm->vtable->status(pdm, check);
}

/**
 * @brief Clear specific status of PDM
 * @param[in] pdm The PDM handle
 * @param[in] check The status will be cleared
 */
__inline__ enum_pdm_retcode_Type upt_pdm_clear_check_status(struct metal_pdm *pdm, enum_pdm_int_flags_Type check) {
	pdm->vtable->status_clear(pdm, check);
	return E_PDM_SUCCESS;
}

/**
 * @brief Read PDM data from FIFO
 * @param[in] pdm The PDM handle
 * @param[out] read_buf Read buffer
 * @param[in] read_buf_len Read buffer length
 * @remarks No return value
 */
__inline__ void upt_pdm_read_data(struct metal_pdm *pdm, uint32_t *read_buf, int32_t read_buf_len) {
	/* No need to implement on this IP */
}

__inline__ enum_pdm_retcode_Type upt_pdm_set_dma_adr(struct metal_pdm *pdm, uint32_t dma_number, uint32_t adr) {
	return pdm->vtable->set_dma_adr(pdm, dma_number, adr);
}

#endif  //METAL__PDM_H
