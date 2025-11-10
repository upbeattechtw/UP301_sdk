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
 * @file  i2s.h
 * @brief API for Integrated Inter-chip Sound
 */
#ifndef METAL__I2S_H
#define METAL__I2S_H
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Device number of I2S device
 * @ingroup UP301_Controller_I2S
 */
enum naon_i2s_select {
	  NAON_I2S_0      = 0,
	  NAON_I2S_1,
	  NAON_I2S_SLAVE_1
};

/*!
 * @brief i2s return error code.
 * @ingroup UP301_Metal constructors & destructors
 */
typedef enum enum_i2s_status{
    E_I2S_SUCCESS,       //Success.
    E_I2S_INVINIT,       //Initial fail or resource is unavailable.
    E_I2S_INVPARA,       //Invalid function parameter/argument.
    E_I2S_ERROR,         //Unspecific error.
} enum_i2s_retcode_Type;

/**
 * @brief Enums to set up I2S mode
 * @ingroup UP301_Controller_I2S
 */
typedef enum enum_i2s_mode_Type {
	i2s_tdm_master = 0,
	i2s_tdm_slave
}enum_i2s_mode_Type;

/**
 * @brief Enums to set up I2S Stream type
 * @ingroup UP301_Controller_I2S
 */
typedef enum enum_i2s_stream_Type {
	i2s_pcm_stream_playback = 0,
	i2s_pcm_stream_capture,
	i2s_pcm_stream_last = i2s_pcm_stream_capture,
}enum_i2s_stream_Type;

/**
 * @brief Enums to set up I2S data precision
 * @ingroup UP301_Controller_I2S
 */
typedef enum enum_i2s_format_Type {
	i2s_pcm_format_s16_le = 0,
	i2s_pcm_format_s24_le,
	i2s_pcm_format_s32_le
}enum_i2s_format_Type;

/**
 * @brief Enums to set up I2S audio channels
 * @ingroup UP301_Controller_I2S
 */
typedef enum enum_i2s_chan_nr_Type {
	i2s_2_channel_support 	= 2,	/* up to 2.0 */
	i2s_4_channel_support 	= 4,	/* up to 3.1 */
	i2s_6_channel_support	= 6,	/* up to 5.1 */
	i2s_8_channel_support	= 8		/* up to 7.1 */
}enum_i2s_chan_nr_Type;

/**
 * @brief Enums to set up I2S variance(TDM) slots
 * @ingroup UP301_Controller_I2S
 */
typedef enum enum_i2s_tdm_chan_nr_Type {
	tdm_none_slot_support		= 0,
	tdm_1_slot_support,
	tdm_2_slot_support,
	tdm_3_slot_support,
	tdm_4_slot_support,
	tdm_5_slot_support,
	tdm_6_slot_support,
	tdm_7_slot_support,
	tdm_8_slot_support
}enum_i2s_tdm_chan_nr_Type;

/**
 * @brief Enums to set up I2S variance(TDM) frame offset
 * @ingroup UP301_Controller_I2S
 */
typedef enum enum_i2s_tdm_frame_offset_Type {
	tdm_frame_offset_0 	= 0,	/* up to 2.0 */
	tdm_frame_offset_1
}enum_i2s_tdm_frame_offset_Type;

/**
 * @brief Enums to set up I2S watermark level
 * @ingroup UP301_Controller_I2S
 */
typedef enum enum_i2s_watermark_Type {
	i2s_watermark_1 	= 0,
	i2s_watermark_2,
	i2s_watermark_3,
	i2s_watermark_4,
	i2s_watermark_5,
	i2s_watermark_6,
	i2s_watermark_7,
	i2s_watermark_8,
	i2s_watermark_9,
	i2s_watermark_10,
	i2s_watermark_11,
	i2s_watermark_12,
	i2s_watermark_13,
	i2s_watermark_14,
	i2s_watermark_15,
	i2s_watermark_16

} enum_i2s_watermark_Type;

/** @brief Interrupt status: return value of upt_i2s_get_status() */
#define i2s_txfo 		(0x1U << 5)
/** @brief Interrupt status: return value of upt_i2s_get_status() */
#define i2s_txfe 		(0x1U << 4)
/** @brief Interrupt status: return value of upt_i2s_get_status() */
#define i2s_rxfo		(0x1U << 1)
/** @brief Interrupt status: return value of upt_i2s_get_status() */
#define i2s_rxda		(0x1U << 0)

struct metal_i2s;
struct metal_i2s_vtable {
	enum_i2s_retcode_Type (*config)(struct metal_i2s *i2s,
    			                    enum_i2s_format_Type param_format,
				                    enum_i2s_chan_nr_Type param_chan_nr,
				                    enum_i2s_stream_Type stream);
	enum_i2s_retcode_Type (*flush)(struct metal_i2s *i2s);

