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
 * @file  upt_powmod.h
 * @brief API for UPT Power mode relative transition actions
 */
#ifndef UPT_POWMOD_H
#define UPT_POWMOD_H

/**
 * @brief bootup re-map mode.
 * @ingroup POWER_MODE
 */
typedef enum enum_upt_remap {
	UPT_REMAP_ROM_ISP = 0,
	UPT_REMAP_FALSH,
	UPT_REMAP_RAM,
	UPT_REMAP_ROM,
} enum_upt_remap_Type;

/**
 * @brief Boot-up source. See @ref SCU_BOOTSTAT
 * @ingroup POWER_MODE
 */
typedef enum enum_upt_boot {
	UPT_POWERON_BOOT = 1 << 0,      // 1<<0
	UPT_E21_ECC_RESET = 1 << 1,     // 1<<1
	UPT_E34_ECC_RESET = 1 << 2,     // 1<<2
	UPT_HW_RESET = 1 << 3,          // 1<<3
	UPT_GPIO_0_BOOTUP = 1 << 4,     // 1<<4
	UPT_GPIO_1_BOOTUP = 1 << 5,     // 1<<5
	UPT_GPIO_2_BOOTUP = 1 << 6,     // 1<<6
	UPT_GPIO_3_BOOTUP = 1 << 7,     // 1<<7
	UPT_RTC_BOOTUP = 1 << 8,        // 1<<8
	UPT_TICK_BOOTUP = 1 << 9,       // 1<<9
	UPT_WDT_RESET = 1 << 10,        // 1<<10
	UPT_WARM_BOOT = 1 << 11,        // 1<<11
	UPT_SW_RESET_BOOT =  1 << 12,   // 1<<12
} enum_upt_boot_Type;

/**
 * @brief R0 to Ax trigger event.
 * @ingroup POWER_MODE
 */
typedef enum enum_upt_rtcm_int {
  UPT_RTCM_GPIO_0,
  UPT_RTCM_GPIO_1,
  UPT_RTCM_GPIO_2,
  UPT_RTCM_GPIO_3,
  UPT_RTC,
  UPT_TICK_TIMER,
} enum_upt_rtcm_int_Type;

/**
 * @brief Ax to Sx/L0 mode
 * @ingroup POWER_MODE
 */
typedef enum enum_upt_sleep {
  UPT_SLP_TO_PSL,
  UPT_SLP_TO_S0,
  UPT_SLP_TO_S1,
  UPT_SLP_TO_L0,
} enum_upt_sleep_Type;

/**
 * @brief Select L0 voltage
 * @ingroup POWER_MODE
 */
typedef enum enum_upt_l0_volt {
  UPT_L0_VOLT_RATING_0,
  UPT_L0_VOLT_RATING_1,
  UPT_L0_VOLT_RATING_2,
} enum_upt_l0_volt_Type;

/**
 * @brief RTCM domain interrupt state
 * @ingroup POWER_MODE
 */
typedef enum upt_rtcm_int_stat {
  UPT_INT_RTCM_GPIO_0 = (0x1 << UPT_RTCM_GPIO_0),
  UPT_INT_RTCM_GPIO_1 = (0x1 << UPT_RTCM_GPIO_1),
  UPT_INT_RTCM_GPIO_2 = (0x1 << UPT_RTCM_GPIO_2),
  UPT_INT_RTCM_GPIO_3 = (0x1 << UPT_RTCM_GPIO_3),
  UPT_INT_RTC = (0x1 << UPT_RTC),
} upt_rtcm_int_stat_Type;

enum enum_upt_aon_int {
  UPT_AON_ENTER_SLEEP,
  UPT_AON_LEAVE_SLEEP,
  UPT_AON_ENTER_LURKING,
  UPT_AON_LEAVE_LURKING,
  UPT_AON_NONE,
  UPT_AON_SW_TO_E21,
};

/**
 * @brief AON domain interrupt state
 * @ingroup POWER_MODE
 */
typedef enum upt_aon_int_stat {
  UPT_INT_AON_ENTER_SLEEP = (0x1 << UPT_AON_ENTER_SLEEP),
  UPT_INT_AON_LEAVE_SLEEP = (0x1 << UPT_AON_LEAVE_SLEEP),
  UPT_INT_AON_ENTER_LURKING = (0x1 << UPT_AON_ENTER_LURKING),
  UPT_INT_AON_LEAVE_LURKING = (0x1 << UPT_AON_LEAVE_LURKING),
  UPT_INT_AON_SW_TO_E21_INT = (0x1 << UPT_AON_SW_TO_E21),
} upt_aon_int_stat_Type;

