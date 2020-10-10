#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cartridge.h"

bool is_all_ascii(char *b, int size) {
	for (int i = 0; i < size; i++) {
		if (b[i] < 32 || b[i] > 126)
			return false;
	}

	return true;
}

size_t cartridge_smc_header_size(size_t size) {
    return size % 1024;
}

size_t cartridge_get_header_offset(uint8_t * data) {
    // We will test for clear and good ASCII title at different locations
    // TODO: Make a better check

    cartridge_header * header = (cartridge_header*) (data + 0x00007FC0);
    if (is_all_ascii(header->title, 21)) {
        return 0x7FC0;
    }

    header = (cartridge_header*) (data + 0x0000FFC0);

    if (is_all_ascii(header->title, 21)) {
        return 0xFFC0;
    }

    return 0x7FC0;
}

cartridge_bank * cartridge_get_bank(cartridge * cart, uint8_t bank) {
    return (cartridge_bank*) cart->rom + (0xffff * bank);
}

cartridge_bank * cartridge_get_current_bank(cartridge * cart) {
    return cartridge_get_bank(cart, cart->bank_index);
}

cartridge * cartridge_load(char * filename) {
    // Open file
    FILE *fp;
    fp = fopen(filename, "r");

    // Make sure file exists
    if(!fp) {
        printf("Error: Could not load the file.\n");
        return NULL;
    }

    // Attempt to get file size
    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    rewind(fp);

    // Allocate memory buffer for file and read content
    uint8_t *cartridgebuffer = (unsigned char*) malloc(sizeof(uint8_t) * file_size );
    size_t read_size = fread(cartridgebuffer, sizeof(uint8_t), file_size, fp);

    // Close file pointer
    fclose(fp);

    // Create a new cartridge
    cartridge * c = malloc(sizeof(cartridge));

    c->raw = cartridgebuffer;
    c->size = read_size;
    

    // Check for cartridge header and ignore it
    cartridgebuffer = cartridgebuffer + cartridge_smc_header_size(read_size);

    // Meta data
    c->header_offset = cartridge_get_header_offset(cartridgebuffer);

    // Mapp data to cartridge
    c->rom = cartridgebuffer;
    c->header = (cartridge_header*) (cartridgebuffer + c->header_offset);

    return c;
}

void cartridge_unload(cartridge * cart) {
    free(cart->raw);
}