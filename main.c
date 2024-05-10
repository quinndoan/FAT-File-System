#include "include/Read_boot_sector.h"
#include "include/Read_Display_Data.h"
#include "include/OpenFile_Console.h"
int main(int argc, char *argv[])
{
    if (OpenFileHandler(argc, argv) == 0)
        return 0;
    uint8_t choice;
    Read_boot_block();
    Read_Display_Root_Directory();
    do
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);
        Function_In(choice);
    } while (!isValidChoice);

    return 0;
}