/**
 * @brief Select AxSX to Ax interrupt source
 * @ingroup POWER_MODE
 */
typedef struct upt_powermode_AxSc2Ax_int_src {
	uint32_t id;
	int32_t status;
} upt_powermode_AxSc2Ax_int_src_Type;

#define UPT_SIF_TRI_MSK_SHIFT			(0)
#define UPT_SIF_TRI_E21_2ECC_RST_POS	(0 + UPT_SIF_TRI_MSK_SHIFT)
#define UPT_SIF_TRI_E34_2ECC_RST_POS	(1 + UPT_SIF_TRI_MSK_SHIFT)
#define UPT_SIF_TRI_HW_RST_POS			(2 + UPT_SIF_TRI_MSK_SHIFT)
#define UPT_SIF_TRI_WDT_RST_POS			(3 + UPT_SIF_TRI_MSK_SHIFT)
#define UPT_SIF_TRI_WARM_BOOT_POS		(4 + UPT_SIF_TRI_MSK_SHIFT)

/**
 * @brief Select PMIC trigger source
 * @ingroup POWER_MODE
 */
typedef enum enum_upt_sif_tri_src {
  UPT_SIF_TRI_E21_2ECC_RST = 	(0x1 << UPT_SIF_TRI_E21_2ECC_RST_POS),
  UPT_SIF_TRI_E34_2ECC_RST = 	(0x1 << UPT_SIF_TRI_E34_2ECC_RST_POS),
  UPT_SIF_TRI_HW_RST = 			(0x1 << UPT_SIF_TRI_HW_RST_POS),
  UPT_SIF_TRI_WDT_RST = 		(0x1 << UPT_SIF_TRI_WDT_RST_POS),
  UPT_SIF_TRI_WARM_BOOT = 		(0x1 << UPT_SIF_TRI_WARM_BOOT_POS),
} enum_upt_sif_tri_src_Type;

/**
 * @brief External/Internal PMIC trigger
 * @ingroup POWER_MODE
 */
typedef enum enum_upt_sif_tri_Type {
  UPT_SIF_TRI_INTERNAL_0,
  UPT_SIF_TRI_INTERNAL_1,
  UPT_SIF_TRI_EXTERNAL,
} enum_upt_sif_tri_Type;

#define UPT_POWERON_BOOT_ENABLE_ALL (UPT_E21_ECC_RESET | UPT_E34_ECC_RESET | \
									 UPT_GPIO_0_BOOTUP | UPT_GPIO_1_BOOTUP | \
									 UPT_GPIO_2_BOOTUP | UPT_GPIO_3_BOOTUP | \
									 UPT_RTC_BOOTUP | UPT_TICK_BOOTUP | \
									 UPT_WDT_RESET | UPT_WARM_BOOT | \
									 UPT_SW_RESET_BOOT)
#define UPT_SIF_PMIC_TRIGGER_ALL	(UPT_SIF_TRI_E21_2ECC_RST | UPT_SIF_TRI_E34_2ECC_RST | \
									 UPT_SIF_TRI_HW_RST | UPT_SIF_TRI_WDT_RST | \
									 UPT_SIF_TRI_WARM_BOOT)
#define UPT_SIF_PMIC_TRIGGER_NONE 	0

/**
 * @brief Value of RTCM GPIOs
 * @ingroup POWER_MODE
 */
typedef enum enum_upt_gpio_tri_val {
  UPT_GPIO_VALUE_000,
  UPT_GPIO_VALUE_001,
  UPT_GPIO_VALUE_010,
  UPT_GPIO_VALUE_011,
  UPT_GPIO_VALUE_100,
  UPT_GPIO_VALUE_101,
  UPT_GPIO_VALUE_110,
  UPT_GPIO_VALUE_111,
} enum_upt_gpio_tri_val_Type;

