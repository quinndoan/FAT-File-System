#include "NTD.h"

FILE *pFile;
uint8_t Buff[9];	
Boot_Block Boot_Info = {0};


uint32_t Move_t_Block(uint32_t Block_idx){
	return 512 * Block_idx; 
}

void Open_File(const char *filename){
	pFile = fopen(filename, "r");
}

void Close_File(){
	fclose(pFile);
}

void Read_File(uint32_t len){
	fgets(Buff, len+1, pFile);
}

void Str_to_Hex(uint8_t len, uint16_t *result){
	*result = 0;
	uint32_t idx;
	for(idx = 0; idx < len; idx++){
		*result = *result + (uint32_t)(Buff[idx] << (8*idx));
	}
}

void copy_String(uint8_t *Arr,uint8_t len){
	uint8_t idx;
	for(idx = 0; idx < len; idx++){
		Arr[idx] = Buff[idx];
	}
}

void Read_boot_block(){
	fseek(pFile, 0x10, SEEK_SET);
	Boot_Info.Numb_of_File_Allocation_Table = fgetc(pFile);
	Read_File(2);
	Str_to_Hex(2, &Boot_Info.Numb_of_directory_entry);
	Read_File(2);
	Str_to_Hex(2, &Boot_Info.Total_Number_of_Blocks);
	fseek(pFile, 0x16, SEEK_SET);
	Read_File(2);
	Str_to_Hex(2, &Boot_Info.FAT_Size);
	fseek(pFile, 0x36, SEEK_SET);
	Read_File(8);
	copy_String(Boot_Info.FAT_style, 8);
	printf("%s",Boot_Info.FAT_style);
}


