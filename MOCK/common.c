#include "common.h"

FILE *pFile;

void Open_File(const char *filename){
	pFile = fopen(filename, "rb");
}

void Close_File(){
	fclose(pFile);
}


uint32_t Move_t_Block(uint32_t Block_idx){
	return 512 * Block_idx; 
}

void Read_File(uint8_t *Arr, uint32_t len){
	fgets(Arr, len+1, pFile);
}

void Str_to_Hex( uint8_t *Source, uint8_t len, uint16_t *result){
	*result = 0;
	uint32_t idx;
	for(idx = 0; idx < len; idx++){
		*result = *result + (uint32_t)(Source[idx] << (8*idx));
	}
}

void copy_String(uint8_t *Source_Address, uint8_t *Dest_Address, uint8_t len){
	uint8_t idx;
	for(idx = 0; idx < len; idx++){
		Dest_Address[idx] = Source_Address[idx];
	}
}

