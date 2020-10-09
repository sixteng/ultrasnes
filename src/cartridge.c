#include <stdio.h>
#include <stdlib.h>
#include "cartridge.h"

cartridge * load_cartridge(char * filename) {
    FILE *fp;
    fp = fopen(filename, "r");

    if(!fp) {
        printf("Error: Could not load the file.\n");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    rewind(fp);

    uint8_t *cartridgebuffer = (unsigned char*) malloc(sizeof(uint8_t) * file_size );
    size_t read_size = fread(cartridgebuffer, sizeof(uint8_t), file_size, fp);

    printf("%zu\n", read_size % 1024);

    fclose(fp);

    cartridge * c = malloc(sizeof(cartridge));
    c->banks = (bank*) cartridgebuffer;
    c->header = (header*) cartridgebuffer;

    return c;
}