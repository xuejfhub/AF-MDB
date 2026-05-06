/*
 * Dev_Inf.c
 *
 */
#include "Dev_Inf.h"
#include "quadspi.h"

/* This structure contains information used by ST-LINK Utility to program and erase the device */
#if defined (__ICCARM__)
__root struct StorageInfo const StorageInfo  =  {
#else
struct StorageInfo const StorageInfo = {
#endif
		"W25Q64JV_STM32H750VB", 	 	     // Device Name + version number
		SPI_FLASH,                  		 // Device Type
		0x90000000,                			 // Device Start Address
		MEMORY_FLASH_SIZE,                 	 // Device Size in Bytes
		MEMORY_PAGE_SIZE,                    // Programming Page Size
		0xFF,                                // Initial Content of Erased Memory

		{
				{
						(MEMORY_FLASH_SIZE / MEMORY_BLOCK_SIZE),  	// Sector Numbers,
						MEMORY_BLOCK_SIZE,				// Sector Size in Bytes
				},
				{
						0x00000000,
						0x00000000,
				},
		}
};
