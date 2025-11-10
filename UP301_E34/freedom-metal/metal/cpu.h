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

/*! @file cpu.h
 *  @brief API for accessing CPU capabilities.
 */
#ifndef METAL_CPU_H
#define METAL_CPU_H
#include <stdint.h>

#include "metal/drivers/sifive_buserror0.h"
#include "metal/interrupt.h"

/*! @brief A device handle for a CPU hart
 */
typedef struct metal_cpu {
    const struct metal_cpu_vtable *vtable;
} metal_cpu_Type;
/*!
 * @brief Function signature for exception handlers
 */
typedef void (*metal_exception_handler_t)(metal_cpu_Type *cpu, uint32_t ecode);

struct metal_cpu_vtable {
    uint64_t (*mcycle_get)(metal_cpu_Type *cpu);
    uint64_t (*timebase_get)(metal_cpu_Type *cpu);
    uint64_t (*mtime_get)(metal_cpu_Type *cpu);
    int32_t (*mtimecmp_set)(metal_cpu_Type *cpu, uint64_t time);
    metal_interrupt_Type *(*tmr_controller_interrupt)(metal_cpu_Type *cpu);
    uint32_t (*get_tmr_interrupt_id)(metal_cpu_Type *cpu);
    metal_interrupt_Type *(*sw_controller_interrupt)(metal_cpu_Type *cpu);
    uint32_t (*get_sw_interrupt_id)(metal_cpu_Type *cpu);
    uint32_t (*set_sw_ipi)(metal_cpu_Type *cpu, uint32_t hartid);
    int32_t (*clear_sw_ipi)(metal_cpu_Type *cpu, uint32_t hartid);
    uint32_t (*get_msip)(metal_cpu_Type *cpu, uint32_t hartid);
    metal_interrupt_Type *(*controller_interrupt)(metal_cpu_Type *cpu);
    int32_t (*exception_register)(metal_cpu_Type *cpu, uint32_t ecode,
                              metal_exception_handler_t handler);
    uint32_t (*get_ilen)(metal_cpu_Type *cpu, uintptr_t epc);
    uintptr_t (*get_epc)(metal_cpu_Type *cpu);
    uint32_t (*set_epc)(metal_cpu_Type *cpu, uintptr_t epc);
    metal_buserror_Type *(*get_buserror)(metal_cpu_Type *cpu);
};


/*! @brief Get a reference to a CPU hart
 *
 * @param hartid The ID of the desired CPU hart
 * @return A pointer to the CPU device handle
 */
#ifndef LOAD_SRAM_CODE
metal_cpu_Type *metal_cpu_get(uint32_t hartid) __attribute__ ((section (".FwHandler")));
#else
metal_cpu_Type *metal_cpu_get(uint32_t hartid);
#endif

/*! @brief Get the hartid of the CPU hart executing this function
 *
 * @return The hartid of the current CPU hart */
uint32_t metal_cpu_get_current_hartid(void);

/*! @brief Get the number of CPU harts
 *
 * @return The number of CPU harts */
uint32_t metal_cpu_get_num_harts(void);

/*! @brief Get the CPU cycle count timer value
 *
 * Get the value of the cycle count timer for a given CPU
 *
 * @param cpu The CPU device handle
 * @return The value of the CPU cycle count timer
 */
__inline__ uint64_t metal_cpu_get_timer(metal_cpu_Type *cpu) {
    return cpu->vtable->mcycle_get(cpu);
}

/*! @brief Get the timebase of the CPU
 *
 * Get the value of the timebase of the cycle count timer
 *
 * @param cpu The CPU device handle
 * @return The value of the cycle count timer timebase
 */
__inline__ uint64_t metal_cpu_get_timebase(metal_cpu_Type *cpu) {
    return cpu->vtable->timebase_get(cpu);
}