#define UPT_PMU_SHUTDN_SRAM_SHIFT		(16)
#define UPT_SHUTDN_L2SRAM_0_POS			(0 + UPT_PMU_SHUTDN_SRAM_SHIFT)
#define UPT_SHUTDN_L2SRAM_1_POS			(1 + UPT_PMU_SHUTDN_SRAM_SHIFT)
#define UPT_SHUTDN_L2SRAM_2_POS			(2 + UPT_PMU_SHUTDN_SRAM_SHIFT)
#define UPT_SHUTDN_L2SRAM_3_POS			(3 + UPT_PMU_SHUTDN_SRAM_SHIFT)
#define UPT_SHUTDN_L2SRAM_4_POS			(4 + UPT_PMU_SHUTDN_SRAM_SHIFT)
#define UPT_SHUTDN_UDLSRAM_0_POS		(5 + UPT_PMU_SHUTDN_SRAM_SHIFT)
#define UPT_SHUTDN_UDLSRAM_1_POS		(6 + UPT_PMU_SHUTDN_SRAM_SHIFT)
#define UPT_SHUTDN_UDLSRAM_2_POS		(7 + UPT_PMU_SHUTDN_SRAM_SHIFT)
#define UPT_SHUTDN_UDLSRAM_3_POS		(8 + UPT_PMU_SHUTDN_SRAM_SHIFT)
#define UPT_SHUTDN_UDLSRAM_4_POS		(9 + UPT_PMU_SHUTDN_SRAM_SHIFT)
#define UPT_SHUTDN_UDLSRAM_5_POS		(10 + UPT_PMU_SHUTDN_SRAM_SHIFT)

/**
 * @brief SRAM power domain control
 * @ingroup POWER_MODE
 */
typedef enum enum_upt_sram_pwr_ctrl {
  UPT_SHUTDN_SRAM_NONE = 0,
  UPT_SHUTDN_L2SRAM_0 = (0x1 << UPT_SHUTDN_L2SRAM_0_POS),
  UPT_SHUTDN_L2SRAM_1 = (0x1 << UPT_SHUTDN_L2SRAM_1_POS),
  UPT_SHUTDN_L2SRAM_2 = (0x1 << UPT_SHUTDN_L2SRAM_2_POS),
  UPT_SHUTDN_L2SRAM_3 = (0x1 << UPT_SHUTDN_L2SRAM_3_POS),
  UPT_SHUTDN_L2SRAM_4 = (0x1 << UPT_SHUTDN_L2SRAM_4_POS),
  UPT_SHUTDN_UDLSRAM_0 = (0x1 << UPT_SHUTDN_UDLSRAM_0_POS),
  UPT_SHUTDN_UDLSRAM_1 = (0x1 << UPT_SHUTDN_UDLSRAM_1_POS),
  UPT_SHUTDN_UDLSRAM_2 = (0x1 << UPT_SHUTDN_UDLSRAM_2_POS),
  UPT_SHUTDN_UDLSRAM_3 = (0x1 << UPT_SHUTDN_UDLSRAM_3_POS),
  UPT_SHUTDN_UDLSRAM_4 = (0x1 << UPT_SHUTDN_UDLSRAM_4_POS),
  UPT_SHUTDN_UDLSRAM_5 = (0x1 << UPT_SHUTDN_UDLSRAM_5_POS),
  UPT_SHUTDN_SRAM_ALL = (UPT_SHUTDN_L2SRAM_0 | UPT_SHUTDN_L2SRAM_1 | \
		  	  	  	  	 UPT_SHUTDN_L2SRAM_2 | UPT_SHUTDN_L2SRAM_3 | \
						 UPT_SHUTDN_L2SRAM_4 | UPT_SHUTDN_UDLSRAM_0 | \
						 UPT_SHUTDN_UDLSRAM_1 | UPT_SHUTDN_UDLSRAM_2 | \
						 UPT_SHUTDN_UDLSRAM_3 | UPT_SHUTDN_UDLSRAM_4 | \
						 UPT_SHUTDN_UDLSRAM_5)
} enum_upt_sram_pwr_ctrl_Type;

/**
 * @brief Power mode return error code.
 * @ingroup POWER_MODE
 */
typedef enum enum_pwmode_retcode{
    E_PWMODE_SUCCESS,		// Success.
	E_PWMODE_INVINIT,		// Initial fail or resource is unavailable.
	E_PWMODE_INVPARA,	 	// Invalid function parameter/argument.
    E_PWMODE_ERROR,     	// Unspecific error.
} enum_pwmode_retcode_Type;


