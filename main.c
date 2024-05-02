#include <stdio.h>
#include <hex.h>
#include <string.h>
#include <stdlib.h>
#include <linked_list.h>
void littleEndianSample()
{
    uint8_t lenE = 2;
    uint32_t result = RUNTIME_SUCCESS;
    char str[] = "0900";
    setHexLen(lenE);
    getSortedString(str, lenE, getStrLen(str));
    str2decArr(hexValArr, getStrLen(hexValArr), &result);
    printf("str(%s),sorted: %s, value: %d\n", str, hexValArr, result);
}
void AllHexSamples()
{
    uint8_t lenE = 2;
    char c = 'A';
    uint32_t result = RUNTIME_SUCCESS;
    result = char2dec(c);
    printf("char2dec(%c): %d\n", c, result);
    printStat(result);

    char str[] = "0900";
    setHexLen(lenE);

    str2decArr(str, getStrLen(str), &result);
    printf("str2decArr(%s): %d\n", str, result);
    strcpy(str, "0009");
    printf("str2decArr(%s):\n", str);
    printStat(result);

    int dec = 5423;
    dec2hex(dec);
    printf("dec2hex, src: %d, hex: %s\n", dec, displayArr);
    str2decArr(displayArr, getStrLen(displayArr), &result);
    printf("str2decArr(%s): %d\n", displayArr, result);

    strcpy(str, "0009");
    getSortedString(str, lenE, getStrLen(str));
    str2decArr(hexValArr, getStrLen(hexValArr), &result);
    printf("str(%s),sorted: %s, value: %d\n", str, hexValArr, result);
}
void linktest()
{
    linkedListStat stat = OOB;
    NodeG_t *HEAD = NULL;
    define_data_size(sizeof(uint32_t));
    int var = 0;
    int idx;
    for (idx = 0; idx < 20; idx++)
    {
        // var = idx + 5;
        var = idx;
        stat = AddNode_lastG(&HEAD, &var, idx);
    }
    PrintListG_ui32(HEAD);
}
int main(int argc, char const *argv[])
{
    // -- SAMPLE --
    // littleEndianSample();
    // AllHexSamples();
    // linktest();

    uint32_t result = 0;
    int len = 0;
    char str[] = "0009";

    // get little Endian of FAT Size
    getSortedString(str, 2, getStrLen(str));
    str2decArr(hexValArr, getStrLen(hexValArr), &result);
    printf("str(%s),sorted: %s, value: %d\n", str, hexValArr, result);
    // get root dir
    int dirRoot_addr = (result * 2 + 1) * 512;
    dec2hex(dirRoot_addr);
    len = getStrLen(displayArr);
    str2dec(displayArr, len, &result);

    FILE *pFile = fopen("./floppy.img", "r");
    uint8_t c;
    result = 2600 * 16;

    if (fseek(pFile, 0x2600, 0) != 0)
    {
        fprintf(stderr, "fseek() failed in file %s at line # %d\n", __FILE__, __LINE__ - 2);
        fclose(pFile);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < 32; i++)
    {
        c = fgetc(pFile);
        printf("%x", c);
    }

    fclose(pFile);
    return 0;
}
