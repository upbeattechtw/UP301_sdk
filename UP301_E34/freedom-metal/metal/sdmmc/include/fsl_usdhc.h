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
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_USDHC_H_
#define FSL_USDHC_H_
#include "fsl_common.h"
/*!
 * @addtogroup usdhc
 * @{
 */
// Mimi add
typedef struct {
    volatile uint32_t DS_ADDR;        // 0x00: DMA System Address
    volatile uint32_t BLK_ATT;        // 0x04: Block Attributes ( Block Count (06h) + Block Size (04h) )
    volatile uint32_t CMD_ARG;        // 0x08: Command Argument
    volatile uint16_t XFR_TYP;       // 0x0C: Command Transfer Type
    volatile uint16_t CMD_REG;        // 0x0E: Command Transfer Type
    volatile uint32_t CMD_RSP0;       // 0x10: Command Response 0
    volatile uint32_t CMD_RSP1;       // 0x14: Command Response 1
    volatile uint32_t CMD_RSP2;       // 0x18: Command Response 2
    volatile uint32_t CMD_RSP3;       // 0x1C: Command Response 3
    volatile uint32_t DATA_BUFF_ACC_PORT; // 0x20: Data Buffer Access Port
    volatile uint32_t PRES_STATE;     // 0x24: Present State
    volatile uint32_t PROT_CTRL;      // 0x28: Protocol Control

    volatile uint16_t SYS_CTRL;       // 0x2C: System Control
    volatile uint8_t TOUT_CTRL;       // 0x2E: Timeout Control
    volatile uint8_t  SW_RESET;       // 0x2F: Software Reset
//  volatile uint32_t SYS_CTRL;       // 0x2C: System Control

    volatile uint32_t INT_STATUS;     // 0x30: Interrupt Status
    volatile uint32_t INT_STATUS_EN;  // 0x34: Interrupt Status Enable
    volatile uint32_t INT_SIGNAL_EN;  // 0x38: Interrupt Signal Enable
    volatile uint32_t AUTOCMD12_ERR_STATUS; // 0x3C: Auto CMD12 Error Status
    volatile uint32_t HOST_CTRL_CAP_0;	// 0x40: Host Controller Capabilities
    volatile uint32_t HOST_CTRL_CAP_1;  // 0x44: Host Controller Capabilities
//    volatile uint32_t WTMK_LVL;       // 0x44: Watermark Level
    volatile uint32_t MIX_CTRL;       // 0x48: Mixer Control
    volatile uint32_t RESERVED_REG_4C;     // 0x4C: Reserved
    volatile uint32_t FORCE_EVENT;    // 0x50: Force Event
    volatile uint32_t ADMA_ERR_STATUS;// 0x54: ADMA Error Status
    volatile uint32_t ADMA_SYS_ADDR;  // 0x58: ADMA System Address
    volatile uint32_t RESERVED_REG_5C;     // 0x5C: Reserved for 64 bits system

    volatile uint32_t DLL_CTRL;       // 0x60: DLL Control
    volatile uint32_t DLL_STATUS;     // 0x64: DLL Status
    volatile uint32_t CLK_TUNE_CTRL_STATUS; // 0x68: Clock Tuning Control and Status
    volatile uint32_t RESERVED_REG_6C;     // 0x6C: Reserved

    volatile uint32_t RESERVED_REG_70;      // 0x70: Reserved
    volatile uint32_t RESERVED_REG_74;      // 0x74: Reserved
    volatile uint32_t RESERVED_REG_78;      // 0x78: Reserved
    volatile uint32_t RESERVED_REG_7C;      // 0x7C: Reserved

    volatile uint32_t RESERVED_REG_80;      // 0x80: Reserved
    volatile uint32_t RESERVED_REG_84;      // 0x84: Reserved
    volatile uint32_t RESERVED_REG_88;      // 0x88: Reserved
    volatile uint32_t RESERVED_REG_8C;      // 0x8C: Reserved

    volatile uint32_t RESERVED_REG_90;      // 0x90: Reserved
    volatile uint32_t RESERVED_REG_94;      // 0x94: Reserved
    volatile uint32_t RESERVED_REG_98;      // 0x98: Reserved
    volatile uint32_t RESERVED_REG_9C;      // 0x9C: Reserved

    volatile uint32_t RESERVED_REG_A0;      // 0xA0: Reserved
    volatile uint32_t RESERVED_REG_A4;      // 0xA4: Reserved
    volatile uint32_t RESERVED_REG_A8;      // 0xA8: Reserved
    volatile uint32_t RESERVED_REG_AC;      // 0xAC: Reserved

    volatile uint32_t RESERVED_REG_B0;      // 0xB0: Reserved
    volatile uint32_t RESERVED_REG_B4;      // 0xB4: Reserved
    volatile uint32_t RESERVED_REG_B8;      // 0xB8: Reserved
    volatile uint32_t RESERVED_REG_BC;      // 0xBC: Reserved


    volatile uint32_t VEND_SPEC;      // 0xC0: Vendor Specific
    volatile uint32_t MMC_BOOT;       // 0xC4: MMC Boot
    volatile uint32_t VEND_SPEC2;     // 0xC8: Vendor Specific 2
    volatile uint32_t RESERVED_REG_CC;     // 0xCC: Reserved
    volatile uint32_t RESERVED_REG_D0;     // 0xD0: Reserved
    volatile uint32_t RESERVED_REG_D4;     // 0xD4: Reserved
    volatile uint32_t RESERVED_REG_D8;     // 0xD8: Reserved
    volatile uint32_t RESERVED_REG_DC;     // 0xDC: Reserved
    volatile uint32_t RESERVED_REG_E0;     // 0xE0: Reserved
    volatile uint32_t RESERVED_REG_E4;     // 0xE4: Reserved
    volatile uint32_t RESERVED_REG_E8;     // 0xE8: Reserved
    volatile uint32_t RESERVED_REG_EC;     // 0xEC: Reserved
    volatile uint32_t RESERVED_REG_F0;     // 0xF0: Reserved
    volatile uint32_t RESERVED_REG_F4;     // 0xF4: Reserved
    volatile uint32_t RESERVED_REG_F8;     // 0xF8: Reserved
    volatile uint32_t RESERVED_REG_FC;     // 0xFC: Reserved
    volatile uint32_t RESERVED_REG_100;     // 0x100: Reserved
    volatile uint32_t RESERVED_REG_104;     // 0x104: Reserved
    volatile uint32_t VEND_SDMMC_TUNING_SEL;     // 0x108: Vendor
    volatile uint32_t RESERVED_REG_10C;     // 0x10C: Reserved
    volatile uint32_t RESERVED_REG_110;     // 0x110: Reserved
    volatile uint32_t RESERVED_REG_114;     // 0x114: Reserved
    volatile uint32_t RESERVED_REG_118;     // 0x118: Reserved
    volatile uint32_t RESERVED_REG_11C;     // 0x11C: Reserved
    volatile uint32_t RESERVED_REG_120;     // 0x120: Reserved
    volatile uint32_t VEND_SDMMC_CTRL;		// 0x124: Vendor
    volatile uint32_t RESERVED_REG_128;     // 0x128: Reserved
    volatile uint32_t RESERVED_REG_12C;     // 0x12C: Reserved
    volatile uint32_t RESERVED_REG_130;     // 0x130: Reserved
    volatile uint32_t RESERVED_REG_134;     // 0x134: Reserved
    volatile uint32_t RESERVED_REG_138;     // 0x138: Reserved
    volatile uint32_t RESERVED_REG_13C;     // 0x13C: Reserved
    volatile uint32_t RESERVED_REG_140;     // 0x140: Reserved
    volatile uint32_t RESERVED_REG_144;     // 0x144: Reserved
    volatile uint32_t RESERVED_REG_148;     // 0x148: Reserved
    volatile uint32_t RESERVED_REG_14C;     // 0x14C: Reserved
    volatile uint32_t RESERVED_REG_150;     // 0x150: Reserved
    volatile uint32_t RESERVED_REG_154;     // 0x154: Reserved
    volatile uint32_t VEND_FORCE_INCERT; 	// 0x158: Reserved
    volatile uint32_t RESERVED_REG_15C;     // 0x15C: Reserved
    volatile uint32_t RESERVED_REG_160;     // 0x160: Reserved
    volatile uint32_t RESERVED_REG_164;     // 0x164: Reserved
    volatile uint32_t RESERVED_REG_168;     // 0x168: Reserved
    volatile uint32_t RESERVED_REG_16C;     // 0x16C: Reserved
    volatile uint32_t RESERVED_REG_170;     // 0x170: Reserved
    volatile uint32_t RESERVED_REG_174;     // 0x174: Reserved
    volatile uint32_t RESERVED_REG_178;     // 0x178: Reserved
    volatile uint32_t RESERVED_REG_17C;     // 0x17C: Reserved
    volatile uint32_t RESERVED_REG_180;     // 0x180: Reserved
    volatile uint32_t RESERVED_REG_184;     // 0x184: Reserved
    volatile uint32_t RESERVED_REG_188;     // 0x188: Reserved
    volatile uint32_t RESERVED_REG_18C;     // 0x18C: Reserved
    volatile uint32_t RESERVED_REG_190;     // 0x190: Reserved
    volatile uint32_t RESERVED_REG_194;     // 0x194: Reserved
    volatile uint32_t RESERVED_REG_198;     // 0x198: Reserved
    volatile uint32_t RESERVED_REG_19C;     // 0x19C: Reserved
    volatile uint32_t RESERVED_REG_1A0;     // 0x1A0: Reserved
    volatile uint32_t RESERVED_REG_1A4;     // 0x1A4: Reserved
    volatile uint32_t RESERVED_REG_1A8;     // 0x1A8: Reserved
    volatile uint32_t RESERVED_REG_1AC;     // 0x1AC: Reserved
    volatile uint32_t RESERVED_REG_1B0;     // 0x1B0: Reserved
    volatile uint32_t RESERVED_REG_1B4;     // 0x1B4: Reserved
    volatile uint32_t RESERVED_REG_1B8;     // 0x1B8: Reserved
    volatile uint32_t RESERVED_REG_1BC;     // 0x1BC: Reserved
    volatile uint32_t RESERVED_REG_1C0;     // 0x1C0: Reserved
    volatile uint32_t RESERVED_REG_1C4;     // 0x1C4: Reserved
    volatile uint32_t RESERVED_REG_1C8;     // 0x1C8: Reserved
    volatile uint32_t RESERVED_REG_1CC;     // 0x1CC: Reserved
    volatile uint32_t RESERVED_REG_1D0;     // 0x1D0: Reserved
    volatile uint32_t RESERVED_REG_1D4;     // 0x1D4: Reserved
    volatile uint32_t RESERVED_REG_1D8;     // 0x1D8: Reserved
    volatile uint32_t RESERVED_REG_1DC;     // 0x1DC: Reserved
    volatile uint32_t RESERVED_REG_1E0;     // 0x1E0: Reserved
    volatile uint32_t RESERVED_REG_1E4;     // 0x1E4: Reserved
    volatile uint32_t RESERVED_REG_1E8;     // 0x1E8: Reserved
    volatile uint32_t RESERVED_REG_1EC;     // 0x1EC: Reserved
    volatile uint32_t RESERVED_REG_1F0;     // 0x1F0: Reserved
    volatile uint32_t RESERVED_REG_1F4;     // 0x1F4: Reserved
    volatile uint32_t RESERVED_REG_1F8;     // 0x1F8: Reserved
    volatile uint32_t RESERVED_REG_1FC;     // 0x1FC: Reserved

    volatile uint32_t WRAPPER_RESET;		// 0x200: Vendor
    volatile uint32_t WRAPPER_CLOCK;		// 0x204: Vendor
    volatile uint32_t WRAPPER_TODIV;		// 0x208: Vendor
    volatile uint32_t WRAPPER_ACTIVE;		// 0x20C: Vendor
    volatile uint32_t WRAPPER_CONT;			// 0x210: Vendor
    volatile uint32_t WRAPPER_INIT;			// 0x214: Vendor
    volatile uint32_t WRAPPER_CLCOK2;		// 0x218: Vendor
    volatile uint32_t WRAPPER_CLCOK3;		// 0x21C: Vendor
    volatile uint32_t WRAPPER_AHBP;			// 0x220: Vendor
    volatile uint32_t RESERVED_REG_224;		// 0x224: Reserved
    volatile uint32_t RESERVED_REG_228;		// 0x228: Reserved
    volatile uint32_t RESERVED_REG_22C;		// 0x22C: Reserved
    volatile uint32_t RESERVED_REG_230;		// 0x230: Reserved
    volatile uint32_t RESERVED_REG_234;		// 0x234: Reserved
    volatile uint32_t RESERVED_REG_238;		// 0x238: Reserved
    volatile uint32_t RESERVED_REG_23C;		// 0x23C: Reserved
    volatile uint32_t WRAPPER_CAPABILITY0;	// 0x240: Vendor
    volatile uint32_t WRAPPER_CAPABILITY1;	// 0x244: Vendor
    volatile uint32_t WRAPPER_MAXCUR;		// 0x248: Vendor
    volatile uint32_t RESERVED_REG_24C;		// 0x24C: Reserved
    volatile uint32_t RESERVED_REG_250;		// 0x250: Reserved
    volatile uint32_t RESERVED_REG_254;		// 0x254: Reserved
    volatile uint32_t RESERVED_REG_258;		// 0x258: Reserved
    volatile uint32_t RESERVED_REG_25C;		// 0x25C: Reserved
    volatile uint32_t WRAPPER_PSET0;		// 0x260: Vendor
    volatile uint32_t WRAPPER_PSET1;		// 0x264: Vendor
    volatile uint32_t WRAPPER_PSET2;		// 0x268: Vendor
    volatile uint32_t WRAPPER_PSET3;		// 0x26C: Vendor
    // Add more registers as needed based on the hardware specification
} USDHC_Type;

