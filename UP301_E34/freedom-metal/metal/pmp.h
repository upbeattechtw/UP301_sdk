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

/*!
 * @file metal/pmp.h
 *
 * @brief API for Configuring Physical Memory Protection on RISC-V Cores
 *
 * The Physical Memory Protection (PMP) interface on RISC-V cores
 * is a form of memory protection unit which allows for a finite number
 * of physical memory regions to be configured with certain access
 * permissions.
 *
 * Additional information about the use and configuration rules for PMPs
 * can be found by reading the RISC-V Privileged Architecture Specification.
 */
#ifndef METAL__PMP_H
#define METAL__PMP_H
#include <stddef.h>

#include "metal.h"

struct metal_pmp;

/*!
 * @brief Set of available PMP addressing modes
 */
enum metal_pmp_address_mode {
    /*! @brief Disable the PMP region */
    METAL_PMP_OFF = 0,
    /*! @brief Use Top-of-Range mode */
    METAL_PMP_TOR = 1,
    /*! @brief Use naturally-aligned 4-byte region mode */
    METAL_PMP_NA4 = 2,
    /*! @brief Use naturally-aligned power-of-two mode */
    METAL_PMP_NAPOT = 3
};

/*!
 * @brief Configuration for a PMP region
 */
struct metal_pmp_config {
    /*! @brief Sets whether reads to the PMP region succeed */
	uint32_t R : 1;
    /*! @brief Sets whether writes to the PMP region succeed */
	uint32_t W : 1;
    /*! @brief Sets whether the PMP region is executable */
	uint32_t X : 1;

    /*! @brief Sets the addressing mode of the PMP region */
    enum metal_pmp_address_mode A : 2;

    uint32_t _pad : 2;

    /*! @brief Sets whether the PMP region is locked */
    enum metal_pmp_locked {
        METAL_PMP_UNLOCKED = 0,
        METAL_PMP_LOCKED = 1
    } L : 1;
};

/*!
 * @brief A handle for the PMP device
 */
struct metal_pmp {
    /* The minimum granularity of the PMP region. Set by metal_pmp_init */
    uintptr_t _granularity[METAL_MAX_CORES];
};

/*!
 * @brief Get the PMP device handle
 */
struct metal_pmp *metal_pmp_get_device(void);

/*!
 * @brief PMP interface return error code.
 */
typedef enum enum_pmp_retcode{
    E_PMP_SUCCESS,     // Success.
    E_PMP_NULLARG,      // Arguments cannot be NULL.
	E_PMP_OUTOFRANGE,	 	// Region outside of supported range.
	E_PMP_INVGRANU,	 	// The requested granularity is too small.
    E_PMP_INVMODIFY,     //Cannot modify locked region
    E_PMP_ERROR,     	// Unspecific error.
} enum_pmp_retcode_Type;


/*!
 * @brief Get the number of pmp regions for the hartid
 */
uint32_t metal_pmp_num_regions(uint32_t hartid);

/*!
 * @brief Initialize the PMP
 * @param pmp The PMP device handle to be initialized
 *
 * The PMP initialization routine is optional and may be called as many times
 * as is desired. The effect of the initialization routine is to attempt to set
 * all regions to unlocked and disabled, as well as to clear the X, W, and R
 * bits. Only the pmp configuration of the hart which executes the routine will
 * be affected.
 *
 * If any regions are fused to preset values by the implementation or locked,
 * those PMP regions will silently remain uninitialized.
 * @return enum_pmp_retcode_Type error call.
 */
enum_pmp_retcode_Type metal_pmp_init(struct metal_pmp *pmp);

/*!
 * @brief Configure a PMP region
 * @param pmp The PMP device handle
 * @param region The PMP region to configure
 * @param config The desired configuration of the PMP region
 * @param address The desired address of the PMP region
 * @return enum_pmp_retcode_Type error call.
 */
enum_pmp_retcode_Type metal_pmp_set_region(struct metal_pmp *pmp, uint32_t region,
                         struct metal_pmp_config config, size_t address);

