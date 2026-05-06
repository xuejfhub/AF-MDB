#ifndef INC_LOADER_SRC_H
#define INC_LOADER_SRC_H

#ifdef __ICCARM__                 //IAR
#define KeepInCompilation __root
#elif __CC_ARM                    //MDK-ARM
#define KeepInCompilation __attribute__((used))
#else // TASKING                  //TrueStudio
#define KeepInCompilation __attribute__((used))
#endif

int Init(uint8_t MemMappedMode);
KeepInCompilation int Write (uint32_t Address, uint32_t Size, uint8_t* buffer);
KeepInCompilation int SectorErase (uint32_t EraseStartAddress ,uint32_t EraseEndAddress);
int MassErase (void);
int Read (uint32_t Address, uint32_t Size, uint8_t* Buffer);
KeepInCompilation uint64_t Verify (uint32_t MemoryAddr, uint32_t RAMBufferAddr, uint32_t Size, uint32_t missalignement);

#endif // INC_LOADER_SRC_H
