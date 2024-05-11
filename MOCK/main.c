#include "Read_boot_sector.h"
#include "Read_Display_Data.h"
#include <stdio.h>
#include <stdint.h>

int main() {
    Open_File("C://Users//Nitro Tiger//Downloads//floppy.img");
    uint8_t choice;
    Read_boot_block();
    Read_Display_Root_Directory();
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);
        Function_In(choice);
    } while (!isValidChoice);

    return 0;
}