/*!
 * @brief Get the configuration for a PMP region
 * @param pmp The PMP device handle
 * @param region The PMP region to read
 * @param config Variable to store the PMP region configuration
 * @param address Variable to store the PMP region address
 * @return enum_pmp_retcode_Type error call.
 */
enum_pmp_retcode_Type metal_pmp_get_region(struct metal_pmp *pmp, uint32_t region,
                         struct metal_pmp_config *config, size_t *address);

/*!
 * @brief Lock a PMP region
 * @param pmp The PMP device handle
 * @param region The PMP region to lock
 * @return enum_pmp_retcode_Type error call.
 */
enum_pmp_retcode_Type metal_pmp_lock(struct metal_pmp *pmp, uint32_t region);

/*!
 * @brief Set the address for a PMP region
 * @param pmp The PMP device handle
 * @param region The PMP region to set
 * @param address The desired address of the PMP region
 * @return enum_pmp_retcode_Type error call.
 */
enum_pmp_retcode_Type metal_pmp_set_address(struct metal_pmp *pmp, uint32_t region,
                          size_t address);

/*!
 * @brief Get the address of a PMP region
 * @param pmp The PMP device handle
 * @param region The PMP region to read
 * @return The address of the PMP region, or 0 if the region could not be read
 */
size_t metal_pmp_get_address(struct metal_pmp *pmp, uint32_t region);

/*!
 * @brief Set the addressing mode of a PMP region
 * @param pmp The PMP device handle
 * @param region The PMP region to set
 * @param mode The PMP addressing mode to set
 * @return enum_pmp_retcode_Type error call.
 */
enum_pmp_retcode_Type metal_pmp_set_address_mode(struct metal_pmp *pmp, uint32_t region,
                               	    enum metal_pmp_address_mode mode);

/*!
 * @brief Get the addressing mode of a PMP region
 * @param pmp The PMP device handle
 * @param region The PMP region to read
 * @return The address mode of the PMP region
 */
enum metal_pmp_address_mode metal_pmp_get_address_mode(struct metal_pmp *pmp,
													   uint32_t region);

/*!
 * @brief Set the executable bit for a PMP region
 * @param pmp The PMP device handle
 * @param region The PMP region to set
 * @param X The desired value of the executable bit
 * @return enum_pmp_retcode_Type error call.
 */
enum_pmp_retcode_Type metal_pmp_set_executable(struct metal_pmp *pmp, uint32_t region, uint32_t X);

/*!
 * @brief Get the executable bit for a PMP region
 * @param pmp The PMP device handle
 * @param region The PMP region to read
 * @return the value of the executable bit
 */
uint32_t metal_pmp_get_executable(struct metal_pmp *pmp, uint32_t region);

/*!
 * @brief Set the writable bit for a PMP region
 * @param pmp The PMP device handle
 * @param region The PMP region to set
 * @param W The desired value of the writable bit
 * @return enum_pmp_retcode_Type error call.
 */
enum_pmp_retcode_Type metal_pmp_set_writeable(struct metal_pmp *pmp, uint32_t region, uint32_t W);

/*!
 * @brief Get the writable bit for a PMP region
 * @param pmp The PMP device handle
 * @param region The PMP region to read
 * @return the value of the writable bit
 */
uint32_t metal_pmp_get_writeable(struct metal_pmp *pmp, uint32_t region);

/*!
 * @brief Set the readable bit for a PMP region
 * @param pmp The PMP device handle
 * @param region The PMP region to set
 * @param R The desired value of the readable bit
 * @return enum_pmp_retcode_Type error call.
 */
enum_pmp_retcode_Type metal_pmp_set_readable(struct metal_pmp *pmp, uint32_t region, uint32_t R);

/*!
 * @brief Set the readable bit for a PMP region
 * @param pmp The PMP device handle
 * @param region The PMP region to read
 * @return the value of the readable bit
 */
uint32_t metal_pmp_get_readable(struct metal_pmp *pmp, uint32_t region);

#endif /* METAL__PMP_H */
