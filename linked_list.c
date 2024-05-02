#include <linked_list.h>
// static NodeG_t *HEAD = NULL; // global only could work just fine, if the memory is not touched, otherwise, it might do some
#define HeadAddr (*HEAD)


void define_data_size(uint32_t size)
{
	cur_data_size = size;
}
void Copy(void *dest, void *src)
{ // Copy content from dest to source
	int i;
	// printf("\n%d size\n", cur_data_size);
	// printf("\ndata%s: \n",());
	for (i = 0; i < cur_data_size; i++)
	{
		*(char *)(dest + i) = *(char *)((src) + i);
	}
}
int AddNode_headG(NodeG_t **HEAD, void *data)
{
	NodeG_t *newNode = (NodeG_t *)malloc(sizeof(NodeG_t));
	newNode->data = malloc(cur_data_size);

	if (newNode == NULL || (int *)(newNode->data) == NULL)
	{
		return MALLOC_FAILED;
	}

	Copy(newNode->data, data);
	if (HeadAddr == NULL)
	{
		newNode->next = NULL;
		HeadAddr = newNode;
		return SUCCESS;
	}
	newNode->next = HeadAddr;
	HeadAddr = newNode;
	return SUCCESS;
}
int AddNode_lastG(NodeG_t **HEAD, void *data)
{
	NodeG_t *newNode = (NodeG_t *)malloc(sizeof(NodeG_t));
	newNode->data = malloc(cur_data_size);
	if (newNode == NULL)
	{
		return MALLOC_FAILED;
	}
	newNode->next = NULL;
	Copy(newNode->data, data);
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
void PrintListG_ui32(NodeG_t *HEAD)
{
	printf("list content from generic linked list:\n{");
	NodeG_t *curNode = HEAD;
	while (curNode != NULL && HEAD != NULL)
	{
		printf("%d ,", *(uint32_t *)(curNode->data));
		curNode = curNode->next;
	}
	printf("}\n");
}

int delete_with_student_id(NodeG_t **HEAD, char *id)
{
	NodeG_t *curNode = HeadAddr;
	NodeG_t *prevNode;
	char *student_id;
	int8_t resCmp;
	student_id = (char *)(((Student_t *)(HeadAddr->data))->Account);
	if (strcmp(id, student_id) == 0)
	{
		HeadAddr = HeadAddr->next;
			// printf("FOUND\n");
		return SUCCESS;
	}
	while (curNode != NULL)
	{
		student_id = (char *)(((Student_t *)(curNode->data))->Account);
		resCmp = strcmp(id, student_id);
		if (curNode->next == NULL && resCmp == 0)
		{
			// printf("FOUND\n");

			prevNode->next = NULL;
			break;
		}
		if (resCmp == 0)
		{
			// printf("FOUND\n");
			prevNode->next = curNode->next;
			curNode = curNode->next->next;
			continue;
		}
		prevNode = curNode;
		curNode = curNode->next;
	}
	return SUCCESS;
}

void PrintListG_Student(NodeG_t *HEAD)
{
	NodeG_t *curNode = HEAD;
	while (curNode != NULL && HEAD != NULL)
	{
		printf("%s ,", ((Student_t *)(curNode->data))->FullName);
		printf("%s ,", ((Student_t *)(curNode->data))->Account);
		printf("%d ,", ((Student_t *)(curNode->data))->Mark);
		printf("\n");
		curNode = curNode->next;
	}
}

// function to print the linked list
void printIt(NodeG_t *node, void (*prt)(void *))
{
	while (node != NULL)
	{
		(*prt)(node->data);
		node = node->next;
	}
	printf("\n");
}

// function to print integer values
void prInt(void *x)
{
	printf(" %d", *(int *)x);
}

// function to print float values
void prFlt(void *x)
{
	printf(" %f", *(float *)x);
}