/**
 * @brief Power mode transition from Ax (active) to AxSC (stop clock) to Ax.
 * @details E34 CPU clock is gated when in AxSC mode.
 * @ingroup AX_TO_AXSC_TO_AX_GROUP
 * @param[in] n_intSrc Number of interrupt sources to wake system up from AxSC to Ax.
 * @param[in, out] intSrcList Interrupt source list of struct @ref upt_powermode_int_src.
 * @param[in] axsc_hclk_en pointer to a list of two values to set @ref SCU_AXSC_HCLK_EN0 and @ref SCU_AXSC_HCLK_EN1. Nevertheless they will be set to @ref SCU_HCLKEN0 and @ref SCU_HCLKEN1 if the pointer is NULL.
 * @remarks no return value.
 */
void upt_power_Ax_AxSc_Ax(
		uint32_t n_intSrc,
		upt_powermode_AxSc2Ax_int_src_Type* intSrcList,
		uint32_t* axsc_hclk_en);
/**
 * @brief Power mode transition from Ax (active) to Sx.
 * @ingroup AX_TO_SX_TO_AX_GROUP
 * @param[in] slp_cycle [31:0] The count down cycles for sleep time, timer clock source is come from 1.3824MHz(Sx) or 32768Hz(Lx).
 * @param[in] l2sram_domain_pwr [0] L2 SRAM power domain control. See @ref SCU_L2SRAM_DOMAIN_PWR.
 *  - 0: L2 SRAM power domain is OFF when system in Sx mode.
 *  - 1: L2 SRAM power domain is ON when system in Sx mode.
 * @param[in] volt the voltage rating to be set for Sx/L0 mode.
 * @param[in] slp_sel select sleep mode.
 * @remarks no return value.
 */
void upt_power_Ax_to_Sx(
		uint32_t slp_cycle,
		enum_upt_sram_pwr_ctrl_Type l2sram_domain_pwr,
		enum_upt_l0_volt_Type volt,
		enum_upt_sleep_Type slp_sel);

/**
 * @brief Power mode transition from Ax to R0.
 * @ingroup AX_TO_R0_TO_AX_GROUP
 * @param[in] n_intSrc Number of interrupt sources to wake system up from R0 to Ax.
 * @param[in] rtcmIntSrcList Interrupt source list.
 * @remarks no return value.
 */
void upt_power_Ax_to_R0(
		uint32_t n_intSrc,
		enum_upt_rtcm_int_Type* rtcmIntSrcList);

/**
 * @brief Enable/Disable bootup sequence.
 * @param[in] BootType Bootup sequence will be enabled or disabled.
 * @param[in] enable bit 1: enable, 0: disable
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_power_enable_bootup(enum_upt_boot_Type BootType, bool enable);

/**
 * @brief Check boot-up status
 * @ingroup POWER_MODE
 * @return Bootup status. See @ref SCU_BOOTSTAT register
 */
uint32_t upt_power_check_bootup(void);

/**
 * @brief Check if the current session boot-up is from source or not.
 * @ingroup POWER_MODE
 * @return true if current session boot-up is from source, 0 otherwise.
 */
bool upt_power_is_bootup_from(enum_upt_boot_Type src);

/**
 * @brief Re-initialize SOC setting after warmboot.
 * @ingroup POWER_MODE
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_wramboot_init_hook(void);

/**
 * @brief System power stable counts(only valid on HW/WDT/ECC/Warmboot).
 * @param[in] waitcycle waiting cycle(s).
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_power_set_power_ok_wait_cycle(uint32_t waitcycle);

/**
 * @brief Set external device power stable counts
 * @param[in] waitcycle waiting cycle(s).
 * @param[in] enable enable or disable of this function.
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_power_set_gpio_ctrl_wait_cycle(uint32_t waitcycle, bool enable);

/**
 * @brief Get rtcm boot-up interrupt event.
 * @ingroup POWER_MODE
 * @return interrupt status.
 */
upt_rtcm_int_stat_Type upt_power_rtcm_interrupt_status(void);