    int32_t (*get_isr_status)(struct metal_i2s *i2s);

    uint32_t (*clear_isr_status)(struct metal_i2s *i2s);

    enum_i2s_retcode_Type (*tx)(struct metal_i2s *i2s,
    		                    uint32_t *l_ch,
                                int32_t l_len,
                                uint32_t *r_ch,
                                int32_t r_len);

    enum_i2s_retcode_Type (*rx)(struct metal_i2s *i2s,
                                uint32_t *l_ch,
                                int32_t l_len,
                                uint32_t *r_ch,
                                int32_t r_len);

    enum_i2s_retcode_Type (*start)(struct metal_i2s *i2s);

    enum_i2s_retcode_Type (*stop)(struct metal_i2s *i2s);

    enum_i2s_retcode_Type (*interrupt_enable)(struct metal_i2s *i2s,
    						 int32_t enable);

    enum_i2s_retcode_Type (*dma_enable)(struct metal_i2s *i2s,
    				       int32_t enable);

    enum_i2s_retcode_Type (*tdm_config)(struct metal_i2s *i2s,
    				                    enum_i2s_format_Type param_format,
					                    enum_i2s_tdm_chan_nr_Type param_slot_nr,
					                    enum_i2s_tdm_frame_offset_Type param_frame_offset,
					                    enum_i2s_stream_Type stream);

    enum_i2s_retcode_Type (*tdm_tx)(struct metal_i2s *i2s,
    			                    int32_t slot_num,
				                    uint32_t *data,
				                    int32_t data_len);

    enum_i2s_retcode_Type (*tdm_rx)(struct metal_i2s *i2s,
    			       int32_t slot_num,
				       uint32_t *data,
				       int32_t data_len);

    enum_i2s_retcode_Type (*set_watermark)(struct metal_i2s *i2s,
    				   enum_i2s_watermark_Type tx_watermark,
					   enum_i2s_watermark_Type rx_watermark);
};

/**
 * @brief Handle for a I2S engine
 */
struct metal_i2s {
    const struct metal_i2s_vtable *vtable;
};

/**
 * @brief Get a handle for a I2S
 * @param[in] device_num Device_num The index of the desired I2S device
 * @return A handle to the I2S, or NULL if the engine does not exist
 */
struct metal_i2s *upt_i2s_get_device(uint32_t device_num);

/**
 * @brief Configure I2S function
 * @param[in] i2s The I2S handle
 * @param[in] param_format UPT_PCM_FORMAT_S16_LE/UPT_PCM_FORMAT_S24_LE/UPT_PCM_FORMAT_S32_LE
 * @param[in] param_chan_nr 2, 4, 6 or 8 channels
 * @param[in] stream UPT_PCM_STREAM_PLAYBACK (TX) or UPT_PCM_STREAM_CAPTURE (RX)
 * @remarks No return value
 */
__inline__ enum_i2s_retcode_Type upt_i2s_config(struct metal_i2s *i2s,
		                       enum_i2s_mode_Type mode,
							   enum_i2s_format_Type param_format,
							   enum_i2s_chan_nr_Type param_chan_nr,
							   enum_i2s_stream_Type stream) {
    i2s->vtable->config(i2s,
    					param_format,
						param_chan_nr,
						stream);
           return E_I2S_SUCCESS;
}

/**
 * @brief Configure TDM function
 * @param[in] i2s The TDM handle
 * @param[in] param_format UPT_PCM_FORMAT_S16_LE/UPT_PCM_FORMAT_S24_LE/UPT_PCM_FORMAT_S32_LE
 * @param[in] param_slot_nr number of slots
 * @param[in] param_frame_offset TDM interface offset, 0 or 1
 * @param[in] stream UPT_PCM_STREAM_PLAYBACK (TX) or UPT_PCM_STREAM_CAPTURE (RX)
 * @remarks No return value
 */
__inline__ enum_i2s_retcode_Type upt_i2s_tdm_config(struct metal_i2s *i2s,
	                 	           enum_i2s_mode_Type mode,
								   enum_i2s_format_Type param_format,
								   enum_i2s_tdm_chan_nr_Type param_slot_nr,
								   enum_i2s_tdm_frame_offset_Type param_frame_offset,
								   enum_i2s_stream_Type stream) {
	i2s->vtable->tdm_config(i2s,
							param_format,
							param_slot_nr,
							param_frame_offset,
							stream);
	return E_I2S_SUCCESS;
}

/**
 * @brief Enable/Disable I2S/TDM Hardware
 * @param[in] i2s The I2S handle
 * @param[in] enable Enable/disable I2S/TDM Hardware
 * @remarks No return value
 */
