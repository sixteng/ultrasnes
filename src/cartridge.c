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

size_t get_cartridge_header_offset(uint8_t * data) {
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

cartridge * load_cartridge(char * filename) {
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

    // Check for cartridge header and ignore it
    cartridgebuffer = cartridgebuffer + cartridge_smc_header_size(read_size);

    // Mapp data to cartridge
    c->banks = (cartridge_bank*) cartridgebuffer;
    c->header = (cartridge_header*) (cartridgebuffer + get_cartridge_header_offset(cartridgebuffer));

    return c;
}

void unload_cartridge(cartridge * cart) {
    // TODO: Free memory
    
    // free(cart->banks);
}