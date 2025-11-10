// mcu_port.c

#include <string.h>
#include <stdlib.h>

#include "flash_map_backend/flash_map_backend.h"
#include "flash_map_backend/internal_flash.h"
#include "mcuboot_config/mcuboot_config.h"
#include "mcuboot_config/mcuboot_logging.h"
#include "sysflash/sysflash.h"

#if defined(MCUBOOT_2M_LAYOUT)
	/* Expected Flash target layout: 2 MB*/
	/*+---------------------------------------------------------------------+*
	*+ Slot					Flash Area Id	Start		End			Size  	+*
	*+----------------------------------------------------------------------+*
	*+ Bootloader			0				0x1000		0x41000		256kB 	+*
	*+----------------------------------------------------------------------+*
	*+ App Primary Slot		1				0x41000		0xC1000		512kB 	+*
	*+----------------------------------------------------------------------+*
	*+ App Upgrade Slot		2				0xC1000		0x141000	512kB 	+*
	*+----------------------------------------------------------------------+*
	*+ Scratch (if exists)	3				0x141000	0x142000	4kB	  	+*
	*+----------------------------------------------------------------------+*
	*+ Data Storage			N/A				0x142000	0x200000	~756 KB +*
	*+----------------------------------------------------------------------+*/
	#define FLASH_BASE_MM				0x60000000UL
	#define BOOTLOADER_START_ADDRESS	(FLASH_BASE_MM + 0x1000)
	#define BOOTLOADER_SIZE 			(256 * 1024)
	#define APPLICATION_SIZE 			(512 * 1024)
	#define FLASH_SECTOR_SIZE 			(4 * 1024)
#elif defined(MCUBOOT_8M_LAYOUT)
	/* Expected Flash target layout: 8 MB*/
	/*+---------------------------------------------------------------------+*
	*+ Slot					Flash Area Id	Start		End			Size  	+*
	*+----------------------------------------------------------------------+*
	*+ Bootloader			0				0x1000		0x41000		256kB 	+*
	*+----------------------------------------------------------------------+*
	*+ App Primary Slot		1				0x41000		0x141000	1MB   	+*
	*+----------------------------------------------------------------------+*
	*+ App Upgrade Slot		2				0x141000	0x241000	1MB	 	+*
	*+----------------------------------------------------------------------+*
	*+ Scratch (if exists)	3				0x241000	0x242000	4kB		+*
	*+----------------------------------------------------------------------+*
	*+ Data Storage			N/A				0x242000	0x800000	~5.75MB	+*
	*+----------------------------------------------------------------------+*/
	#define FLASH_BASE_MM				0x60000000UL
	#define BOOTLOADER_START_ADDRESS 	(FLASH_BASE_MM + 0x1000)
	#define BOOTLOADER_SIZE 			(256 * 1024)
	#define APPLICATION_SIZE 			(1024 * 1024)
	#define FLASH_SECTOR_SIZE 			(4 * 1024)
#else
	#error "Please exactly define MCUBOOT_2M_LAYOUT or MCUBOOT_8M_LAYOUT"
#endif

#define APPLICATION_PRIMARY_START_ADDRESS 	(BOOTLOADER_START_ADDRESS + BOOTLOADER_SIZE)
#define APPLICATION_SECONDARY_START_ADDRESS (APPLICATION_PRIMARY_START_ADDRESS + APPLICATION_SIZE)
#if defined(MCUBOOT_SWAP_USING_SCRATCH)
#define SCRATCH_START_ADDRESS (APPLICATION_SECONDARY_START_ADDRESS + APPLICATION_SIZE)
#endif

#define VALIDATE_PROGRAM_OP 1

static const struct flash_area bootloader = {
  .fa_id = FLASH_AREA_BOOTLOADER,
  .fa_device_id = FLASH_DEVICE_INTERNAL_FLASH,
  .fa_off = BOOTLOADER_START_ADDRESS,
  .fa_size = BOOTLOADER_SIZE,
};

static const struct flash_area primary_img0 = {
  .fa_id = FLASH_AREA_IMAGE_PRIMARY(0),
  .fa_device_id = FLASH_DEVICE_INTERNAL_FLASH,
  .fa_off = APPLICATION_PRIMARY_START_ADDRESS,
  .fa_size = APPLICATION_SIZE,
};

