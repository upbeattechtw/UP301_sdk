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

/**
 * @file  spi.h
 * @brief API for Serial Peripheral Interface
 */
#ifndef METAL__SPI_H
#define METAL__SPI_H
#include <stdbool.h>
#include <stdint.h>

#define SPI_TIMEOUT_US 10000

/**
 * @brief Device number of SPI controller
 * @ingroup UP301_Controller_SPI
 */
typedef enum enum_spi_device {
	NAON_SPI_0		= 0,
	NAON_SPI_SLAVE_0,
	NAON_SPI_1,
	NAON_SPI_2,
	NAON_SPI_3,
	AON_SPI_0,
	AON_SPI_1,
	SPI_DEVICE_NUMBER_LAST
} enum_spi_device_Type;

/**
 * @brief Enums to set up SPI master/slave
 * @ingroup UP301_Controller_SPI
 */
typedef enum enum_spi_type {
	spi_slave = 0,
	spi_master
} enum_spi_type_Type;

typedef enum Transfer_Mode
{
	Transmit_Receive = 0,
	Transmit_Only,
	Receive_Only,
	EEPROM_read
}Tmode_Type;

/**
 * @brief Enums to set SPI CPOL/CPHA
 * @ingroup UP301_Controller_SPI
 */
typedef enum enum_spi_mode {
	spi_mode_0 = 0,
	spi_mode_1,
	spi_mode_2,
	spi_mode_3
} enum_spi_mode_Type;

/**
 * @brief Enums to speed mode
 * @ingroup UP301_Controller_SPI
 */
typedef enum enum_spi_speed {
	spi_1M_speed = 0,		// AON: Actually 0.9216Mhz, NAON: Actually 0.9963Mhz
	spi_2M_speed,			// AON: Actually 1.8432Mhz, NAON: Actually 1.9749Mhz
	spi_5M_speed,			// AON: Actually 5.5296Mhz, NAON: Actually 4.8083Mhz
	spi_10M_speed			// AON: Can't use this mode, NAON: Actually 9.2160Mhz
} enum_spi_speed_Type;

/**
 * @brief SPI DMA mode selection
 * @ingroup UP301_Controller_SPI
 */
typedef enum enum_spi_dma_mode {
	spi_dma_disable		= 0,
	spi_dma_tx_enable,
	spi_dma_rx_enable,
	spi_dma_txrx_enable
} enum_spi_dma_mode_Type;

/**
 * @brief SPI slave mode enable
 * @ingroup UP301_Controller_SPI
 */
typedef enum enum_spi_act {
	spi_disable		= 0,
	spi_enable
} enum_spi_act_Type;

/**
 * @brief SPI FIFO watermark level
 * @ingroup UP301_Controller_SPI
 */
typedef enum enum_spi_watermark {
	spi_watermark_1		= 0,
	spi_watermark_2		= 1,
	spi_watermark_3		= 2,
	spi_watermark_4		= 3,
	spi_watermark_5		= 4,
	spi_watermark_6		= 5,
	spi_watermark_7		= 6,
	spi_watermark_8		= 7
} enum_spi_watermark_Type;

typedef enum enum_spi_retcode {
    E_SPI_SUCCESS,     // Success.
	E_SPI_INVINIT,	 	// Initial fail or resource is unavailable.
	E_SPI_INVPARA,	 	// Invalid function parameter/argument.
	E_SPI_TIMEOUT,		// Timeout
    E_SPI_ERROR     	// Unspecific error.
} enum_spi_retcode_Type;

/** @brief Interrupt status: return value of upt_spi_get_status() */
#define spi_txeis						(0x1U << 0)	/* TX fifo empty */
/** @brief Interrupt status: return value of upt_spi_get_status() */
#define spi_txois						(0x1U << 1)	/* TX fifo overflow */
/** @brief Interrupt status: return value of upt_spi_get_status() */
#define spi_rxuis						(0x1U << 2)	/* RX fifo underflow */
/** @brief Interrupt status: return value of upt_spi_get_status() */
#define spi_rxois						(0x1U << 3)	/* RX fifo overflow */
/** @brief Interrupt status: return value of upt_spi_get_status() */
#define spi_rxfis						(0x1U << 4)	/* RX fifo full */
/** @brief Interrupt status: return value of upt_spi_get_status() */
#define spi_mstis						(0x1U << 5)	/* multi-master contention status */

typedef struct metal_spi_config {
    /** This IP will active in master or slave */
    uint32_t master : 1;
    /** The polarity of the SPI transfer, equivalent to CPOL */
    uint32_t polarity : 1;
    /** The phase of the SPI transfer, equivalent to CPHA */
    uint32_t phase : 1;
    /** The spi clock divider */
    uint32_t clk_div;
    /** The spi RX fifo */
    uint32_t spi_rxfifo;
    /** The spi RX fifo */
    uint32_t spi_txfifo;
} metal_spi_config_Type;

/**
 * @brief A handle for a SPI device
 **/
