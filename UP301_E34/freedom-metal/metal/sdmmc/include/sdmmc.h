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
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _SDMMC_H_
#define _SDMMC_H_
#include<stdio.h>
#include<stdlib.h>


#define COMMAND_INT 1
#define DATA_INT 2
/*! @brief Enum _usdhc_transfer_data_type. Tansfer data type definition. */
enum
{
    kUSDHC_TransferDataNormal        = 0U, /*!< Transfer normal read/write data. */
    kUSDHC_TransferDataTuning        = 1U, /*!< Transfer tuning data. */
    kUSDHC_TransferDataBoot          = 2U, /*!< Transfer boot data. */
    kUSDHC_TransferDataBootcontinous = 3U, /*!< Transfer boot data continuously. */
};

enum
{
    kUSDHC_CommandInhibitFlag      = (0x1<<0),  /*!< Command inhibit. */
    kUSDHC_DataInhibitFlag         = (0x1<<1), /*!< Data inhibit. */
    kUSDHC_DataLineActiveFlag      = (0x1<<2),   /*!< Data line active. */
    kUSDHC_SdClockStableFlag       = (0x1<<1), /*!< SD bus clock stable. */
    kUSDHC_WriteTransferActiveFlag = (0x1<<8),   /*!< Write transfer active. */
    kUSDHC_ReadTransferActiveFlag  = (0x1<<9),   /*!< Read transfer active. */
    kUSDHC_BufferWriteEnableFlag   = (0x1<<10),  /*!< Buffer write enable. */
    kUSDHC_BufferReadEnableFlag    = (0x1<<11),  /*!< Buffer read enable. */

    kUSDHC_ReTuningRequestFlag = (0x1<<3), /*!< Re-tuning request flag, only used for SDR104 mode. */
    kUSDHC_CardInsertedFlag     = (0x1<<16), /*!< Card inserted. */
    kUSDHC_CommandLineLevelFlag = (0x1<<24),  /*!< Command line signal level. */

    kUSDHC_Data0LineLevelFlag = 1U << 20,               /*!< Data0 line signal level. */
    kUSDHC_Data1LineLevelFlag = 1U << (20 + 1U),        /*!< Data1 line signal level. */
    kUSDHC_Data2LineLevelFlag = 1U << (20 + 2U),        /*!< Data2 line signal level. */
    kUSDHC_Data3LineLevelFlag = 1U << (20 + 3U),        /*!< Data3 line signal level. */
//    kUSDHC_Data4LineLevelFlag = 1U << (USDHC_PRES_STATE_DLSL_SHIFT + 4U),        /*!< Data4 line signal level. */ // Mimi
//    kUSDHC_Data5LineLevelFlag = 1U << (USDHC_PRES_STATE_DLSL_SHIFT + 5U),        /*!< Data5 line signal level. */ // Mimi
//    kUSDHC_Data6LineLevelFlag = 1U << (USDHC_PRES_STATE_DLSL_SHIFT + 6U),        /*!< Data6 line signal level. */ // Mimi
//    kUSDHC_Data7LineLevelFlag = (int)(1U << (USDHC_PRES_STATE_DLSL_SHIFT + 7U)), /*!< Data7 line signal level. */ // Mimi
};


#define USDHC_SYS_CTRL_RSTA_MASK	(0x1<<0)
#define USDHC_SYS_CTRL_RSTC_MASK	(0x1<<1)
#define USDHC_SYS_CTRL_RSTD_MASK	(0x1<<2)

//0x3E
#define USDHC_SYS_CTRL_RSTT_MASK	(0x1<<23)
/*! @brief Enum _usdhc_reset. Reset type mask.
 *  @anchor _usdhc_reset
 */
enum
{
    kUSDHC_ResetAll     = USDHC_SYS_CTRL_RSTA_MASK, /*!< Reset all except card detection. */
    kUSDHC_ResetCommand = USDHC_SYS_CTRL_RSTC_MASK, /*!< Reset command line. */
    kUSDHC_ResetData    = USDHC_SYS_CTRL_RSTD_MASK, /*!< Reset data line. */

#if defined(FSL_FEATURE_USDHC_HAS_SDR50_MODE) /*&& (!FSL_FEATURE_USDHC_HAS_SDR50_MODE)*/
    kUSDHC_ResetTuning = USDHC_SYS_CTRL_RSTT_MASK, /*!< no reset tuning circuit bit */
#else
    kUSDHC_ResetTuning         = USDHC_SYS_CTRL_RSTT_MASK,                /*!< Reset tuning circuit. */ // Mimi
#endif

