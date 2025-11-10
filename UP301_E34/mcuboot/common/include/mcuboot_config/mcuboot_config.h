/*
 * Copyright (c) 2018 Open Source Foundries Limited
 * Copyright (c) 2019-2024 Arm Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __MCUBOOT_CONFIG_H__
#define __MCUBOOT_CONFIG_H__

#include "metal/upt_init.h"

/*
 * Template configuration file for MCUboot.
 *
 * When porting MCUboot to a new target, copy it somewhere that your
 * include path can find it as mcuboot_config/mcuboot_config.h, and
 * make adjustments to suit your platform.
 *
 * For examples, see:
 *
 * boot/zephyr/include/mcuboot_config/mcuboot_config.h
 * boot/mynewt/mcuboot_config/include/mcuboot_config/mcuboot_config.h
 */

/*==================== Platform-Specific ====================*/
/*
 * Flash layout
 *
 * You must choose exactly one layout.
 */

/* Uncomment for 2MB layout support */
#define MCUBOOT_2M_LAYOUT

/* Uncomment for 8MB layout support */
// #define MCUBOOT_8M_LAYOUT

/*
 * Ram-Load settings
 */

#ifdef MCUBOOT_2M_LAYOUT
    #define CONFIG_BOOT_IMAGE_EXECUTABLE_RAM_START 0x50080000
    #define CONFIG_BOOT_IMAGE_EXECUTABLE_RAM_SIZE 0x80000
#else
    #define CONFIG_BOOT_IMAGE_EXECUTABLE_RAM_START 0x50000000
    #define CONFIG_BOOT_IMAGE_EXECUTABLE_RAM_SIZE 0x100000
#endif

/*==================== Bootloader Features ====================*/
#ifdef MP_BOOT
/*
 * Signature types
 *
 * You must choose exactly one signature type.
 */

/* Uncomment for RSA signature support */
//#define MCUBOOT_SIGN_RSA

/* Uncomment for ECDSA signatures using curve P-256. */
#define MCUBOOT_SIGN_EC256

/*
 * Public key handling
 *
 * Choose one or none from the different public key handling options.
 */

/* Uncomment to use key hash(es) instead of incorporating
 * the public key into the code. */
// #define MCUBOOT_HW_KEY

/* Uncomment to use builtin key(s) instead of incorporating
 * the public key into the code. */
// #define MCUBOOT_BUILTIN_KEY

/*
 * Upgrade mode
 *
 * The default is to support A/B image swapping with rollback.  Other modes
 * with simpler code path, which only supports overwriting the existing image
 * with the update image or running the newest image directly from its flash
 * partition, are also available.
 *
 * You can enable only one mode at a time from the list below to override
 * the default upgrade mode.
 */

/* Uncomment to enable the swap-using-scratch code path. */
#define MCUBOOT_SWAP_USING_SCRATCH

/* Uncomment to enable the overwrite-only code path. */
// #define MCUBOOT_OVERWRITE_ONLY
#ifdef MCUBOOT_OVERWRITE_ONLY
    /* Uncomment to only erase and overwrite those primary slot sectors needed
    * to install the new image, rather than the entire image slot. */
    #define MCUBOOT_OVERWRITE_ONLY_FAST
    /* Uncomment to enable the software-based downgrade prevention. */
    #define MCUBOOT_DOWNGRADE_PREVENTION
#endif

/* Uncomment to enable the direct-xip code path. */
// #define MCUBOOT_DIRECT_XIP
#ifdef MCUBOOT_DIRECT_XIP
    /* Uncomment to enable the revert mechanism in direct-xip mode. */
    // #define MCUBOOT_DIRECT_XIP_REVERT
#endif

/* Uncomment to enable the ram-load code path. */
/* Must to be defined IMAGE_EXECUTABLE_RAM_START/IMAGE_EXECUTABLE_RAM_SIZE as well. */
// #define MCUBOOT_RAM_LOAD
#ifdef MCUBOOT_RAM_LOAD
    #define IMAGE_EXECUTABLE_RAM_START CONFIG_BOOT_IMAGE_EXECUTABLE_RAM_START
    #define IMAGE_EXECUTABLE_RAM_SIZE CONFIG_BOOT_IMAGE_EXECUTABLE_RAM_SIZE
