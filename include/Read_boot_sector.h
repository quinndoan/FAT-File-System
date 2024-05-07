#include "lib.h"

typedef struct {
	uint8_t Numb_of_File_Allocation_Table;			//2	
	uint16_t Numb_of_directory_entry;				//e0
	uint16_t Total_Number_of_Blocks;						
	uint16_t FAT_Size;								//9
	uint8_t FAT_style[8];							//FAT12
}Boot_Block;

void Read_boot_block();
