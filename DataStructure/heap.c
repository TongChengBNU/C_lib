/************************************************************************
 > File Name: heap.c
 > Description: min_heap implementation
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Tue 26 Nov 2019 02:57:02 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_LENGTH 100
#define LEFT 1
#define RIGHT 0


typedef unsigned int ele_t;

typedef struct heap{
	unsigned int length;
	ele_t data[MAX_HEAP_LENGTH];
}Heap;

void init(Heap *pheap);
void swap(ele_t *ptr_a, ele_t *ptr_b);
void show_state(Heap *pheap);
int shiftDown_part(Heap *pheap);
void shiftDown(Heap *pheap);

int main(int argc, char *argv[])
{
	Heap *heap = (Heap *)malloc(sizeof(Heap));
	init(heap);
	show_state(heap);
	shiftDown(heap);
	show_state(heap);
	

	return 0;
}

void init(Heap *pheap)
{
	ele_t *ptr = pheap->data;
	scanf("%d", &pheap->length);
	for(int i=0;i<pheap->length;i++)
	{
		scanf("%d", ptr++);
	}
	return;
}
void show_state(Heap *pheap)
{
	ele_t *ptr = pheap->data;
	printf("\nCurrent sequence of heap:\n");
	for(int i=0;i<pheap->length;i++)
	{
		printf("%d ", *(ptr++));
	}
	putchar('\n');
	return;
}
void swap(ele_t *ptr_a, ele_t *ptr_b)
{
	ele_t tmp = *ptr_a;	
	*ptr_a = *ptr_b;
	*ptr_b = tmp;
}
int shiftDown_part(Heap *pheap)
{
	int flag, start;
	int ret = 0;
	if((pheap->length-1) % 2)
	{
		// odd - left node
		flag = LEFT;
		start = (pheap->length-1)/2;

	}
	else
	{
		// even
		flag = RIGHT;
		start = (pheap->length-1)/2 - 1;
	}

	// exception handling 
	if(flag)
	{
		if(pheap->data[start] > pheap->data[start*2+1])	
			swap(&pheap->data[start], &pheap->data[start*2+1]);
	}
	else
	{
		if(pheap->data[start*2+1] <= pheap->data[start*2+2])
		{
			if(pheap->data[start] > pheap->data[start*2+1])	
			{
				swap(&pheap->data[start], &pheap->data[start*2+1]);
				ret = 1;
			}
		}
		else
		{
			if(pheap->data[start] > pheap->data[start*2+2])	
			{
				swap(&pheap->data[start], &pheap->data[start*2+2]);
				ret = 1;
			}
		}
	
	}
	start--;


	for(;start>=0;start--)
	{
		if(pheap->data[start*2+1] <= pheap->data[start*2+2])
		{
			if(pheap->data[start] > pheap->data[start*2+1])	
			{
				swap(&pheap->data[start], &pheap->data[start*2+1]);
				ret = 1;
			}
		}
		else
		{
			if(pheap->data[start] > pheap->data[start*2+2])	
			{
				swap(&pheap->data[start], &pheap->data[start*2+2]);
				ret = 1;
			}
		}
	}
	return ret;
}

void shiftDown(Heap *pheap)
{
	int option;
	do{
		option = shiftDown_part(pheap);	
	}while(option);

}