/*! @brief Get the value of the mtime RTC
 *
 * Get the value of the mtime real-time clock. The CPU interrupt controller
 * must be initialized before this function is called or the return value
 * will be 0.
 *
 * @param cpu The CPU device handle
 * @return The value of mtime, or 0 if failure
 */
#ifndef LOAD_SRAM_CODE
extern uint64_t metal_cpu_get_mtime(metal_cpu_Type *cpu) __attribute__ ((section (".FwHandler")));
#else
extern uint64_t metal_cpu_get_mtime(metal_cpu_Type *cpu);
#endif

/*! @brief Set the value of the RTC mtimecmp RTC
 *
 * Set the value of the mtime real-time clock compare register. The CPU
 * interrupt controller must be initialized before this function is called
 * or the return value will be -1;
 *
 * @param cpu The CPU device handle
 * @param time The value to set the compare register to
 * @return The value of mtimecmp or -1 if error
 */
__inline__ int32_t metal_cpu_set_mtimecmp(metal_cpu_Type *cpu,
                                      uint64_t time) {
    return cpu->vtable->mtimecmp_set(cpu, time);
}

/*! @brief Get a reference to RTC timer interrupt controller
 *
 * Get a reference to the interrupt controller for the real-time clock
 * interrupt. The controller returned by this function must be initialized
 * before any interrupts are registered or enabled with it.
 *
 * @param cpu The CPU device handle
 * @return A pointer to the timer interrupt handle
 */
__inline__ metal_interrupt_Type *
metal_cpu_timer_interrupt_controller(metal_cpu_Type *cpu) {
    return cpu->vtable->tmr_controller_interrupt(cpu);
}

/*! @brief Get the RTC timer interrupt id
 *
 * Get the interrupt ID of the real-time clock interrupt
 *
 * @param cpu The CPU device handle
 * @return The timer interrupt ID
 */
__inline__ uint32_t metal_cpu_timer_get_interrupt_id(metal_cpu_Type *cpu) {
    return cpu->vtable->get_tmr_interrupt_id(cpu);
}

/*! @brief Get a reference to the software interrupt controller
 *
 * Get a reference to the interrupt controller for the software/inter-process
 * interrupt. The controller returned by this function must be initialized
 * before any interrupts are registered or enabled with it.
 *
 * @param cpu The CPU device handle
 * @return A pointer to the software interrupt handle
 */
__inline__ metal_interrupt_Type *
metal_cpu_software_interrupt_controller(metal_cpu_Type *cpu) {
    return cpu->vtable->sw_controller_interrupt(cpu);
}

/*! @brief Get the software interrupt id
 *
 * Get the interrupt ID for the software/inter-process interrupt
 *
 * @param cpu The CPU device handle
 * @return the software interrupt ID
 */
__inline__ uint32_t metal_cpu_software_get_interrupt_id(metal_cpu_Type *cpu) {
    return cpu->vtable->get_sw_interrupt_id(cpu);
}

/*!
 * @brief Set the inter-process interrupt for a hart
 *
 * Trigger a software/inter-process interrupt for a hart. The CPU interrupt
 * controller for the CPU handle passed to this function must be initialized
 * before this function is called.
 *
 * @param cpu The CPU device handle
 * @param hartid The CPU hart ID to be interrupted
 * @return 0 upon success
 */
__inline__ int32_t metal_cpu_software_set_ipi(metal_cpu_Type *cpu, uint32_t hartid) {
    return cpu->vtable->set_sw_ipi(cpu, hartid);
}

/*!
 * @brief Clear the inter-process interrupt for a hart
 *
 * Clear the software/inter-process interrupt for a hart. The CPU interrupt
 * controller for the CPU handle passed to this function must be initialized
 * before this function is called.
 *
 * @param cpu The CPU device handle
 * @param hartid The CPU hart ID to clear
 * @return 0 upon success
 */