#endif

/*
 * Cryptographic settings
 *
 * You must choose between mbedTLS and Tinycrypt as source of
 * cryptographic primitives. Other cryptographic settings are also
 * available.
 */

/* Uncomment to use ARM's mbedTLS cryptographic primitives */
#define MCUBOOT_USE_MBED_TLS

/* Uncomment to use Tinycrypt's. */
// #define MCUBOOT_USE_TINYCRYPT

/*
 * Encrypted images
 *
 * Uncomment one of the below options (MCUBOOT_ENCRYPT_x) to enable
 * encrypted image upgrades.
 */

/* Uncomment to use RSA-OAEP for key encryption */
// #define MCUBOOT_ENCRYPT_RSA

/* Uncomment to use AES-KW for key encryption */
// #define MCUBOOT_ENCRYPT_KW

/* Uncomment to use ECIES-P256 for key encryption */
#define MCUBOOT_ENCRYPT_EC256

/* Uncomment to use ECIES-X25519 for key encryption */
// #define MCUBOOT_ENCRYPT_X25519

/* Uncomment to use a builtin key-encryption key (retrieved from a trusted
 * source - if implemented) instead of a key embedded in the bootloader. */
/* #define MCUBOOT_ENC_BUILTIN_KEY */

#if defined(MCUBOOT_ENCRYPT_RSA)    || \
    defined(MCUBOOT_ENCRYPT_KW)     || \
    defined(MCUBOOT_ENCRYPT_EC256)  || \
    defined(MCUBOOT_ENCRYPT_X25519)
#define MCUBOOT_ENC_IMAGES
#endif

/*
 * Always check the signature of the image in the primary slot before booting,
 * even if no upgrade was performed. This is recommended if the boot
 * time penalty is acceptable.
 */
#define MCUBOOT_VALIDATE_PRIMARY_SLOT

/*
 * Flash abstraction
 */

/* Uncomment if your flash map API supports flash_area_get_sectors().
 * See the flash APIs for more details. */
#define MCUBOOT_USE_FLASH_AREA_GET_SECTORS

/* Default maximum number of flash sectors per image slot; change
 * as desirable. */
#ifdef MCUBOOT_2M_LAYOUT
    #define MCUBOOT_MAX_IMG_SECTORS 128		// 128 * 4 KB = 512 KB
#else
    #define MCUBOOT_MAX_IMG_SECTORS 256		// 256 * 4 KB = 1024 KB
#endif

/* Default number of separately updateable images; change in case of
 * multiple images. */
/* #define MCUBOOT_IMAGE_NUMBER 1 */

/*
 * Logging
 */

/*
 * If logging is enabled the following functions must be defined by the
 * platform:
 *
 *    MCUBOOT_LOG_MODULE_REGISTER(domain)
 *      Register a new log module and add the current C file to it.
 *
 *    MCUBOOT_LOG_MODULE_DECLARE(domain)
 *      Add the current C file to an existing log module.
 *
 *    MCUBOOT_LOG_ERR(...)
 *    MCUBOOT_LOG_WRN(...)
 *    MCUBOOT_LOG_INF(...)
 *    MCUBOOT_LOG_DBG(...)
 *
 * The function priority is:
 *
 *    MCUBOOT_LOG_ERR > MCUBOOT_LOG_WRN > MCUBOOT_LOG_INF > MCUBOOT_LOG_DBG
 */
#define MCUBOOT_HAVE_LOGGING 1

/*
 * Assertions
 */

/* Uncomment if your platform has its own mcuboot_config/mcuboot_assert.h.
 * If so, it must provide an ASSERT macro for use by bootutil. Otherwise,
 * "assert" is used. */
/* #define MCUBOOT_HAVE_ASSERT_H */

/*
 * Watchdog feeding
 */

/* This macro might be implemented if the OS / HW watchdog is enabled while
 * doing a swap upgrade and the time it takes for a swapping is long enough
 * to cause an unwanted reset. If implementing this, the OS main.c must also
 * enable the watchdog (if required)!
 *
 * #define MCUBOOT_WATCHDOG_FEED()
 *    do { do watchdog feeding here! } while (0)
 */
