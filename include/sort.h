#ifndef _SORT_H_
#define _SORT_H_
#include <stdio.h>
void swap(int *a, int *b);
int partition(int array[], int low, int high);
extern void quickSort(int array[], int low, int high);
#endif