/**
 * @brief Clear rtcm boot-up interrupt event.
 * @ingroup POWER_MODE
 * @param[in] int_event Interrupt to be cleared.
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_power_rtcm_clear_interrupt(upt_rtcm_int_stat_Type int_event);

/**
 * @brief Enable/Disable RTCM Bootup interrupt.
 * @ingroup POWER_MODE
 * @param[in] interrupt Interrupt to be enable or disable.
 * @param[in] enable enable or disable.
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_power_rtcm_enable_interrupt(upt_rtcm_int_stat_Type interrupt, bool enable);

/**
 * @brief Get aon power mode switching interrupt event (E34 shouldn't use, only debug usage).
 * @ingroup POWER_MODE
 * @return interrupt status.
 */
upt_aon_int_stat_Type upt_power_aon_interrupt_status(void);

/**
 * @brief Clear aon power mode switching interrupt event (E34 shouldn't use, only debug usage).
 * @ingroup POWER_MODE
 * @param[in] int_event Interrupt to be cleared.
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_power_aon_clear_interrupt(upt_aon_int_stat_Type int_event);

/**
 * @brief Enable/Disable aon power mode switching interrupt (E34 shouldn't use, only debug usage).
 * @ingroup POWER_MODE
 * @param[in] interrupt Interrupt to be enable or disable.
 * @param[in] enable enable or disable.
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_power_aon_enable_interrupt(upt_aon_int_stat_Type interrupt, bool enable);

/**
 * @brief Set SIF as PMIC trigger.
 * @ingroup POWER_MODE
 * @param[in] trigger_src target source(s).
 * @param[in] type Trigger mode.
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_power_sif_pmic_trigger(
		enum_upt_sif_tri_src_Type trigger_src,
		enum_upt_sif_tri_Type type);

/**
 * @brief Set PMIC_GPIO as PMIC trigger.
 * @ingroup POWER_MODE
 * @param[in] trigger_src target source(s).
 * @param[in] type Trigger mode.
 * @param[in] org_data PMIC_GPIO data before trigger.
 * @param[in] tri_data PMIC_GPIO data after trigger.
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_power_gpio_pmic_trigger(
		enum_upt_sif_tri_src_Type trigger_src,
		enum_upt_sif_tri_Type type,
		enum_upt_gpio_tri_val_Type org_data,
		enum_upt_gpio_tri_val_Type tri_data);

/**
 * @brief Software interrupt to E34.
 * @ingroup POWER_MODE
 * @param[in] enable Software interrupt to E34.
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_power_sw_to_e34_interrupt(bool enable);

/**
 * @brief Get software interrupt to E34 status.
 * @ingroup POWER_MODE
 * @return interrupt status
 */
bool upt_power_sw_to_e34_interrupt_status(void);

/**
 * @brief Clear software interrupt to E34 event.
 * @ingroup POWER_MODE
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_power_sw_to_e34_clear_interrupt(void);

/**
 * @brief Software interrupt to E21.
 * @ingroup POWER_MODE
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_power_sw_to_e21_interrupt(bool enable);

/**
 * @brief Get software interrupt to E21 status.
 * @ingroup POWER_MODE
 * @return interrupt status
 */
bool upt_power_sw_to_e21_interrupt_status(void);

/**
 * @brief Clear software interrupt to E21 event.
 * @ingroup POWER_MODE
 * @return enum_pwmode_retcode_Type value.
 */
enum_pwmode_retcode_Type upt_power_sw_to_e21_clear_interrupt(void);

/**
 * @brief Do software reset (internal use).
 * @ingroup POWER_MODE
 * @param[in] remap choose re-map location.
 * @param[in] reset_group2_msk reset mask of scu group2. SET 1 will cause Flash over speed!!
 * @param[in] reset_group_msk pointer to a list of 3 SCU registers to set @ref SCU_SWRSTMSK0, @ref SCU_SWRSTMSK1 and @ref SCU_SWRSTMSK2.
 */
void _upt_power_sw_reset(
		enum_upt_remap_Type remap,
		bool reset_group2_msk,
		uint32_t* reset_group_msk);

/**
 * @brief Do software reset for user.
 * @ingroup POWER_MODE
 * @param[in] remap choose re-map location.
 * @param[in] reset_group_msk pointer to a list of 3 SCU registers to set @ref SCU_SWRSTMSK0, @ref SCU_SWRSTMSK1 and @ref SCU_SWRSTMSK2.
 */
#define upt_power_sw_reset(remap, reset_group_msk) _upt_power_sw_reset(remap, 0, reset_group_msk)


#endif /* UPT_POWMOD_H */