/*! @brief extern variable for isr determination */
extern uint8_t sdc_interrupt_flag;
extern uint8_t sdc_interrupt_enable;
extern bool sdc_isr_done;
/******************************************************************************
 * Definitions.
 *****************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief Driver version 2.8.4. */
#define FSL_USDHC_DRIVER_VERSION (MAKE_VERSION(2U, 8U, 4U))
/*! @} */

/*! @brief Maximum block count can be set one time */
//#define USDHC_MAX_BLOCK_COUNT (USDHC_BLK_ATT_BLKCNT_MASK >> USDHC_BLK_ATT_BLKCNT_SHIFT)
#define USDHC_MAX_BLOCK_COUNT (512) // Mimi

/*! @brief USDHC scatter gather feature control macro */
#ifndef FSL_USDHC_ENABLE_SCATTER_GATHER_TRANSFER
#define FSL_USDHC_ENABLE_SCATTER_GATHER_TRANSFER 0U
#endif

/*! @brief check flag avalibility */
#define IS_USDHC_FLAG_SET(reg, flag) (((reg) & ((uint32_t)flag)) != 0UL)

#define USDHC_MMC_BOOT_BOOT_EN_MASK		(0x1 << 18)

/* 0x24h */
#define USDHC_PRES_STATE_RTR_MASK		(0x1 << 3)

/* 0x28h */
#define USDHC_PROT_CTRL_4DTW_MASK		(0x1 << 1)
#define USDHC_PROT_CTRL_8DTW_MASK		(0x1 << 5)
#define USDHC_PROT_CTRL_DTW_MASK		(USDHC_PROT_CTRL_4DTW_MASK | USDHC_PROT_CTRL_8DTW_MASK)
#define USDHC_PROT_CTRL_DTW(width)		(width==kUSDHC_DataBusWidth1Bit? 0 : (width==kUSDHC_DataBusWidth4Bit? USDHC_PROT_CTRL_4DTW_MASK : USDHC_PROT_CTRL_DTW_MASK) )

/* 0x2Ch */
#define USDHC_AUTOCMD12_ERR_STATUS_EXECUTE_TUNING_MASK	(0x1 << 22)
#define USDHC_AUTOCMD12_ERR_STATUS_SMP_CLK_SEL_MASK		(0x1 << 23)

/* 0x44h */
#define USDHC_HOST_CTRL_CAP_USE_TUNING_SDR50_MASK	(0x1 << 13)
#define USDHC_HOST_CTRL_CAP_TIME_COUNT_RETUNING_MASK		(0xF << 8)
#define USDHC_HOST_CTRL_CAP_TIME_COUNT_RETUNING(counter)	((counter&0xF) << 8)

#if 0
/*! @brief Enum _usdhc_status. USDHC status. */
enum
{
    kStatus_USDHC_BusyTransferring            = MAKE_STATUS(kStatusGroup_USDHC, 0U),  /*!< Transfer is on-going. */
    kStatus_USDHC_PrepareAdmaDescriptorFailed = MAKE_STATUS(kStatusGroup_USDHC, 1U),  /*!< Set DMA descriptor failed. */
    kStatus_USDHC_SendCommandFailed           = MAKE_STATUS(kStatusGroup_USDHC, 2U),  /*!< Send command failed. */
    kStatus_USDHC_TransferDataFailed          = MAKE_STATUS(kStatusGroup_USDHC, 3U),  /*!< Transfer data failed. */
    kStatus_USDHC_DMADataAddrNotAlign         = MAKE_STATUS(kStatusGroup_USDHC, 4U),  /*!< Data address not aligned. */
    kStatus_USDHC_ReTuningRequest             = MAKE_STATUS(kStatusGroup_USDHC, 5U),  /*!< Re-tuning request. */
    kStatus_USDHC_TuningError                 = MAKE_STATUS(kStatusGroup_USDHC, 6U),  /*!< Tuning error. */
    kStatus_USDHC_NotSupport                  = MAKE_STATUS(kStatusGroup_USDHC, 7U),  /*!< Not support. */
    kStatus_USDHC_TransferDataComplete        = MAKE_STATUS(kStatusGroup_USDHC, 8U),  /*!< Transfer data complete. */
    kStatus_USDHC_SendCommandSuccess          = MAKE_STATUS(kStatusGroup_USDHC, 9U),  /*!< Transfer command complete. */
    kStatus_USDHC_TransferDMAComplete         = MAKE_STATUS(kStatusGroup_USDHC, 10U), /*!< Transfer DMA complete. */
};
#endif // Mimi
#if 0
/*! @brief Enum _usdhc_capability_flag. Host controller capabilities flag mask.
 *  @anchor _usdhc_capability_flag
 */
enum
{
    kUSDHC_SupportAdmaFlag          = USDHC_HOST_CTRL_CAP_ADMAS_MASK, /*!< Support ADMA. */
    kUSDHC_SupportHighSpeedFlag     = USDHC_HOST_CTRL_CAP_HSS_MASK,   /*!< Support high-speed. */
    kUSDHC_SupportDmaFlag           = USDHC_HOST_CTRL_CAP_DMAS_MASK,  /*!< Support DMA. */
    kUSDHC_SupportSuspendResumeFlag = USDHC_HOST_CTRL_CAP_SRS_MASK,   /*!< Support suspend/resume. */
    kUSDHC_SupportV330Flag          = USDHC_HOST_CTRL_CAP_VS33_MASK,  /*!< Support voltage 3.3V. */
    kUSDHC_SupportV300Flag          = USDHC_HOST_CTRL_CAP_VS30_MASK,  /*!< Support voltage 3.0V. */
#if !(defined(FSL_FEATURE_USDHC_HAS_NO_VS18) && FSL_FEATURE_USDHC_HAS_NO_VS18)
    kUSDHC_SupportV180Flag          = USDHC_HOST_CTRL_CAP_VS18_MASK,  /*!< Support voltage 1.8V. */
#endif
    kUSDHC_Support4BitFlag          = (USDHC_HOST_CTRL_CAP_MBL_SHIFT << 0U),
    /*!< Flag in HTCAPBLT_MBL's position, supporting 4-bit mode. */
    kUSDHC_Support8BitFlag = (USDHC_HOST_CTRL_CAP_MBL_SHIFT << 1U),
    /*!< Flag in HTCAPBLT_MBL's position, supporting 8-bit mode. */
    kUSDHC_SupportDDR50Flag = USDHC_HOST_CTRL_CAP_DDR50_SUPPORT_MASK,
/*!< SD version 3.0 new feature, supporting DDR50 mode. */

#if defined(FSL_FEATURE_USDHC_HAS_SDR104_MODE) && (!FSL_FEATURE_USDHC_HAS_SDR104_MODE)
    kUSDHC_SupportSDR104Flag = 0, /*!< not support SDR104 mode */
#else
    kUSDHC_SupportSDR104Flag   = USDHC_HOST_CTRL_CAP_SDR104_SUPPORT_MASK, /*!< Support SDR104 mode. */
#endif
#if defined(FSL_FEATURE_USDHC_HAS_SDR50_MODE) && (!FSL_FEATURE_USDHC_HAS_SDR50_MODE)
    kUSDHC_SupportSDR50Flag = 0U, /*!< not support SDR50 mode */
#else
    kUSDHC_SupportSDR50Flag    = USDHC_HOST_CTRL_CAP_SDR50_SUPPORT_MASK,  /*!< Support SDR50 mode. */
#endif
};

/*! @brief Enum _usdhc_wakeup_event. Wakeup event mask.
 *  @anchor _usdhc_wakeup_event
 */
enum
{
    kUSDHC_WakeupEventOnCardInt    = USDHC_PROT_CTRL_WECINT_MASK, /*!< Wakeup on card interrupt. */
    kUSDHC_WakeupEventOnCardInsert = USDHC_PROT_CTRL_WECINS_MASK, /*!< Wakeup on card insertion. */
    kUSDHC_WakeupEventOnCardRemove = USDHC_PROT_CTRL_WECRM_MASK,  /*!< Wakeup on card removal. */
    kUSDHC_WakeupEventsAll =
        (kUSDHC_WakeupEventOnCardInt | kUSDHC_WakeupEventOnCardInsert | kUSDHC_WakeupEventOnCardRemove),
    /*!< All wakeup events */
};

/*! @brief Enum _usdhc_reset. Reset type mask.
 *  @anchor _usdhc_reset
 */
enum
{
    kUSDHC_ResetAll     = USDHC_SYS_CTRL_RSTA_MASK, /*!< Reset all except card detection. */
    kUSDHC_ResetCommand = USDHC_SYS_CTRL_RSTC_MASK, /*!< Reset command line. */
    kUSDHC_ResetData    = USDHC_SYS_CTRL_RSTD_MASK, /*!< Reset data line. */

#if defined(FSL_FEATURE_USDHC_HAS_SDR50_MODE) && (!FSL_FEATURE_USDHC_HAS_SDR50_MODE)
    kUSDHC_ResetTuning = 0U, /*!< no reset tuning circuit bit */
#else
    kUSDHC_ResetTuning         = USDHC_SYS_CTRL_RSTT_MASK,                /*!< Reset tuning circuit. */
#endif

    kUSDHC_ResetsAll = (kUSDHC_ResetAll | kUSDHC_ResetCommand | kUSDHC_ResetData | kUSDHC_ResetTuning),
    /*!< All reset types */
};

/*! @brief Enum _usdhc_transfer_flag. Transfer flag mask. */
enum
{
    kUSDHC_EnableDmaFlag = USDHC_MIX_CTRL_DMAEN_MASK, /*!< Enable DMA. */

    kUSDHC_CommandTypeSuspendFlag = USDHC_CMD_XFR_TYP_CMDTYP(1U), /*!< Suspend command. */
    kUSDHC_CommandTypeResumeFlag  = USDHC_CMD_XFR_TYP_CMDTYP(2U), /*!< Resume command. */
    kUSDHC_CommandTypeAbortFlag   = USDHC_CMD_XFR_TYP_CMDTYP(3U), /*!< Abort command. */

    kUSDHC_EnableBlockCountFlag    = USDHC_MIX_CTRL_BCEN_MASK,   /*!< Enable block count. */
    kUSDHC_EnableAutoCommand12Flag = USDHC_MIX_CTRL_AC12EN_MASK, /*!< Enable auto CMD12. */
    kUSDHC_DataReadFlag            = USDHC_MIX_CTRL_DTDSEL_MASK, /*!< Enable data read. */
    kUSDHC_MultipleBlockFlag       = USDHC_MIX_CTRL_MSBSEL_MASK, /*!< Multiple block data read/write. */
    kUSDHC_EnableAutoCommand23Flag = USDHC_MIX_CTRL_AC23EN_MASK, /*!< Enable auto CMD23. */

    kUSDHC_ResponseLength136Flag    = USDHC_CMD_XFR_TYP_RSPTYP(1U), /*!< 136-bit response length. */
    kUSDHC_ResponseLength48Flag     = USDHC_CMD_XFR_TYP_RSPTYP(2U), /*!< 48-bit response length. */
    kUSDHC_ResponseLength48BusyFlag = USDHC_CMD_XFR_TYP_RSPTYP(3U), /*!< 48-bit response length with busy status. */

    kUSDHC_EnableCrcCheckFlag   = USDHC_CMD_XFR_TYP_CCCEN_MASK, /*!< Enable CRC check. */
    kUSDHC_EnableIndexCheckFlag = USDHC_CMD_XFR_TYP_CICEN_MASK, /*!< Enable index check. */
    kUSDHC_DataPresentFlag      = USDHC_CMD_XFR_TYP_DPSEL_MASK, /*!< Data present flag. */
};

/*! @brief Enum _usdhc_present_status_flag. Present status flag mask.
 *  @anchor _usdhc_present_status_flag
 */
