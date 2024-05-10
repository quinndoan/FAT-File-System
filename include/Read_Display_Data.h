#ifndef _INC_DATA_
#define _INC_DATA_
#include "lib.h"
#define STACK_SIZE 100
#define BLOCK_SIZE 512
typedef struct{
	uint8_t File_Name[8];
	uint8_t File_Extension[3];
	uint8_t File_Attribute;
	uint8_t Reserved[10];
	uint16_t Time;
	uint16_t Date;
	uint16_t First_Cluster_Number;
	uint32_t File_Size; 
}Root_Directory_t;

typedef struct Node_Data{
	uint8_t index;
	uint8_t *pData;
	struct Node_Data *Next;
}Node_Data;

typedef enum{
	Directory,
	Sub_Directory,
	File_Txt,
}File_t;

static isValidChoice = 0;
static Node_Data *HEAD = NULL;
static uint32_t directory_stack[STACK_SIZE];

void Read_Display_Root_Directory();
void Function_In(uint8_t choice);
void Read_Display_File(uint16_t Address);
#endif
