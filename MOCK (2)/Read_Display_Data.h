#include "lib.h"
#include "common.h"
#define STACK_SIZE 100
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

typedef enum {
	Invalid,
	Valid,
}status_t;

typedef enum{
	Directory,
	Sub_Directory,
	File_Txt,
}File_t;

static Node_Data *HEAD = NULL;
static Root_Directory_t *ptrStruct = NULL;
static File_t File_Type = Directory; 

void Read_Display_Root_Directory();
status_t Function_In(uint8_t choice);


uint32_t directory_stack[STACK_SIZE];
int top = -1;
void push(uint32_t directory);
uint32_t pop();
uint32_t topStack();