static const struct flash_area secondary_img0 = {
  .fa_id = FLASH_AREA_IMAGE_SECONDARY(0),
  .fa_device_id = FLASH_DEVICE_INTERNAL_FLASH,
  .fa_off = APPLICATION_SECONDARY_START_ADDRESS,
  .fa_size = APPLICATION_SIZE,
};

#if defined(MCUBOOT_SWAP_USING_SCRATCH)
static const struct flash_area scratch = {
  .fa_id = FLASH_AREA_IMAGE_SCRATCH,
  .fa_device_id = FLASH_DEVICE_INTERNAL_FLASH,
  .fa_off = SCRATCH_START_ADDRESS,
  .fa_size = FLASH_SECTOR_SIZE,
};
#endif

static const struct flash_area *s_flash_areas[] = {
  &bootloader,
  &primary_img0,
  &secondary_img0,
#if defined(MCUBOOT_SWAP_USING_SCRATCH)
  &scratch,
#endif
};

#define ARRAY_SIZE(arr) sizeof(arr)/sizeof(arr[0])

static const struct flash_area *prv_lookup_flash_area(uint8_t id) {
  for (size_t i = 0; i < ARRAY_SIZE(s_flash_areas); i++) {
    const struct flash_area *area = s_flash_areas[i];
    if (id == area->fa_id) {
      return area;
    }
  }
  return NULL;
}

int flash_area_open(uint8_t id, const struct flash_area **area_outp) {
	MCUBOOT_LOG_DBG("%s: ID=%d\n", __func__, (int)id);

	const struct flash_area *area = prv_lookup_flash_area(id);
	*area_outp = area;
	return area != NULL ? 0 : -1;
}

void flash_area_close(const struct flash_area *area) {
	// no cleanup to do for this flash part
}

SRAM_ATTR static void internal_flash_read(void * dest_addr, const size_t src, size_t size) {
#ifdef BOOTLOADER
	// Direct mode.
	memcpy(dest_addr, (const void*)src, size);
#else
	// Indirect mode.
	fospi_read(dest_addr, src, size);
#endif
}

int flash_area_read(const struct flash_area *fa, uint32_t off, void *dst,
                    uint32_t len) {
	if (fa->fa_device_id != FLASH_DEVICE_INTERNAL_FLASH) {
		return -1;
	}

	const uint32_t end_offset = off + len;
	if (end_offset > fa->fa_size) {
		MCUBOOT_LOG_ERR("%s: Out of Bounds (0x%x vs 0x%x)\n", __func__, (int)end_offset, (int)fa->fa_size);
		return -1;
	}
	
	const uint32_t addr = fa->fa_off + off;
	// MCUBOOT_LOG_DBG("%s: Addr: 0x%08x Length: %d\n", __func__, (int)addr, (int)len);
	internal_flash_read(dst, addr, len);

	return 0;
}

SRAM_ATTR static void internal_flash_write(size_t dest_addr, const void *src, size_t size) {
	fospi_write((dest_addr - FLASH_BASE_MM), src, size);
}

int flash_area_write(const struct flash_area *fa, uint32_t off, const void *src,
                     uint32_t len) {
	  if (fa->fa_device_id != FLASH_DEVICE_INTERNAL_FLASH) {
	    return -1;
	  }

	  const uint32_t end_offset = off + len;
	  if (end_offset > fa->fa_size) {
	    MCUBOOT_LOG_ERR("%s: Out of Bounds (0x%x vs 0x%x)\n", __func__, (int)end_offset, (int)fa->fa_size);
	    return -1;
	  }

	  const uint32_t addr = fa->fa_off + off;
	//   MCUBOOT_LOG_DBG("%s: Addr: 0x%08x Length: %d\n", __func__, (int)addr, (int)len);
	  internal_flash_write(addr, src, len);

#if VALIDATE_PROGRAM_OP
	  if (memcmp((void *)addr, src, len) != 0) {
	    MCUBOOT_LOG_ERR("%s: Program Failed\n", __func__);
	  }
#endif
	  return 0;
}

static void internal_flash_erase_range(size_t start_addr) {
	fospi_4kerase((start_addr - FLASH_BASE_MM));
}

