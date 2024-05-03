#include "NTD.h"
#include "Read_Display_Data.h"

int main(){
	Open_File("C://Users//Nitro Tiger//Downloads//floppy.img");
	uint8_t choice;
	Read_boot_block();
	Read_Display_Root_Directory();
	while(1){
		printf("Enter your choice:\n");
		scanf("%d", &choice);
		
		if(Function_In(choice) == Invalid){
			printf("Invalid\n");
			continue;
		}
		fflush(stdin);
	}
	Close_File();
}
