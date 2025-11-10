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
 * @file  ospi.h
 * @brief API for Octal Serial Peripheral Interface
 */
#ifndef METAL_OSPI_H
#define METAL_OSPI_H
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Device number of OSPI engine
 * @ingroup UP301_Controller_OSPI
 */
typedef enum enum_ospi_device {
	NAON_OSPI = 0,
	OSPI_DEVICE_NUMBER_LAST
} enum_ospi_device_Type;

/**
 * @brief DLL delay phase
 * @ingroup UP301_Controller_OSPI
 */
typedef enum enum_ospi_dll_delay {
	ospi_dll_0_degree		= 0,
	ospi_dll_45_degree		= 0x8,
	ospi_dll_90_degree		= 0x10,
	ospi_dll_135_degree		= 0x18,
	ospi_dll_180_degree		= 0x20,
	ospi_dll_225_degree		= 0x28,
} enum_ospi_dll_delay_Type;

/**
 * @brief OSPI clock divider
 * @ingroup UP301_Controller_OSPI
 */
typedef enum enum_ospi_div {
	ospi_div_1 = 0,
	ospi_div_2,
	ospi_div_4,
	ospi_div_8
} enum_ospi_div_Type;

/**
 * @brief OSPI output clock phase
 * @ingroup UP301_Controller_OSPI
 */
typedef enum enum_ospi_phase {
	ospi_phase_180 = 0,
	ospi_phase_90
} enum_ospi_phase_Type;

/**
 * @brief OSPI device selection
 * @ingroup UP301_Controller_OSPI
 */
typedef enum enum_ospi_cs_sel {
	ospi_slave_0_en = 1,
	ospi_slave_1_en
} enum_ospi_cs_sel_Type;

/**
 * @brief OSPI IO mode
 * @ingroup UP301_Controller_OSPI
 */
typedef enum enum_ospi_io_mode {
	ospi_io_single = 0,
	ospi_io_dual,
	ospi_io_quad,
	ospi_io_octal
} enum_ospi_io_mode_Type;

/**
 * @brief select OSPI data rate
 * @ingroup UP301_Controller_OSPI
 */
typedef enum enum_ospi_data_rate {
	ospi_data_rate_sdr = 0,
	ospi_data_rate_ddr
} enum_ospi_data_rate_Type;

/**
 * @brief select OSPI data rate
 * @ingroup UP301_Controller_OSPI
 */
typedef enum enum_ospi_order {
	ospi_bit_order_msbf	= 0,
	ospi_bit_order_lsbf
} enum_ospi_order_Type;

/**
 * @brief OSPI access mode
 * @ingroup UP301_Controller_OSPI
 */
typedef enum enum_ospi_access_ctrl {
	ospi_mode_indirect = 0,
	ospi_mode_AXI_read,
	ospi_mode_AXI_write
} enum_ospi_access_ctrl_Type;

/**
 * @brief set OSPI access R/W type
 * @ingroup UP301_Controller_OSPI
 */
typedef enum enum_ospi_access {
	ospi_transfer_read = 0,
	ospi_transfer_write,
	ospi_transfer_nd
} enum_ospi_access_Type;

/**
 * @brief OSPI DMA mode selection
 * @ingroup UP301_Controller_OSPI
 */
typedef enum enum_ospi_dma_mode {
	ospi_dma_disable = 0,
	ospi_dma_tx_enable,
	ospi_dma_rx_enable
} enum_ospi_dma_mode_Type;

/**
 * @brief OSPI return error code.
 * @ingroup UP301_Controller_OSPI
 */
typedef enum enum_ospi_retcode {
    E_OSPI_SUCCESS,     // Success.
	E_OSPI_INVINIT,	 	// Initial fail or resource is unavailable.
	E_OSPI_INVPARA,	 	// Invalid function parameter/argument.
	E_OSPI_RUNINGCLK,	// Invalid running clock
    E_OSPI_TIMEOUT,		// Timeout error
    E_OSPI_ERROR,     	// Unspecific error.
} enum_ospi_retcode_Type;

