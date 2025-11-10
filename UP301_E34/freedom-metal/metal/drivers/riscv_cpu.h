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
#ifndef METAL_DRIVERS_RISCV_CPU_H
#define METAL_DRIVERS_RISCV_CPU_H
#include <stdint.h>

#include "metal/compiler.h"
#include "metal/cpu.h"

#define METAL_MAX_CORES 8
#define METAL_MAX_MI 32 /* Per ISA MCause interrupts 32+ are Reserved */
#define METAL_MAX_ME 12 /* Per ISA Exception codes 12+ are Reserved   */
#define METAL_DEFAULT_RTC_FREQ 32768

#define METAL_DISABLE 0
#define METAL_ENABLE 1

#define METAL_ISA_A_EXTENSIONS 0x0001
#define METAL_ISA_C_EXTENSIONS 0x0004
#define METAL_ISA_D_EXTENSIONS 0x0008
#define METAL_ISA_E_EXTENSIONS 0x0010
#define METAL_ISA_F_EXTENSIONS 0x0020
#define METAL_ISA_G_EXTENSIONS 0x0040
#define METAL_ISA_I_EXTENSIONS 0x0100
#define METAL_ISA_M_EXTENSIONS 0x1000
#define METAL_ISA_N_EXTENSIONS 0x2000
#define METAL_ISA_Q_EXTENSIONS 0x10000
#define METAL_ISA_S_EXTENSIONS 0x40000
#define METAL_ISA_U_EXTENSIONS 0x100000
#define METAL_ISA_V_EXTENSIONS 0x200000
#define METAL_ISA_XL32_EXTENSIONS 0x40000000UL
#define METAL_ISA_XL64_EXTENSIONS 0x8000000000000000UL
#define METAL_ISA_XL128_EXTENSIONS 0xC000000000000000UL

#define METAL_MTVEC_DIRECT 0x00
#define METAL_MTVEC_VECTORED 0x01
#define METAL_MTVEC_CLIC 0x02
#define METAL_MTVEC_CLIC_VECTORED 0x03
#define METAL_MTVEC_CLIC_RESERVED 0x3C
#define METAL_MTVEC_MASK 0x3F
#if __riscv_xlen == 32
#define METAL_MCAUSE_INTR 0x80000000UL
#define METAL_MCAUSE_CAUSE 0x000003FFUL
#else
#define METAL_MCAUSE_INTR 0x8000000000000000UL
#define METAL_MCAUSE_CAUSE 0x00000000000003FFUL
#endif
#define METAL_MCAUSE_MINHV 0x40000000UL
#define METAL_MCAUSE_MPP 0x30000000UL
#define METAL_MCAUSE_MPIE 0x08000000UL
#define METAL_MCAUSE_MPIL 0x00FF0000UL
#define METAL_MSTATUS_MIE 0x00000008UL
#define METAL_MSTATUS_MPIE 0x00000080UL
#define METAL_MSTATUS_MPP 0x00001800UL
#define METAL_MSTATUS_FS_INIT 0x00002000UL
#define METAL_MSTATUS_FS_CLEAN 0x00004000UL
#define METAL_MSTATUS_FS_DIRTY 0x00006000UL
#define METAL_MSTATUS_MPRV 0x00020000UL
#define METAL_MSTATUS_MXR 0x00080000UL
#define METAL_MINTSTATUS_MIL 0xFF000000UL
#define METAL_MINTSTATUS_SIL 0x0000FF00UL
#define METAL_MINTSTATUS_UIL 0x000000FFUL

#define METAL_LOCAL_INTR(X) (16 + X)
#define METAL_MCAUSE_EVAL(cause) (cause & METAL_MCAUSE_INTR)
#define METAL_INTERRUPT(cause) (METAL_MCAUSE_EVAL(cause) ? 1 : 0)
#define METAL_EXCEPTION(cause) (METAL_MCAUSE_EVAL(cause) ? 0 : 1)
#define METAL_SW_INTR_EXCEPTION (METAL_MCAUSE_INTR + 3)
#define METAL_TMR_INTR_EXCEPTION (METAL_MCAUSE_INTR + 7)
#define METAL_EXT_INTR_EXCEPTION (METAL_MCAUSE_INTR + 11)
#define METAL_LOCAL_INTR_EXCEPTION(X) (METAL_MCAUSE_INTR + METAL_LOCAL_INTR(X))
#define METAL_LOCAL_INTR_RESERVE0 1
#define METAL_LOCAL_INTR_RESERVE1 2
#define METAL_LOCAL_INTR_RESERVE2 4
#define METAL_LOCAL_INTERRUPT_SW 8 /* Bit3 0x008 */
#define METAL_LOCAL_INTR_RESERVE4 16
#define METAL_LOCAL_INTR_RESERVE5 32
#define METAL_LOCAL_INTR_RESERVE6 64
#define METAL_LOCAL_INTERRUPT_TMR 128 /* Bit7 0x080 */
#define METAL_LOCAL_INTR_RESERVE8 256
#define METAL_LOCAL_INTR_RESERVE9 512
#define METAL_LOCAL_INTR_RESERVE10 1024
#define METAL_LOCAL_INTERRUPT_EXT 2048 /* Bit11 0x800 */
/* Bit12 to Bit15 are Reserved */
#define METAL_LOCAL_INTERRUPT(X)                                               \
    (0x10000 << X) /* Bit16+ Start of Custom Local Interrupt */
#define METAL_MIE_INTERRUPT METAL_MSTATUS_MIE

#define METAL_INSN_LENGTH_MASK 3
#define METAL_INSN_NOT_COMPRESSED 3

