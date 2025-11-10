/*
 * Copyright (c) 2018 Open Source Foundries Limited
 * Copyright (c) 2019 Arm Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __FLASH_MAP_BACKEND_H__
#define __FLASH_MAP_BACKEND_H__

#include <inttypes.h>

#include "metal/upt_sysctrl.h"

/* 
 * Remap generic flash_area symbols to unique prefixed names.
 * This avoids multiple-definition and linking conflicts when 
 * integrating with other libraries (e.g., Zephyr).
 * 
 * Example:
 *   flash_area_open(...) -> upt_flash_area_open(...)
 */
#define flash_area_open                     upt_flash_area_open
#define flash_area_close                    upt_flash_area_close
#define flash_area_read                     upt_flash_area_read
#define flash_area_write                    upt_flash_area_write
#define flash_area_erase                    upt_flash_area_erase
#define flash_area_align                    upt_flash_area_align
#define flash_area_erased_val               upt_flash_area_erased_val
#define flash_area_get_sectors              upt_flash_area_get_sectors
#define flash_area_get_sector               upt_flash_area_get_sector
#define flash_area_id_from_multi_image_slot upt_flash_area_id_from_multi_image_slot
#define flash_area_id_from_image_slot       upt_flash_area_id_from_image_slot
#define flash_area_id_to_multi_image_slot   upt_flash_area_id_to_multi_image_slot

struct flash_area {
  uint8_t  fa_id;         /** The slot/scratch identification */
  uint8_t  fa_device_id;  /** The device id (usually there's only one) */
  uint16_t pad16;
  uint32_t fa_off;        /** The flash offset from the beginning */
  uint32_t fa_size;       /** The size of this sector */
};

//! Structure describing a sector within a flash area.
struct flash_sector {
  //! Offset of this sector, from the start of its flash area (not device).
  uint32_t fs_off;

  //! Size of this sector, in bytes.
  uint32_t fs_size;
};

static inline uint32_t flash_area_get_off(const struct flash_area *fa)
{
	return (uint32_t)fa->fa_off;
}

static inline uint32_t flash_area_get_size(const struct flash_area *fa)
{
	return (uint32_t)fa->fa_size;
}

static inline uint8_t flash_area_get_id(const struct flash_area *fa)
{
	return fa->fa_id;
}

static inline uint8_t flash_area_get_device_id(const struct flash_area *fa)
{
	return fa->fa_device_id;
}

static inline uint32_t flash_sector_get_off(const struct flash_sector *fs)
{
	return fs->fs_off;
}

static inline uint32_t flash_sector_get_size(const struct flash_sector *fs)
{
	return fs->fs_size;
}

//! Opens the area for use. id is one of the `fa_id`s */
int flash_area_open(uint8_t id, const struct flash_area **area_outp);
void flash_area_close(const struct flash_area *fa);

//! Reads `len` bytes of flash memory at `off` to the buffer at `dst`
int flash_area_read(const struct flash_area *fa, uint32_t off,
                    void *dst, uint32_t len);
//! Writes `len` bytes of flash memory at `off` from the buffer at `src`
SRAM_ATTR int flash_area_write(const struct flash_area *fa, uint32_t off,
                     const void *src, uint32_t len);
//! Erases `len` bytes of flash memory at `off`
int flash_area_erase(const struct flash_area *fa,
                     uint32_t off, uint32_t len);

//! Returns this `flash_area`s alignment
size_t flash_area_align(const struct flash_area *area);
//! Returns the value read from an erased flash area byte
uint8_t flash_area_erased_val(const struct flash_area *area);

//! Given flash area ID, return info about sectors within the area
int flash_area_get_sectors(int fa_id, uint32_t *count, struct flash_sector *sectors);

int flash_area_get_sector(const struct flash_area *fa, uint32_t off, struct flash_sector *sector);

//! Returns the `fa_id` for slot, where slot is 0 (primary) or 1 (secondary).
//!
//! `image_index` (0 or 1) is the index of the image. Image index is
//!  relevant only when multi-image support support is enabled
int flash_area_id_from_multi_image_slot(int image_index, int slot);
int flash_area_id_from_image_slot(int slot);

//! Returns the slot (0 for primary or 1 for secondary), for the supplied
//! `image_index` and `area_id`. `area_id` is unique and is represented by
//! `fa_id` in the `flash_area` struct.
int flash_area_id_to_multi_image_slot(int image_index, int area_id);

#endif /* __FLASH_MAP_BACKEND_H__ */