/**  @brief Interrupt status: return value of upt_ospi_get_status() */
#define ospi_transfer_complete 				(0x1U << 0)
/**  @brief Interrupt status: return value of upt_ospi_get_status() */
#define ospi_read_buffer_rdy		 		(0x1U << 1)
/**  @brief Interrupt status: return value of upt_ospi_get_status() */
#define ospi_write_buffer_rdy				(0x1U << 2)
/**  @brief Interrupt status: return value of upt_ospi_get_status() */
#define ospi_cs_deassert					(0x1U << 8)

/**
 * @brief The buffer information for a SPI transfer
 */
typedef struct ospi_transfer_info {
    uintptr_t buf;
    uint32_t remains;
} ospi_transfer_info_Type;

/**
 * @brief The extend configuration for a SPI transfer
 */
typedef struct ospi_config {
	uint32_t protocol[3];
	uint32_t swap[3];
	uint32_t xip_enable;
	uint32_t dqs_enable;
	uint32_t sampling_edge;
    ospi_transfer_info_Type trs_info;
    uint32_t timeout_val;
    uint32_t timeout_cnt;
} ospi_config_Type;

/**
 * @brief The configuration for a SPI transfer
 */
typedef struct ospi_frame_info {
	uint32_t cmd;
	uint32_t adr;
	uint32_t alt;
    uintptr_t dat;
    uint32_t cmd_len;
    uint32_t adr_len;
    uint32_t alt_len;
    uint32_t pre_cyc;
    uint32_t dmy_cyc;
    uint32_t dat_len;
} ospi_frame_info_Type;

/**
 * @brief The detail of protocol type for a SPI transfer
 */
typedef struct ospi_spi_protocol {
	enum_ospi_io_mode_Type io_width;   	// 0:single, 1:dual, 2:quad, 3:octal
	enum_ospi_data_rate_Type data_rate;  // 0:SDR, 1:DDR
	enum_ospi_order_Type bit_order;  	// 0:MSB first, 1:LSB first
	uint32_t dmy;
} ospi_spi_protocol_Type;

/**
 * @brief The protocol type for a SPI transfer
 */
typedef struct opsi_field_protocol {
	ospi_spi_protocol_Type f_code;
	ospi_spi_protocol_Type f_addr;
	ospi_spi_protocol_Type f_altr;
	ospi_spi_protocol_Type f_data;
} ospi_field_protocol_Type;

/** @brief Fospi_config_Type initialization */
#define OSPI_INIT_CONFIG(val) val = (ospi_config_Type){0}

/** @brief Fospi_frame_info_Type initialization */
#define OSPI_INIT_FRAME_INFO(val) val = (ospi_frame_info_Type){0}

/** @brief Fopsi_field_protocol_Type initialization */
#ifdef LOAD_SRAM_CODE
#define OSPI_INIT_FIELD_PROTOCOL(val) val = (ospi_field_protocol_Type){0}
#else
#define OSPI_INIT_FIELD_PROTOCOL(val) \
	for(uint32_t i = 0; i < sizeof(ospi_field_protocol_Type); i++) { \
		*(uint8_t *)((uint32_t)(&(val))+i) = 0; \
	}
#endif

// Global timeout counter
#define OSPI_TIMEOUT_US	0x7FFFFFFF

/**
 * @brief Handle for a OSPI
 */
typedef struct metal_ospi {
    /*const*/ struct metal_ospi_vtable *vtable;
} metal_ospi_Type;

