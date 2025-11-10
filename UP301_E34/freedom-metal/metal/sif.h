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

#ifndef METAL_SIF_H
#define METAL_SIF_H
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Device number of SIF engine
 * @ingroup UP301_Controller_SIF
 */
typedef enum enum_sif_device {
	AON_SIF	= 0,
} enum_sif_device_Type;

/**
 * @brief SIF command queue function select
 * @ingroup UP301_Controller_SIF
 */
typedef enum sif_ic_function {
	IC_DATA_CMD	= 0,
	IC_ENABLE,
	IC_STATUS,
} sif_ic_function_Type;

/**
 * @brief SIF command queue R/W select
 * @ingroup UP301_Controller_SIF
 */
typedef enum sif_ic_cmd_type {
	SIF_CMD_WRITE = 0,
	SIF_CMD_READ,
}sif_ic_cmd_type_Type;

/**
 * @brief SIF command queue trigger method select
 * @ingroup UP301_Controller_SIF
 */
typedef enum sif_ic_trigger {
	SIF_EXTERNAL = 0,
	SIF_INTERNAL,
}sif_ic_trigger_Type;

/**
 * @brief SIF return error code.
 * @ingroup UP301_Controller_SIF
 */
typedef enum enum_sif_retcode {
    E_SIF_SUCCESS,     // Success.
	E_SIF_INVINIT,	 	// Initial fail or resource is unavailable.
	E_SIF_INVPARA,	 	// Invalid function parameter/argument.
    E_SIF_ERROR,     	// Unspecific error.
} enum_sif_retcode_Type;

/** @brief SIF upt_sif_write_command_queue() which use in function field is IC_DATA_CMD && cmd field is SIF_CMD_READ/SIF_CMD_WRITE */
#define	SIF_STOP_ENABLE				(1 << 9)

/** @brief SIF upt_sif_write_command_queue() which use in function field is IC_ENABLE && cmd field is SIF_CMD_WRITE */
#define SIF_I2C_ENABLE				(1 << 0)
#define SIF_I2C_DISABLE				(0 << 0)

/** @brief SIF upt_sif_write_command_queue() which use in function field is IC_STATUS && cmd field is SIF_CMD_READ */
#define SIF_ACTIVITY                (1 << 16)     	// Check with i2c 0x70.
#define	SIF_TFNF                    (1 << 17)		// Transmit FIFO Status.
#define	SIF_TFE						(1 << 18)		// Transmit FIFO Completely Empty Status.
#define	SIF_RFNE					(1 << 19)		// Receive FIFO Not Empty.
#define	SIF_RFF						(1 << 20)		// Receive FIFO Completely Full.
#define SIF_MST_ACTIVITY			(1 << 21)
#define SIF_SLV_ACTIVITY			(1 << 22)
#define SIF_MST_HOLD_TX_FIFO_EMPTY 	(1 << 23)

/** @brief SIF upt_sif_write_command_queue() which use in function field is IC_STATUS && cmd field is SIF_CMD_READ */
#define SIF_ACTIVITY_BUSY				(1 << 0)
#define SIF_ACTIVITY_IDLE				~(1 << 0)
#define	SIF_TFNF_NOT_FULL				(1 << 1)			// Transmit FIFO Status
#define	SIF_TFNF_FULL					~(1 << 1)			// Transmit FIFO Status
#define	SIF_TFE_EMPTY					(1 << 2)			// Transmit FIFO Completely Empty Status
#define	SIF_TFE_NOT_EMPTY				~(1 << 2)			// Transmit FIFO Completely Empty Status
#define	SIF_RFNE_NOT_EMPTY				(1 << 3)			// Receive FIFO Not Empty
#define	SIF_RFNE_EMPTY					~(1 << 3)			// Receive FIFO Not Empty
#define	SIF_RFF_FULL					(1 << 4)			// Receive FIFO Completely Full
#define	SIF_RFF_NOT_FULL				~(1 << 4)
#define SIF_MST_ACTIVITY_BUSY			(1 << 5)
#define SIF_MST_ACTIVITY_IDLE			~(1 << 5)
#define SIF_MST_HOLD_TX_FIFO_EMPTY_		(1 << 7)
#define SIF_MST_NOT_HOLD_TX_FIFO_EMPTY	~(1<< 7)

/**
 * @brief A handle for a SIF engine.
 */
typedef struct metal_sif {
    const struct metal_sif_vtable *vtable;
} metal_sif_Type;

struct metal_sif_vtable {
	enum_sif_retcode_Type (*write_to_nth_cmd)(metal_sif_Type *sif, uint32_t seq, sif_ic_function_Type function, sif_ic_cmd_type_Type cmd, uint32_t data, bool last);
	enum_sif_retcode_Type (*config)(metal_sif_Type *sif, sif_ic_trigger_Type trig);
};

/**
 * @brief Get a handle for a SIF device.
 * @param[in] device_num The index of the desired SIF device.
 * @return A handle to the SIF device, or NULL if the device does not exist.
 * @return The SIF handle, or NULL if there is no device at that index.
 * */
metal_sif_Type *upt_sif_get_device(enum_sif_device_Type device_num);

/**
 * @brief Set SIF command queue.
 * @param[in] sif The SIF handle
 * @param[in] seq command queue sequence
 * @param[in] function Action to be performed
 * @param[in] cmd I2C command read/write
 * @param[in] data depends on command type to decide which information to be filled
 * @param[in] last if last command in command queue
 * @return enum_sif_retcode_Type value.
 */
inline enum_sif_retcode_Type upt_sif_write_command_queue(metal_sif_Type *sif,
										uint32_t seq,
										sif_ic_function_Type function,
										sif_ic_cmd_type_Type cmd,
										uint32_t data,
										bool last) {
    return sif->vtable->write_to_nth_cmd(sif, seq, function, cmd, data, last);
}


/**
 * @brief Set SIF trigger mode
 * @param[in] sif The SIF handle
 * @param[in] trig Decide the trigger type
 * @return enum_sif_retcode_Type value.
 */
inline enum_sif_retcode_Type upt_sif_trigger(metal_sif_Type *sif,
							sif_ic_trigger_Type trig) {
    return sif->vtable->config(sif, trig);
}

#endif /* METAL_SIF_H */
