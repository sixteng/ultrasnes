#include <stdio.h>
#include "cartridge.h"

int main() {
    cartridge * cart = load_cartridge("roms/Super Mario Kart.smc");

    if (cart == NULL) {
        printf("File missing\n");
        return 0;
    }

    printf("%.21s\n", cart->header->title);
    printf("%i\n", cart->header->make.mode);

    unload_cartridge(cart);

    return 0;
}