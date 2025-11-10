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
#include "metal/ospi.h"

enum_ospi_retcode_Type upt_ospi_init(
		metal_ospi_Type *ospi,
		enum_ospi_div_Type div,
		enum_ospi_phase_Type phase) {
	enum_ospi_retcode_Type ret = E_OSPI_SUCCESS;

	ret = ospi->vtable->init(ospi, div);
	if (ret != E_OSPI_SUCCESS)
		return ret;
	return ospi->vtable->set_clock_divider(ospi, div, phase, OSPI_TIMEOUT_US);
}

enum_ospi_retcode_Type upt_ospi_transfer(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		enum_ospi_access_Type dir,
		ospi_frame_info_Type *pst_frame,
		ospi_field_protocol_Type *pst_protocol) {
	return ospi->vtable->transfer(ospi, config, dir, pst_frame, pst_protocol);
}

enum_ospi_retcode_Type upt_ospi_transfer_command(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		enum_ospi_access_Type dir,
		ospi_frame_info_Type *pst_frame,
		ospi_field_protocol_Type *pst_protocol) {
	return ospi->vtable->transfer_command(ospi, config, dir, pst_frame, pst_protocol);
}

enum_ospi_retcode_Type upt_get_transfer_info(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		uintptr_t *puipBuf,
		uint32_t *pdwSize) {
	return ospi->vtable->get_transfer_info(ospi, config, puipBuf, pdwSize);
}

enum_ospi_retcode_Type upt_set_transfer_info(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		uintptr_t puipBuf,
		uint32_t *pdwSize) {
	return ospi->vtable->set_transfer_info(ospi, config, puipBuf, pdwSize);
}

enum_ospi_retcode_Type upt_ospi_set_xip_conf(
		metal_ospi_Type *ospi,
		ospi_config_Type *config,
		enum_ospi_access_ctrl_Type dw_mode,
		ospi_frame_info_Type *pst_frame,
		ospi_field_protocol_Type *pst_protocol,
		uint32_t *padw_base_address,
		uint32_t dw_mask_addr) {
	return ospi->vtable->set_xip_conf(ospi,config, dw_mode, pst_frame, pst_protocol, padw_base_address, dw_mask_addr);
}

enum_ospi_retcode_Type upt_ospi_set_slave_en(
		metal_ospi_Type *ospi,
	enum_ospi_cs_sel_Type slave_sel) {
	return ospi->vtable->set_slave_en(ospi, slave_sel);
}

enum_ospi_retcode_Type upt_ospi_set_xip_boot_enable(
		metal_ospi_Type *ospi,
		bool enable) {
	return ospi->vtable->set_xip_boot_enable(ospi, enable, OSPI_TIMEOUT_US);
}

enum_ospi_retcode_Type upt_ospi_dll_enable(
		metal_ospi_Type *ospi,
		bool enable,
		enum_ospi_dll_delay_Type dalay) {
	return ospi->vtable->dll_enable(ospi, enable, dalay, OSPI_TIMEOUT_US);
}

enum_ospi_retcode_Type upt_ospi_isr_enable(
		metal_ospi_Type *ospi,
		bool enable) {
	return ospi->vtable->isr_enable(ospi, enable);
}

uint32_t upt_ospi_get_status(metal_ospi_Type *ospi) {
	return ospi->vtable->get_int_status(ospi);
}

enum_ospi_retcode_Type upt_ospi_clear_status(metal_ospi_Type *ospi, uint32_t status) {
	return ospi->vtable->clear_int_status(ospi, status);
}

enum_ospi_retcode_Type upt_ospi_read_data(
		metal_ospi_Type *ospi,
		uint8_t *read_buf,
		uint32_t read_buf_len) {
	return ospi->vtable->read_fifo(ospi, read_buf, read_buf_len);
}

enum_ospi_retcode_Type upt_ospi_send_data(
		metal_ospi_Type *ospi,
		uint8_t *send_buf,
		uint32_t send_buf_len) {
	return ospi->vtable->write_fifo(ospi, send_buf, send_buf_len);
}

metal_ospi_Type *upt_ospi_get_device(enum_ospi_device_Type device_num) {
#if __METAL_DT_MAX_OSPIS > 0
	if (device_num > __METAL_DT_MAX_OSPIS) {
		return NULL;
	}
#endif
	return (metal_ospi_Type *)__metal_ospi_table[device_num];
}
