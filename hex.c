#include <hex.h>

uint16_t num_pair = 0;  // pair of hex value in a string
uint16_t decArrLen = 0; // pair of hex value in a string
uint32_t decArr[ARR_MAX_LEN];
uint16_t setted_hexlen = 2;
uint8_t hexlen = 0;

uint8_t displayArr[ARR_MAX_LEN] = {0};
uint8_t hexValArr[ARR_MAX_LEN] = {0};
void setHexLen(uint8_t len)
{
    setted_hexlen = len;
}
void printStat(runStat stat)
{
    switch (stat)
    {
    case RUNTIME_SUCCESS /* constant-expression */:
        printf("RUNTIME_SUCCESS \n");
        break;
    case RUNTIME_ERROR /* constant-expression */:
        printf("RUNTIME_ERROR \n");
        break;
    case RUNTIME_ERROR_MALLOC /* constant-expression */:
        printf("RUNTIME_ERROR_MALLOC \n");
        break;
    case RUNTIME_ERROR_HEX_FORMAT /* constant-expression */:
        printf("RUNTIME_ERROR_HEX_FORMAT \n");
        break;
    case RUNTIME_FILE_ERROR_READ /* constant-expression */:
        printf("RUNTIME_FILE_ERROR_READ \n");
        break;
    default:
        break;
    }
}
void init_0()
{
    hexlen = 0;
    for (int idx = ARR_MAX_LEN; idx > 0; idx--)
    {
        displayArr[idx] = 0;
    }
}
uint8_t char2dec(int8_t c)
{
    uint8_t result = RUNTIME_SUCCESS;
    if (c < '0' || c > 'F')
    {
        result = RUNTIME_ERROR_HEX_FORMAT;
    }
    else
    {
        result = c - '0';
        if (c > '9')
            result -= 7;
    }
    return result;
}

uint32_t str2decArr(const char *str, uint8_t len, uint32_t *pDecimal)
{
    runStat stat = RUNTIME_SUCCESS;
    uint8_t idx = 0;
    uint8_t cur_hexVal = 0; // in decimal btw
    *pDecimal = 0;
    for (idx = 0; idx < len; idx++)
    {
        cur_hexVal = char2dec(str[idx]);
        if (cur_hexVal == RUNTIME_ERROR_HEX_FORMAT)
        {
            stat = RUNTIME_ERROR_HEX_FORMAT;
            break;
        }
        *pDecimal += cur_hexVal * ipow(16, len - 1 - idx);
        // printf("curHexval: %d, ipow: %d,  *pDecimal %d\n",cur_hexVal,ipow(16, len - 1 - idx), *pDecimal);
    }
    return stat;
}
void str2dec(const char *str, uint8_t len, int* dec){
     *dec = 0;
    for (int idx = 0; idx < len; idx++)
    {
        *dec += char2dec(displayArr[idx])*pow(10,len-idx-1);
    }
}
void flipHexArr()
{
    uint16_t idx = 0;
    // while (displayArr[ARR_MAX_LEN - idx] != '\0')
    while (displayArr[ARR_MAX_LEN - idx] != '\0')
    {
        if (hexlen < setted_hexlen)
        {
            displayArr[idx] = displayArr[ARR_MAX_LEN - (hexlen - idx)];
        }
        else
        {
            displayArr[idx] = displayArr[ARR_MAX_LEN - (hexlen - idx - 1)];
        }
        idx++;
    }
    displayArr[idx] = '\0';
}
void printHexStr()
{
    uint8_t idx = ARR_MAX_LEN;

    while (displayArr[idx] != '\0')
    {
        printf("%c", displayArr[idx]);
        idx--;
    }
    printf("\n");
}
void dec2hex(uint32_t dec)
{
    init_0();
    // printHexStr();

    int idx = ARR_MAX_LEN;
    char c = '0';
    if (dec == 0)
    {
        displayArr[idx] = '0';
        hexlen++;
    }
    while (dec != 0)
    {
        uint32_t result = dec % 16;
        if (result < 10)
        {
            result += 48;
        }
        else
        {
            result += 55;
        }
        c = result;
        displayArr[idx] = c;
        dec = dec / 16;
        idx--;
        hexlen++;
    }
    // printHexStr();

    for (; idx > ARR_MAX_LEN - setted_hexlen; idx--)
    {
        displayArr[idx] = '0';
    }
    flipHexArr();
    // printHexStr();
}
void decArr2HexStr(uint32_t *arr, uint16_t len, char *HexArr)
{
    uint8_t idx = 0;
    uint8_t HArr_idx = 0;
    for (idx = 0; idx < len; idx++)
    {
        // printf("len: %d - idx: %d\n",len,idx);
        dec2hex(arr[idx]);
        // printf("dec2hex, src: %d, hex: %s\n", arr[idx], displayArr);
        for (int j = 0; j < setted_hexlen; j++)
        {
            // printf("displayArr[j];%d\n",displayArr[j]);
            HexArr[HArr_idx] = displayArr[j];
            HArr_idx++;
        }
    }
    // HexArr[idx+setted_hexlen+1]='\0';
    // printf("HexArr: %s\n\n eof\n",HexArr);
    int result = 0;
    str2decArr(HexArr, getStrLen(HexArr), &result);
    // printf("str2decArr(%s): %d\n", HexArr, result);
}
void getSortedString(const char *src, uint8_t lenE, uint32_t lenA)
{
    if (lenA == 0)
    {
        decArr[0] = 0; // return empty array
    }
    else
    {
        decArrLen = 0;
        num_pair = lenA / lenE;
        uint8_t idx = 0;
        uint8_t idx_dArr = 0;
        uint8_t idx_e = 0;
        char elementPair[50];
        for (idx = 0; idx <= num_pair;)
        {
            for (idx_e = 0; idx_e < lenE; idx_e++)
            {
                elementPair[idx_e] = src[idx + idx_e];
            }
            elementPair[idx_e] = '\0';
            // printf("elementPair: %s\n", elementPair);
            str2decArr(elementPair, lenE, &(decArr[idx_dArr]));
            // printf("idx: %d, idx-LenE: %d\n",idx,idx_dArr);
            // printf("decArr:");
            // printdArray(decArr,decArrLen);
            quickSort(decArr, 0, decArrLen);
            // printdArray(decArr,decArrLen);
            idx += lenE;
            decArrLen++;
            idx_dArr++;
        }
    }
    decArr2HexStr(decArr, decArrLen, hexValArr);
}