/* Uncomment to enable the watchdog timer. */
// #define MCUBOOT_WDT_ENABLE
#ifdef MCUBOOT_WDT_ENABLE
    #define MCUBOOT_WATCHDOG_FEED() \
        do{							\
            upt_wdt_software_kick(); \
        } while(0)
#else
    #define MCUBOOT_WATCHDOG_FEED() \
        do {                   \
        } while (0)
#endif

/* If a OS ports support single thread mode or is bare-metal then:
 * This macro implements call that switches CPU to an idle state, from which
 * the CPU may be woken up by, for example, UART transmission event.
 *
 * Otherwise this macro should be no-op.
 */
#define MCUBOOT_CPU_IDLE() \
    do {                   \
    } while (0)

#else
/*
 * Signature types
 *
 * You must choose exactly one signature type.
 */

/* Uncomment for RSA signature support */
//#define MCUBOOT_SIGN_RSA

/* Uncomment for ECDSA signatures using curve P-256. */
//#define MCUBOOT_SIGN_EC256

/*
 * Public key handling
 *
 * Choose one or none from the different public key handling options.
 */

/* Uncomment to use key hash(es) instead of incorporating
 * the public key into the code. */
// #define MCUBOOT_HW_KEY

/* Uncomment to use builtin key(s) instead of incorporating
 * the public key into the code. */
// #define MCUBOOT_BUILTIN_KEY

/*
 * Upgrade mode
 *
 * The default is to support A/B image swapping with rollback.  Other modes
 * with simpler code path, which only supports overwriting the existing image
 * with the update image or running the newest image directly from its flash
 * partition, are also available.
 *
 * You can enable only one mode at a time from the list below to override
 * the default upgrade mode.
 */

/* Uncomment to enable the swap-using-scratch code path. */
// #define MCUBOOT_SWAP_USING_SCRATCH

/* Uncomment to enable the overwrite-only code path. */
#define MCUBOOT_OVERWRITE_ONLY
#ifdef MCUBOOT_OVERWRITE_ONLY
    /* Uncomment to only erase and overwrite those primary slot sectors needed
    * to install the new image, rather than the entire image slot. */
    #define MCUBOOT_OVERWRITE_ONLY_FAST
    /* Uncomment to enable the software-based downgrade prevention. */
    #define MCUBOOT_DOWNGRADE_PREVENTION
#endif

/* Uncomment to enable the direct-xip code path. */
// #define MCUBOOT_DIRECT_XIP
#ifdef MCUBOOT_DIRECT_XIP
    /* Uncomment to enable the revert mechanism in direct-xip mode. */
    // #define MCUBOOT_DIRECT_XIP_REVERT
#endif

/* Enable the ram-load code path */
/* Must to be defined IMAGE_EXECUTABLE_RAM_START/IMAGE_EXECUTABLE_RAM_SIZE as well. */
// #define MCUBOOT_RAM_LOAD
#ifdef MCUBOOT_RAM_LOAD
    #define IMAGE_EXECUTABLE_RAM_START CONFIG_BOOT_IMAGE_EXECUTABLE_RAM_START
    #define IMAGE_EXECUTABLE_RAM_SIZE CONFIG_BOOT_IMAGE_EXECUTABLE_RAM_SIZE
#endif

/*
 * Cryptographic settings
 *
 * You must choose between mbedTLS and Tinycrypt as source of
 * cryptographic primitives. Other cryptographic settings are also
 * available.
 */

/* Uncomment to use ARM's mbedTLS cryptographic primitives */
#define MCUBOOT_USE_MBED_TLS

/* Uncomment to use Tinycrypt's. */
// #define MCUBOOT_USE_TINYCRYPT

/*
 * Encrypted images
 *
 * Uncomment one of the below options (MCUBOOT_ENCRYPT_x) to enable
 * encrypted image upgrades.
 */

/* Uncomment to use RSA-OAEP for key encryption */
// #define MCUBOOT_ENCRYPT_RSA

/* Uncomment to use AES-KW for key encryption */
// #define MCUBOOT_ENCRYPT_KW