    kUSDHC_ResetsAll = (kUSDHC_ResetAll | kUSDHC_ResetCommand | kUSDHC_ResetData | kUSDHC_ResetTuning),
    /*!< All reset types */
};


#define USDHC_SDMMC_CTRL_HS200_EMMC		(0x1 << 24)
/*! @brief Constant to pass as timeout value in order to wait indefinitely. */
#define osaWaitForever_c   ((uint32_t)(-1)) //Mimi add

#define USDHC_HOST_VOL_BUS_POWER  (0x1<<8)
#define USDHC_HOST_CTRL2_1V8        (0x1<<19)
#define USDHC_HOST_VOL_1V8          (0x5<<9)   

#define USDHC_INT_STATUS_CC_MASK	(0x1<<0)
#define USDHC_INT_STATUS_TC_MASK	(0x1<<1)
#define USDHC_INT_STATUS_BGE_MASK	(0x1<<2)
#define USDHC_INT_STATUS_DINT_MASK	(0x1<<3)
#define USDHC_INT_STATUS_BWR_MASK	(0x1<<4)
#define USDHC_INT_STATUS_BRR_MASK	(0x1<<5)
#define USDHC_INT_STATUS_CINS_MASK	(0x1<<6)
#define USDHC_INT_STATUS_CRM_MASK	(0x1<<7)
#define USDHC_INT_STATUS_CINT_MASK	(0x1<<8)

#define USDHC_INT_STATUS_RTE_MASK	(0x1<<12)
#define USDHC_INT_STATUS_TP_MASK	(0x0<<13)	// Mimi: Can't find in SPEC
#define USDHC_INT_STATUS_TNE_MASK	(0x1<<26)

#define USDHC_INT_STATUS_CTOE_MASK	(0x1<<16)
#define USDHC_INT_STATUS_CCE_MASK	(0x1<<17)
#define USDHC_INT_STATUS_CEBE_MASK	(0x1<<18)
#define USDHC_INT_STATUS_CIE_MASK	(0x1<<19)
#define USDHC_INT_STATUS_DTOE_MASK	(0x1<<20)
#define USDHC_INT_STATUS_DCE_MASK	(0x1<<21)
#define USDHC_INT_STATUS_DEBE_MASK	(0x1<<22)
#define USDHC_INT_STATUS_AC12E_MASK	(0x1<<24)
#define USDHC_INT_STATUS_DMAE_MASK	(0x1<<25)

/*! @brief Enum _usdhc_interrupt_status_flag. Interrupt status flag mask.
 *  @anchor _usdhc_interrupt_status_flag
 */
enum
{
    kUSDHC_CommandCompleteFlag  = USDHC_INT_STATUS_CC_MASK,   /*!< Command complete. */
    kUSDHC_DataCompleteFlag     = USDHC_INT_STATUS_TC_MASK,   /*!< Data complete. */
    kUSDHC_BlockGapEventFlag    = USDHC_INT_STATUS_BGE_MASK,  /*!< Block gap event. */
    kUSDHC_DmaCompleteFlag      = USDHC_INT_STATUS_DINT_MASK, /*!< DMA interrupt. */
    kUSDHC_BufferWriteReadyFlag = USDHC_INT_STATUS_BWR_MASK,  /*!< Buffer write ready. */
    kUSDHC_BufferReadReadyFlag  = USDHC_INT_STATUS_BRR_MASK,  /*!< Buffer read ready. */
    kUSDHC_CardInsertionFlag    = USDHC_INT_STATUS_CINS_MASK, /*!< Card inserted. */
    kUSDHC_CardRemovalFlag      = USDHC_INT_STATUS_CRM_MASK,  /*!< Card removed. */
    kUSDHC_CardInterruptFlag    = USDHC_INT_STATUS_CINT_MASK, /*!< Card interrupt. */

#if defined(FSL_FEATURE_USDHC_HAS_SDR50_MODE) && (!FSL_FEATURE_USDHC_HAS_SDR50_MODE)
    kUSDHC_ReTuningEventFlag = 0U, /*!< Re-Tuning event, only for SD3.0 SDR104 mode. */
    kUSDHC_TuningPassFlag    = 0U, /*!< SDR104 mode tuning pass flag. */
    kUSDHC_TuningErrorFlag   = 0U, /*!< SDR104 tuning error flag. */
#else
    kUSDHC_ReTuningEventFlag        = USDHC_INT_STATUS_RTE_MASK,  /*!< Re-Tuning event, only for SD3.0 SDR104 mode. */
    kUSDHC_TuningPassFlag           = USDHC_INT_STATUS_TP_MASK,   /*!< SDR104 mode tuning pass flag. */
    kUSDHC_TuningErrorFlag          = USDHC_INT_STATUS_TNE_MASK,  /*!< SDR104 tuning error flag. */
#endif