struct metal_ospi_vtable {
	enum_ospi_retcode_Type (*init)(metal_ospi_Type *ospi, enum_ospi_div_Type div);
	enum_ospi_retcode_Type (*transfer_command)(
			metal_ospi_Type *ospi,
			ospi_config_Type *config,
			enum_ospi_access_Type dir,
			ospi_frame_info_Type *pst_frame,
			ospi_field_protocol_Type *pst_protocol);
	enum_ospi_retcode_Type (*transfer)(
			metal_ospi_Type *ospi,
			ospi_config_Type *config,
			enum_ospi_access_Type dir,
			ospi_frame_info_Type *pst_frame,
			ospi_field_protocol_Type *pst_protocol);
	enum_ospi_retcode_Type (*get_transfer_info)(
			metal_ospi_Type *ospi,
			ospi_config_Type *config,
			uintptr_t *puipBuf,
			uint32_t *pdwSize);
	enum_ospi_retcode_Type (*set_transfer_info)(
			metal_ospi_Type *ospi,
			ospi_config_Type *config,
			uintptr_t puipBuf,
			uint32_t *pdwSize);
	uint32_t (*get_clock_divider)(metal_ospi_Type *ospi);
    enum_ospi_retcode_Type (*set_clock_divider)(
    		metal_ospi_Type *ospi,
			enum_ospi_div_Type div,
			enum_ospi_phase_Type phase,
			uint32_t timeout_cnt);
    enum_ospi_retcode_Type (*set_xip_boot_enable)(
    		metal_ospi_Type *ospi,
			bool enable,
			uint32_t timeout_cnt);
    enum_ospi_retcode_Type (*set_xip_conf)(
    		metal_ospi_Type *ospi,
			ospi_config_Type *config,
			enum_ospi_access_ctrl_Type dw_mode,
			ospi_frame_info_Type *pst_frame,
			ospi_field_protocol_Type *pst_protocol,
			uint32_t *padw_base_address,
			uint32_t dw_mask_addr);
    enum_ospi_retcode_Type (*set_slave_en)(
    		metal_ospi_Type *ospi,
    		enum_ospi_cs_sel_Type slave_sel);
    enum_ospi_retcode_Type (*dll_enable)(
    		metal_ospi_Type *ospi,
			bool enable,
			enum_ospi_dll_delay_Type dalay,
			uint32_t timeout_cnt);
    enum_ospi_retcode_Type (*isr_enable)(
    		struct metal_ospi *ospi,
			bool enable);
    uint32_t (*get_int_status)(metal_ospi_Type *ospi);
    enum_ospi_retcode_Type (*clear_int_status)(metal_ospi_Type *ospi, uint32_t status);
    enum_ospi_retcode_Type (*read_fifo)(
    		metal_ospi_Type *ospi,
			uint8_t *read_buf,
			uint32_t read_buf_len);
    enum_ospi_retcode_Type (*write_fifo)(
    		metal_ospi_Type *ospi,
			uint8_t *send_buf,
			uint32_t send_buf_len);
};

/**
 * @brief Get a handle of OSPI
 * @param[in] device_num The index of the desired OSPI device
 * @return A handle to the OSPI device, or NULL if the device does not exist
 */
#ifndef LOAD_SRAM_CODE
metal_ospi_Type *upt_ospi_get_device(enum_ospi_device_Type device_num) __attribute__ ((section (".FwHandler")));
#else
metal_ospi_Type *upt_ospi_get_device(enum_ospi_device_Type device_num);
#endif

/**
 * @brief Initialize a OSPI device.
 * @param[in] ospi The OSPI handle.
 * @param[in] div Set the clock divider.
 * @param[in] phase Set clock delay phase.
 * @return enum_ospi_retcode_Type value.
 */
#ifndef LOAD_SRAM_CODE
enum_ospi_retcode_Type upt_ospi_init(
		metal_ospi_Type *ospi,
		enum_ospi_div_Type div,
		enum_ospi_phase_Type phase) __attribute__ ((section (".FwHandler")));
#else
enum_ospi_retcode_Type upt_ospi_init(
		metal_ospi_Type *ospi,
		enum_ospi_div_Type div,
		enum_ospi_phase_Type phase);
#endif

/**
 * @brief Perform a OSPI transfer command only.
 * @param[in] ospi The OSPI handle.
 * @param[in] config The configuration for the OSPI transfer.
 * @param[in] dir operate read/write/no data.
 * @param[in] pst_frame FOSPI_INIT_FIELD_PROTOCOL to be used.
 * @param[in] pst_protocol FOSPI_INIT_FIELD_PROTOCOL to be used.
 * @return enum_ospi_retcode_Type value.
 */
#ifndef LOAD_SRAM_CODE
enum_ospi_retcode_Type upt_ospi_transfer_command(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		enum_ospi_access_Type dir,
		ospi_frame_info_Type *pst_frame,
		ospi_field_protocol_Type *pst_protocol) __attribute__ ((section (".FwHandler")));
#else
enum_ospi_retcode_Type upt_ospi_transfer_command(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		enum_ospi_access_Type dir,
		ospi_frame_info_Type *pst_frame,
		ospi_field_protocol_Type *pst_protocol);
#endif

