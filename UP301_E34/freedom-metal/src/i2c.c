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

#include "metal.h"
#include "metal/i2c.h"

extern __inline__ enum_i2c_retcode_Type upt_i2c_init(metal_i2c_Type *i2c, enum_i2c_speed_Type speed_mode,
                        	metal_i2c_mode_Type mode, bool addr_10bit_en);

extern __inline__ enum_i2c_retcode_Type upt_i2c_set_slave_address(metal_i2c_Type *i2c, uint16_t slave_address, bool _10_bit_enable);

extern __inline__ enum_i2c_retcode_Type upt_i2c_set_slave(metal_i2c_Type *i2c, uint32_t slave_addr);

extern __inline__ enum_i2c_retcode_Type upt_i2c_write(metal_i2c_Type *i2c, uint32_t slave_addr,
						 				unsigned int len, uint8_t buf[], enum_i2c_stop_bit_Type stop_bit);

extern __inline__ enum_i2c_retcode_Type upt_i2c_read(metal_i2c_Type *i2c, uint32_t slave_addr, uint16_t len,uint8_t buf[],
									   enum_i2c_restart_bit_Type restart_bit);
extern __inline__ enum_i2c_retcode_Type upt_i2c_read_ready(metal_i2c_Type *i2c, uint16_t len, enum_i2c_restart_bit_Type restart_bit);

extern __inline__ enum_i2c_retcode_Type upt_i2c_read_end(metal_i2c_Type *i2c, uint16_t len);

extern __inline__ bool upt_i2c_check_status_idle(metal_i2c_Type *i2c);   

extern __inline__ enum_i2c_retcode_Type upt_i2c_enable(metal_i2c_Type *i2c, bool enable);

extern __inline__ enum_i2c_retcode_Type upt_i2c_read_nonblocking(metal_i2c_Type *i2c, uint16_t len, enum_i2c_restart_bit_Type restart_bit, enum_i2c_stop_bit_Type stop_bit);

extern __inline__ enum_i2c_retcode_Type upt_i2c_transfer(metal_i2c_Type *i2c, uint32_t slave_addr,
										   uint8_t txbuf[], uint16_t txlen, uint8_t rxbuf[], uint16_t rxlen,
										   int16_t restart_enable);
						   
extern __inline__ enum_i2c_retcode_Type upt_i2c_isr_enable(metal_i2c_Type *i2c, uint32_t enable_evt);

extern __inline__ enum_i2c_retcode_Type upt_i2c_dma_enable(metal_i2c_Type *i2c, enum_i2c_dma_mode_Type mode);

extern __inline__ enum_i2c_retcode_Type upt_i2c_set_watermark(metal_i2c_Type *i2c, enum_i2c_watermark_Type watermark);

extern __inline__ uint32_t upt_i2c_get_status(metal_i2c_Type *i2c);

extern __inline__ uint32_t upt_i2c_get_status_register(metal_i2c_Type *i2c);

extern __inline__ uint32_t upt_i2c_clear_status(metal_i2c_Type *i2c);

extern __inline__ enum_i2c_retcode_Type upt_i2c_read_data(metal_i2c_Type *i2c, uint8_t *read_buf, int16_t read_buf_len);

extern __inline__ enum_i2c_retcode_Type upt_i2c_send_data(metal_i2c_Type *i2c, uint8_t *send_buf, int16_t send_buf_len, enum_i2c_stop_bit_Type stop_bit);

extern __inline__ enum_i2c_retcode_Type upt_i2c_set_timeout_us(metal_i2c_Type *i2c, uint64_t timeout_us); 

extern __inline__ uint64_t upt_i2c_get_timeout_us(metal_i2c_Type *i2c); 

metal_i2c_Type *upt_i2c_get_device(uint16_t device_num) {
#if __METAL_DT_MAX_I2CS > 0
    if (device_num < __METAL_DT_MAX_I2CS) {
        return (metal_i2c_Type *)__metal_i2c_table[device_num];
    }
#endif

    return NULL;
}
