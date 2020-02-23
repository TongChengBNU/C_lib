/************************************************************************
 > File Name: test.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Tue 12 Nov 2019 04:46:26 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int address;
typedef int job_id;
typedef unsigned int job_length;
typedef int kind;

#define MAX_MEM_SIZE 1000
#define IDLE -1
#define MEM_BEGIN 1
#define TRUE 1
#define FALSE 0

typedef struct cell{
	address begin;
	job_id  id;
	job_length length;
	kind head;
	struct cell *before;
	struct cell *next;
	
}Node;

void change(Node *ptr)
{
	Node *ptr2 = ptr;
	ptr2->begin++;
}

void allocate(Node *ptr)
{
	//ptr = (Node *)malloc(sizeof(Node));
	ptr->length = 100;
	Node *new = (Node *)malloc(sizeof(Node));
	new->before = ptr;
	new->length = 50;
	ptr->next = new;
}

int main(int argc, char *argv[])
{
	//Node *test = (Node *)malloc(sizeof(Node));
	//change(test);
	//printf("%d\n", test->begin);

	//bool var=true;
	//printf("%d\n", var);
	
	Node *ptr;
	ptr = (Node *)malloc(sizeof(Node));
	allocate(ptr);
	printf("%d\n", ptr->next->length);


	return 0;
}
