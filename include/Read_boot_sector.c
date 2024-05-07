#include "Read_boot_sector.h"
#include "common.h"

static uint8_t Buff[9];	
Boot_Block Boot_Info = {0};
uint32_t Root_Directory_Address;

void Read_boot_block(){
	fseek(pFile, 0x10, SEEK_SET);
	Boot_Info.Numb_of_File_Allocation_Table = fgetc(pFile);
	Read_File(Buff, 2);
	Str_to_Hex(Buff, 2, &Boot_Info.Numb_of_directory_entry);
	Read_File(Buff, 2);
	Str_to_Hex(Buff, 2, &Boot_Info.Total_Number_of_Blocks);
	fseek(pFile, 0x16, SEEK_SET);
	Read_File(Buff, 2);
	Str_to_Hex(Buff, 2, &Boot_Info.FAT_Size);
	fseek(pFile, 0x36, SEEK_SET);
	Read_File(Buff, 8);
	copy_String(Buff, Boot_Info.FAT_style, 8);
	Root_Directory_Address = Move_t_Block(Boot_Info.Numb_of_File_Allocation_Table * Boot_Info.FAT_Size + 1);
}