    kUSDHC_CommandTimeoutFlag     = USDHC_INT_STATUS_CTOE_MASK,  /*!< Command timeout error. */
    kUSDHC_CommandCrcErrorFlag    = USDHC_INT_STATUS_CCE_MASK,   /*!< Command CRC error. */
    kUSDHC_CommandEndBitErrorFlag = USDHC_INT_STATUS_CEBE_MASK,  /*!< Command end bit error. */
    kUSDHC_CommandIndexErrorFlag  = USDHC_INT_STATUS_CIE_MASK,   /*!< Command index error. */
    kUSDHC_DataTimeoutFlag        = USDHC_INT_STATUS_DTOE_MASK,  /*!< Data timeout error. */
    kUSDHC_DataCrcErrorFlag       = USDHC_INT_STATUS_DCE_MASK,   /*!< Data CRC error. */
    kUSDHC_DataEndBitErrorFlag    = USDHC_INT_STATUS_DEBE_MASK,  /*!< Data end bit error. */
    kUSDHC_AutoCommand12ErrorFlag = USDHC_INT_STATUS_AC12E_MASK, /*!< Auto CMD12 error. */
    kUSDHC_DmaErrorFlag           = USDHC_INT_STATUS_DMAE_MASK,  /*!< DMA error. */

    kUSDHC_CommandErrorFlag = (kUSDHC_CommandTimeoutFlag | kUSDHC_CommandCrcErrorFlag | kUSDHC_CommandEndBitErrorFlag |
                               kUSDHC_CommandIndexErrorFlag), /*!< Command error */
    kUSDHC_DataErrorFlag    = (kUSDHC_DataTimeoutFlag | kUSDHC_DataCrcErrorFlag | kUSDHC_DataEndBitErrorFlag |
                            kUSDHC_AutoCommand12ErrorFlag),                                        /*!< Data error */
    kUSDHC_ErrorFlag        = (kUSDHC_CommandErrorFlag | kUSDHC_DataErrorFlag | kUSDHC_DmaErrorFlag), /*!< All error */

    kUSDHC_DataFlag = (kUSDHC_DataCompleteFlag | kUSDHC_BufferWriteReadyFlag | kUSDHC_BufferReadReadyFlag |
                       kUSDHC_DataErrorFlag), /*!< Data interrupts */

    kUSDHC_DataDMAFlag = (kUSDHC_DataCompleteFlag | kUSDHC_DataErrorFlag | kUSDHC_DmaErrorFlag), /*!< Data interrupts */

    kUSDHC_CommandFlag      = (kUSDHC_CommandErrorFlag | kUSDHC_CommandCompleteFlag), /*!< Command interrupts */
    kUSDHC_CardDetectFlag   = (kUSDHC_CardInsertionFlag | kUSDHC_CardRemovalFlag),    /*!< Card detection interrupts */
    kUSDHC_SDR104TuningFlag = (kUSDHC_TuningErrorFlag | kUSDHC_TuningPassFlag | kUSDHC_ReTuningEventFlag),
    /*!< SDR104 tuning flag. */
    kUSDHC_AllInterruptFlags =
        (kUSDHC_BlockGapEventFlag | kUSDHC_CardInterruptFlag | kUSDHC_CommandFlag | kUSDHC_DataFlag | kUSDHC_ErrorFlag |
         kUSDHC_SDR104TuningFlag | kUSDHC_DmaCompleteFlag), /*!< All flags mask */
};


#endif