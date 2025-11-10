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
 * @file  i2c.h
 * @brief API for Inter-Integrated Circuit
 */
#ifndef METAL__I2C_H
#define METAL__I2C_H
#include <stdbool.h>
#include <stdint.h>

#include "metal-platform.h"

#define I2C_TIMEOUT_US 10000
/**
 * @brief Device number of I2C controller
 * @ingroup UP301_Controller_I2C
 */
typedef enum enum_i2c_device {
	NAON_I2C_0		= 0,
	NAON_I2C_1,
	NAON_I2C_2,
	NAON_I2C_3,
	NAON_I2C_4,
	NAON_I2C_5,
	NAON_I2C_6,
	AON_I2C_0,
	AON_I2C_1,
	AON_I2C_2,
	AON_I2C_3,
	AON_I2C_4,
	I2C_DEVICE_NUMBER_LAST
} enum_i2c_device_Type;

/**
 * @brief Enums to set up I2C device modes
 * @ingroup UP301_Controller_I2C
 */
typedef enum metal_i2c_mode {
	i2c_slave = 0,
	i2c_master
} metal_i2c_mode_Type;

/**
 * @brief Enums to speed mode
 * @ingroup UP301_Controller_I2C
 */
typedef enum enum_i2c_speed {
	i2c_standard = 0,		// 100K
	i2c_fast,				// 400K
	i2c_fast_plus,		// 1M
	i2c_highspeed,		// 3.4M
} enum_i2c_speed_Type;

/**
 * @brief Enums to enable/disable stop condition
 * @ingroup UP301_Controller_I2C
 */
typedef enum enum_i2c_stop_bit {
    i2c_stop_disable = 0,
    i2c_stop_enable = 1
} enum_i2c_stop_bit_Type;

/**
 * @brief Enums to enable/disable restart condition
 * @ingroup UP301_Controller_I2C
 */
typedef enum enum_i2c_restart_bit {
    i2c_restart_disable = 0,
    i2c_restart_enable = 1
} enum_i2c_restart_bit_Type;


/**
 * @brief I2C DMA mode selection
 * @ingroup UP301_Controller_I2C
 */
typedef enum enum_i2c_dma_mode {
	i2c_dma_disable		= 0,
	i2c_dma_tx_enable,
	i2c_dma_rx_enable,
	i2c_dma_txrx_enable
} enum_i2c_dma_mode_Type;

/**
 * @brief I2C FIFO watermark level
 * @ingroup UP301_Controller_I2C
 */
typedef enum enum_i2c_watermark {
	i2c_watermark_1		= 0,
	i2c_watermark_2,
	i2c_watermark_3,
	i2c_watermark_4,
	i2c_watermark_5,
	i2c_watermark_6,
	i2c_watermark_7,
	i2c_watermark_8
} enum_i2c_watermark_Type;

typedef enum enum_i2c_retcode{
   E_I2C_SUCCESS,     // Success.
   E_I2C_INVINIT,	 	// Initial fail or resource is unavailable.
   E_I2C_INVPARA,	 	// Invalid function parameter/argument.
   E_I2C_TIMEOUT,       // Timeout
   E_I2C_ERROR,     	// Unspecific error.
} enum_i2c_retcode_Type;

/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_rx_under 						(0x1U << 0)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_rx_over				 		(0x1U << 1)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_rx_full						(0x1U << 2)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_tx_over						(0x1U << 3)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_tx_empty			 			(0x1U << 4)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_rd_req				 		(0x1U << 5)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_tx_abrt						(0x1U << 6)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_rx_done						(0x1U << 7)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_activity			 			(0x1U << 8)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_stop_det				 		(0x1U << 9)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_start_det						(0x1U << 10)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_gen_call						(0x1U << 11)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_restart_det 					(0x1U << 12)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_master_on_hold		 		(0x1U << 13)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_scl_stuck_at_low				(0x1U << 14)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_wr_req						(0x1U << 15)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_slv_addr1_tag		 			(0x1U << 16)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_slv_addr2_tag 				(0x1U << 17)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_slv_addr3_tag					(0x1U << 18)
/** @brief Interrupt status: return value of upt_i2c_get_status() */
#define i2c_r_slv_addr4_tag					(0x1U << 19)

/**
 * @brief A handle for a I2C device.
 */