int flash_area_erase(const struct flash_area *fa, uint32_t off, uint32_t len) {
	if (fa->fa_device_id != FLASH_DEVICE_INTERNAL_FLASH) {
		return -1;
	}

	if ((len % FLASH_SECTOR_SIZE) != 0 || (off % FLASH_SECTOR_SIZE) != 0) {
		MCUBOOT_LOG_ERR("%s: Not aligned on sector Offset: 0x%x Length: 0x%x\n", __func__, (int)off, (int)len);
		return -1;
	}

	const uint32_t start_addr = fa->fa_off + off;
	// MCUBOOT_LOG_DBG("%s: Addr: 0x%08x Length: %d\n", __func__, (int)start_addr, (int)len);

	for (size_t i = 0; i < len; i+= FLASH_SECTOR_SIZE) {
		const uint32_t addr = start_addr + i;
		internal_flash_erase_range(addr);
	}

#if VALIDATE_PROGRAM_OP
	for (size_t i = 0; i < len; i++) {
		uint8_t *val = (void *)(start_addr + i);
		if (*val != 0xff) {
			MCUBOOT_LOG_ERR("%s: Erase at 0x%x failed, value = 0x%02x)\n", __func__, (int)val, *val);
		}
	}
#endif
	return 0;
}

size_t flash_area_align(const struct flash_area *area) {
  // the smallest unit a flash write can occur along.
  // Note: Image trailers will be scaled by this size
	return 1;
}

uint8_t flash_area_erased_val(const struct flash_area *area) {
	// the value a byte reads when erased on storage.
	return 0xff;
}

int flash_area_get_sectors(int fa_id, uint32_t *count,
                           struct flash_sector *sectors) {
	const struct flash_area *fa = prv_lookup_flash_area(fa_id);
	if (fa->fa_device_id != FLASH_DEVICE_INTERNAL_FLASH) {
		return -1;
	}

	// All sectors for the NRF52 are the same size
	const size_t sector_size = FLASH_SECTOR_SIZE;
	uint32_t total_count = 0;
	for (size_t off = 0; off < fa->fa_size; off += sector_size) {
		// Note: Offset here is relative to flash area, not device
		sectors[total_count].fs_off = off;
		sectors[total_count].fs_size = sector_size;
		total_count++;
	}

	*count = total_count;
	return 0;
}

int flash_area_get_sector(const struct flash_area *fa, uint32_t off,
                          struct flash_sector *sector) {
    const size_t sector_size = FLASH_SECTOR_SIZE;

    // Check for null pointers
    if (fa == NULL || sector == NULL) {
        return -1;
    }

    // Check if the offset is within the flash area range
    if (off >= fa->fa_size) {
        return -1;
    }

    // Fill the sector structure
    sector->fs_off = (off / sector_size) * sector_size;
    sector->fs_size = sector_size;

    return 0;
}

int flash_area_id_from_multi_image_slot(int image_index, int slot) {
	switch (slot) {
	case 0:
		return FLASH_AREA_IMAGE_PRIMARY(image_index);
	case 1:
		return FLASH_AREA_IMAGE_SECONDARY(image_index);
#if defined(MCUBOOT_SWAP_USING_SCRATCH)
	case 2:
		return FLASH_AREA_IMAGE_SCRATCH;
#endif
    }
	MCUBOOT_LOG_ERR("Unexpected Request: image_index=%d, slot=%d\n", image_index, slot);
	return -1; /* flash_area_open will fail on that */
}

int flash_area_id_from_image_slot(int slot) {
  return flash_area_id_from_multi_image_slot(0, slot);
}

int flash_area_id_to_multi_image_slot(int image_index, int area_id)
{
    if (area_id == FLASH_AREA_IMAGE_PRIMARY(image_index)) {
        return 0; // Primary slot
    } else if (area_id == FLASH_AREA_IMAGE_SECONDARY(image_index)) {
        return 1; // Secondary slot
#if defined(MCUBOOT_SWAP_USING_SCRATCH)
    } else if (area_id == FLASH_AREA_IMAGE_SCRATCH) {
        return 2; // Scratch
#endif
    }

    MCUBOOT_LOG_ERR("Unknown area_id=%d for image_index=%d\n", area_id, image_index);
    return -1; // Invalid mapping
}

void example_assert_handler(const char *file, int line) {
	MCUBOOT_LOG_DBG("ASSERT: File: %s Line: %d\n", file, line);
	//TODO: Not implement complete.
}
