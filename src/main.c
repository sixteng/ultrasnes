#include <stdio.h>
#include "cartridge.h"

int main() {
    cartridge * cart = cartridge_load("roms/Ultima VII - The Black Gate.smc");

    if (cart == NULL) {
        printf("File missing\n");
        return 0;
    }

    printf("%.21s\n", cart->header->title);
    printf("%i\n", cart->header->make.mode);

    cartridge_unload(cart);

    return 0;
}