enum
{
    kUSDHC_CommandInhibitFlag      = USDHC_PRES_STATE_CIHB_MASK,  /*!< Command inhibit. */
    kUSDHC_DataInhibitFlag         = USDHC_PRES_STATE_CDIHB_MASK, /*!< Data inhibit. */
    kUSDHC_DataLineActiveFlag      = USDHC_PRES_STATE_DLA_MASK,   /*!< Data line active. */
    kUSDHC_SdClockStableFlag       = USDHC_PRES_STATE_SDSTB_MASK, /*!< SD bus clock stable. */
    kUSDHC_WriteTransferActiveFlag = USDHC_PRES_STATE_WTA_MASK,   /*!< Write transfer active. */
    kUSDHC_ReadTransferActiveFlag  = USDHC_PRES_STATE_RTA_MASK,   /*!< Read transfer active. */
    kUSDHC_BufferWriteEnableFlag   = USDHC_PRES_STATE_BWEN_MASK,  /*!< Buffer write enable. */
    kUSDHC_BufferReadEnableFlag    = USDHC_PRES_STATE_BREN_MASK,  /*!< Buffer read enable. */

#if defined(FSL_FEATURE_USDHC_HAS_SDR50_MODE) && (!FSL_FEATURE_USDHC_HAS_SDR50_MODE)
    kUSDHC_DelaySettingFinishedFlag = 0U, /*!< not support */
    kUSDHC_ReTuningRequestFlag      = 0U, /*!< not support */
#else
    kUSDHC_ReTuningRequestFlag = USDHC_PRES_STATE_RTR_MASK, /*!< Re-tuning request flag, only used for SDR104 mode. */
    kUSDHC_DelaySettingFinishedFlag = USDHC_PRES_STATE_TSCD_MASK, /*!< Delay setting finished flag. */
#endif

    kUSDHC_CardInsertedFlag     = USDHC_PRES_STATE_CINST_MASK, /*!< Card inserted. */
    kUSDHC_CommandLineLevelFlag = USDHC_PRES_STATE_CLSL_MASK,  /*!< Command line signal level. */

    kUSDHC_Data0LineLevelFlag = 1U << USDHC_PRES_STATE_DLSL_SHIFT,               /*!< Data0 line signal level. */
    kUSDHC_Data1LineLevelFlag = 1U << (USDHC_PRES_STATE_DLSL_SHIFT + 1U),        /*!< Data1 line signal level. */
    kUSDHC_Data2LineLevelFlag = 1U << (USDHC_PRES_STATE_DLSL_SHIFT + 2U),        /*!< Data2 line signal level. */
    kUSDHC_Data3LineLevelFlag = 1U << (USDHC_PRES_STATE_DLSL_SHIFT + 3U),        /*!< Data3 line signal level. */
    kUSDHC_Data4LineLevelFlag = 1U << (USDHC_PRES_STATE_DLSL_SHIFT + 4U),        /*!< Data4 line signal level. */
    kUSDHC_Data5LineLevelFlag = 1U << (USDHC_PRES_STATE_DLSL_SHIFT + 5U),        /*!< Data5 line signal level. */
    kUSDHC_Data6LineLevelFlag = 1U << (USDHC_PRES_STATE_DLSL_SHIFT + 6U),        /*!< Data6 line signal level. */
    kUSDHC_Data7LineLevelFlag = (int)(1U << (USDHC_PRES_STATE_DLSL_SHIFT + 7U)), /*!< Data7 line signal level. */
};
#endif //Bill
/*! 
 *  Bill move from fsl_usdhc.h to .c for isr mode
 */
// #define USDHC_INT_STATUS_CC_MASK	(0x1<<0)
// #define USDHC_INT_STATUS_TC_MASK	(0x1<<1)
// #define USDHC_INT_STATUS_BGE_MASK	(0x1<<2)
// #define USDHC_INT_STATUS_DINT_MASK	(0x1<<3)
// #define USDHC_INT_STATUS_BWR_MASK	(0x1<<4)
// #define USDHC_INT_STATUS_BRR_MASK	(0x1<<5)
// #define USDHC_INT_STATUS_CINS_MASK	(0x1<<6)
// #define USDHC_INT_STATUS_CRM_MASK	(0x1<<7)
// #define USDHC_INT_STATUS_CINT_MASK	(0x1<<8)

// #define USDHC_INT_STATUS_RTE_MASK	(0x1<<12)
// #define USDHC_INT_STATUS_TP_MASK	(0x0<<13)	// Mimi: Can't find in SPEC
// #define USDHC_INT_STATUS_TNE_MASK	(0x1<<26)

// #define USDHC_INT_STATUS_CTOE_MASK	(0x1<<16)
// #define USDHC_INT_STATUS_CCE_MASK	(0x1<<17)
// #define USDHC_INT_STATUS_CEBE_MASK	(0x1<<18)
// #define USDHC_INT_STATUS_CIE_MASK	(0x1<<19)
// #define USDHC_INT_STATUS_DTOE_MASK	(0x1<<20)
// #define USDHC_INT_STATUS_DCE_MASK	(0x1<<21)
// #define USDHC_INT_STATUS_DEBE_MASK	(0x1<<22)
// #define USDHC_INT_STATUS_AC12E_MASK	(0x1<<24)
// #define USDHC_INT_STATUS_DMAE_MASK	(0x1<<25)

// /*! @brief Enum _usdhc_interrupt_status_flag. Interrupt status flag mask.
//  *  @anchor _usdhc_interrupt_status_flag
//  */
// enum
// {
//     kUSDHC_CommandCompleteFlag  = USDHC_INT_STATUS_CC_MASK,   /*!< Command complete. */
//     kUSDHC_DataCompleteFlag     = USDHC_INT_STATUS_TC_MASK,   /*!< Data complete. */
//     kUSDHC_BlockGapEventFlag    = USDHC_INT_STATUS_BGE_MASK,  /*!< Block gap event. */
//     kUSDHC_DmaCompleteFlag      = USDHC_INT_STATUS_DINT_MASK, /*!< DMA interrupt. */
//     kUSDHC_BufferWriteReadyFlag = USDHC_INT_STATUS_BWR_MASK,  /*!< Buffer write ready. */
//     kUSDHC_BufferReadReadyFlag  = USDHC_INT_STATUS_BRR_MASK,  /*!< Buffer read ready. */
//     kUSDHC_CardInsertionFlag    = USDHC_INT_STATUS_CINS_MASK, /*!< Card inserted. */
//     kUSDHC_CardRemovalFlag      = USDHC_INT_STATUS_CRM_MASK,  /*!< Card removed. */
//     kUSDHC_CardInterruptFlag    = USDHC_INT_STATUS_CINT_MASK, /*!< Card interrupt. */

// #if defined(FSL_FEATURE_USDHC_HAS_SDR50_MODE) && (!FSL_FEATURE_USDHC_HAS_SDR50_MODE)
//     kUSDHC_ReTuningEventFlag = 0U, /*!< Re-Tuning event, only for SD3.0 SDR104 mode. */
//     kUSDHC_TuningPassFlag    = 0U, /*!< SDR104 mode tuning pass flag. */
//     kUSDHC_TuningErrorFlag   = 0U, /*!< SDR104 tuning error flag. */
// #else
//     kUSDHC_ReTuningEventFlag        = USDHC_INT_STATUS_RTE_MASK,  /*!< Re-Tuning event, only for SD3.0 SDR104 mode. */
//     kUSDHC_TuningPassFlag           = USDHC_INT_STATUS_TP_MASK,   /*!< SDR104 mode tuning pass flag. */
//     kUSDHC_TuningErrorFlag          = USDHC_INT_STATUS_TNE_MASK,  /*!< SDR104 tuning error flag. */
// #endif

//     kUSDHC_CommandTimeoutFlag     = USDHC_INT_STATUS_CTOE_MASK,  /*!< Command timeout error. */
//     kUSDHC_CommandCrcErrorFlag    = USDHC_INT_STATUS_CCE_MASK,   /*!< Command CRC error. */
//     kUSDHC_CommandEndBitErrorFlag = USDHC_INT_STATUS_CEBE_MASK,  /*!< Command end bit error. */
//     kUSDHC_CommandIndexErrorFlag  = USDHC_INT_STATUS_CIE_MASK,   /*!< Command index error. */
//     kUSDHC_DataTimeoutFlag        = USDHC_INT_STATUS_DTOE_MASK,  /*!< Data timeout error. */
//     kUSDHC_DataCrcErrorFlag       = USDHC_INT_STATUS_DCE_MASK,   /*!< Data CRC error. */
//     kUSDHC_DataEndBitErrorFlag    = USDHC_INT_STATUS_DEBE_MASK,  /*!< Data end bit error. */
//     kUSDHC_AutoCommand12ErrorFlag = USDHC_INT_STATUS_AC12E_MASK, /*!< Auto CMD12 error. */
//     kUSDHC_DmaErrorFlag           = USDHC_INT_STATUS_DMAE_MASK,  /*!< DMA error. */

//     kUSDHC_CommandErrorFlag = (kUSDHC_CommandTimeoutFlag | kUSDHC_CommandCrcErrorFlag | kUSDHC_CommandEndBitErrorFlag |
//                                kUSDHC_CommandIndexErrorFlag), /*!< Command error */
//     kUSDHC_DataErrorFlag    = (kUSDHC_DataTimeoutFlag | kUSDHC_DataCrcErrorFlag | kUSDHC_DataEndBitErrorFlag |
//                             kUSDHC_AutoCommand12ErrorFlag),                                        /*!< Data error */
//     kUSDHC_ErrorFlag        = (kUSDHC_CommandErrorFlag | kUSDHC_DataErrorFlag | kUSDHC_DmaErrorFlag), /*!< All error */

//     kUSDHC_DataFlag = (kUSDHC_DataCompleteFlag | kUSDHC_BufferWriteReadyFlag | kUSDHC_BufferReadReadyFlag |
//                        kUSDHC_DataErrorFlag), /*!< Data interrupts */

//     kUSDHC_DataDMAFlag = (kUSDHC_DataCompleteFlag | kUSDHC_DataErrorFlag | kUSDHC_DmaErrorFlag), /*!< Data interrupts */

//     kUSDHC_CommandFlag      = (kUSDHC_CommandErrorFlag | kUSDHC_CommandCompleteFlag), /*!< Command interrupts */
//     kUSDHC_CardDetectFlag   = (kUSDHC_CardInsertionFlag | kUSDHC_CardRemovalFlag),    /*!< Card detection interrupts */
//     kUSDHC_SDR104TuningFlag = (kUSDHC_TuningErrorFlag | kUSDHC_TuningPassFlag | kUSDHC_ReTuningEventFlag),
//     /*!< SDR104 tuning flag. */
//     kUSDHC_AllInterruptFlags =
//         (kUSDHC_BlockGapEventFlag | kUSDHC_CardInterruptFlag | kUSDHC_CommandFlag | kUSDHC_DataFlag | kUSDHC_ErrorFlag |
//          kUSDHC_SDR104TuningFlag | kUSDHC_DmaCompleteFlag), /*!< All flags mask */
// };
#if 0 //Bill
/*! @brief Enum _usdhc_auto_command12_error_status_flag. Auto CMD12 error status flag mask.
 *  @anchor _usdhc_auto_command12_error_status_flag
 */
enum
{
    kUSDHC_AutoCommand12NotExecutedFlag = USDHC_AUTOCMD12_ERR_STATUS_AC12NE_MASK,    /*!< Not executed error. */
    kUSDHC_AutoCommand12TimeoutFlag     = USDHC_AUTOCMD12_ERR_STATUS_AC12TOE_MASK,   /*!< Timeout error. */
    kUSDHC_AutoCommand12EndBitErrorFlag = USDHC_AUTOCMD12_ERR_STATUS_AC12EBE_MASK,   /*!< End bit error. */
    kUSDHC_AutoCommand12CrcErrorFlag    = USDHC_AUTOCMD12_ERR_STATUS_AC12CE_MASK,    /*!< CRC error. */
    kUSDHC_AutoCommand12IndexErrorFlag  = USDHC_AUTOCMD12_ERR_STATUS_AC12IE_MASK,    /*!< Index error. */
    kUSDHC_AutoCommand12NotIssuedFlag   = USDHC_AUTOCMD12_ERR_STATUS_CNIBAC12E_MASK, /*!< Not issued error. */
};

/*! @brief Enum _usdhc_standard_tuning. Standard tuning flag. */
enum
{
#if defined(FSL_FEATURE_USDHC_HAS_SDR50_MODE) && (!FSL_FEATURE_USDHC_HAS_SDR50_MODE)
    kUSDHC_ExecuteTuning        = 0U, /*!< not support */
    kUSDHC_TuningSampleClockSel = 0U, /*!< not support */
#else
    kUSDHC_ExecuteTuning = USDHC_AUTOCMD12_ERR_STATUS_EXECUTE_TUNING_MASK, /*!< Used to start tuning procedure. */
    kUSDHC_TuningSampleClockSel =
        USDHC_AUTOCMD12_ERR_STATUS_SMP_CLK_SEL_MASK,               /*!< When <b>std_tuning_en</b> bit is set, this
                                                                    bit is used to select sampleing clock. */
#endif
};

