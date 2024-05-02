#ifndef NODEG_T_GH_H
#define NODEG_T_GH_H
#include <stdint.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
// #include "user_param.h"
/* types of linked list that doesn't depend on 
 specific pData type, in layman's term:
a linked list that can store any type of pData*/

/* void pointer can store the address of any pData type.
hence it will be used.
*/
#define NAME_STR_LEN 50
#define ACC_STR_LEN 10
#define HeadAddr (*HEAD)

typedef enum{
    SUCCESS,
    OOB,
    MALLOC_FAILED
}linkedListStat;
static uint32_t data_size; // current datasize
typedef struct NodeG_t{
    int node_idx;
    void* pData;
    struct NodeG_t* next;
}NodeG_t;
extern void define_data_size(uint32_t size)
{
	data_size = size;
}
void memCopy(void *dest, void *src,uint8_t len){
    int idx;
	for (idx = 0; idx < len; idx++)
	{
		*(char *)(dest + idx) = *(char *)((src) + idx);
	}
}
extern int AddNode_lastG(NodeG_t **HEAD, void *pData,uint8_t node_idx)
{
	NodeG_t *newNode = (NodeG_t *)malloc(sizeof(NodeG_t));
	newNode->pData = malloc(data_size);
	if (newNode == NULL)
	{
		return MALLOC_FAILED;
	}
	newNode->next = NULL;
    newNode->node_idx == node_idx;
	memCopy(newNode->pData, pData,data_size);
	if (HeadAddr == NULL)
	{
		HeadAddr = newNode;
	}
	else
	{
		NodeG_t *curNode = HeadAddr;
		while (curNode->next != NULL)
		{
			curNode = curNode->next;
		}
		curNode->next = newNode;
	}
	return SUCCESS;
}
extern void PrintListG_ui32(NodeG_t *HEAD)
{
	printf("list content from generic linked list:\n{");
	NodeG_t *curNode = HEAD;
	while (curNode != NULL && HEAD != NULL)
	{
		printf("%d ,", *(uint32_t *)(curNode->pData));
		curNode = curNode->next;
	}
	printf("}\n");
}
#endif