/**
 * @brief Perform a OSPI transfer.
 * @param[in] ospi The OSPI handle.
 * @param[in] config The configuration for the OSPI transfer.
 * @param[in] dir operate read/write/no data.
 * @param[in] pst_frame FOSPI_INIT_FIELD_PROTOCOL to be used.
 * @param[in] pst_protocol FOSPI_INIT_FIELD_PROTOCOL to be used.
 * @return enum_ospi_retcode_Type value.
 */
#ifndef LOAD_SRAM_CODE
enum_ospi_retcode_Type upt_ospi_transfer(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		enum_ospi_access_Type dir,
		ospi_frame_info_Type *pst_frame,
		ospi_field_protocol_Type *pst_protocol) __attribute__ ((section (".FwHandler")));
#else
enum_ospi_retcode_Type upt_ospi_transfer(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		enum_ospi_access_Type dir,
		ospi_frame_info_Type *pst_frame,
		ospi_field_protocol_Type *pst_protocol);
#endif

/**
 * @brief Get transfer buffer information.
 * @param[in] ospi The OSPI handle.
 * @param[in] config The configuration for the OSPI transfer.
 * @param[out] puipBuf Data buffer pointer.
 * @param[out] pdwSize Data buffer size.
 * @return enum_ospi_retcode_Type value.
 */
#ifndef LOAD_SRAM_CODE
enum_ospi_retcode_Type upt_get_transfer_info(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		uintptr_t *puipBuf,
		uint32_t *pdwSize) __attribute__ ((section (".FwHandler")));
#else
enum_ospi_retcode_Type upt_get_transfer_info(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		uintptr_t *puipBuf,
		uint32_t *pdwSize);
#endif

/**
 * @brief Set transfer buffer information.
 * @param[in] ospi The OSPI handle.
 * @param[in] config The configuration for the OSPI transfer.
 * @param[out] puipBuf Data buffer pointer.
 * @param[out] pdwSize Data buffer size.
 * @return enum_ospi_retcode_Type value.
 */
#ifndef LOAD_SRAM_CODE
enum_ospi_retcode_Type upt_set_transfer_info(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		uintptr_t puipBuf,
		uint32_t *pdwSize) __attribute__ ((section (".FwHandler")));
#else
enum_ospi_retcode_Type upt_set_transfer_info(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		uintptr_t puipBuf,
		uint32_t *pdwSize);
#endif

/**
 * @brief Set the XIP window/protocol of the OSPI device.
 * @param[in] ospi The OSPI handle.
 * @param[in] config The configuration for the OSPI transfer.
 * @param[in] dw_mode OSPI mode: AXI read or write.
 * @param[in] pst_frame Fospi_frame_info_Type to be used.
 * @param[in] pst_protocol FOSPI_INIT_FIELD_PROTOCOL to be used.
 * @param[in] padw_base_address The base address of the SPI-flash region.
 * @param[in] dw_mask_addr The XIP mask address of the SPI-flash region.
 * @return enum_ospi_retcode_Type value.
 */
#ifndef LOAD_SRAM_CODE
enum_ospi_retcode_Type upt_ospi_set_xip_conf(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		enum_ospi_access_ctrl_Type dw_mode,
		ospi_frame_info_Type *pst_frame,
		ospi_field_protocol_Type *pst_protocol,
		uint32_t *padw_base_address,
		uint32_t dw_mask_addr) __attribute__ ((section (".FwHandler")));
#else
enum_ospi_retcode_Type upt_ospi_set_xip_conf(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		enum_ospi_access_ctrl_Type dw_mode,
		ospi_frame_info_Type *pst_frame,
		ospi_field_protocol_Type *pst_protocol,
		uint32_t *padw_base_address,
		uint32_t dw_mask_addr);
#endif

/**
 * @brief Select flash device.
 * @param[in] ospi The OSPI handle.
 * @param[in] slave_sel slave index.
 * @return enum_ospi_retcode_Type value.
 */
#ifndef LOAD_SRAM_CODE
enum_ospi_retcode_Type upt_ospi_set_slave_en(
		metal_ospi_Type *ospi,
		enum_ospi_cs_sel_Type slave_sel) __attribute__ ((section (".FwHandler")));
#else
enum_ospi_retcode_Type upt_ospi_set_slave_en(
		metal_ospi_Type *ospi,
		enum_ospi_cs_sel_Type slave_sel);
#endif