/*! @brief Enum _usdhc_adma_error_status_flag. ADMA error status flag mask.
 *  @anchor _usdhc_adma_error_status_flag
 */
enum
{
    kUSDHC_AdmaLenghMismatchFlag   = USDHC_ADMA_ERR_STATUS_ADMALME_MASK, /*!< Length mismatch error. */
    kUSDHC_AdmaDescriptorErrorFlag = USDHC_ADMA_ERR_STATUS_ADMADCE_MASK, /*!< Descriptor error. */
};

/*!
 * @brief Enum _usdhc_adma_error_state. ADMA error state.
 *
 * This state is the detail state when ADMA error has occurred.
 */
enum
{
    kUSDHC_AdmaErrorStateStopDma = 0x00U,
    /*!< Stop DMA, previous location set in the ADMA system address is errored address. */
    kUSDHC_AdmaErrorStateFetchDescriptor = 0x01U,
    /*!< Fetch descriptor, current location set in the ADMA system address is errored address. */
    kUSDHC_AdmaErrorStateChangeAddress = 0x02U, /*!< Change address, no DMA error has occurred. */
    kUSDHC_AdmaErrorStateTransferData  = 0x03U,
    /*!< Transfer data, previous location set in the ADMA system address is errored address. */
    kUSDHC_AdmaErrorStateInvalidLength     = 0x04U, /*!< Invalid length in ADMA descriptor. */
    kUSDHC_AdmaErrorStateInvalidDescriptor = 0x08U, /*!< Invalid descriptor fetched by ADMA. */

    kUSDHC_AdmaErrorState = kUSDHC_AdmaErrorStateInvalidLength | kUSDHC_AdmaErrorStateInvalidDescriptor |
                            kUSDHC_AdmaErrorStateFetchDescriptor, /*!< ADMA error state */
};

/*! @brief Enum _usdhc_force_event. Force event bit position.
 *  @anchor _usdhc_force_event
 */
enum
{
    kUSDHC_ForceEventAutoCommand12NotExecuted =
        USDHC_FORCE_EVENT_FEVTAC12NE_MASK, /*!< Auto CMD12 not executed error. */
    kUSDHC_ForceEventAutoCommand12Timeout    = USDHC_FORCE_EVENT_FEVTAC12TOE_MASK,  /*!< Auto CMD12 timeout error. */
    kUSDHC_ForceEventAutoCommand12CrcError   = USDHC_FORCE_EVENT_FEVTAC12CE_MASK,   /*!< Auto CMD12 CRC error. */
    kUSDHC_ForceEventEndBitError             = USDHC_FORCE_EVENT_FEVTAC12EBE_MASK,  /*!< Auto CMD12 end bit error. */
    kUSDHC_ForceEventAutoCommand12IndexError = USDHC_FORCE_EVENT_FEVTAC12IE_MASK,   /*!< Auto CMD12 index error. */
    kUSDHC_ForceEventAutoCommand12NotIssued = USDHC_FORCE_EVENT_FEVTCNIBAC12E_MASK, /*!< Auto CMD12 not issued error. */
    kUSDHC_ForceEventCommandTimeout         = USDHC_FORCE_EVENT_FEVTCTOE_MASK,      /*!< Command timeout error. */
    kUSDHC_ForceEventCommandCrcError        = USDHC_FORCE_EVENT_FEVTCCE_MASK,       /*!< Command CRC error. */
    kUSDHC_ForceEventCommandEndBitError     = USDHC_FORCE_EVENT_FEVTCEBE_MASK,      /*!< Command end bit error. */
    kUSDHC_ForceEventCommandIndexError      = USDHC_FORCE_EVENT_FEVTCIE_MASK,       /*!< Command index error. */
    kUSDHC_ForceEventDataTimeout            = USDHC_FORCE_EVENT_FEVTDTOE_MASK,      /*!< Data timeout error. */
    kUSDHC_ForceEventDataCrcError           = USDHC_FORCE_EVENT_FEVTDCE_MASK,       /*!< Data CRC error. */
    kUSDHC_ForceEventDataEndBitError        = USDHC_FORCE_EVENT_FEVTDEBE_MASK,      /*!< Data end bit error. */
    kUSDHC_ForceEventAutoCommand12Error     = USDHC_FORCE_EVENT_FEVTAC12E_MASK,     /*!< Auto CMD12 error. */
    kUSDHC_ForceEventCardInt                = (int)USDHC_FORCE_EVENT_FEVTCINT_MASK, /*!< Card interrupt. */
    kUSDHC_ForceEventDmaError               = USDHC_FORCE_EVENT_FEVTDMAE_MASK,      /*!< Dma error. */
#if defined(FSL_FEATURE_USDHC_HAS_SDR50_MODE) && (!FSL_FEATURE_USDHC_HAS_SDR50_MODE)
    kUSDHC_ForceEventTuningError = 0U, /*!< not support */
#else
    kUSDHC_ForceEventTuningError = USDHC_FORCE_EVENT_FEVTTNE_MASK, /*!< Tuning error. */
#endif

    kUSDHC_ForceEventsAll =
        (int)(USDHC_FORCE_EVENT_FEVTAC12NE_MASK | USDHC_FORCE_EVENT_FEVTAC12TOE_MASK |
              USDHC_FORCE_EVENT_FEVTAC12CE_MASK | USDHC_FORCE_EVENT_FEVTAC12EBE_MASK |
              USDHC_FORCE_EVENT_FEVTAC12IE_MASK | USDHC_FORCE_EVENT_FEVTCNIBAC12E_MASK |
              USDHC_FORCE_EVENT_FEVTCTOE_MASK | USDHC_FORCE_EVENT_FEVTCCE_MASK | USDHC_FORCE_EVENT_FEVTCEBE_MASK |
              USDHC_FORCE_EVENT_FEVTCIE_MASK | USDHC_FORCE_EVENT_FEVTDTOE_MASK | USDHC_FORCE_EVENT_FEVTDCE_MASK |
              USDHC_FORCE_EVENT_FEVTDEBE_MASK | USDHC_FORCE_EVENT_FEVTAC12E_MASK | USDHC_FORCE_EVENT_FEVTCINT_MASK |
              USDHC_FORCE_EVENT_FEVTDMAE_MASK | kUSDHC_ForceEventTuningError), /*!< All force event flags mask. */
};
#endif // Mimi
/*! @brief Data transfer direction. */
typedef enum _usdhc_transfer_direction
{
    kUSDHC_TransferDirectionReceive = 1U, /*!< USDHC transfer direction receive. */
    kUSDHC_TransferDirectionSend    = 0U, /*!< USDHC transfer direction send. */
} usdhc_transfer_direction_t;

/*! @brief Data transfer width. */
typedef enum _usdhc_data_bus_width
{
    kUSDHC_DataBusWidth1Bit = 0U, /*!< 1-bit mode */
    kUSDHC_DataBusWidth4Bit = 1U, /*!< 4-bit mode */
    kUSDHC_DataBusWidth8Bit = 2U, /*!< 8-bit mode */
} usdhc_data_bus_width_t;

/*! @brief Endian mode */
typedef enum _usdhc_endian_mode
{
    kUSDHC_EndianModeBig         = 0U, /*!< Big endian mode. */
    kUSDHC_EndianModeHalfWordBig = 1U, /*!< Half word big endian mode. */
    kUSDHC_EndianModeLittle      = 2U, /*!< Little endian mode. */
} usdhc_endian_mode_t;

/*! @brief DMA mode */
typedef enum _usdhc_dma_mode
{
    kUSDHC_DmaModeSimple = 0U, /*!< External DMA. */
    kUSDHC_DmaModeAdma1  = 1U, /*!< ADMA1 is selected. */
    kUSDHC_DmaModeAdma2  = 2U, /*!< ADMA2 is selected. */
    kUSDHC_ExternalDMA   = 3U, /*!< External DMA mode selected. */
} usdhc_dma_mode_t;

#define USDHC_PROT_CTRL_SABGREQ_MASK 	(0x1<<0)
#define USDHC_PROT_CTRL_CREQ_MASK		(0x1<<1)
#define USDHC_PROT_CTRL_RWCTL_MASK 		(0x1<<2)
#define USDHC_PROT_CTRL_IABG_MASK 		(0x1<<3)
/*! @brief Enum _usdhc_sdio_control_flag. SDIO control flag mask.
 *  @anchor _usdhc_sdio_control_flag
 */
enum
{
    kUSDHC_StopAtBlockGapFlag      = USDHC_PROT_CTRL_SABGREQ_MASK, /*!< Stop at block gap. */
    kUSDHC_ReadWaitControlFlag     = USDHC_PROT_CTRL_RWCTL_MASK,   /*!< Read wait control. */
    kUSDHC_InterruptAtBlockGapFlag = USDHC_PROT_CTRL_IABG_MASK,    /*!< Interrupt at block gap. */
//    kUSDHC_ReadDoneNo8CLK = USDHC_PROT_CTRL_RD_DONE_NO_8CLK_MASK,  /*!< Read done without 8 clk for block gap. */	// Mimi
//    kUSDHC_ExactBlockNumberReadFlag = USDHC_PROT_CTRL_NON_EXACT_BLK_RD_MASK, /*!< Exact block number read. */	// Mimi
};

/*! @brief MMC card boot mode */
typedef enum _usdhc_boot_mode
{
    kUSDHC_BootModeNormal      = 0U, /*!< Normal boot */
    kUSDHC_BootModeAlternative = 1U, /*!< Alternative boot */
} usdhc_boot_mode_t;

/*! @brief The command type */
typedef enum _usdhc_card_command_type
{
    kCARD_CommandTypeNormal  = 0U, /*!< Normal command */
    kCARD_CommandTypeSuspend = 1U, /*!< Suspend command */
    kCARD_CommandTypeResume  = 2U, /*!< Resume command */
    kCARD_CommandTypeAbort   = 3U, /*!< Abort command */
    kCARD_CommandTypeEmpty   = 4U, /*!< Empty command */
} usdhc_card_command_type_t;

/*!
 * @brief The command response type.
 *
 * Defines the command response type from card to host controller.
 */
typedef enum _usdhc_card_response_type
{
    kCARD_ResponseTypeNone = 0U, /*!< Response type: none */
    kCARD_ResponseTypeR1   = 1U, /*!< Response type: R1 */
    kCARD_ResponseTypeR1b  = 2U, /*!< Response type: R1b */
    kCARD_ResponseTypeR2   = 3U, /*!< Response type: R2 */
    kCARD_ResponseTypeR3   = 4U, /*!< Response type: R3 */
    kCARD_ResponseTypeR4   = 5U, /*!< Response type: R4 */
    kCARD_ResponseTypeR5   = 6U, /*!< Response type: R5 */
    kCARD_ResponseTypeR5b  = 7U, /*!< Response type: R5b */
    kCARD_ResponseTypeR6   = 8U, /*!< Response type: R6 */
    kCARD_ResponseTypeR7   = 9U, /*!< Response type: R7 */
} usdhc_card_response_type_t;

/*! @brief The alignment size for ADDRESS filed in ADMA1's descriptor. */
#define USDHC_ADMA1_ADDRESS_ALIGN (4096U)
/*! @brief The alignment size for LENGTH field in ADMA1's descriptor. */
#define USDHC_ADMA1_LENGTH_ALIGN (4096U)
/*! @brief The alignment size for ADDRESS field in ADMA2's descriptor. */
#define USDHC_ADMA2_ADDRESS_ALIGN (4U)
/*! @brief The alignment size for LENGTH filed in ADMA2's descriptor. */
#define USDHC_ADMA2_LENGTH_ALIGN (4U)

/* ADMA1 descriptor table:
 * |------------------------|---------|--------------------------|
 * | Address/page field     |Reserved |         Attribute        |
 * |------------------------|---------|--------------------------|
 * |31                    12|11      6|05  |04  |03|02 |01 |00   |
 * |------------------------|---------|----|----|--|---|---|-----|
 * | address or data length | 000000  |Act2|Act1| 0|Int|End|Valid|
 * |------------------------|---------|----|----|--|---|---|-----|
 *
 * ADMA2 action table:
 * |------|------|-----------------|-------|-------------|
 * | Act2 | Act1 |     Comment     | 31-28 | 27 - 12     |
 * |------|------|-----------------|---------------------|
 * |   0  |   0  | No op           | Don't care          |
 * |------|------|-----------------|-------|-------------|
 * |   0  |   1  | Set data length |  0000 | Data Length |
 * |------|------|-----------------|-------|-------------|
 * |   1  |   0  | Transfer data   | Data address        |
 * |------|------|-----------------|---------------------|
 * |   1  |   1  | Link descriptor | Descriptor address  |
 * |------|------|-----------------|---------------------|
 */