__inline__ int32_t metal_cpu_software_clear_ipi(metal_cpu_Type *cpu, uint32_t hartid) {
    return cpu->vtable->clear_sw_ipi(cpu, hartid);
}

/*!
 * @brief Get the value of MSIP for the given hart
 *
 * Get the value of the machine software interrupt pending bit for
 * the given hart. The CPU interrupt controller for the CPU handle passed
 * as argument to this function must be initialized before this function
 * is called.
 *
 * @param cpu the CPU device handle
 * @param hartid The CPU hart to read
 * @return 0 upon success
 */
__inline__ uint32_t metal_cpu_get_msip(metal_cpu_Type *cpu, uint32_t hartid) {
    return cpu->vtable->get_msip(cpu, hartid);
}

/*!
 * @brief Get the interrupt controller for the CPU
 *
 * Get the CPU interrupt controller. The controller returned by this
 * function must be initialized before any interrupts are registered
 * or enabled and before any exception handlers are registered with
 * this CPU.
 *
 * @param cpu The CPU device handle
 * @return The handle for the CPU interrupt controller
 */
__inline__ metal_interrupt_Type *
metal_cpu_interrupt_controller(metal_cpu_Type *cpu) {
    return cpu->vtable->controller_interrupt(cpu);
}

/*!
 * @brief Register an exception handler
 *
 * Register an exception handler for the CPU. The CPU interrupt controller must
 * be initialized before this function is called.
 *
 * @param cpu The CPU device handle
 * @param ecode The exception code to register a handler for
 * @param handler Callback function for the exception handler
 * @return 0 upon success
 */
__inline__ int32_t metal_cpu_exception_register(metal_cpu_Type *cpu, uint32_t ecode,
                                            metal_exception_handler_t handler) {
    return cpu->vtable->exception_register(cpu, ecode, handler);
}

/*!
 * @brief Get the length of an instruction in bytes
 *
 * Get the length of an instruction in bytes.
 *
 * On RISC-V platforms, this is useful for detecting whether an instruction is
 * compressed (2 bytes long) or uncompressed (4 bytes long).
 *
 * This function is useful in conjuction with `metal_cpu_get_exception_pc()`
 * and `metal_cpu_set_exception_pc()` in order to cause the exception handler to
 * return execution after the faulting instruction.
 *
 * @param cpu The CPU device handle
 * @param epc The address of the instruction to measure
 * @return the length of the instruction in bytes
 */
__inline__ uint32_t metal_cpu_get_instruction_length(metal_cpu_Type *cpu,
                                                uintptr_t epc) {
    return cpu->vtable->get_ilen(cpu, epc);
}

/*!
 * @brief Get the program counter of the current exception.
 *
 * This function must be called within an exception handler. The behavior is
 * undefined outside of an exception handler.
 *
 * @param cpu The CPU device handle
 * @return The value of the program counter at the time of the exception
 */
__inline__ uintptr_t metal_cpu_get_exception_pc(metal_cpu_Type *cpu) {
    return cpu->vtable->get_epc(cpu);
}

/*!
 * @brief Set the exception program counter
 *
 * This function must be called within an exception handler. The behavior
 * is undefined outside of an exception handler.
 *
 * This function can be used to cause an exception handler to return execution
 * to an address other than the one that caused the exception.
 *
 * @param cpu the CPU device handle
 * @param epc The address to set the exception program counter to
 * @return 0 upon success
 */
__inline__ uint32_t metal_cpu_set_exception_pc(metal_cpu_Type *cpu,
                                          uintptr_t epc) {
    return cpu->vtable->set_epc(cpu, epc);
}

/*!
 * @brief Get the handle for the hart's bus error unit
 *
 * @param cpu The CPU device handle
 * @return A pointer to the bus error unit handle
 */
__inline__ metal_buserror_Type *
metal_cpu_get_buserror(metal_cpu_Type *cpu) {
    return cpu->vtable->get_buserror(cpu);
}

#endif
