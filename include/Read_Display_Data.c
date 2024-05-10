#include "Read_boot_sector.h"
#include "Read_Display_Data.h"
#include "common.h"
#define BLOCK_SIZE 512
#include "decode.h"

static Root_Directory_t *ptrStruct = NULL;
static File_t File_Type = Directory;
static uint8_t Buff[32];
static int top = -1;
extern Boot_Block Boot_Info;
extern uint32_t Root_Directory_Address;

Node_Data *Create_Node(uint8_t idx)
{
	Node_Data *NewNode = (Node_Data *)malloc(sizeof(Node_Data));
	NewNode->index = idx;
	NewNode->pData = (uint8_t *)malloc(sizeof(Root_Directory_t));
	copy_String(Buff, NewNode->pData, sizeof(Root_Directory_t));
	NewNode->Next = NULL;
	return NewNode;
}

void Add_Node(uint8_t idx)
{
	if (HEAD == NULL)
	{
		HEAD = Create_Node(idx);
	}
	else
	{
		Node_Data *New_Node = Create_Node(idx);
		Node_Data *pCheck = HEAD;
		while (pCheck->Next != NULL)
		{
			pCheck = pCheck->Next;
		}
		pCheck->Next = New_Node;
	}
}

void Clear_Linked_List()
{
	Node_Data *pCheck;
	while (HEAD != NULL)
	{
		pCheck = HEAD;
		HEAD = HEAD->Next;
		free(pCheck);
	}
}

void Read_Root_Directory()
{
	uint8_t index = 1;
	fseek(pFile, Root_Directory_Address, SEEK_SET);
	while (1)
	{
		Read_File(Buff, sizeof(Root_Directory_t));
		if (Buff[0] == 0)
		{
			break;
		}
		else if (Buff[0x1A] == 0 && Buff[0x1B] == 0)
		{
			continue;
		}
		else
		{
			Add_Node(index);
			index++;
		}
	}
}

void Display_Directory()
{
	// system("cls");
	printf("------------------------------------------------------------------------------\n");
	printf("ID	Filename 	Extension	Time		Date		Size\n");
	printf("------------------------------------------------------------------------------\n");
	Node_Data *pCheck = HEAD;
	while (pCheck != NULL)
	{
		ptrStruct = (Root_Directory_t *)pCheck->pData;
		printf("%d	", pCheck->index);
		// copy_String(ptrStruct->File_Name, Buff,8);
		printf("%.8s ", ptrStruct->File_Name);
		printf("%10s%.10s	", ptrStruct->File_Extension, "");
		decode_Time(ptrStruct->Time);
		decode_Date(ptrStruct->Date);
		printf("%8d:%d:%d	", dateTime.h, dateTime.m, dateTime.s);
		printf("%8d/%d/%d	", dateTime.y, dateTime.mth, dateTime.d);
		printf("%10u\n", ptrStruct->File_Size);
		printf("\n");
		pCheck = pCheck->Next;
	}
	printf("------------------------------------------------------------------------------\n");
	printf("0.Back\n");
}
void Read_Sub_Directory(uint32_t Address)
{
	uint8_t index = 1;
	Clear_Linked_List();
	Address = Move_t_Block(Address + 31);
	fseek(pFile, Address + 64, SEEK_SET);
	while (1)
	{
		Read_File(Buff, sizeof(Root_Directory_t));
		if (Buff[0] == 0)
		{
			break;
		}
		else
		{
			Add_Node(index);
			index++;
		}
	}
}

void Read_Display_Sub_Directory(uint32_t Address)
{
	Read_Sub_Directory(Address);
	Display_Directory();
}

void Read_Display_Root_Directory()
{
	Read_Root_Directory();
	Display_Directory();
}
void push(uint32_t directory)
{
	if (top >= STACK_SIZE - 1)
	{
		printf("Stack overflow.\n");
		return;
	}
	directory_stack[++top] = directory;
}

uint32_t pop()
{
	if (top < 0)
	{
		printf("Stack underflow.\n");
		return 0;
	}
	return directory_stack[top--];
}
uint32_t topStack()
{
	if (top < 0)
	{
		printf("Stack is empty.\n");
		return 0;
	}
	return directory_stack[top];
}

void Display_File(uint32_t Address)
{
	uint16_t idx = 0;
	fseek(pFile, Address, SEEK_SET);
	for (idx = 0; idx < BLOCK_SIZE; idx++)
	{
		if (feof(pFile) != 0)
		{
			break;
		}
		printf("%c", fgetc(pFile));
	}
}

uint16_t Get_next_Address(uint16_t Address)
{
	uint16_t *ptr;
	fseek(pFile, 0x200 + 3 * Address / 2, SEEK_SET);
	Read_File(Buff, 2);
	ptr = (uint16_t *)Buff;
	if (Address % 2 == 0)
	{
		Address = *ptr & 0xFFF;
	}
	else
	{
		Address = (*ptr & 0xFFF0) >> 4;
	}
	return Address;
}

void Read_Display_File(uint16_t Address)
{
	Clear_Linked_List();
	system("cls");
	while (Address < 0x0FF8)
	{
		Display_File(Move_t_Block((uint32_t)Address + 31));
		Address = Get_next_Address(Address);
	}
	printf("\n");
}

void Function_In(uint8_t choice)
{
	if (choice == 0)
	{
		if (top >= 0)
		{
			pop();
			Clear_Linked_List();
			if (top >= 1)
			{
				Read_Display_Sub_Directory(topStack());
			}
			else
			{
				Read_Display_Root_Directory();
			}
		}
		else
		{
			printf("You entered exit. Exiting...\n");
			exit(0);
		}
	}
	else
	{
		Node_Data *pCheck = HEAD;
		while (pCheck != NULL)
		{
			if (pCheck->index == choice)
			{
				Root_Directory_t *ptrStruct = (Root_Directory_t *)pCheck->pData;
				if (ptrStruct->File_Attribute == 0x10)
				{
					uint16_t directoryAddress = (uint16_t)ptrStruct->First_Cluster_Number;
					push(directoryAddress);
					Clear_Linked_List();
					Read_Display_Sub_Directory(topStack());
				}
				else
				{
					uint16_t fileAddress = (uint16_t)ptrStruct->First_Cluster_Number;
					push(fileAddress);
					Read_Display_File(fileAddress);
				}
				isValidChoice = 1;
				break;
			}
			pCheck = pCheck->Next;
		}
	}
}