/****************************tables below are created only for Doxygen*********************************/
/*! @brief The bit shift for ADDRESS filed in ADMA1's descriptor.
 *  <table>
 *  <caption>ADMA1 descriptor table</caption>
 *  <tr><th>Address/page field     <th>Reserved   <th colspan="6">Attribute
 *  <tr><td>31 12                  <td>11 6       <td>05   <td>04   <td>03 <td>02  <td>01  <td>00
 *  <tr><td>address or data length <td>000000     <td>Act2 <td>Act1 <td>0  <td>Int <td>End <td>Valid
 *  </table>
 *
 *  <table>
 *  <caption>ADMA2 action</caption>
 *  <tr><th>Act2  <th>Act1      <th>Comment            <th>31-28    <th>27-12
 *  <tr><td>0     <td>0         <td>No op              <td colspan="2">Don't care
 *  <tr><td>0     <td>1         <td>Set data length    <td>0000     <td> Data Length
 *  <tr><td>1     <td>0         <td>Transfer data      <td colspan="2">Data address
 *  <tr><td>1     <td>1         <td>Link descriptor    <td colspan="2">Descriptor address
 *  </table>
 */
#define USDHC_ADMA1_DESCRIPTOR_ADDRESS_SHIFT (12U)
/*! @brief The bit mask for ADDRESS field in ADMA1's descriptor. */
#define USDHC_ADMA1_DESCRIPTOR_ADDRESS_MASK (0xFFFFFU)
/*! @brief The bit shift for LENGTH filed in ADMA1's descriptor. */
#define USDHC_ADMA1_DESCRIPTOR_LENGTH_SHIFT (12U)
/*! @brief The mask for LENGTH field in ADMA1's descriptor. */
#define USDHC_ADMA1_DESCRIPTOR_LENGTH_MASK (0xFFFFU)
/*! @brief The maximum value of LENGTH filed in ADMA1's descriptor.
 * Since the max transfer size ADMA1 support is 65535 which is indivisible by
 * 4096, so to make sure a large data load transfer (>64KB) continuously (require the data
 * address be always align with 4096), software will set the maximum data length
 * for ADMA1 to (64 - 4)KB.
 */
#define USDHC_ADMA1_DESCRIPTOR_MAX_LENGTH_PER_ENTRY (USDHC_ADMA1_DESCRIPTOR_LENGTH_MASK + 1U - 4096U)

/*! @brief Enum _usdhc_adma1_descriptor_flag. The mask for the control/status field in ADMA1 descriptor. */
enum
{
    kUSDHC_Adma1DescriptorValidFlag     = (1U << 0U),                        /*!< Valid flag. */
    kUSDHC_Adma1DescriptorEndFlag       = (1U << 1U),                        /*!< End flag. */
    kUSDHC_Adma1DescriptorInterrupFlag  = (1U << 2U),                        /*!< Interrupt flag. */
    kUSDHC_Adma1DescriptorActivity1Flag = (1U << 4U),                        /*!< Activity 1 flag. */
    kUSDHC_Adma1DescriptorActivity2Flag = (1U << 5U),                        /*!< Activity 2 flag. */
    kUSDHC_Adma1DescriptorTypeNop       = (kUSDHC_Adma1DescriptorValidFlag), /*!< No operation. */
    kUSDHC_Adma1DescriptorTypeTransfer  = (kUSDHC_Adma1DescriptorActivity2Flag | kUSDHC_Adma1DescriptorValidFlag),
    /*!< Transfer data. */
    kUSDHC_Adma1DescriptorTypeLink      = (kUSDHC_Adma1DescriptorActivity1Flag | kUSDHC_Adma1DescriptorActivity2Flag |
                                      kUSDHC_Adma1DescriptorValidFlag), /*!< Link descriptor. */
    kUSDHC_Adma1DescriptorTypeSetLength = (kUSDHC_Adma1DescriptorActivity1Flag | kUSDHC_Adma1DescriptorValidFlag),
    /*!< Set data length. */
};

/* ADMA2 descriptor table:
 * |----------------|---------------|-------------|--------------------------|
 * | Address field  |     Length    | Reserved    |         Attribute        |
 * |----------------|---------------|-------------|--------------------------|
 * |63            32|31           16|15         06|05  |04  |03|02 |01 |00   |
 * |----------------|---------------|-------------|----|----|--|---|---|-----|
 * | 32-bit address | 16-bit length | 0000000000  |Act2|Act1| 0|Int|End|Valid|
 * |----------------|---------------|-------------|----|----|--|---|---|-----|
 *
 * ADMA2 action table:
 * | Act2 | Act1 |     Comment     | Operation                                                         |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   0  |   0  | No op           | Don't care                                                        |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   0  |   1  | Reserved        | Read this line and go to next one                                 |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   1  |   0  | Transfer data   | Transfer data with address and length set in this descriptor line |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   1  |   1  | Link descriptor | Link to another descriptor                                        |
 * |------|------|-----------------|-------------------------------------------------------------------|
 */
/**********************************tables below are created only for Doxygen***********************************/
/*! @brief The bit shift for LENGTH field in ADMA2's descriptor.
 *
 * <table>
 * <caption>ADMA2 descriptor table</caption>
 * <tr><th>Address field    <th>Length         <th>Reserved     <th colspan="6">Attribute
 * <tr><td>63 32            <td>31 16          <td>15 06        <td>05   <td>04   <td>03  <td>02  <td>01  <td>00
 * <tr><td>32-bit address   <td>16-bit length  <td>0000000000   <td>Act2 <td>Act1 <td>0   <td>Int <td>End <td>Valid
 *</table>
 *
 * <table>
 * <caption>ADMA2 action</caption>
 * <tr><th>Act2   <th>Act1   <th>Comment          <th>Operation
 * <tr><td> 0     <td>0      <td>No op            <td>Don't care
 * <tr><td> 0     <td>1      <td> Reserved        <td> Read this line and go to next one
 * <tr><td> 1     <td>0      <td>Transfer data    <td>Transfer data with address and length set in this descriptor line
 * <tr><td> 1     <td>1      <td>Link descriptor  <td>Link to another descriptor
 * </table>
 */
#define USDHC_ADMA2_DESCRIPTOR_LENGTH_SHIFT (16U)
/*! @brief The bit mask for LENGTH field in ADMA2's descriptor. */
#define USDHC_ADMA2_DESCRIPTOR_LENGTH_MASK (0xFFFFU)
/*! @brief The maximum value of LENGTH field in ADMA2's descriptor. */
#define USDHC_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY (USDHC_ADMA2_DESCRIPTOR_LENGTH_MASK - 3U)

/*! @brief Enum _usdhc_adma2_descriptor_flag. ADMA1 descriptor control and status mask. */
enum
{
    kUSDHC_Adma2DescriptorValidFlag     = (1U << 0U), /*!< Valid flag. */
    kUSDHC_Adma2DescriptorEndFlag       = (1U << 1U), /*!< End flag. */
    kUSDHC_Adma2DescriptorInterruptFlag = (1U << 2U), /*!< Interrupt flag. */
    kUSDHC_Adma2DescriptorActivity1Flag = (1U << 4U), /*!< Activity 1 mask. */
    kUSDHC_Adma2DescriptorActivity2Flag = (1U << 5U), /*!< Activity 2 mask. */

    kUSDHC_Adma2DescriptorTypeNop      = (kUSDHC_Adma2DescriptorValidFlag), /*!< No operation. */
    kUSDHC_Adma2DescriptorTypeReserved = (kUSDHC_Adma2DescriptorActivity1Flag | kUSDHC_Adma2DescriptorValidFlag),
    /*!< Reserved. */
    kUSDHC_Adma2DescriptorTypeTransfer = (kUSDHC_Adma2DescriptorActivity2Flag | kUSDHC_Adma2DescriptorValidFlag),
    /*!< Transfer type. */
    kUSDHC_Adma2DescriptorTypeLink = (kUSDHC_Adma2DescriptorActivity1Flag | kUSDHC_Adma2DescriptorActivity2Flag |
                                      kUSDHC_Adma2DescriptorValidFlag), /*!< Link type. */
};
#if 0
/*! @brief Enum _usdhc_adma_flag. ADMA descriptor configuration flag.
 *  @anchor _usdhc_adma_flag
 */
enum
{
    kUSDHC_AdmaDescriptorSingleFlag = 0U,
    /*!< Try to finish the transfer in a single ADMA descriptor. If transfer size is bigger than one
       ADMA descriptor's ability, new another descriptor for data transfer. */
    kUSDHC_AdmaDescriptorMultipleFlag =
        1U, /*!< Create multiple ADMA descriptors within the ADMA table, this is used for
             mmc boot mode specifically, which need
             to modify the ADMA descriptor on the fly, so the flag should be used
             combining with stop at block gap feature. */
};
#endif // Mimi
/*! @brief DMA transfer burst len config. */
typedef enum _usdhc_burst_len
{
    kUSDHC_EnBurstLenForINCR         = 0x01U, /*!< Enable burst len for INCR. */
    kUSDHC_EnBurstLenForINCR4816     = 0x02U, /*!< Enable burst len for INCR4/INCR8/INCR16. */
    kUSDHC_EnBurstLenForINCR4816WRAP = 0x04U, /*!< Enable burst len for INCR4/8/16 WRAP. */
} usdhc_burst_len_t;
#if 0
/*! @brief Enum _usdhc_transfer_data_type. Tansfer data type definition. */
enum
{
    kUSDHC_TransferDataNormal        = 0U, /*!< Transfer normal read/write data. */
    kUSDHC_TransferDataTuning        = 1U, /*!< Transfer tuning data. */
    kUSDHC_TransferDataBoot          = 2U, /*!< Transfer boot data. */
    kUSDHC_TransferDataBootcontinous = 3U, /*!< Transfer boot data continuously. */
};
#endif // Mimi
/*! @brief Defines the ADMA1 descriptor structure. */
typedef uint32_t usdhc_adma1_descriptor_t;

/*! @brief Defines the ADMA2 descriptor structure. */
typedef struct _usdhc_adma2_descriptor
{
    uint32_t attribute;      /*!< The control and status field. */
    const uint32_t *address; /*!< The address field. */
} usdhc_adma2_descriptor_t;

/*!
 * @brief USDHC capability information.
 *
 * Defines a structure to save the capability information of USDHC.
 */
typedef struct _usdhc_capability
{
    uint32_t sdVersion;      /*!< Support SD card/sdio version. */
    uint32_t mmcVersion;     /*!< Support EMMC card version. */
    uint32_t maxBlockLength; /*!< Maximum block length united as byte. */
    uint32_t maxBlockCount;  /*!< Maximum block count can be set one time. */
    uint32_t flags;          /*!< Capability flags to indicate the support information(@ref _usdhc_capability_flag). */
} usdhc_capability_t;

/*! @brief Data structure to configure the MMC boot feature. */
typedef struct _usdhc_boot_config
{
    uint32_t ackTimeoutCount;      /*!< Timeout value for the boot ACK. The available range is 0 ~ 15. */
    usdhc_boot_mode_t bootMode;    /*!< Boot mode selection. */
    uint32_t blockCount;           /*!< Stop at block gap value of automatic mode. Available range is 0 ~ 65535. */
    size_t blockSize;              /*!< Block size. */
    bool enableBootAck;            /*!< Enable or disable boot ACK. */
    bool enableAutoStopAtBlockGap; /*!< Enable or disable auto stop at block gap function in boot period. */
} usdhc_boot_config_t;

/*! @brief Data structure to initialize the USDHC. */
typedef struct _usdhc_config
{
    uint32_t dataTimeout;           /*!< Data timeout value. */
    usdhc_endian_mode_t endianMode; /*!< Endian mode. */
    uint8_t readWatermarkLevel;     /*!< Watermark level for DMA read operation. Available range is 1 ~ 128. */
    uint8_t writeWatermarkLevel;    /*!< Watermark level for DMA write operation. Available range is 1 ~ 128. */
#if !(defined(FSL_FEATURE_USDHC_HAS_NO_RW_BURST_LEN) && FSL_FEATURE_USDHC_HAS_NO_RW_BURST_LEN)
    uint8_t readBurstLen;  /*!< Read burst len. */
    uint8_t writeBurstLen; /*!< Write burst len. */
#endif
} usdhc_config_t;

/*!
 * @brief Card command descriptor.
 *
 * Defines card command-related attribute.
 */
typedef struct _usdhc_command
{
    uint32_t index;                          /*!< Command index. */
    uint32_t argument;                       /*!< Command argument. */
    usdhc_card_command_type_t type;          /*!< Command type. */
    usdhc_card_response_type_t responseType; /*!< Command response type. */
    uint32_t response[4U];                   /*!< Response for this command. */
    uint32_t responseErrorFlags;             /*!< Response error flag, which need to check
                                                 the command reponse. */
    uint32_t flags;                          /*!< Cmd flags. */
} usdhc_command_t;

