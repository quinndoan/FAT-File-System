#ifndef _HEX_H_
#define _HEX_H_
#include <stdint.h>
#include <stdlib.h>
#include <sort.h>
#include <strHandler.h>
#include <math.h>
#include <hex.h>

typedef enum
{
    RUNTIME_SUCCESS = 50,
    RUNTIME_ERROR,
    RUNTIME_ERROR_MALLOC,
    RUNTIME_ERROR_HEX_FORMAT,
    RUNTIME_FILE_ERROR_READ
} runStat;
#define ARR_MAX_LEN 100
extern uint8_t  displayArr[ARR_MAX_LEN] ;
extern uint8_t  hexValArr[ARR_MAX_LEN] ;
extern 
void setHexLen(uint8_t len);
extern void printStat(runStat stat);

void init_0();
extern uint8_t char2dec(int8_t c);
extern uint32_t str2decArr(const char *str, uint8_t len, uint32_t *pDecimal);
extern void str2dec(const char *str, uint8_t len, int* dec);
void flipHexArr();
extern void printHexStr();
extern void dec2hex(uint32_t dec);
extern void decArr2HexStr(uint32_t *arr, uint16_t len, char *HexArr);
extern void getSortedString(const char *src, uint8_t lenE, uint32_t lenA);
#endif