typedef struct metal_i2c{
    const struct __metal_i2c_vtable *vtable;
} metal_i2c_Type;

struct __metal_i2c_vtable {
    enum_i2c_retcode_Type (*init)(metal_i2c_Type *i2c, enum_i2c_speed_Type speed_mode,
				uint16_t hcnt, uint16_t lcnt, uint16_t spklen,
				uint16_t hs_hcnt, uint16_t hs_lcnt, uint16_t hs_spklen,
                metal_i2c_mode_Type mode, bool addr_10bit_en);
	enum_i2c_retcode_Type (*set_slave_address) (metal_i2c_Type *i2c, uint16_t slave_address, bool _10_bit_enable);
    enum_i2c_retcode_Type (*set_slave)(metal_i2c_Type *i2c, uint16_t slave_addr);
    enum_i2c_retcode_Type (*fifo_thr)(metal_i2c_Type *i2c, int16_t tx_thr, int16_t rx_thr);
    enum_i2c_retcode_Type (*write)(metal_i2c_Type *i2c, uint16_t slave_addr, uint16_t len, uint8_t buf[],
				 	 enum_i2c_stop_bit_Type stop_bit);
    enum_i2c_retcode_Type (*read)(metal_i2c_Type *i2c, uint16_t slave_addr, uint16_t len, uint8_t buf[],
				enum_i2c_restart_bit_Type restart_bit);
    bool (*check_status_idle)(metal_i2c_Type *i2c);
	enum_i2c_retcode_Type (*enable)(metal_i2c_Type *i2c, bool enable);
	enum_i2c_retcode_Type (*read_nonblocking)(metal_i2c_Type *i2c, uint16_t len, enum_i2c_restart_bit_Type restart_bit, enum_i2c_stop_bit_Type stop_bit);
    enum_i2c_retcode_Type (*read_ready)(metal_i2c_Type *i2c, uint16_t len, enum_i2c_restart_bit_Type restart_bit);
    enum_i2c_retcode_Type (*read_end)(metal_i2c_Type *i2c, uint16_t len);
    enum_i2c_retcode_Type (*transfer)(metal_i2c_Type *i2c, uint16_t slave_addr,
                    uint8_t txbuf[], uint16_t txlen, uint8_t rxbuf[], uint16_t rxlen, int16_t restart_enable);
	enum_i2c_retcode_Type (*interrupt_enable)(metal_i2c_Type *i2c, uint32_t enable_evt);
    enum_i2c_retcode_Type (*dma_thr_level)(metal_i2c_Type *i2c, int16_t tx_thr, int16_t rx_thr);
    enum_i2c_retcode_Type (*dma_enable)(metal_i2c_Type *i2c, int16_t tx_dma_en, int16_t rx_dma_en);
	uint32_t (*get_status_register)(metal_i2c_Type *i2c);
    uint32_t (*get_status)(metal_i2c_Type *i2c);
    uint32_t (*clear_status)(metal_i2c_Type *i2c);
    enum_i2c_retcode_Type (*read_data)(metal_i2c_Type *i2c, uint8_t *read_buf, int16_t read_buf_len);
    enum_i2c_retcode_Type (*send_data)(metal_i2c_Type *i2c, uint8_t *send_buf, int16_t send_buf_len, enum_i2c_stop_bit_Type stop_bit);
	enum_i2c_retcode_Type (*set_timeout_us)(metal_i2c_Type *i2c, uint64_t timeout_us);
	uint64_t (*get_timeout_us) (metal_i2c_Type *i2c);
};



/**
 * @brief Get a handle for a I2C device.
 * @param[in] device_num The index of the desired I2C device.
 * @return A handle to the I2C device, or NULL if the device does not exist.
 */
metal_i2c_Type *upt_i2c_get_device(uint16_t device_num);

/**
 * @brief Initialize a I2C device with a certain baud rate.
 * @param[in] i2c The I2C handle
 * @param[in] speed_mode I2C speed
 * @param[in] mode I2C device is master or slave
 * @param[in] addr_10bit_en Enable 10-bit addressing mode
 * @return 0 if the initialize succeeds
 */