/*! @brief ADMA configuration. */
typedef struct _usdhc_adma_config
{
    usdhc_dma_mode_t dmaMode; /*!< DMA mode. */
#if !(defined(FSL_FEATURE_USDHC_HAS_NO_RW_BURST_LEN) && FSL_FEATURE_USDHC_HAS_NO_RW_BURST_LEN)
    usdhc_burst_len_t burstLen; /*!< Burst len config. */
#endif
    uint32_t *admaTable;     /*!< ADMA table address, can't be null if transfer way is ADMA1/ADMA2. */
    uint32_t admaTableWords; /*!< ADMA table length united as words, can't be 0 if transfer way is ADMA1/ADMA2. */
} usdhc_adma_config_t;

/*!
 * @brief Card scatter gather data list.
 *
 * Allow application register uncontinuous data buffer for data transfer.
 */
typedef struct _usdhc_scatter_gather_data_list
{
    uint32_t *dataAddr;
    uint32_t dataSize;
    struct _usdhc_scatter_gather_data_list *dataList;
} usdhc_scatter_gather_data_list_t;

/*!
 * @brief Card scatter gather data descriptor.
 *
 * Defines a structure to contain data-related attribute. The 'enableIgnoreError' is used when upper card
 * driver wants to ignore the error event to read/write all the data and not to stop read/write immediately when an
 * error event happens. For example, bus testing procedure for MMC card.
 */
typedef struct _usdhc_scatter_gather_data
{
    bool enableAutoCommand12; /*!< Enable auto CMD12. */
    bool enableAutoCommand23; /*!< Enable auto CMD23. */
    bool enableIgnoreError;   /*!< Enable to ignore error event to read/write all the data. */

    usdhc_transfer_direction_t dataDirection; /*!< data direction */
    uint8_t dataType;                         /*!< this is used to distinguish the normal/tuning/boot data. */
    size_t blockSize;                         /*!< Block size. */

    usdhc_scatter_gather_data_list_t sgData; /*!<  scatter gather data */
} usdhc_scatter_gather_data_t;

/*! @brief usdhc scatter gather transfer. */
typedef struct _usdhc_scatter_gather_transfer
{
    usdhc_scatter_gather_data_t *data; /*!< Data to transfer. */
    usdhc_command_t *command;          /*!< Command to send. */
} usdhc_scatter_gather_transfer_t;

/*!
 * @brief Card data descriptor.
 *
 * Defines a structure to contain data-related attribute. The 'enableIgnoreError' is used when upper card
 * driver wants to ignore the error event to read/write all the data and not to stop read/write immediately when an
 * error event happens. For example, bus testing procedure for MMC card.
 */
typedef struct _usdhc_data
{
    bool enableAutoCommand12; /*!< Enable auto CMD12. */
    bool enableAutoCommand23; /*!< Enable auto CMD23. */
    bool enableIgnoreError;   /*!< Enable to ignore error event to read/write all the data. */
    uint8_t dataType;         /*!< this is used to distinguish the normal/tuning/boot data. */
    size_t blockSize;         /*!< Block size. */
    uint32_t blockCount;      /*!< Block count. */
    uint32_t *rxData;         /*!< Buffer to save data read. */
    const uint32_t *txData;   /*!< Data buffer to write. */
} usdhc_data_t;

/*! @brief Transfer state. */
typedef struct _usdhc_transfer
{
    usdhc_data_t *data;       /*!< Data to transfer. */
    usdhc_command_t *command; /*!< Command to send. */
} usdhc_transfer_t;

/*! @brief USDHC handle typedef. */
typedef struct _usdhc_handle usdhc_handle_t;

/*! @brief USDHC callback functions. */
typedef struct _usdhc_transfer_callback
{
    void (*CardInserted)(USDHC_Type *base,
                         void *userData); /*!< Card inserted occurs when DAT3/CD pin is for card detect */
    void (*CardRemoved)(USDHC_Type *base, void *userData);   /*!< Card removed occurs */
    void (*SdioInterrupt)(USDHC_Type *base, void *userData); /*!< SDIO card interrupt occurs */
    void (*BlockGap)(USDHC_Type *base, void *userData);      /*!< stopped at block gap event */
    void (*TransferComplete)(USDHC_Type *base,
                             usdhc_handle_t *handle,
                             status_t status,
                             void *userData);           /*!< Transfer complete callback. */
    void (*ReTuning)(USDHC_Type *base, void *userData); /*!< Handle the re-tuning. */
} usdhc_transfer_callback_t;

/*!
 * @brief USDHC handle.
 *
 * Defines the structure to save the USDHC state information and callback function.
 *
 * @note All the fields except interruptFlags and transferredWords must be allocated by the user.
 */
struct _usdhc_handle
{
#if (defined FSL_USDHC_ENABLE_SCATTER_GATHER_TRANSFER) && FSL_USDHC_ENABLE_SCATTER_GATHER_TRANSFER
    usdhc_scatter_gather_data_t *volatile data; /*!< scatter gather data pointer  */
#else
    usdhc_data_t *volatile data;                                   /*!< Transfer parameter. Data to transfer. */
#endif
    usdhc_command_t *volatile command; /*!< Transfer parameter. Command to send. */

    volatile uint32_t transferredWords; /*!< Transfer status. Words transferred by DATAPORT way. */

    usdhc_transfer_callback_t callback; /*!< Callback function. */
    void *userData;                     /*!< Parameter for transfer complete callback. */
};

/*! @brief USDHC transfer function. */
typedef status_t (*usdhc_transfer_function_t)(USDHC_Type *base, usdhc_transfer_t *content);

/*! @brief USDHC host descriptor. */
typedef struct _usdhc_host
{
    USDHC_Type *base;                   /*!< USDHC peripheral base address. */
    uint32_t sourceClock_Hz;            /*!< USDHC source clock frequency united in Hz. */
    usdhc_config_t config;              /*!< USDHC configuration. */
    usdhc_capability_t capability;      /*!< USDHC capability information. */
    usdhc_transfer_function_t transfer; /*!< USDHC transfer function. */
} usdhc_host_t;

/*************************************************************************************************
 * API
 ************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief USDHC module initialization function.
 *
 * Configures the USDHC according to the user configuration.
 *
 * Example:
   @code
   usdhc_config_t config;
   config.cardDetectDat3 = false;
   config.endianMode = kUSDHC_EndianModeLittle;
   config.dmaMode = kUSDHC_DmaModeAdma2;
   config.readWatermarkLevel = 128U;
   config.writeWatermarkLevel = 128U;
   USDHC_Init(USDHC, &config);
   @endcode
 *
 * @param base USDHC peripheral base address.
 * @param config USDHC configuration information.
 * @retval #kStatus_Success Operate successfully.
 */
void USDHC_Init(USDHC_Type *base, const usdhc_config_t *config);

/*!
 * @brief Deinitializes the USDHC.
 *
 * @param base USDHC peripheral base address.
 */
void USDHC_Deinit(USDHC_Type *base);

/*!
 * @brief Resets the USDHC.
 *
 * @param base USDHC peripheral base address.
 * @param mask The reset type mask(@ref _usdhc_reset).
 * @param timeout Timeout for reset.
 * @retval true Reset successfully.
 * @retval false Reset failed.
 */
bool USDHC_Reset(USDHC_Type *base, uint32_t mask, uint32_t timeout);

/*! @} */

/*!
 * @name DMA Control
 * @{
 */

/*!
 * @brief Sets the DMA descriptor table configuration.
 * A high level DMA descriptor configuration function.
 * @param base USDHC peripheral base address.
 * @param dmaConfig ADMA configuration
 * @param dataConfig Data descriptor
 * @param flags ADAM descriptor flag, used to indicate to create multiple or single descriptor, please
 *  refer to enum @ref _usdhc_adma_flag.
 * @retval #kStatus_OutOfRange ADMA descriptor table length isn't enough to describe data.
 * @retval #kStatus_Success Operate successfully.
 */
status_t USDHC_SetAdmaTableConfig(USDHC_Type *base,
                                  usdhc_adma_config_t *dmaConfig,
                                  usdhc_data_t *dataConfig,
                                  uint32_t flags);

/*!
 * @brief Internal DMA configuration.
 * This function is used to config the USDHC DMA related registers.
 * @param base USDHC peripheral base address.
 * @param dmaConfig ADMA configuration.
 * @param dataAddr Transfer data address, a simple DMA parameter, if ADMA is used, leave it to NULL.
 * @param enAutoCmd23 Flag to indicate Auto CMD23 is enable or not, a simple DMA parameter, if ADMA is used, leave it
 * to false.
 * @retval #kStatus_OutOfRange ADMA descriptor table length isn't enough to describe data.
 * @retval #kStatus_Success Operate successfully.
 */
status_t USDHC_SetInternalDmaConfig(USDHC_Type *base,
                                    usdhc_adma_config_t *dmaConfig,
                                    const uint32_t *dataAddr,
                                    bool enAutoCmd23);

/*!
 * @brief Sets the ADMA2 descriptor table configuration.
 *
 * @param admaTable ADMA table address.
 * @param admaTableWords ADMA table length.
 * @param dataBufferAddr Data buffer address.
 * @param dataBytes Data Data length.
 * @param flags ADAM descriptor flag, used to indicate to create multiple or single descriptor, please
 *  refer to enum @ref _usdhc_adma_flag.
 * @retval #kStatus_OutOfRange ADMA descriptor table length isn't enough to describe data.
 * @retval #kStatus_Success Operate successfully.
 */
status_t USDHC_SetADMA2Descriptor(
    uint32_t *admaTable, uint32_t admaTableWords, const uint32_t *dataBufferAddr, uint32_t dataBytes, uint32_t flags);

/*!
 * @brief Sets the ADMA1 descriptor table configuration.
 *
 * @param admaTable ADMA table address.
 * @param admaTableWords ADMA table length.
 * @param dataBufferAddr Data buffer address.
 * @param dataBytes Data length.
 * @param flags ADAM descriptor flag, used to indicate to create multiple or single descriptor, please
 *  refer to enum @ref _usdhc_adma_flag.
 * @retval #kStatus_OutOfRange ADMA descriptor table length isn't enough to describe data.
 * @retval #kStatus_Success Operate successfully.
 */
status_t USDHC_SetADMA1Descriptor(
    uint32_t *admaTable, uint32_t admaTableWords, const uint32_t *dataBufferAddr, uint32_t dataBytes, uint32_t flags);

/*!
 * @brief Enables internal DMA.
 *
 * @param base USDHC peripheral base address.
 * @param enable enable or disable flag
 */
static inline void USDHC_EnableInternalDMA(USDHC_Type *base, bool enable)
{
    if (enable)
    {
        //base->MIX_CTRL |= USDHC_MIX_CTRL_DMAEN_MASK; // Mimi: removed
    	base->XFR_TYP |= 0x1;	// Mimi: DMA enable
    }
    else
    {
        //ase->MIX_CTRL &= ~USDHC_MIX_CTRL_DMAEN_MASK;	// Mimi: removed
        //base->PROT_CTRL &= ~USDHC_PROT_CTRL_DMASEL_MASK; // Mimi: removed
    	base->XFR_TYP &= ~0x1;	// Mimi: DMA disable
    }
}

/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables the interrupt status.
 *
 * @param base USDHC peripheral base address.
 * @param mask Interrupt status flags mask(@ref _usdhc_interrupt_status_flag).
 */
static inline void USDHC_EnableInterruptStatus(USDHC_Type *base, uint32_t mask)
{
    base->INT_STATUS_EN |= mask;
}

/*!
 * @brief Disables the interrupt status.
 *
 * @param base USDHC peripheral base address.
 * @param mask The interrupt status flags mask(@ref _usdhc_interrupt_status_flag).
 */
static inline void USDHC_DisableInterruptStatus(USDHC_Type *base, uint32_t mask)
{
    base->INT_STATUS_EN &= ~mask;
}

/*!
 * @brief Enables the interrupt signal corresponding to the interrupt status flag.
 *
 * @param base USDHC peripheral base address.
 * @param mask The interrupt status flags mask(@ref _usdhc_interrupt_status_flag).
 */
static inline void USDHC_EnableInterruptSignal(USDHC_Type *base, uint32_t mask)
{
    base->INT_SIGNAL_EN |= mask;
}

/*!
 * @brief Disables the interrupt signal corresponding to the interrupt status flag.
 *
 * @param base USDHC peripheral base address.
 * @param mask The interrupt status flags mask(@ref _usdhc_interrupt_status_flag).
 */
static inline void USDHC_DisableInterruptSignal(USDHC_Type *base, uint32_t mask)
{
    base->INT_SIGNAL_EN &= ~mask;
}

/*! @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the enabled interrupt status.
 *
 * @param base USDHC peripheral base address.
 * @return Current interrupt status flags mask(@ref _usdhc_interrupt_status_flag).
 */
static inline uint32_t USDHC_GetEnabledInterruptStatusFlags(USDHC_Type *base)
{
    uint32_t intStatus = base->INT_STATUS;

    return intStatus & base->INT_SIGNAL_EN;
}

