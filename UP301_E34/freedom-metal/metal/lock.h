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
 * @file lock.h
 * @brief API for creating and using a software lock/mutex
 */
#ifndef METAL__LOCK_H
#define METAL__LOCK_H
#include "metal.h"
#include "metal/compiler.h"
#include "metal/memory.h"

/* TODO: How can we make the exception code platform-independant? */
#define _METAL_STORE_AMO_ACCESS_FAULT 7

#define METAL_LOCK_BACKOFF_CYCLES 32
#define METAL_LOCK_BACKOFF_EXPONENT 2

/*!
 * @def METAL_LOCK_DECLARE
 * @brief Declare a lock
 *
 * Locks must be declared with METAL_LOCK_DECLARE to ensure that the lock
 * is linked into a memory region which supports atomic memory operations.
 */
#define METAL_LOCK_DECLARE(name)                                               \
    __attribute__((section(".data.locks"))) struct metal_lock name

/*!
 * @brief A handle for a lock
 */
struct metal_lock {
    int _state;
};

/*!
 * @brief Initialize a lock
 * @param lock The handle for a lock
 * @return 0 if the lock is successfully initialized. A non-zero code indicates
 * failure.
 *
 * If the lock cannot be initialized, attempts to take or give the lock
 * will result in a Store/AMO access fault.
 */
__inline__ int metal_lock_init(struct metal_lock *lock) {
#ifdef __riscv_atomic
    /* Get a handle for the memory which holds the lock state */
    struct metal_memory *lock_mem =
        metal_get_memory_from_address((uintptr_t) & (lock->_state));
    if (!lock_mem) {
        return 1;
    }

    /* If the memory doesn't support atomics, report an error */
    if (!metal_memory_supports_atomics(lock_mem)) {
        return 2;
    }

    lock->_state = 0;

    return 0;
#else
    return 3;
#endif
}

/*!
 * @brief Take a lock
 * @param lock The handle for a lock
 * @return 0 if the lock is successfully taken
 *
 * If the lock initialization failed, attempts to take a lock will result in
 * a Store/AMO access fault.
 */
__inline__ int metal_lock_take(struct metal_lock *lock) {
#ifdef __riscv_atomic
    int old = 1;
    int new = 1;

    int backoff = 1;
    const int max_backoff = METAL_LOCK_BACKOFF_CYCLES * METAL_MAX_CORES;

    while (1) {
        __asm__ volatile("amoswap.w.aq %[old], %[new], (%[state])"
                         : [old] "=r"(old)
                         : [new] "r"(new), [state] "r"(&(lock->_state))
                         : "memory");

        if (old == 0) {
            break;
        }

        for (int i = 0; i < backoff; i++) {
            __asm__ volatile("");
        }

        if (backoff < max_backoff) {
            backoff *= METAL_LOCK_BACKOFF_EXPONENT;
        }
    }

    return 0;
#else
    /* Store the memory address in mtval like a normal store/amo access fault */
    __asm__("csrw mtval, %[state]" ::[state] "r"(&(lock->_state)));

    /* Trigger a Store/AMO access fault */
    _metal_trap(_METAL_STORE_AMO_ACCESS_FAULT);

    /* If execution returns, indicate failure */
    return 1;
#endif
}

/*!
 * @brief Give back a held lock
 * @param lock The handle for a lock
 * @return 0 if the lock is successfully given
 *
 * If the lock initialization failed, attempts to give a lock will result in
 * a Store/AMO access fault.
 */
__inline__ int metal_lock_give(struct metal_lock *lock) {
#ifdef __riscv_atomic
    __asm__ volatile(
        "amoswap.w.rl x0, x0, (%[state])" ::[state] "r"(&(lock->_state))
        : "memory");

    return 0;
#else
    /* Store the memory address in mtval like a normal store/amo access fault */
    __asm__("csrw mtval, %[state]" ::[state] "r"(&(lock->_state)));

    /* Trigger a Store/AMO access fault */
    _metal_trap(_METAL_STORE_AMO_ACCESS_FAULT);

    /* If execution returns, indicate failure */
    return 1;
#endif
}

#endif /* METAL__LOCK_H */
