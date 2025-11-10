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
 * @file upt_isr.h
 * @brief API for UPT ISR
 */
#ifndef __UPT_ISR_H__
#define __UPT_ISR_H__
#include <stdint.h>

#include "riscv_cpu.h"

extern uint32_t upt_sw_wdt_event;

#define UPT_INTERRUPT_ID(src_name) (upt_##src_name##_int_id)
#define UPT_PLIC_INTERRUPT_ID(id) (id & ~UPT_PLIC_ID_FLAG)
#define EXTERN_VOID_ISR(src_name) extern void src_name##_isr(uint32_t id, void* data)
#define CLINT_INT_ID_OFFSET     16
#define PLIC_INT_ID_OFFSET      1
#define UPT_PLIC_ID_FLAG        0x1000

#ifdef __cplusplus
extern "C" {
#endif

void trigger_sw_interrupt(void);
void init_sw_interrupt(void *sw_isr_handler);
void __attribute__((weak)) exception_ecall_handler(metal_cpu_Type *cpu, uint32_t ecode);
void init_interrupts(void);
int32_t e34_interrupt_enable(void);
int32_t e34_interrupt_disable(void);
int32_t upt_interrupt_enable(uint32_t id);
int32_t upt_interrupt_disable(uint32_t id);
int32_t upt_interrupt_set_priority(uint32_t id, uint32_t priority);
int32_t upt_interrupt_register_handle(uint32_t id, metal_interrupt_handler_t handler, void *priv_data);
uint32_t __is_plic(uint32_t id);


typedef enum cpu_interrupt_id {
  upt_cpu_software_int_id = 3,                        //3
  upt_cpu_mtime_int_id = 7,                           //7
} cpu_interrupt_id_Type;

typedef enum clint_interrupt_id {
  upt_scu_e34_powermode_int_id = CLINT_INT_ID_OFFSET, //16
  upt_scu_e34_bootup_int_id,                          //17
  upt_scu_e34_sw_int_id,                              //18
  upt_scu_pllx_stable_change_int_id,                  //19
  upt_aon_timer2to3_int_id,                           //20
  upt_fw_timer2to3_int_id,                            //21
  upt_sys_timer_7_int_id,                             //22
  upt_udl2_int_id,                                    //23
  upt_udl1_int_id,                                    //24
  upt_nema_irq_int_id,                                //25
  upt_nema_syserror_irq_int_id,                       //26
  upt_nema_freeze_int_id,                             //27
  upt_nemadc_irq_int_id,                              //28
  upt_dmac2_int_id,                                   //29
  upt_dmac1_int_id,                                   //30
  upt_dmac0_int_id,                                   //31
} clint_interrupt_id_Type;

typedef enum plic_interrupt_id {
  upt_ospi_int_id = PLIC_INT_ID_OFFSET + UPT_PLIC_ID_FLAG,       //1
  upt_dsi_controller_int_id,    		                 //2
  upt_rsvd_3_int_id,            		                 //3
  upt_uart0_int_id,             		                 //4
  upt_uart1_int_id,             		                 //5
  upt_spi0_master_slave_int_id, 		                 //6
  upt_spi1_master_int_id,       		                 //7
  upt_i2c0_int_id,              		                 //8
  upt_i2c1_int_id,              		                 //9
  upt_i2c2_int_id,              		                 //10
  upt_pufiot_int_id,            		                 //11
  upt_sys_gpio_0_int_id,        		                 //12
  upt_sys_gpio_1_int_id,        		                 //13
  upt_sys_gpio_2_int_id,        		                 //14
  upt_sys_gpio_3_int_id,        		                 //15
  upt_sys_gpio_4_int_id,        		                 //16
  upt_sys_gpio_5_int_id,        		                 //17
  upt_sys_gpio_6_int_id,        		                 //18
  upt_sys_gpio_7_int_id,        		                 //19
  upt_sys_gpio_8_int_id,        		                 //20
  upt_sys_gpio_9_int_id,        		                 //21
  upt_sys_gpio_10_int_id,       		                 //22
  upt_sys_gpio_11_int_id,       		                 //23
  upt_sys_gpio_12_int_id,       		                 //24
  upt_sys_gpio_13_int_id,       		                 //25
  upt_sys_gpio_14_int_id,       		                 //26
  upt_sys_gpio_15_int_id,       		                 //27
  upt_sys_gpio_16_int_id,       		                 //28
  upt_sys_gpio_17_int_id,       		                 //29
  upt_sys_gpio_18_int_id,       		                 //30
  upt_sys_gpio_19_int_id,       		                 //31
  upt_sys_gpio_20_int_id,       		                 //32
  upt_sys_gpio_21_int_id,       		                 //33
  upt_sys_gpio_22_int_id,       		                 //34
  upt_sys_gpio_23_int_id,       		                 //35
  upt_sys_gpio_24_int_id,       		                 //36
  upt_sys_gpio_25_int_id,       		                 //37
  upt_sys_gpio_26_int_id,       		                 //38
  upt_sys_gpio_27_int_id,       		                 //39
  upt_sys_gpio_28_int_id,       		                 //40
  upt_sys_gpio_29_int_id,       		                 //41
  upt_sys_gpio_30_int_id,       		                 //42
  upt_sys_gpio_31_int_id,       		                 //43
  upt_sys_gpio_32_int_id,       		                 //44
  upt_sys_gpio_33_int_id,       		                 //45
  upt_sys_gpio_34_int_id,       		                 //46
  upt_sys_gpio_35_int_id,       		                 //47
  upt_sys_gpio_36_int_id,       		                 //48
  upt_sys_gpio_37_int_id,       		                 //49
  upt_sys_gpio_38_int_id,       		                 //50
  upt_sys_gpio_39_int_id,       		                 //51
  upt_sys_gpio_40_int_id,       		                 //52
  upt_sys_gpio_41_int_id,       		                 //53
  upt_sys_gpio_42_int_id,       		                 //54
  upt_sys_gpio_43_int_id,       		                 //55
  upt_sys_gpio_44_int_id,       		                 //56
  upt_nemadc_int_id,            		                 //57
  upt_spi2_master_int_id,       		                 //58
  upt_spi3_master_int_id,       		                 //59
  upt_i2c3_int_id,              		                 //60
  upt_i2c4_int_id,              		                 //61
  upt_i2c5_int_id,              		                 //62
  upt_i2c6_int_id,              		                 //63
  upt_peri_gpio_0_int_id,       		                 //64
  upt_peri_gpio_1_int_id,       		                 //65
  upt_peri_gpio_2_int_id,       		                 //66
  upt_peri_gpio_3_int_id,       		                 //67
  upt_peri_gpio_4_int_id,       		                 //68
  upt_peri_gpio_5_int_id,       		                 //69
  upt_peri_gpio_6_int_id,       		                 //70
  upt_peri_gpio_7_int_id,       		                 //71
  upt_peri_gpio_8_int_id,       		                 //72
  upt_peri_gpio_9_int_id,       		                 //73
  upt_peri_gpio_10_int_id,      		                 //74
  upt_peri_gpio_11_int_id,      		                 //75
  upt_peri_gpio_12_int_id,      		                 //76
  upt_peri_gpio_13_int_id,      		                 //77
  upt_peri_gpio_14_int_id,      		                 //78
  upt_peri_gpio_15_int_id,      		                 //79
  upt_peri_gpio_16_int_id,      		                 //80
  upt_peri_gpio_17_int_id,      		                 //81
  upt_peri_gpio_18_int_id,      		                 //82
  upt_peri_gpio_19_int_id,      		                 //83
  upt_peri_gpio_20_int_id,      		                 //84
  upt_peri_gpio_21_int_id,      		                 //85
  upt_peri_gpio_22_int_id,      		                 //86
  upt_peri_gpio_23_int_id,      		                 //87
  upt_peri_gpio_24_int_id,      		                 //88
  upt_peri_gpio_25_int_id,      		                 //89
  upt_peri_gpio_26_int_id,      		                 //90
  upt_peri_gpio_27_int_id,      		                 //91
  upt_peri_gpio_28_int_id,      		                 //92
  upt_peri_gpio_29_int_id,      		                 //93
  upt_uart2_int_id,             		                 //94
  upt_uart3_int_id,             		                 //95
  upt_pdmtopcm0_int_id,         		                 //96
  upt_pdmtopcm1_int_id,         		                 //97
  upt_i2s0_master_int_id,       		                 //98
  upt_i2s1_master_slave_int_id, 		                 //99
  upt_peri_pwm_0_int_id,        		                 //100
  upt_peri_pwm_1_int_id,        		                 //101
  upt_peri_pwm_2_int_id,        		                 //102
  upt_peri_pwm_3_int_id,        		                 //103
  upt_sys_timer_0_int_id,       		                 //104
  upt_sys_timer_1_int_id,       		                 //105
  upt_sys_timer_2_int_id,       		                 //106
  upt_sys_timer_3_int_id,       		                 //107
  upt_sys_timer_4_int_id,       		                 //108
  upt_sys_timer_5_int_id,       		                 //109
  upt_sys_timer_6_int_id,       		                 //110
  upt_sdc_int_id,               		                 //111
  upt_rtcm_gpio_int_id,         		                 //112
  upt_rtc_int_id,               		                 //113
  upt_tick_timer_int_id,        		                 //114
  upt_pmu_int_id,               		                 //115
  upt_aon_wdt_int_id,               		             //116
  upt_aon_pwm_int_id,           		                 //117
  upt_fw_timer0to1_int_id,      		                 //118
  upt_sif_int_id,               		                 //119
  upt_tempsensor_int_id,        		                 //120
  upt_aon_uart_int_id,          		                 //121
  upt_aon_spi0to1_int_id,       		                 //122
  upt_aon_i2c0to4_int_id,       		                 //123
  upt_aon_timer0to1_int_id,     		                 //124
  upt_adc_audio0to3_int_id,     		                 //125
  upt_adc_general0to5_int_id,   		                 //126
  upt_aon_gpio_0to20_int_id,    		                 //127
} plic_interrupt_id_Type;

// CPU interrupt handlers
EXTERN_VOID_ISR(cpu_software);
EXTERN_VOID_ISR(cpu_mtime);

// CLINT interrupt handlers
EXTERN_VOID_ISR(scu_e34_powermode);
EXTERN_VOID_ISR(scu_e34_bootup);
EXTERN_VOID_ISR(scu_e34_sw);
EXTERN_VOID_ISR(scu_pllx_stable_change);
EXTERN_VOID_ISR(aon_timer2to3);
EXTERN_VOID_ISR(fw_timer2to3);
EXTERN_VOID_ISR(sys_timer_7);
EXTERN_VOID_ISR(udl2);
EXTERN_VOID_ISR(udl1);
EXTERN_VOID_ISR(nema_irq);
EXTERN_VOID_ISR(nema_syserror_irq);
EXTERN_VOID_ISR(nema_freeze);
EXTERN_VOID_ISR(nemadc_irq);
EXTERN_VOID_ISR(dmac2);
EXTERN_VOID_ISR(dmac1);
EXTERN_VOID_ISR(dmac0);

// PLIC interrupt handlers
EXTERN_VOID_ISR(ospi);
EXTERN_VOID_ISR(dsi_controller);
EXTERN_VOID_ISR(uart0);
EXTERN_VOID_ISR(uart1);
EXTERN_VOID_ISR(spi0_master_slave);
EXTERN_VOID_ISR(spi1_master);
EXTERN_VOID_ISR(i2c0);
EXTERN_VOID_ISR(i2c1);
EXTERN_VOID_ISR(i2c2);
EXTERN_VOID_ISR(pufiot);
EXTERN_VOID_ISR(sys_gpio_0);
EXTERN_VOID_ISR(sys_gpio_1);
EXTERN_VOID_ISR(sys_gpio_2);
EXTERN_VOID_ISR(sys_gpio_3);
EXTERN_VOID_ISR(sys_gpio_4);
EXTERN_VOID_ISR(sys_gpio_5);
EXTERN_VOID_ISR(sys_gpio_6);
EXTERN_VOID_ISR(sys_gpio_7);
EXTERN_VOID_ISR(sys_gpio_8);
EXTERN_VOID_ISR(sys_gpio_9);
EXTERN_VOID_ISR(sys_gpio_10);
EXTERN_VOID_ISR(sys_gpio_11);
EXTERN_VOID_ISR(sys_gpio_12);
EXTERN_VOID_ISR(sys_gpio_13);
EXTERN_VOID_ISR(sys_gpio_14);
EXTERN_VOID_ISR(sys_gpio_15);
EXTERN_VOID_ISR(sys_gpio_16);
EXTERN_VOID_ISR(sys_gpio_17);
EXTERN_VOID_ISR(sys_gpio_18);
EXTERN_VOID_ISR(sys_gpio_19);
EXTERN_VOID_ISR(sys_gpio_20);
EXTERN_VOID_ISR(sys_gpio_21);
EXTERN_VOID_ISR(sys_gpio_22);
EXTERN_VOID_ISR(sys_gpio_23);
EXTERN_VOID_ISR(sys_gpio_24);
EXTERN_VOID_ISR(sys_gpio_25);
EXTERN_VOID_ISR(sys_gpio_26);
EXTERN_VOID_ISR(sys_gpio_27);
EXTERN_VOID_ISR(sys_gpio_28);
EXTERN_VOID_ISR(sys_gpio_29);
EXTERN_VOID_ISR(sys_gpio_30);
EXTERN_VOID_ISR(sys_gpio_31);
EXTERN_VOID_ISR(sys_gpio_32);
EXTERN_VOID_ISR(sys_gpio_33);
EXTERN_VOID_ISR(sys_gpio_34);
EXTERN_VOID_ISR(sys_gpio_35);
EXTERN_VOID_ISR(sys_gpio_36);
EXTERN_VOID_ISR(sys_gpio_37);
EXTERN_VOID_ISR(sys_gpio_38);
EXTERN_VOID_ISR(sys_gpio_39);
EXTERN_VOID_ISR(sys_gpio_40);
EXTERN_VOID_ISR(sys_gpio_41);
EXTERN_VOID_ISR(sys_gpio_42);
EXTERN_VOID_ISR(sys_gpio_43);
EXTERN_VOID_ISR(sys_gpio_44);
EXTERN_VOID_ISR(nemadc);
EXTERN_VOID_ISR(spi2_master);
EXTERN_VOID_ISR(spi3_master);
EXTERN_VOID_ISR(i2c3);
EXTERN_VOID_ISR(i2c4);
EXTERN_VOID_ISR(i2c5);
EXTERN_VOID_ISR(i2c6);
EXTERN_VOID_ISR(peri_gpio_0);
EXTERN_VOID_ISR(peri_gpio_1);
EXTERN_VOID_ISR(peri_gpio_2);
EXTERN_VOID_ISR(peri_gpio_3);
EXTERN_VOID_ISR(peri_gpio_4);
EXTERN_VOID_ISR(peri_gpio_5);
EXTERN_VOID_ISR(peri_gpio_6);
EXTERN_VOID_ISR(peri_gpio_7);
EXTERN_VOID_ISR(peri_gpio_8);
EXTERN_VOID_ISR(peri_gpio_9);
EXTERN_VOID_ISR(peri_gpio_10);
EXTERN_VOID_ISR(peri_gpio_11);
EXTERN_VOID_ISR(peri_gpio_12);
EXTERN_VOID_ISR(peri_gpio_13);
EXTERN_VOID_ISR(peri_gpio_14);
EXTERN_VOID_ISR(peri_gpio_15);
EXTERN_VOID_ISR(peri_gpio_16);
EXTERN_VOID_ISR(peri_gpio_17);
EXTERN_VOID_ISR(peri_gpio_18);
EXTERN_VOID_ISR(peri_gpio_19);
EXTERN_VOID_ISR(peri_gpio_20);
EXTERN_VOID_ISR(peri_gpio_21);
EXTERN_VOID_ISR(peri_gpio_22);
EXTERN_VOID_ISR(peri_gpio_23);
EXTERN_VOID_ISR(peri_gpio_24);
EXTERN_VOID_ISR(peri_gpio_25);
EXTERN_VOID_ISR(peri_gpio_26);
EXTERN_VOID_ISR(peri_gpio_27);
EXTERN_VOID_ISR(peri_gpio_28);
EXTERN_VOID_ISR(peri_gpio_29);
EXTERN_VOID_ISR(uart2);
EXTERN_VOID_ISR(uart3);
EXTERN_VOID_ISR(pdmtopcm0);
EXTERN_VOID_ISR(pdmtopcm1);
EXTERN_VOID_ISR(i2s0_master);
EXTERN_VOID_ISR(i2s1_master_slave);
EXTERN_VOID_ISR(peri_pwm_0);
EXTERN_VOID_ISR(peri_pwm_1);
EXTERN_VOID_ISR(peri_pwm_2);
EXTERN_VOID_ISR(peri_pwm_3);
EXTERN_VOID_ISR(sys_timer_0);
EXTERN_VOID_ISR(sys_timer_1);
EXTERN_VOID_ISR(sys_timer_2);
EXTERN_VOID_ISR(sys_timer_3);
EXTERN_VOID_ISR(sys_timer_4);
EXTERN_VOID_ISR(sys_timer_5);
EXTERN_VOID_ISR(sys_timer_6);
EXTERN_VOID_ISR(sdc);
EXTERN_VOID_ISR(rtcm_gpio);
EXTERN_VOID_ISR(rtc);
EXTERN_VOID_ISR(tick_timer);
EXTERN_VOID_ISR(pmu);
EXTERN_VOID_ISR(wdt);
EXTERN_VOID_ISR(aon_pwm);
EXTERN_VOID_ISR(fw_timer0to1);
EXTERN_VOID_ISR(sif);
EXTERN_VOID_ISR(tempsensor);
EXTERN_VOID_ISR(aon_uart);
EXTERN_VOID_ISR(aon_spi0to1);
EXTERN_VOID_ISR(aon_i2c0to4);
EXTERN_VOID_ISR(aon_timer0to1);
EXTERN_VOID_ISR(adc_audio0to3);
EXTERN_VOID_ISR(adc_general0to5);
EXTERN_VOID_ISR(aon_gpio_0to20);
#ifdef __cplusplus
}
#endif
#endif //__UPT_ISR_H__