/*!
 * @brief Gets the current interrupt status.
 *
 * @param base USDHC peripheral base address.
 * @return Current interrupt status flags mask(@ref _usdhc_interrupt_status_flag).
 */
static inline uint32_t USDHC_GetInterruptStatusFlags(USDHC_Type *base)
{
    return base->INT_STATUS;
}

/*!
 * @brief Clears a specified interrupt status.
 * write 1 clears
 * @param base USDHC peripheral base address.
 * @param mask The interrupt status flags mask(@ref _usdhc_interrupt_status_flag).
 */
static inline void USDHC_ClearInterruptStatusFlags(USDHC_Type *base, uint32_t mask)
{
    base->INT_STATUS = mask;
}

/*!
 * @brief Gets the status of auto command 12 error.
 *
 * @param base USDHC peripheral base address.
 * @return Auto command 12 error status flags mask(@ref _usdhc_auto_command12_error_status_flag).
 */
static inline uint32_t USDHC_GetAutoCommand12ErrorStatusFlags(USDHC_Type *base)
{
    return base->AUTOCMD12_ERR_STATUS;
}

/*!
 * @brief Gets the status of the ADMA error.
 *
 * @param base USDHC peripheral base address.
 * @return ADMA error status flags mask(@ref _usdhc_adma_error_status_flag).
 */
static inline uint32_t USDHC_GetAdmaErrorStatusFlags(USDHC_Type *base)
{
    return base->ADMA_ERR_STATUS & 0xFUL;
}

/*!
 * @brief Gets a present status.
 *
 * This function gets the present USDHC's status except for an interrupt status and an error status.
 *
 * @param base USDHC peripheral base address.
 * @return Present USDHC's status flags mask(@ref _usdhc_present_status_flag).
 */
static inline uint32_t USDHC_GetPresentStatusFlags(USDHC_Type *base)
{
    return base->PRES_STATE;
}

/*! @} */

/*!
 * @name Bus Operations
 * @{
 */

/*!
 * @brief Gets the capability information.
 *
 * @param base USDHC peripheral base address.
 * @param capability Structure to save capability information.
 */
void USDHC_GetCapability(USDHC_Type *base, usdhc_capability_t *capability);

/*!
 * @brief Forces the card clock on.
 *
 * @param base USDHC peripheral base address.
 * @param enable enable/disable flag
 */
static inline void USDHC_ForceClockOn(USDHC_Type *base, bool enable)
{
#if 0
    if (enable)
    {
        base->VEND_SPEC |= USDHC_VEND_SPEC_FRC_SDCLK_ON_MASK;
    }
    else
    {
        base->VEND_SPEC &= ~USDHC_VEND_SPEC_FRC_SDCLK_ON_MASK;
    }
#endif //Mimi: removed
}

/*!
 * @brief Sets the SD bus clock frequency.
 *
 * @param base USDHC peripheral base address.
 * @param srcClock_Hz USDHC source clock frequency united in Hz.
 * @param busClock_Hz SD bus clock frequency united in Hz.
 *
 * @return The nearest frequency of busClock_Hz configured for SD bus.
 */
uint32_t USDHC_SetSdClock(USDHC_Type *base, uint32_t srcClock_Hz, uint32_t busClock_Hz);
/*!
 * @brief Sends 80 clocks to the card to set it to the active state.
 *
 * This function must be called each time the card is inserted to ensure that the card can receive the command
 * correctly.
 *
 * @param base USDHC peripheral base address.
 * @param timeout Timeout to initialize card.
 * @retval true Set card active successfully.
 * @retval false Set card active failed.
 */
bool USDHC_SetCardActive(USDHC_Type *base, uint32_t timeout);

/*!
 * @brief Triggers a hardware reset.
 *
 * @param base USDHC peripheral base address.
 * @param high 1 or 0 level
 */
static inline void USDHC_AssertHardwareReset(USDHC_Type *base, bool high)
{
    if (high)
    {
        //base->SYS_CTRL |= USDHC_SYS_CTRL_IPP_RST_N_MASK; // Mimi
    }
    else
    {
        //base->SYS_CTRL &= ~USDHC_SYS_CTRL_IPP_RST_N_MASK; // Mimi
    }
}

/*!
 * @brief Sets the data transfer width.
 *
 * @param base USDHC peripheral base address.
 * @param width Data transfer width.
 */
static inline void USDHC_SetDataBusWidth(USDHC_Type *base, usdhc_data_bus_width_t width)
{
	base->PROT_CTRL = ((base->PROT_CTRL & ~USDHC_PROT_CTRL_DTW_MASK) | USDHC_PROT_CTRL_DTW(width));
}

/*!
 * @brief Fills the data port.
 *
 * This function is used to implement the data transfer by Data Port instead of DMA.
 *
 * @param base USDHC peripheral base address.
 * @param data The data about to be sent.
 */
static inline void USDHC_WriteData(USDHC_Type *base, uint32_t data)
{
    base->DATA_BUFF_ACC_PORT = data;
}

/*!
 * @brief Retrieves the data from the data port.
 *
 * This function is used to implement the data transfer by Data Port instead of DMA.
 *
 * @param base USDHC peripheral base address.
 * @return The data has been read.
 */
static inline uint32_t USDHC_ReadData(USDHC_Type *base)
{
    return base->DATA_BUFF_ACC_PORT;
}

/*!
 * @brief Sends command function.
 *
 * @param base USDHC peripheral base address.
 * @param command configuration
 */
void USDHC_SendCommand(USDHC_Type *base, usdhc_command_t *command);

/*!
 * @brief Enables or disables a wakeup event in low-power mode.
 *
 * @param base USDHC peripheral base address.
 * @param mask Wakeup events mask(@ref _usdhc_wakeup_event).
 * @param enable True to enable, false to disable.
 */
static inline void USDHC_EnableWakeupEvent(USDHC_Type *base, uint32_t mask, bool enable)
{
    if (enable)
    {
        base->PROT_CTRL |= mask;
    }
    else
    {
        base->PROT_CTRL &= ~mask;
    }
}

/*!
 * @brief Detects card insert status.
 *
 * @param base USDHC peripheral base address.
 * @param enable enable/disable flag
 */
static inline void USDHC_CardDetectByData3(USDHC_Type *base, bool enable)
{
    if (enable)
    {
        //base->PROT_CTRL |= USDHC_PROT_CTRL_D3CD_MASK;	// Mimi
    }
    else
    {
        //base->PROT_CTRL &= ~USDHC_PROT_CTRL_D3CD_MASK;	// Mimi
    }
}

/*!
 * @brief Detects card insert status.
 *
 * @param base USDHC peripheral base address.
 */
static inline bool USDHC_DetectCardInsert(USDHC_Type *base)
{
    //return ((base->PRES_STATE & (uint32_t)kUSDHC_CardInsertedFlag) != 0UL) ? true : false;	// Mimi
	return 0;	// Mimi
}

/*!
 * @brief Enables or disables the SDIO card control.
 *
 * @param base USDHC peripheral base address.
 * @param mask SDIO card control flags mask(@ref _usdhc_sdio_control_flag).
 * @param enable True to enable, false to disable.
 */
static inline void USDHC_EnableSdioControl(USDHC_Type *base, uint32_t mask, bool enable)
{
    if (enable)
    {
        base->PROT_CTRL |= mask;
    }
    else
    {
        base->PROT_CTRL &= ~mask;
    }
}

/*!
 * @brief Restarts a transaction which has stopped at the block GAP for the SDIO card.
 *
 * @param base USDHC peripheral base address.
 */
static inline void USDHC_SetContinueRequest(USDHC_Type *base)
{
    //base->PROT_CTRL |= USDHC_PROT_CTRL_CREQ_MASK;	// Mimi
}

/*!
 * @brief Request stop at block gap function.
 *
 * @param base USDHC peripheral base address.
 * @param enable True to stop at block gap, false to normal transfer.
 */
static inline void USDHC_RequestStopAtBlockGap(USDHC_Type *base, bool enable)
{
    if (enable)
    {
        //base->PROT_CTRL |= USDHC_PROT_CTRL_SABGREQ_MASK;	// Mimi
    }
    else
    {
        //base->PROT_CTRL &= ~USDHC_PROT_CTRL_SABGREQ_MASK;	// Mimi
    }
}

/*!
 * @brief Configures the MMC boot feature.
 *
 * Example:
   @code
   usdhc_boot_config_t config;
   config.ackTimeoutCount = 4;
   config.bootMode = kUSDHC_BootModeNormal;
   config.blockCount = 5;
   config.enableBootAck = true;
   config.enableBoot = true;
   config.enableAutoStopAtBlockGap = true;
   USDHC_SetMmcBootConfig(USDHC, &config);
   @endcode
 *
 * @param base USDHC peripheral base address.
 * @param config The MMC boot configuration information.
 */
void USDHC_SetMmcBootConfig(USDHC_Type *base, const usdhc_boot_config_t *config);

/*!
 * @brief Enables or disables the mmc boot mode.
 *
 * @param base USDHC peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void USDHC_EnableMmcBoot(USDHC_Type *base, bool enable)
{
    if (enable)
    {
        base->VEND_SDMMC_CTRL |= USDHC_MMC_BOOT_BOOT_EN_MASK;
    }
    else
    {
        base->VEND_SDMMC_CTRL &= ~USDHC_MMC_BOOT_BOOT_EN_MASK;
    }
}

/*!
 * @brief Forces generating events according to the given mask.
 *
 * @param base USDHC peripheral base address.
 * @param mask The force events bit posistion (_usdhc_force_event).
 */
static inline void USDHC_SetForceEvent(USDHC_Type *base, uint32_t mask)
{
    base->FORCE_EVENT = mask;
}

#if !(defined(FSL_FEATURE_USDHC_HAS_NO_VOLTAGE_SELECT) && (FSL_FEATURE_USDHC_HAS_NO_VOLTAGE_SELECT))
/*!
 * @brief Selects the USDHC output voltage.
 *
 * @param base USDHC peripheral base address.
 * @param en18v True means 1.8V, false means 3.0V.
 */
static inline void UDSHC_SelectVoltage(USDHC_Type *base, bool en18v)
{
#if 0
    if (en18v)
    {
        base->VEND_SPEC |= USDHC_VEND_SPEC_VSELECT_MASK;
    }
    else
    {
        base->VEND_SPEC &= ~USDHC_VEND_SPEC_VSELECT_MASK;
    }
#endif // Mimi: removed
}
#endif

#if defined(FSL_FEATURE_USDHC_HAS_SDR50_MODE) /*&& (FSL_FEATURE_USDHC_HAS_SDR50_MODE)*/
/*!
 * @brief Checks the SDR50 mode request tuning bit.
 * When this bit set, application shall perform tuning for SDR50 mode.
 * @param base USDHC peripheral base address.
 */
static inline bool USDHC_RequestTuningForSDR50(USDHC_Type *base)
{
    return ((base->HOST_CTRL_CAP_1 & USDHC_HOST_CTRL_CAP_USE_TUNING_SDR50_MASK) != 0UL) ? true : false;
}

/*!
 * @brief Checks the request re-tuning bit.
 * When this bit is set, user should do manual tuning or standard tuning function.
 * @param base USDHC peripheral base address.
 */
static inline bool USDHC_RequestReTuning(USDHC_Type *base)
{
    return ((base->PRES_STATE & USDHC_PRES_STATE_RTR_MASK) != 0UL) ? true : false;
}

/*!
 * @brief The SDR104 mode auto tuning enable and disable.
 * This function should be called after tuning function execute pass, auto tuning will handle
 * by hardware.
 * @param base USDHC peripheral base address.
 * @param enable enable/disable flag
 */
static inline void USDHC_EnableAutoTuning(USDHC_Type *base, bool enable)
{
#if 0
    if (enable)
    {
        base->MIX_CTRL |= USDHC_MIX_CTRL_AUTO_TUNE_EN_MASK;
    }
    else
    {
        base->MIX_CTRL &= ~USDHC_MIX_CTRL_AUTO_TUNE_EN_MASK;
    }
#endif // Mimi: removed
}

#if !(defined(FSL_FEATURE_USDHC_REGISTER_HOST_CTRL_CAP_HAS_NO_RETUNING_TIME_COUNTER) && \
      FSL_FEATURE_USDHC_REGISTER_HOST_CTRL_CAP_HAS_NO_RETUNING_TIME_COUNTER)
/*!
 * @brief Configs the re-tuning timer for mode 1 and mode 3.
 * This timer is used for standard tuning auto re-tuning,
 * @param base USDHC peripheral base address.
 * @param counter timer counter value
 */
static inline void USDHC_SetRetuningTimer(USDHC_Type *base, uint32_t counter)
{
    base->HOST_CTRL_CAP_1 &= ~USDHC_HOST_CTRL_CAP_TIME_COUNT_RETUNING_MASK;
    base->HOST_CTRL_CAP_1 |= USDHC_HOST_CTRL_CAP_TIME_COUNT_RETUNING(counter);
}
#endif /* FSL_FEATURE_USDHC_REGISTER_HOST_CTRL_CAP_HAS_RETUNING_TIME_COUNTER */

