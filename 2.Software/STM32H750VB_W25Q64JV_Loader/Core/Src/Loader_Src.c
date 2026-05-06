#include "main.h"
#include "gpio.h"
#include "quadspi.h"
#include "w25q64jv.h"
#include "Loader_Src.h"
#include "Dev_Inf.h"
#include "usart.h"

#define LOADER_OK	0x1
#define LOADER_FAIL	0x0

int Init(uint8_t configureMemoryMappedMode) {
  uint8_t w25q64jv_device_id[2];
  uint8_t w25q64jv_id_number[12];

  SystemInit();
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_QUADSPI_Init();

  QSPI_W25Q64JV_Reset();
  MX_USART1_UART_Init();
  QSPI_W25Q64JV_DeviceID(w25q64jv_device_id);
  QSPI_W25Q64JV_IDNumber(w25q64jv_id_number);

  return LOADER_OK;
}

int Read (uint32_t Address, uint32_t Size, uint8_t* buffer) {

	QSPI_W25Q64JV_EnableMemoryMappedMode();
	for (int i=0;i<Size;i++){
		*(uint8_t*)buffer++ = *(uint8_t*)Address++;
	}
    return LOADER_OK;
}

int Write(uint32_t Address, uint32_t Size, uint8_t* buffer) {

	QSPI_W25Q64JV_Write((uint8_t*) buffer, (Address & (0x0fffffff)),Size);

	return LOADER_OK;
}

int SectorErase(uint32_t EraseStartAddress, uint32_t EraseEndAddress) {
	uint32_t BlockAddr;

	EraseStartAddress &= 0x0fffffff;
	EraseEndAddress &= 0x0fffffff;

	BlockAddr = EraseStartAddress -  EraseStartAddress % MEMORY_BLOCK_SIZE;

    while (BlockAddr <= EraseEndAddress)
    {
        QSPI_W25Q64JV_EraseSector( BlockAddr);
        BlockAddr += MEMORY_BLOCK_SIZE;
    }

	return LOADER_OK;
}

int MassErase(void) {
	uint32_t BlockAddr = 0;

    while (BlockAddr <= MEMORY_FLASH_SIZE-1)
    {
        QSPI_W25Q64JV_EraseSector( BlockAddr);
        BlockAddr += MEMORY_BLOCK_SIZE;
    }

	return LOADER_OK;
}

uint32_t CheckSum(uint32_t StartAddress, uint32_t Size, uint32_t InitVal) {
	uint8_t missalignementAddress = StartAddress % 4;
	uint8_t missalignementSize = Size;
	int cnt;
	uint32_t Val;

	StartAddress -= StartAddress % 4;
	Size += (Size % 4 == 0) ? 0 : 4 - (Size % 4);

	for (cnt = 0; cnt < Size; cnt += 4) {
		Val = *(uint32_t*) StartAddress;
		if (missalignementAddress) {
			switch (missalignementAddress) {
			case 1:
				InitVal += (uint8_t) (Val >> 8 & 0xff);
				InitVal += (uint8_t) (Val >> 16 & 0xff);
				InitVal += (uint8_t) (Val >> 24 & 0xff);
				missalignementAddress -= 1;
				break;
			case 2:
				InitVal += (uint8_t) (Val >> 16 & 0xff);
				InitVal += (uint8_t) (Val >> 24 & 0xff);
				missalignementAddress -= 2;
				break;
			case 3:
				InitVal += (uint8_t) (Val >> 24 & 0xff);
				missalignementAddress -= 3;
				break;
			}
		} else if ((Size - missalignementSize) % 4 && (Size - cnt) <= 4) {
			switch (Size - missalignementSize) {
			case 1:
				InitVal += (uint8_t) Val;
				InitVal += (uint8_t) (Val >> 8 & 0xff);
				InitVal += (uint8_t) (Val >> 16 & 0xff);
				missalignementSize -= 1;
				break;
			case 2:
				InitVal += (uint8_t) Val;
				InitVal += (uint8_t) (Val >> 8 & 0xff);
				missalignementSize -= 2;
				break;
			case 3:
				InitVal += (uint8_t) Val;
				missalignementSize -= 3;
				break;
			}
		} else {
			InitVal += (uint8_t) Val;
			InitVal += (uint8_t) (Val >> 8 & 0xff);
			InitVal += (uint8_t) (Val >> 16 & 0xff);
			InitVal += (uint8_t) (Val >> 24 & 0xff);
		}
		StartAddress += 4;
	}

	return (InitVal);
}

uint64_t Verify (uint32_t MemoryAddr, uint32_t RAMBufferAddr, uint32_t Size, uint32_t missalignement)
{
	uint32_t VerifiedData = 0, InitVal = 0;
	uint64_t checksum;
	Size*=4;

	QSPI_W25Q64JV_EnableMemoryMappedMode();

	checksum = CheckSum((uint32_t)MemoryAddr + (missalignement & 0xF), Size - ((missalignement >> 16) & 0xF), InitVal);
	while (Size>VerifiedData)
	{
		if ( *(uint8_t*)MemoryAddr++ != *((uint8_t*)RAMBufferAddr + VerifiedData))
			return ((checksum<<32) + (MemoryAddr + VerifiedData));

		VerifiedData++;
	}

	return (checksum<<32);
}