__inline__ enum_i2c_retcode_Type upt_i2c_init(metal_i2c_Type *i2c, enum_i2c_speed_Type speed_mode,
                        	metal_i2c_mode_Type mode, bool addr_10bit_en) {
	int16_t i = 0;
	uint16_t hcnt = 0, lcnt = 0, spklen= 1, hs_hcnt = 27, hs_lcnt = 32, hs_spklen = 3;

	for(i = 0; i < I2C_DEVICE_NUMBER_LAST; i++) {
		if( i2c == upt_i2c_get_device(i))
			break;
		else if (i == I2C_DEVICE_NUMBER_LAST)
			return E_I2C_INVINIT;
	}

	//TODO: To set I2C push pull mode, use SCU function call instead
	// Configure the I2C SCL Push-pull mode
	if(speed_mode == i2c_highspeed) {
		*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_MISCCTRL) |= (0x1 << (4 + i));
	}
	else {
		*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_MISCCTRL) &= ~(0x1 << (4 + i));
	}

	// AON I2C src_clock = 11.0592MHz  => 90ns
	// speed mode: 100K => 10000ns, 400K => 2500ns, 1M => 1000ns, 3.4M => 294ns
	// speed mode / 90ns = HCNT(minimum value is 5) + SPKL(1) + 3 +LCNT(minimum value is 6)
	if(i > NAON_I2C_6) {
		if (speed_mode == i2c_standard) {hcnt = 52; lcnt = 55; }
		else if (speed_mode == i2c_fast) {hcnt = 9; lcnt = 14; }
		else if (speed_mode == i2c_fast_plus) {hcnt = 1; lcnt = 6; }
		else 
			return E_I2C_INVINIT;
 	}
	// NAON I2C src_clock = 221.184MHz => 4.5ns
	// speed mode: 100K => 10000ns, 400K => 2500ns, 1M => 1000ns, 3.4M => 294ns
	// speed mode / 4.5ns = HCNT(minimum value is 5) + SPKL(1) + 3 +LCNT(minimum value is 6)
	else {
		if (speed_mode == i2c_standard) {hcnt = 1085; lcnt = 1104; spklen = 12;}
		if (speed_mode == i2c_fast) {hcnt = 255; lcnt = 275; spklen = 12;}
		if (speed_mode == i2c_fast_plus) {hcnt = 89; lcnt = 109; spklen = 12;}
		if (speed_mode == i2c_highspeed) {hcnt = 97; lcnt = 109; spklen = 12;
										  hs_hcnt = 27; hs_lcnt = 32; hs_spklen = 3;}
	}
    return i2c->vtable->init(i2c, speed_mode,hcnt, lcnt, spklen,
					  		hs_hcnt, hs_lcnt, hs_spklen,
					  		mode, addr_10bit_en);
}

/**
 * @brief set the I2C slave address value
 * @param[in] i2c The I2C handler
 * @param[in] slave_address I2C slave address
 * @param[in] _10_bit_Enable enable 10bit addressing mode
 */
__inline__ enum_i2c_retcode_Type upt_i2c_set_slave_address(metal_i2c_Type *i2c, uint16_t slave_address, bool _10_bit_enable) {
	return i2c->vtable->set_slave_address(i2c, slave_address, _10_bit_enable);
}

/**
 * @brief Preset I2C slave address
 * @param[in] i2c The I2C handle
 * @param[in] slave_addr I2C slave address
 */
__inline__ enum_i2c_retcode_Type upt_i2c_set_slave(metal_i2c_Type *i2c, uint32_t slave_addr) {
	return i2c->vtable->set_slave(i2c, slave_addr);
}

/**
 * @brief Perform a I2C write.
 * @param[in] i2c The I2C handle
 * @param[in] slave_addr I2C slave address
 * @param[in] len The number of bytes to transfer.
 * @param[in] buf The buffer to send over the I2C bus and must be len bytes long
 * @param[in] stop_bit Enable/disable STOP condition
 * @return 0 if write command is successfully executed
 */
__inline__ enum_i2c_retcode_Type upt_i2c_write(metal_i2c_Type *i2c, uint32_t slave_addr,
						 unsigned int len, uint8_t buf[], enum_i2c_stop_bit_Type stop_bit) {

    return i2c->vtable->write(i2c, slave_addr, len, buf, stop_bit);
}

/**
 * @brief Perform a I2C read.
 * @param[in] i2c The I2C handle
 * @param[in] slave_addr I2C slave address
 * @param[in] len The number of bytes to transfer.
 * @param[out] buf The buffer to store data from I2C bus and must be len bytes long
 * @param[in] restart_bit Enable/disable restart condition
 * @return 0 if read command is successfully executed
 */
