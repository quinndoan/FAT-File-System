#include "Read_Display_Data.h"

static uint8_t Buff[32];
extern uint32_t Root_Directory_Address;

Node_Data * Create_Node(uint8_t idx){
	Node_Data *NewNode = (Node_Data *)malloc(sizeof(Node_Data));
	NewNode->index = idx;
	NewNode->pData = (uint8_t*)malloc(sizeof(Root_Directory_t));
	copy_String(Buff, NewNode->pData,sizeof(Root_Directory_t));
	NewNode->Next = NULL;
	return NewNode;
}

void Add_Node(uint8_t idx){
	if(HEAD == NULL){
		HEAD = Create_Node(idx);		//set up HEAD
	}
	else{
		Node_Data *New_Node = Create_Node(idx);
		Node_Data *pCheck = HEAD;
		while(pCheck->Next != NULL){
			pCheck = pCheck->Next;
		}
		pCheck->Next = New_Node;
	}
}

void Clear_Linked_List(){
	Node_Data *pCheck;
	while(HEAD != NULL){
		pCheck = HEAD;
		HEAD = HEAD->Next;
		free(pCheck);
	}
}

void Read_Root_Directory(){
	uint8_t index = 1;
	fseek(pFile, Root_Directory_Address, SEEK_SET);
	while(1){
		Read_File(Buff, sizeof(Root_Directory_t));
		if(Buff[0] == 0){
			break;
		}
		else if(Buff[0x1A] == 0 && Buff[0x1B] == 0){
			continue;
		}
		else{
			Add_Node(index);
			index++;
		}
	}
}

void Display_Directory(){
	printf("---------------------------------------------------------------------\n");
    printf("ID	Filename	 	Extension	Attributes	Time		Date		Size\n");
    printf("---------------------------------------------------------------------\n");
	Node_Data *pCheck = HEAD;
	while(pCheck != NULL){
		ptrStruct = (Root_Directory_t *)pCheck->pData;
		printf("%d	",pCheck->index);
		printf("Filename: %-9s	", ptrStruct->File_Name);
    printf("Extension: %-3s	", ptrStruct->File_Extension);
    printf("Attributes: %02X	", ptrStruct->File_Attribute);
    printf("Time: %04X	", ptrStruct->Time);
    printf("Date: %04X	", ptrStruct->Date);
    printf("Size: %u\n", ptrStruct->File_Size);
		
		printf("\n");
		pCheck = pCheck->Next;
	}
}

void Read_Sub_Directory(uint32_t Address){
	uint8_t index = 1;
	Clear_Linked_List();
	Address = Move_t_Block(Address + 31);
	fseek(pFile, Address + 64, SEEK_SET);
	while(1){
		Read_File(Buff, sizeof(Root_Directory_t));
		if(Buff[0] == 0){
			break;
		}
		else{
			Add_Node(index);
			index++;
		}
	}
}

void Read_Display_File(){
	//
}

void Read_Display_Sub_Directory(uint32_t Address){
	Read_Sub_Directory(Address);
	Display_Directory();
}

void Read_Display_Root_Directory(){
	Read_Root_Directory();
	Display_Directory();
}
void push(uint32_t directory) {
    if (top >= STACK_SIZE - 1) {
        printf("Stack overflow.\n");
        return;
    }
    directory_stack[++top] = directory;
}

uint32_t pop() {
    if (top < 0) {
        printf("Stack underflow.\n");
        return 0;
    }
    return directory_stack[top--];
}
uint32_t topStack() {
    if (top < 0) {
        printf("Stack is empty.\n");
        return 0; 
    }
    return directory_stack[top];
}

status_t Function_In(uint8_t choice) {
    if (choice == 0) {
        if (top >= 0) {
            if (top >= 1) {
                pop();
                Clear_Linked_List();
                Read_Display_Sub_Directory(topStack()); 
                return Valid;
            } else {
                pop();
                Clear_Linked_List(); 
                Read_Display_Root_Directory(); 
                return Valid;
            }
        } else {
            printf("Already at root. You entered exiting.\n");
            exit(0);
        }
    } else {
        Node_Data *pCheck = HEAD;
        while (pCheck != NULL) {
            if (pCheck->index == choice) {
                Root_Directory_t *ptrStruct = (Root_Directory_t*)pCheck->pData;
                if (ptrStruct->File_Attribute == 0x10) {
                    uint32_t directoryAddress = (uint32_t)ptrStruct->First_Cluster_Number;
                    push(directoryAddress);
                    Clear_Linked_List(); 
                    Read_Display_Sub_Directory(topStack()); 
                } else {
                    printf("File\n");
                    // Code vào ra tuong tu cho file
                }
                return Valid;
            }
            pCheck = pCheck->Next;
        }
        printf("You entered an invalid number. Please enter again.\n");
        return Invalid;
    }
}


