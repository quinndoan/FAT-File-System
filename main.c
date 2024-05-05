#include "Read_boot_sector.h"
#include "Read_Display_Data.h"

int main(){
	Open_File("./floppy.img");
	uint8_t choice;
	Read_boot_block();
	Read_Display_Root_Directory();
	while(1){
		printf("Enter your choice: ");
		scanf("%d", &choice);
		Function_In(choice);
		fflush(stdin);
	}
	Close_File();
}
