#include <stdio.h>
#include "cartridge.h"

int main() {
    cartridge * cart = load_cartridge("roms/Super Mario Kart.smc");

    printf("%s", cart->header->title);

    return 0;
}