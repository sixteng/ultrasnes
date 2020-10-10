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

/* Mappings
    LoROM - 0x00007FC0 - Final Fantasy 2
    HiROM - 0x0000FFC0 - Super Mario Cart / Final Fantasy 3
    SA-1 ROM - 0x00007FC0 - Super Mario RPG
    LoROM + FastROM - 0x000081C0 - Ultima VII
    HiROM + FastROM - ??????
    ExLoROM - 0x00007FC0 - Super Mario RPG
    ExHiROM - ????? - Tales of Phantasia

*/

typedef enum {
    LOROM = 0,
    HIROM = 0xFFC0,
} cartridge_type;

typedef struct {
    uint8_t unused:3;
    uint8_t speed:1;
    uint8_t mode: 4;
} cartridge_makeup;

typedef struct {
    char title[21];
    cartridge_makeup make;
    uint8_t type;
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t rest[4];
} cartridge_header;

typedef struct {
    uint8_t data[0xffff]; // 64kb of data
} cartridge_bank;

typedef struct {
    cartridge_header *header; // First bank contains the header
    cartridge_bank *banks; // The banks of the cartridge
} cartridge;

cartridge * load_cartridge(char * filename);
void unload_cartridge(cartridge *);
