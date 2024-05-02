#include <imath.h>

uint32_t ipow(int base, int exp)
{
    int result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}
void printdArray(uint32_t*arr,uint16_t len){
    uint8_t idx = 0;
            for (idx = 0; idx <= len; idx++)
        {
            printf("%d,",arr[idx]);
        }
            printf("\n");

}