typedef struct metal_spi {
    const struct __metal_spi_vtable *vtable;
} metal_spi_Type;

struct __metal_spi_vtable {
    enum_spi_retcode_Type (*init)(metal_spi_Type *spi, metal_spi_config_Type *spi_config);
    enum_spi_retcode_Type (*transfer)(metal_spi_Type *spi, uint8_t *tx_buf, int16_t tx_len, uint8_t *rx_buf, int16_t rx_len, int16_t slave_num);
	enum_spi_retcode_Type (*set_mode)(metal_spi_Type *spi, enum_spi_mode_Type mode);
    enum_spi_retcode_Type (*interrupt_enable)(metal_spi_Type *spi, uint32_t enable_evt);
    enum_spi_retcode_Type (*dma_enable)(metal_spi_Type *spi, enum_spi_dma_mode_Type mode);
    enum_spi_retcode_Type (*set_watermark)(metal_spi_Type *spi, enum_spi_watermark_Type watermark);
	enum_spi_retcode_Type (*configure)(metal_spi_Type *spi, int16_t slave_num, Tmode_Type mode);
    uint32_t (*raw_status)(metal_spi_Type *spi);
	uint32_t (*get_status_register)(metal_spi_Type *spi);
    uint32_t (*clear_status)(metal_spi_Type *spi);
    enum_spi_retcode_Type (*read_fifo)(metal_spi_Type *spi, uint8_t *read_buf, int16_t read_buf_len);
    enum_spi_retcode_Type (*write_fifo)(metal_spi_Type *spi, uint8_t *send_buf, int16_t send_buf_len);
	enum_spi_retcode_Type (*write_dummy)(metal_spi_Type *spi, int16_t send_buf_len);
    enum_spi_retcode_Type (*spi_enable)(metal_spi_Type *spi, enum_spi_act_Type mode);
	enum_spi_retcode_Type (*set_timeout_us)(metal_spi_Type *spi, uint64_t timeout_us);
	uint64_t (*get_timeout_us) (metal_spi_Type *spi);
};

/**
 * @brief Get a handle for a SPI device
 * @param[in] device_num The index of the desired SPI device
 * @return A handle to the SPI device, or NULL if the device does not exist
 **/
metal_spi_Type *upt_spi_get_device(uint16_t device_num);

/**
 * @brief Initialize a SPI device with a certain baud rate
 * @param[in] spi The SPI handle
 * @param[in] type Master or Slave usage
 * @param[in] mode CPOL and CPHA
 * @param[in] speed_mode SPI speed
 * @return 0 if the initialize succeeds
 */
__inline__ enum_spi_retcode_Type upt_spi_init(metal_spi_Type *spi, enum_spi_type_Type type, enum_spi_mode_Type mode, enum_spi_speed_Type speed_mode) {
	metal_spi_config_Type spi_config = {0};
	int16_t i = 0;

	for(i = 0; i < SPI_DEVICE_NUMBER_LAST; i++) {
		if( spi == upt_spi_get_device(i))
			break;
		else if ( i == AON_SPI_1)
			return E_SPI_INVINIT;
	}

	// AON SPI src_clock = 11.0592MHz, clk_div only set even number
	if(i > NAON_SPI_3) {
		if (speed_mode == spi_1M_speed ) {spi_config.clk_div = 12;}
		if (speed_mode == spi_2M_speed ) {spi_config.clk_div = 6;}
		if (speed_mode == spi_5M_speed ) {spi_config.clk_div = 2;}
		if (speed_mode == spi_10M_speed )
			return E_SPI_INVPARA;
	}
	// NAON SPI src_clock = 221.184MHz, clk_div only set even number
	else {
		if (speed_mode == spi_1M_speed ) {spi_config.clk_div = 222;}
		if (speed_mode == spi_2M_speed ) {spi_config.clk_div = 112;}
		if (speed_mode == spi_5M_speed ) {spi_config.clk_div = 46;}
		if (speed_mode == spi_10M_speed ) {spi_config.clk_div = 24;}
	}

	// Master or slave
	spi_config.master = type;

	// Set SPI mode
	if( mode == spi_mode_0 ) {
		spi_config.polarity = 0;
		spi_config.phase = 0;
	} else if( mode == spi_mode_1 ) {
		spi_config.polarity = 0;
		spi_config.phase = 1;
	} else if( mode == spi_mode_2 ) {
		spi_config.polarity = 1;
		spi_config.phase = 0;
	} else /*if( mode == spi_mode_3 )*/ {
		spi_config.polarity = 1;
		spi_config.phase = 1;
	}

	spi_config.spi_rxfifo = spi_watermark_4;
	spi_config.spi_rxfifo = spi_watermark_4;

    return spi->vtable->init(spi, &spi_config);
}

__inline__ enum_spi_retcode_Type upt_spi_set_mode(metal_spi_Type *spi, enum_spi_mode_Type mode) {
    return spi->vtable->set_mode(spi, mode);
}