/* Uncomment to use ECIES-P256 for key encryption */
// #define MCUBOOT_ENCRYPT_EC256

/* Uncomment to use ECIES-X25519 for key encryption */
// #define MCUBOOT_ENCRYPT_X25519

/* Uncomment to use a builtin key-encryption key (retrieved from a trusted
 * source - if implemented) instead of a key embedded in the bootloader. */
/* #define MCUBOOT_ENC_BUILTIN_KEY */

#if defined(MCUBOOT_ENCRYPT_RSA)    || \
    defined(MCUBOOT_ENCRYPT_KW)     || \
    defined(MCUBOOT_ENCRYPT_EC256)  || \
    defined(MCUBOOT_ENCRYPT_X25519)
#define MCUBOOT_ENC_IMAGES
#endif

/*
 * Always check the signature of the image in the primary slot before booting,
 * even if no upgrade was performed. This is recommended if the boot
 * time penalty is acceptable.
 */
//#define MCUBOOT_VALIDATE_PRIMARY_SLOT

/*
 * Flash abstraction
 */

/* Uncomment if your flash map API supports flash_area_get_sectors().
 * See the flash APIs for more details. */
#define MCUBOOT_USE_FLASH_AREA_GET_SECTORS

/* Default maximum number of flash sectors per image slot; change
 * as desirable. */
#ifdef MCUBOOT_2M_LAYOUT
    #define MCUBOOT_MAX_IMG_SECTORS 128		// 128 * 4 KB = 512 KB
#else
    #define MCUBOOT_MAX_IMG_SECTORS 256		// 256 * 4 KB = 1024 KB
#endif

/* Default number of separately updateable images; change in case of
 * multiple images. */
/* #define MCUBOOT_IMAGE_NUMBER 1 */

/*
 * Logging
 */

/*
 * If logging is enabled the following functions must be defined by the
 * platform:
 *
 *    MCUBOOT_LOG_MODULE_REGISTER(domain)
 *      Register a new log module and add the current C file to it.
 *
 *    MCUBOOT_LOG_MODULE_DECLARE(domain)
 *      Add the current C file to an existing log module.
 *
 *    MCUBOOT_LOG_ERR(...)
 *    MCUBOOT_LOG_WRN(...)
 *    MCUBOOT_LOG_INF(...)
 *    MCUBOOT_LOG_DBG(...)
 *
 * The function priority is:
 *
 *    MCUBOOT_LOG_ERR > MCUBOOT_LOG_WRN > MCUBOOT_LOG_INF > MCUBOOT_LOG_DBG
 */
#define MCUBOOT_HAVE_LOGGING 1

/*
 * Assertions
 */

/* Uncomment if your platform has its own mcuboot_config/mcuboot_assert.h.
 * If so, it must provide an ASSERT macro for use by bootutil. Otherwise,
 * "assert" is used. */
/* #define MCUBOOT_HAVE_ASSERT_H */

/*
 * Watchdog feeding
 */

/* This macro might be implemented if the OS / HW watchdog is enabled while
 * doing a swap upgrade and the time it takes for a swapping is long enough
 * to cause an unwanted reset. If implementing this, the OS main.c must also
 * enable the watchdog (if required)!
 *
 * #define MCUBOOT_WATCHDOG_FEED()
 *    do { do watchdog feeding here! } while (0)
 */
/* Uncomment to enable the watchdog timer. */
// #define MCUBOOT_WDT_ENABLE
#ifdef MCUBOOT_WDT_ENABLE
    #define MCUBOOT_WATCHDOG_FEED() \
        do{							\
            upt_wdt_software_kick(); \
        } while(0)
#else
    #define MCUBOOT_WATCHDOG_FEED() \
        do {                   \
        } while (0)
#endif

/* If a OS ports support single thread mode or is bare-metal then:
 * This macro implements call that switches CPU to an idle state, from which
 * the CPU may be woken up by, for example, UART transmission event.
 * 
 * Otherwise this macro should be no-op.
 */
#define MCUBOOT_CPU_IDLE() \
    do {                   \
    } while (0)

#endif /* MP_BOOT */
#endif /* __MCUBOOT_CONFIG_H__ */
