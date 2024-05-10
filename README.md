this can be run by running "make" then "./a.exe" in the terminal </br>
Alternatively, for running on DevC you can replace this function inside `Read_Display_Data.c`
```c
void Display_Directory(){
	system("cls");
	printf("------------------------------------------------------------------------------\n");
    printf("ID	Filename 	Extension	Time		Date		Size\n");
    printf("------------------------------------------------------------------------------\n");
	Node_Data *pCheck = HEAD;
	while(pCheck != NULL){
		ptrStruct = (Root_Directory_t *)pCheck->pData;
		printf("%d	",pCheck->index);
		// copy_String(ptrStruct->File_Name, Buff,8);
		printf("%8s ",Buff);
    	printf("%10s%.10s	", ptrStruct->File_Extension,"");
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
```
