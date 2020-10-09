#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint16_t COP;
    uint16_t BRK;
    uint16_t ABORT;
    uint16_t NMI;
    uint16_t IRQ;
} header_interupts;

// 000101C0 = 65984
// https://en.wikibooks.org/wiki/Super_NES_Programming/SNES_memory_map
// https://problemkaputt.de/fullsnes.htm#snescartridgeromheader

// TODO: Handle different cartridge types, dynamic allication or structs ?

typedef struct {
    uint8_t data[0xffff + 0x200 - 0x3f];
    char title[21];
    uint8_t make;
    uint8_t type;
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t rest[4];
} header;

typedef struct {
    uint8_t data[0xffff + 0x200]; // 64kb of data
} bank;

typedef struct {
    header *header; // First bank contains the header
    bank *banks; // The banks of the cartridge
} cartridge;

cartridge * load_cartridge(char * filename);