__inline__ enum_i2c_retcode_Type upt_i2c_read(metal_i2c_Type *i2c, uint32_t slave_addr, uint16_t len,uint8_t buf[],
							enum_i2c_restart_bit_Type restart_bit) {

    return i2c->vtable->read(i2c, slave_addr, len, buf, restart_bit);
}


/**
 * @brief Perform the signal before I2C read.
 * @param[in] i2c The I2C handle
 * @param[in] len The number of bytes to transfer.
 * @param[in] restart_bit Enable/disable restart condition
 * @return 0 if read command is successfully executed
 */
__inline__ enum_i2c_retcode_Type upt_i2c_read_ready(metal_i2c_Type *i2c, uint16_t len, enum_i2c_restart_bit_Type restart_bit){

	return i2c->vtable->read_ready(i2c, len, restart_bit);
}

/**
 * @brief Perform the signal before I2C read.
 * @param[in] i2c The I2C handle
 * @param[in] len The number of bytes to transfer.
 * @return 0 if read command is successfully executed
 */
__inline__ enum_i2c_retcode_Type upt_i2c_read_end(metal_i2c_Type *i2c, uint16_t len){

	return i2c->vtable->read_end(i2c, len);
}

__inline__ enum_i2c_retcode_Type upt_i2c_enable(metal_i2c_Type *i2c, bool enable) {
	return i2c->vtable->enable(i2c, enable);
}

/**
 * @brief Perform a I2C read, put read commands in tx fifo.
 * @param[in] i2c The I2C handle
 * @param[in] len The number of bytes to transfer.
 * @param[in] restart_bit Enable/disable restart condition
 */

__inline__ enum_i2c_retcode_Type upt_i2c_read_nonblocking(metal_i2c_Type *i2c, uint16_t len, enum_i2c_restart_bit_Type restart_bit, enum_i2c_stop_bit_Type stop_bit) {

	return i2c->vtable->read_nonblocking(i2c, len, restart_bit, stop_bit);
}

/**
 * @brief check whether i2c is idle
 * @param[in] i2c The I2C handle
 */
__inline__ bool upt_i2c_check_status_idle(metal_i2c_Type *i2c) {
	return i2c->vtable->check_status_idle(i2c);
}
/**
 * @brief Performs back to back I2C write and read operations
 * @details if you use rxbuf to read data from rxfifo,don't use rxfifo to trigger interrupt.
 * @details Since you probably read data in your interrupt routine, the read in trnasfer has nothing to read you will stuck in this transfer function.
 * @param[in] i2c The I2C handle
 * @param[in] slave_addr I2C slave address
 * @param[in] txbuf The data buffer to be transmitted over I2C bus
 * @param[in] txlen The number of bytes to write over I2C
 * @param[out] rxbuf The buffer to store data received over I2C bus
 * @param[in] rxlen The number of bytes to read over I2C
 * @param[in] restart_enable Restart enable
 * @return 0 if the transfer succeeds
 */
__inline__ enum_i2c_retcode_Type upt_i2c_transfer(metal_i2c_Type *i2c, uint32_t slave_addr,
								uint8_t txbuf[], uint16_t txlen, uint8_t rxbuf[], uint16_t rxlen,
								int16_t restart_enable) {

    return i2c->vtable->transfer(i2c, slave_addr, txbuf, txlen, rxbuf, rxlen, restart_enable);
}

/**
 * @brief Enable/Disable I2C interrupt
 * @param[in] i2c The I2C handle
 * @param[in] enable_evt Enable event of I2C ISR
 */
__inline__ enum_i2c_retcode_Type upt_i2c_isr_enable(metal_i2c_Type *i2c, uint32_t enable_evt) {
	int16_t i;

	for(i = 0; i < I2C_DEVICE_NUMBER_LAST; i++) {
		if( i2c == upt_i2c_get_device(i))
			break;
		else if (i == AON_I2C_4)
			return E_I2C_INVINIT;
	}
	if (i > NAON_I2C_6) {
		// TODO: To enable E34 AON I2C interrupt, use SCU function call instead.
		*(volatile uint32_t *)(METAL_UP_SCU_20000000_BASE_ADDRESS + METAL_UP_SCU_E34IE) |= 0x1 << (20 + (i - AON_I2C_0));
	}
    return i2c->vtable->interrupt_enable(i2c, enable_evt);
}