__inline__ enum_spi_retcode_Type upt_spi_configure(metal_spi_Type *spi, int16_t slave_num, Tmode_Type mode) {
    return spi->vtable->configure(spi, slave_num, mode);
}

/**
 * @brief Perform a SPI transfer
 * @param[in] spi The SPI handle
 * @param[in] txbuf The data buffer to be transmitted over SPI bus
 * @param[in] txlen The number of bytes to write over SPI
 * @param[out] rxbuf The buffer to store data received over SPI bus
 * @param[in] rxlen The number of bytes to read over SPI
 * @param[in] slave_num the selected slave of SPI transfer
 * @return 0 if the transfer succeeds
 */
__inline__ enum_spi_retcode_Type upt_spi_transfer(metal_spi_Type *spi, uint8_t *txbuf, int16_t txlen, uint8_t *rxbuf, int16_t rxlen, int16_t slave_num) {
    return spi->vtable->transfer(spi, txbuf, txlen, rxbuf, rxlen, slave_num);
}

/**
 * @brief Enable/Disable SPI interrupt
 * @param[in] spi The SPI handle
 * @param[in] enable_evt Enable/Disable SPI interrupt
 */
__inline__ enum_spi_retcode_Type upt_spi_isr_enable(metal_spi_Type *spi, uint32_t enable_evt) {
    return spi->vtable->interrupt_enable(spi, enable_evt);
}

/**
 * @brief Enable/disable DMA bit.
 * @param[in] spi The SPI handle
 * @param[in] mode DMA mode
 * @remarks No return value
 */
__inline__ enum_spi_retcode_Type upt_spi_dma_enable(metal_spi_Type *spi, enum_spi_dma_mode_Type mode) {
	return spi->vtable->dma_enable(spi, mode);
}

/**
 * @brief Set DMA/interrupt watermark of SPI
 * @param[in] spi The SPI handle
 * @param[in] watermark Threshold of DMA request
 * @remarks No return value
 */
__inline__ enum_spi_retcode_Type upt_spi_set_watermark(metal_spi_Type *spi, enum_spi_watermark_Type watermark) {
	return spi->vtable->set_watermark(spi, watermark);
}

/**
 * @brief Get interrupt status of SPI
 * @param[in] spi The SPI handle
 * @return Status of SPI
 */
__inline__ uint32_t upt_spi_get_status(metal_spi_Type *spi) {
	return spi->vtable->raw_status(spi);
}

/**
 * @brief Get status register SPI
 * @param[in] spi The SPI handle
 * @return Status of SPI
 */
__inline__ uint32_t upt_spi_get_status_register(metal_spi_Type *spi) {
	return spi->vtable->get_status_register(spi);
}

/**
 * @brief Clear interrupt status of SPI
 * @param[in] spi The SPI handle
 * @remarks No return value
 */
__inline__ uint32_t upt_spi_clear_status(metal_spi_Type *spi) {
	return spi->vtable->clear_status(spi);
}

/**
 * @brief Read data from SPI
 * @param[in] spi The SPI handle
 * @param[out] read_buf Read buffer
 * @param[in] read_buf_len Read buffer length
 * @remarks No return value
 */
__inline__ enum_spi_retcode_Type upt_spi_read_data(metal_spi_Type *spi, uint8_t *read_buf, int16_t read_buf_len) {
	return spi->vtable->read_fifo(spi, read_buf, read_buf_len);
}

/**
 * @brief Send data to SPI
 * @param[in] spi The SPI handle
 * @param[in] send_buf Send buffer
 * @param[in] send_buf_len Send buffer length
 * @remarks No return value
 */
__inline__ enum_spi_retcode_Type upt_spi_send_data(metal_spi_Type *spi, uint8_t *send_buf, int16_t send_buf_len) {
	return spi->vtable->write_fifo(spi, send_buf, send_buf_len);
}

__inline__ enum_spi_retcode_Type upt_spi_send_dummy(metal_spi_Type *spi, int16_t send_buf_len) {
	return spi->vtable->write_dummy(spi, send_buf_len);
}

__inline__ enum_spi_retcode_Type upt_spi_enable(metal_spi_Type *spi, enum_spi_act_Type mode) {
	return spi->vtable->spi_enable(spi, mode);
}

/**
 * @brief set SPI timeout us
 * @param[in] spi The SPI handle
 * @param[in] timeout SPI timeout us
 * @remarks No return value
 */
__inline__ enum_spi_retcode_Type upt_spi_set_timeout_us(metal_spi_Type *spi, uint64_t timeout_us) {
	return spi->vtable->set_timeout_us(spi, timeout_us);
}

/**
 * @brief get SPI timeout us
 * @param[in] spi The SPI handle
 * @remarks SPI timeout us
 */
__inline__ uint64_t upt_spi_get_timeout_us(metal_spi_Type *spi) {
	return spi->vtable->get_timeout_us(spi);
}


#endif