__inline__ enum_i2s_retcode_Type upt_i2s_enable(struct metal_i2s *i2s,
							   bool enable) {
	if(enable) {
		i2s->vtable->flush(i2s);
		i2s->vtable->start(i2s);
	}else {
		i2s->vtable->stop(i2s);
	}
	return E_I2S_SUCCESS;
}

/**
 * @brief Enable/Disable I2S interrupt
 * @param[in] i2d The I2S handle
 * @param[in] enable Enable/disable I2S ISR
 * @remarks No return value
 */
__inline__ enum_i2s_retcode_Type upt_i2s_isr_enable(struct metal_i2s *i2s,
								   bool enable) {
    i2s->vtable->interrupt_enable(i2s, enable);
    return E_I2S_SUCCESS;
}

/**
 * @brief Enable/Disable I2S/TDM DMA control
 * @param[in] i2s The I2S handle
 * @param[in] enable Enable/disable I2S DMA control
 * @remarks No return value
 */
__inline__ enum_i2s_retcode_Type upt_i2s_dma_enable(struct metal_i2s *i2s,
								   bool enable) {
    i2s->vtable->dma_enable(i2s, enable);
    return E_I2S_SUCCESS;
}

/**
 * @brief Set DMA watermark of I2S
 * @param[in] i2s The I2S handle
 * @param[in] watermark Threshold of DMA request
 * @remarks No return value
 */
__inline__ enum_i2s_retcode_Type upt_i2s_set_watermark(struct metal_i2s *i2s,
									  enum_i2s_watermark_Type watermark) {
	i2s->vtable->set_watermark(i2s, watermark, watermark);
	return E_I2S_SUCCESS;
}

/**
 * @brief Get all status of I2S
 * @param[in] i2s The I2S handle
 * @return Status of I2S
 */
__inline__ uint32_t upt_i2s_get_status(struct metal_i2s *i2s) {
    return i2s->vtable->get_isr_status(i2s);
}

/**
 * @brief Clear all status of
 * @param[in] i2s The I2S handle
 * @remarks No return value
 */
__inline__ enum_i2s_retcode_Type upt_i2s_clear_status(struct metal_i2s *i2s) {
    i2s->vtable->clear_isr_status(i2s);
    return E_I2S_SUCCESS;
}

/**
 * @brief Send i2s audio data to FIFO
 * @param[in] i2s The I2S handle
 * @param[in] l_ch Left channel data to be send
 * @param[in] l_len Left channel data length
 * @param[in] r_ch Right channel data to be send
 * @param[in] r_len Right channel data length
 * @remarks No return value
 */
__inline__ enum_i2s_retcode_Type upt_i2s_tx(struct metal_i2s *i2s,
						   uint32_t *l_ch,
						   int32_t l_len,
						   uint32_t *r_ch,
						   int32_t r_len) {
    i2s->vtable->tx(i2s, l_ch, l_len, r_ch, r_len);
    return E_I2S_SUCCESS;
}

/*! @brief Receive i2s audio data from FIFO
 * @param i2s The I2S handle
 * @param[out] l_ch Left channel buffer
 * @param[in] l_len Left channel buffer length
 * @param[out] r_ch Right channel buffer
 * @param[in] r_len Right channel buffer length
 * @remarks No return value
 */
__inline__ enum_i2s_retcode_Type upt_i2s_rx(struct metal_i2s *i2s,
						   uint32_t *l_ch,
						   int32_t l_len,
						   uint32_t *r_ch,
						   int32_t r_len) {
	i2s->vtable->rx(i2s, l_ch, l_len, r_ch, r_len);
	return E_I2S_SUCCESS;
}

/**
 * @brief Send TDM audio data to FIFO
 * @param[in] i2s The I2S handle
 * @param[in] slot_num Number of slots
 * @param[in] data Audio data to be transfer
 * @param[in] data_len Audio data length
 * @remarks No return value
 */
__inline__ enum_i2s_retcode_Type upt_i2s_tdm_tx(struct metal_i2s *i2s,
							   int32_t slot_num,
							   uint32_t *data,
							   int32_t data_len) {
	i2s->vtable->tdm_tx(i2s, slot_num, data, data_len);
	return E_I2S_SUCCESS;
}

/**
 * @brief Send TDM audio data from FIFO
 * @param[in] i2s The I2S handle
 * @param[in] slot_num Number of slots
 * @param[out] data Audio data to be received
 * @param[in] data_len Audio data length
 * @remarks No return value
 */
__inline__ enum_i2s_retcode_Type upt_i2s_tdm_rx(struct metal_i2s *i2s,
							   int32_t slot_num,
							   uint32_t *data,
							   int32_t data_len) {
	i2s->vtable->tdm_rx(i2s, slot_num, data, data_len);
	return E_I2S_SUCCESS;
}

#endif
