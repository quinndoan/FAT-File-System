#ifndef _DECODE_H_
#define _DECODE_H_
void decode_Time(uint32_t decVal, int *h, int *m, int *s)
{
    *m = (decVal >> 5) & ~(31 << 6);
    *h = (decVal >> 11) & 31;
    *s = (decVal) & 31;
}
void decode_Date(uint32_t decVal, int *y, int *mth, int *day)
{
    *y = ((decVal >> 9) & 31)+1980;
    *mth = (decVal >> 5) & (15);
    *day = (decVal) & 31;
}
#endif