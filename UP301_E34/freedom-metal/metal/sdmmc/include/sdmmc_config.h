/*
 * Copyright (C) 2025 UpbeatTech Inc. All Rights Reserved
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * This file contains code derived from software originally developed by NXP.
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

/* 
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _SDMMC_CONFIG_H_
#define _SDMMC_CONFIG_H_
#include "fsl_common.h"
#ifdef SD_ENABLED
#include "fsl_sd.h"
#endif
#ifdef MMC_ENABLED
#include "fsl_mmc.h"
#endif
#ifdef SDIO_ENABLED
#include "fsl_sdio.h"
#endif
#include "fsl_sdmmc_host.h"
#include "fsl_sdmmc_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* @brief host basic configuration */
#define BOARD_SDMMC_SD_HOST_BASEADDR   SDIF
#define BOARD_SDMMC_SD_HOST_IRQ        SDIO_IRQn
#define BOARD_SDMMC_MMC_HOST_BASEADDR  0x58024000
#define BOARD_SDMMC_MMC_HOST_IRQ       SDIO_IRQn
#define BOARD_SDMMC_SDIO_HOST_BASEADDR SDIF
#define BOARD_SDMMC_SDIO_HOST_IRQ      SDIO_IRQn
/* @brief card detect configuration */
#define BOARD_SDMMC_SD_CD_TYPE                       kSD_DetectCardByHostCD
#define BOARD_SDMMC_SD_CARD_DETECT_DEBOUNCE_DELAY_MS (100U)

/* @brief mmc configuration */
#define BOARD_SDMMC_MMC_VCC_SUPPLY         kMMC_VoltageWindow170to195
#define BOARD_SDMMC_MMC_VCCQ_SUPPLY        kMMC_VoltageWindow170to195
#define BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE (4U)

/*!@ brief host interrupt priority*/
#define BOARD_SDMMC_SD_HOST_IRQ_PRIORITY   (5U)
#define BOARD_SDMMC_MMC_HOST_IRQ_PRIORITY  (5U)
#define BOARD_SDMMC_SDIO_HOST_IRQ_PRIORITY (5U)
/*!@brief dma descriptor buffer size */
#define BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE (0x40U)

extern uint32_t s_sdmmcHostDmaBuffer[];	// Mimi: to be checked

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief BOARD SD configurations.
 * @param card card descriptor
 * @param cd card detect callback
 * @param userData user data for callback
 */
#ifdef SD_ENABLED
void BOARD_SD_Config(void *card, sd_cd_t cd, uint32_t hostIRQPriority, void *userData);
#endif

/*!
 * @brief BOARD SDIO configurations.
 * @param card card descriptor
 * @param cd card detect callback
 * @param cardInt card interrupt
 */
#ifdef SDIO_ENABLED
void BOARD_SDIO_Config(void *card, sd_cd_t cd, uint32_t hostIRQPriority, sdio_int_t cardInt);
#endif

/*!
 * @brief BOARD MMC configurations.
 * @param card card descriptor
 * @param cd card detect callback
 * @param userData user data for callback
 */
#ifdef MMC_ENABLED
void BOARD_MMC_Config(void *card/*, uint32_t hostIRQPriority*/);

#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
