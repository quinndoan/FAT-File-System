#ifndef _INC_COMMON_
#define _INC_COMMON_
#include "lib.h"

extern FILE *pFile;

void Open_File(const char *filename);
void Close_File();
uint32_t Move_t_Block(uint32_t Block_idx);
void Read_File(uint8_t *Arr, uint32_t len);
void Str_to_Hex( uint8_t *Source, uint8_t len, uint16_t *result);
void copy_String(uint8_t *Source_Address, uint8_t *Dest_Address, uint8_t len);
#endif