/*!
 * @brief The auto tuning enbale for CMD/DATA line.
 *
 * @param base USDHC peripheral base address.
 */
void USDHC_EnableAutoTuningForCmdAndData(USDHC_Type *base);

/*!
 * @brief Manual tuning trigger or abort.
 * User should handle the tuning cmd and find the boundary of the delay
 * then calucate a average value which will be configured to the <b>CLK_TUNE_CTRL_STATUS</b>
 * This function should be called before function @ref USDHC_AdjustDelayForManualTuning.
 * @param base USDHC peripheral base address.
 * @param enable tuning enable flag
 */
void USDHC_EnableManualTuning(USDHC_Type *base, bool enable);

/*!
 * @brief Get the tuning delay cell setting.
 *
 * @param base USDHC peripheral base address.
 * @retval CLK Tuning Control and Status register value.
 */
static inline uint32_t USDHC_GetTuningDelayStatus(USDHC_Type *base)
{
    return base->CLK_TUNE_CTRL_STATUS >> 16U;
}

/*!
 * @brief The tuning delay cell setting.
 *
 * @param base USDHC peripheral base address.
 * @param preDelay Set the number of delay cells on the feedback clock between the feedback clock and CLK_PRE.
 * @param outDelay Set the number of delay cells on the feedback clock between CLK_PRE and CLK_OUT.
 * @param postDelay Set the number of delay cells on the feedback clock between CLK_OUT and CLK_POST.
 * @retval kStatus_Fail config the delay setting fail
 * @retval kStatus_Success config the delay setting success
 */
status_t USDHC_SetTuningDelay(USDHC_Type *base, uint32_t preDelay, uint32_t outDelay, uint32_t postDelay);

/*!
 * @brief Adjusts delay for mannual tuning.
 * @deprecated Do not use this function.  It has been superceded by USDHC_SetTuingDelay
 * @param base USDHC peripheral base address.
 * @param delay setting configuration
 * @retval #kStatus_Fail config the delay setting fail
 * @retval #kStatus_Success config the delay setting success
 */
status_t USDHC_AdjustDelayForManualTuning(USDHC_Type *base, uint32_t delay);

/*!
 * @brief set tuning counter tuning.
 * @param base USDHC peripheral base address.
 * @param counter tuning counter
 * @retval #kStatus_Fail config the delay setting fail
 * @retval #kStatus_Success config the delay setting success
 */
static inline void USDHC_SetStandardTuningCounter(USDHC_Type *base, uint8_t counter)
{
#if 0
    base->TUNING_CTRL =
        (base->TUNING_CTRL & (~USDHC_TUNING_CTRL_TUNING_COUNTER_MASK)) | USDHC_TUNING_CTRL_TUNING_COUNTER(counter);
#endif // Mimi
}

/*!
 * @brief The enable standard tuning function.
 * The standard tuning window and tuning counter using the default config
 * tuning cmd is sent by the software, user need to check whether the tuning result
 * can be used for SDR50, SDR104, and HS200 mode tuning.
 * @param base USDHC peripheral base address.
 * @param tuningStartTap start tap
 * @param step tuning step
 * @param enable enable/disable flag
 */
void USDHC_EnableStandardTuning(USDHC_Type *base, /*uint32_t tuningStartTap, uint32_t step,*/ bool enable);

/*!
 * @brief Gets execute STD tuning status.
 *
 * @param base USDHC peripheral base address.
 */
static inline uint32_t USDHC_GetExecuteStdTuningStatus(USDHC_Type *base)
{
    return (base->AUTOCMD12_ERR_STATUS & USDHC_AUTOCMD12_ERR_STATUS_EXECUTE_TUNING_MASK);
}

/*!
 * @brief Checks STD tuning result.
 *
 * @param base USDHC peripheral base address.
 */
static inline uint32_t USDHC_CheckStdTuningResult(USDHC_Type *base)
{
    return (base->AUTOCMD12_ERR_STATUS & USDHC_AUTOCMD12_ERR_STATUS_SMP_CLK_SEL_MASK);
}

/*!
 * @brief Checks tuning error.
 *
 * @param base USDHC peripheral base address.
 */
static inline uint32_t USDHC_CheckTuningError(USDHC_Type *base)
{
#if 0
    return (base->CLK_TUNE_CTRL_STATUS &
            (USDHC_CLK_TUNE_CTRL_STATUS_NXT_ERR_MASK | USDHC_CLK_TUNE_CTRL_STATUS_PRE_ERR_MASK));
#endif // Mimi: removed
    return ((base->VEND_SDMMC_TUNING_SEL & 0xFF) == 0);
}

#endif
/*!
 * @brief The enable/disable DDR mode.
 *
 * @param base USDHC peripheral base address.
 * @param enable enable/disable flag
 * @param nibblePos nibble position
 */
void USDHC_EnableDDRMode(USDHC_Type *base, bool enable, uint32_t nibblePos);

#if FSL_FEATURE_USDHC_HAS_HS400_MODE
/*!
 * @brief The enable/disable HS400 mode.
 *
 * @param base USDHC peripheral base address.
 * @param enable enable/disable flag
 */
static inline void USDHC_EnableHS400Mode(USDHC_Type *base, bool enable)
{
    if (enable)
    {
        base->MIX_CTRL |= USDHC_MIX_CTRL_HS400_MODE_MASK;
    }
    else
    {
        base->MIX_CTRL &= ~USDHC_MIX_CTRL_HS400_MODE_MASK;
    }
}

/*!
 * @brief Resets the strobe DLL.
 *
 * @param base USDHC peripheral base address.
 */
static inline void USDHC_ResetStrobeDLL(USDHC_Type *base)
{
    base->STROBE_DLL_CTRL |= USDHC_STROBE_DLL_CTRL_STROBE_DLL_CTRL_RESET_MASK;
}

/*!
 * @brief Enables/disables the strobe DLL.
 *
 * @param base USDHC peripheral base address.
 * @param enable enable/disable flag
 */
static inline void USDHC_EnableStrobeDLL(USDHC_Type *base, bool enable)
{
    if (enable)
    {
        base->STROBE_DLL_CTRL |= USDHC_STROBE_DLL_CTRL_STROBE_DLL_CTRL_ENABLE_MASK;
    }
    else
    {
        base->STROBE_DLL_CTRL &= ~USDHC_STROBE_DLL_CTRL_STROBE_DLL_CTRL_ENABLE_MASK;
    }
}

/*!
 * @brief Configs the strobe DLL delay target and update interval.
 *
 * @param base USDHC peripheral base address.
 * @param delayTarget delay target
 * @param updateInterval update interval
 */
void USDHC_ConfigStrobeDLL(USDHC_Type *base, uint32_t delayTarget, uint32_t updateInterval);

/*!
 * @brief Enables manual override for slave delay chain using <b>STROBE_SLV_OVERRIDE_VAL</b>.
 *
 * @param base USDHC peripheral base address.
 * @param delayTaps Valid delay taps range from 1 - 128 taps. A value of 0 selects tap 1, and a value of 0x7F selects
 * tap 128.
 */
static inline void USDHC_SetStrobeDllOverride(USDHC_Type *base, uint32_t delayTaps)
{
    base->STROBE_DLL_CTRL &= (USDHC_STROBE_DLL_CTRL_STROBE_DLL_CTRL_ENABLE_MASK |
                              USDHC_STROBE_DLL_CTRL_STROBE_DLL_CTRL_SLV_OVERRIDE_VAL_MASK);

    base->STROBE_DLL_CTRL |= USDHC_STROBE_DLL_CTRL_STROBE_DLL_CTRL_SLV_OVERRIDE_MASK |
                             USDHC_STROBE_DLL_CTRL_STROBE_DLL_CTRL_SLV_OVERRIDE_VAL(delayTaps);
}

/*!
 * @brief Gets the strobe DLL status.
 *
 * @param base USDHC peripheral base address.
 */
static inline uint32_t USDHC_GetStrobeDLLStatus(USDHC_Type *base)
{
    return base->STROBE_DLL_STATUS;
}

#endif

/*!
 * @brief USDHC data configuration.
 *
 * @param base USDHC peripheral base address.
 * @param dataDirection Data direction, tx or rx.
 * @param blockCount Data block count.
 * @param blockSize Data block size.
 *
 */
void USDHC_SetDataConfig(USDHC_Type *base,
                         usdhc_transfer_direction_t dataDirection,
                         uint32_t blockCount,
                         uint32_t blockSize);
/*! @} */

/*!
 * @name Transactional functions
 * @{
 */

/*!
 * @brief Creates the USDHC handle.
 *
 * @param base USDHC peripheral base address.
 * @param handle USDHC handle pointer.
 * @param callback Structure pointer to contain all callback functions.
 * @param userData Callback function parameter.
 */
void USDHC_TransferCreateHandle(USDHC_Type *base,
                                usdhc_handle_t *handle,
                                const usdhc_transfer_callback_t *callback,
                                void *userData);

#if (defined FSL_USDHC_ENABLE_SCATTER_GATHER_TRANSFER) && FSL_USDHC_ENABLE_SCATTER_GATHER_TRANSFER
/*!
 * @brief Transfers the command/scatter gather data using an interrupt and an asynchronous method.
 *
 * This function sends a command and data and returns immediately. It doesn't wait for the transfer to complete or
 * to encounter an error. The application must not call this API in multiple threads at the same time. Because of that
 * this API doesn't support the re-entry mechanism.
 * This function is target for the application would like to have scatter gather buffer to be transferred within one
 * read/write request, non scatter gather buffer is support by this function also.
 *
 * @note Call API @ref USDHC_TransferCreateHandle when calling this API.
 *
 * @param base USDHC peripheral base address.
 * @param handle USDHC handle.
 * @param dmaConfig adma configurations, must be not NULL, since the function is target for ADMA only.
 * @param transfer scatter gather transfer content.
 *
 * @retval #kStatus_InvalidArgument Argument is invalid.
 * @retval #kStatus_USDHC_BusyTransferring Busy transferring.
 * @retval #kStatus_USDHC_PrepareAdmaDescriptorFailed Prepare ADMA descriptor failed.
 * @retval #kStatus_Success Operate successfully.
 */
status_t USDHC_TransferScatterGatherADMANonBlocking(USDHC_Type *base,
                                                    usdhc_handle_t *handle,
                                                    usdhc_adma_config_t *dmaConfig,
                                                    usdhc_scatter_gather_transfer_t *transfer);
#else
/*!
 * @brief Transfers the command/data using an interrupt and an asynchronous method.
 *
 * This function sends a command and data and returns immediately. It doesn't wait for the transfer to complete or
 * to encounter an error. The application must not call this API in multiple threads at the same time. Because of that
 * this API doesn't support the re-entry mechanism.
 *
 * @note Call API @ref USDHC_TransferCreateHandle when calling this API.
 *
 * @param base USDHC peripheral base address.
 * @param handle USDHC handle.
 * @param dmaConfig ADMA configuration.
 * @param transfer Transfer content.
 * @retval #kStatus_InvalidArgument Argument is invalid.
 * @retval #kStatus_USDHC_BusyTransferring Busy transferring.
 * @retval #kStatus_USDHC_PrepareAdmaDescriptorFailed Prepare ADMA descriptor failed.
 * @retval #kStatus_Success Operate successfully.
 */
status_t USDHC_TransferNonBlocking(USDHC_Type *base,
                                   usdhc_handle_t *handle,
                                   usdhc_adma_config_t *dmaConfig,
                                   usdhc_transfer_t *transfer);
#endif

/*!
 * @brief Transfers the command/data using a blocking method.
 *
 * This function waits until the command response/data is received or the USDHC encounters an error by polling the
 * status flag. \n
 * The application must not call this API in multiple threads at the same time. Because this API doesn't
 * support the re-entry mechanism.
 *
 * @note There is no need to call API @ref USDHC_TransferCreateHandle when calling this API.
 *
 * @param base USDHC peripheral base address.
 * @param dmaConfig adma configuration
 * @param transfer Transfer content.
 * @retval #kStatus_InvalidArgument Argument is invalid.
 * @retval #kStatus_USDHC_PrepareAdmaDescriptorFailed Prepare ADMA descriptor failed.
 * @retval #kStatus_USDHC_SendCommandFailed Send command failed.
 * @retval #kStatus_USDHC_TransferDataFailed Transfer data failed.
 * @retval #kStatus_Success Operate successfully.
 */
status_t USDHC_TransferBlocking(USDHC_Type *base, usdhc_adma_config_t *dmaConfig, usdhc_transfer_t *transfer);

/*!
 * @brief IRQ handler for the USDHC.
 *
 * This function deals with the IRQs on the given host controller.
 *
 * @param base USDHC peripheral base address.
 * @param handle USDHC handle.
 */
void USDHC_TransferHandleIRQ(USDHC_Type *base, usdhc_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif
/*! @} */

#endif /* FSL_USDHC_H_*/