/**
 * @brief Enable/Disable DLL function.
 * @param[in] ospi The OSPI handle.
 * @param[in] enable Enable/Disable OSPI DLL function.
 * @param[in] dalay Delay phase to be set.
 * @return enum_ospi_retcode_Type value.
 */
#ifndef LOAD_SRAM_CODE
enum_ospi_retcode_Type upt_ospi_dll_enable(
		metal_ospi_Type *ospi,
		bool enable,
		enum_ospi_dll_delay_Type dalay) __attribute__ ((section (".FwHandler")));
#else
enum_ospi_retcode_Type upt_ospi_dll_enable(
		metal_ospi_Type *ospi,
		bool enable,
		enum_ospi_dll_delay_Type dalay);
#endif

/**
 * @brief Enable/Disable ospi interrupt.
 * @param[in] ospi The OSPI handle.
 * @param[in] enable Enable/Disable OSPI interrupt.
 * @return enum_ospi_retcode_Type value.
 */
#ifndef LOAD_SRAM_CODE
enum_ospi_retcode_Type upt_ospi_isr_enable(
		metal_ospi_Type *ospi,
		bool enable) __attribute__ ((section (".FwHandler")));
#else
enum_ospi_retcode_Type upt_ospi_isr_enable(
		metal_ospi_Type *ospi,
		bool enable);
#endif

/**
 * @brief Enable/Disable boot mode function of flash execution-in-place.
 * @param[in] ospi The OSPI handle.
 * @param[in] enable Enable/Disable XIP boot mode.
 * @return enum_ospi_retcode_Type value.
 */
#ifndef LOAD_SRAM_CODE
enum_ospi_retcode_Type upt_ospi_set_xip_boot_enable(
		metal_ospi_Type *ospi,
		bool enable) __attribute__ ((section (".FwHandler")));
#else
enum_ospi_retcode_Type upt_ospi_set_xip_boot_enable(
		metal_ospi_Type *ospi,
		bool enable);
#endif

/**
 * @brief Get all status of OSPI.
 * @param[in] ospi The OSPI handle.
 * @return Status of SPI.
 */
#ifndef LOAD_SRAM_CODE
uint32_t upt_ospi_get_status(metal_ospi_Type *ospi) __attribute__ ((section (".FwHandler")));
#else
uint32_t upt_ospi_get_status(metal_ospi_Type *ospi);
#endif

/**
 * @brief Clear all status of OSPI.
 * @param[in] ospi The OSPI handle.
 * @param[in] status The status to be cleared.
 * @return enum_ospi_retcode_Type value.
 */
#ifndef LOAD_SRAM_CODE
enum_ospi_retcode_Type upt_ospi_clear_status(metal_ospi_Type *ospi, uint32_t status) __attribute__ ((section (".FwHandler")));
#else
enum_ospi_retcode_Type upt_ospi_clear_status(metal_ospi_Type *ospi, uint32_t status);
#endif

/**
 * @brief Read data from OSPI.
 * @param[in] ospi The OSPI handle.
 * @param[out] read_buf Read buffer.
 * @param[in] read_buf_len Read buffer length.
 * @return enum_ospi_retcode_Type value.
 */
#ifndef LOAD_SRAM_CODE
enum_ospi_retcode_Type upt_ospi_read_data(
		metal_ospi_Type *ospi,
		uint8_t *read_buf,
		uint32_t read_buf_len) __attribute__ ((section (".FwHandler")));
#else
enum_ospi_retcode_Type upt_ospi_read_data(
		metal_ospi_Type *ospi,
		uint8_t *read_buf,
		uint32_t read_buf_len);
#endif

/**
 * @brief Send data to OSPI
 * @param[in] ospi The OSPI handle
 * @param[in] send_buf Send buffer
 * @param[in] send_buf_len Send buffer length
 * @return enum_ospi_retcode_Type value.
 */
#ifndef LOAD_SRAM_CODE
enum_ospi_retcode_Type upt_ospi_send_data(
		metal_ospi_Type *ospi,
		uint8_t *send_buf,
		uint32_t send_buf_len) __attribute__ ((section (".FwHandler")));
#else
enum_ospi_retcode_Type upt_ospi_send_data(
		metal_ospi_Type *ospi,
		uint8_t *send_buf,
		uint32_t send_buf_len);
#endif

#endif /* METAL_OSPI_H */
