#ifndef _DECODE_H_
#define _DECODE_H_
#include <stdint.h>
typedef struct
{
    uint16_t y : 16;
    uint16_t mth : 4;
    uint16_t d : 5;

    uint16_t h : 5;
    uint16_t m : 6;
    uint16_t s : 5;
} date_time;
static date_time dateTime;
void decode_Time(uint32_t decVal)
{
    dateTime.m = (decVal >> 5) & ~(31 << 6);
    dateTime.h = (decVal >> 11) & 31;
    dateTime.s = (decVal) & 31;
}
void decode_Date(uint32_t decVal)
{
    dateTime.y = ((decVal >> 9) & 31) + 1980;
    dateTime.mth = (decVal >> 5) & (15);
    dateTime.d = (decVal) & 31;
}
#endif