/**
 * @brief Enable/disable DMA bit.
 * @param[in] i2c The I2C handle
 * @param[in] mode DMA mode
 * @remarks No return value
 */
__inline__ enum_i2c_retcode_Type upt_i2c_dma_enable(metal_i2c_Type *i2c, enum_i2c_dma_mode_Type mode) {
	if(mode == i2c_dma_disable)
    	return i2c->vtable->dma_enable(i2c, 0, 0);
	else if(mode == i2c_dma_tx_enable)
		return i2c->vtable->dma_enable(i2c, 1, 0);
	else if(mode == i2c_dma_rx_enable)
		return i2c->vtable->dma_enable(i2c, 0, 1);
	else if (mode == i2c_dma_txrx_enable)
		return i2c->vtable->dma_enable(i2c, 1, 1);
	else 
		return E_I2C_INVINIT;
}

/**
 * @brief Set DMA/interrupt watermark of I2C
 * @param[in] i2c The I2C handle
 * @param[in] watermark Threshold of DMA request
 * @remarks No return value
 */
__inline__ enum_i2c_retcode_Type upt_i2c_set_watermark(metal_i2c_Type *i2c, enum_i2c_watermark_Type watermark) {
    enum_i2c_retcode_Type ercode;

	ercode = i2c->vtable->dma_thr_level(i2c, watermark, watermark);
	if (ercode != E_I2C_SUCCESS)
		return ercode;

    ercode = i2c->vtable->fifo_thr(i2c, watermark, watermark);
	if (ercode != E_I2C_SUCCESS)
		return ercode;

	return E_I2C_SUCCESS;
}

/**
 * @brief Get status register of I2C
 * @param[in] i2c The I2C handle
 * @return Status of I2C
 */
__inline__ uint32_t upt_i2c_get_status_register(metal_i2c_Type *i2c) {
	return i2c->vtable->get_status_register(i2c);
}

/**
 * @brief Get interrupt status of I2C
 * @param[in] i2c The I2C handle
 * @return Status of I2C
 */
__inline__ uint32_t upt_i2c_get_status(metal_i2c_Type *i2c) {
	return i2c->vtable->get_status(i2c);
}

/**
 * @brief Clear interrupt status of I2C
 * @param[in] i2c The I2C handle
 * @remarks No return value
 */
__inline__ uint32_t upt_i2c_clear_status(metal_i2c_Type *i2c) {
	return i2c->vtable->clear_status(i2c);
}

/**
 * @brief Read data from I2C
 * @param[in] i2c The I2C handle
 * @param[out] read_buf Read buffer
 * @param[in] read_buf_len Read buffer length
 * @remarks No return value
 */
__inline__ enum_i2c_retcode_Type upt_i2c_read_data(metal_i2c_Type *i2c, uint8_t *read_buf, int16_t read_buf_len) {
	return i2c->vtable->read_data(i2c, read_buf, read_buf_len);
}

/**
 * @brief Send data to I2C
 * @param[in] i2c The I2C handle
 * @param[in] send_buf Send buffer
 * @param[in] send_buf_len Send buffer length
 * @param[in] send_stop_bit stop or not
 * @remarks No return value
 */
__inline__ enum_i2c_retcode_Type upt_i2c_send_data(metal_i2c_Type *i2c, uint8_t *send_buf, int16_t send_buf_len, enum_i2c_stop_bit_Type stop_bit) {
	return i2c->vtable->send_data(i2c, send_buf, send_buf_len, stop_bit);
}
/**
 * @brief set I2C timeout us
 * @param[in] i2c The I2C handle
 * @param[in] timeout I2C timeout us
 * @remarks No return value
 */
__inline__ enum_i2c_retcode_Type upt_i2c_set_timeout_us(metal_i2c_Type *i2c, uint64_t timeout_us) {
	return i2c->vtable->set_timeout_us(i2c, timeout_us);
}

/**
 * @brief get I2C timeout us
 * @param[in] i2c The I2C handle
 * @remarks I2C timeout us
 */
__inline__ uint64_t upt_i2c_get_timeout_us(metal_i2c_Type *i2c) {
	return i2c->vtable->get_timeout_us(i2c);
}

#endif