typedef enum metal_privilege_mode {
    METAL_MACHINE_PRIVILEGE_MODE,
    METAL_SUPERVISOR_PRIVILEGE_MODE,
    METAL_USER_PRIVILEGE_MODE,
} metal_privilege_mode_Type;

typedef enum enum_metal_interrupt_id {
    METAL_INTERRUPT_ID_BASE,
    METAL_INTERRUPT_ID_SW = (METAL_INTERRUPT_ID_BASE + 3),
    METAL_INTERRUPT_ID_TMR = (METAL_INTERRUPT_ID_BASE + 7),
    METAL_INTERRUPT_ID_EXT = (METAL_INTERRUPT_ID_BASE + 11),
    METAL_INTERRUPT_ID_CSW = (METAL_INTERRUPT_ID_BASE + 12),
    METAL_INTERRUPT_ID_LC0 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(0)),
    METAL_INTERRUPT_ID_LC1 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(1)),
    METAL_INTERRUPT_ID_LC2 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(2)),
    METAL_INTERRUPT_ID_LC3 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(3)),
    METAL_INTERRUPT_ID_LC4 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(4)),
    METAL_INTERRUPT_ID_LC5 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(5)),
    METAL_INTERRUPT_ID_LC6 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(6)),
    METAL_INTERRUPT_ID_LC7 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(7)),
    METAL_INTERRUPT_ID_LC8 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(8)),
    METAL_INTERRUPT_ID_LC9 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(9)),
    METAL_INTERRUPT_ID_LC10 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(10)),
    METAL_INTERRUPT_ID_LC11 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(11)),
    METAL_INTERRUPT_ID_LC12 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(12)),
    METAL_INTERRUPT_ID_LC13 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(13)),
    METAL_INTERRUPT_ID_LC14 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(14)),
    METAL_INTERRUPT_ID_LC15 = (METAL_INTERRUPT_ID_BASE + METAL_LOCAL_INTR(15)),
    METAL_INTERRUPT_ID_LCMX,
    METAL_INTERRUPT_ID_GL0 = METAL_INTERRUPT_ID_LCMX,
    METAL_INTERRUPT_ID_GLMX = (METAL_MCAUSE_CAUSE + 1),
    METAL_INTERRUPT_ID_BEU = 128,
} enum_metal_interrupt_id_Type;

typedef enum metal_exception_code {
    METAL_IAM_EXCEPTION_CODE,     /* Instruction address misaligned */
    METAL_IAF_EXCEPTION_CODE,     /* Instruction access faultd */
    METAL_II_EXCEPTION_CODE,      /* Illegal instruction */
    METAL_BREAK_EXCEPTION_CODE,   /* Breakpoint */
    METAL_LAM_EXCEPTION_CODE,     /* Load address misaligned */
    METAL_LAF_EXCEPTION_CODE,     /* Load access fault */
    METAL_SAMOAM_EXCEPTION_CODE,  /* Store/AMO address misaligned */
    METAL_SAMOAF_EXCEPTION_CODE,  /* Store/AMO access fault */
    METAL_ECALL_U_EXCEPTION_CODE, /* Environment call from U-mode */
    METAL_R9_EXCEPTION_CODE,      /* Reserved */
    METAL_R10_EXCEPTION_CODE,     /* Reserved */
    METAL_ECALL_M_EXCEPTION_CODE, /* Environment call from M-mode */
    METAL_MAX_EXCEPTION_CODE,
} metal_exception_code_Type;

typedef enum metal_interrup_cmd {
    METAL_TIMER_MTIME_GET = 1,
    METAL_SOFTWARE_IPI_CLEAR,
    METAL_SOFTWARE_IPI_SET,
    METAL_SOFTWARE_MSIP_GET,
    METAL_MAX_INTERRUPT_GET,
    METAL_INDEX_INTERRUPT_GET,
} metal_interrup_cmd_Type;

typedef struct __metal_interrupt_data {
    int64_t pad : 64;
    metal_interrupt_handler_t handler;
    void *sub_int;
    void *exint_data;
} __metal_interrupt_data_Type;

/* CPU interrupt controller */
#ifndef LOAD_SRAM_CODE
uintptr_t __metal_myhart_id(void) __attribute__ ((section (".FwHandler")));
#else
uintptr_t __metal_myhart_id(void);
#endif
struct __metal_driver_vtable_riscv_cpu_intc {
    struct metal_interrupt_vtable controller_vtable;
};

static void __metal_interrupt_global_enable(void);
static void __metal_interrupt_global_disable(void);
metal_vector_mode_Type __metal_controller_interrupt_vector_mode(void);
void __metal_controller_interrupt_vector(metal_vector_mode_Type mode,
                                         void *vec_table);

__METAL_S_DECLARE_VTABLE(__metal_driver_vtable_riscv_cpu_intc)

struct __metal_driver_riscv_cpu_intc {
    struct metal_interrupt controller;
    uint32_t init_done;
    uintptr_t metal_mtvec_table[METAL_MAX_MI];
    __metal_interrupt_data_Type metal_int_table[METAL_MAX_MI];
    __metal_interrupt_data_Type metal_int_beu;
    metal_exception_handler_t metal_exception_table[METAL_MAX_ME];
};

/* CPU driver*/
struct __metal_driver_vtable_cpu {
    struct metal_cpu_vtable cpu_vtable;
};

__METAL_S_DECLARE_VTABLE(__metal_driver_vtable_cpu)

struct __metal_driver_cpu {
    metal_cpu_Type cpu;
    uint32_t hpm_count; /* Available HPM counters per CPU */
};

#endif
