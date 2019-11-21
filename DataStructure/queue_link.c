/************************************************************************
 > File Name: ../../DataStructure/queue_link.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Thu 21 Nov 2019 03:37:13 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct node{
	int id;
	int head;
	struct node *before;
	struct node *next; 
}Node;

void initialization(Node *queue)
{
	// queue has been allocated
	queue->head = TRUE;
	queue->next = NULL;
}

void push(int id, Node *queue)
{
	Node *ptr = queue;	
	while(ptr->next != NULL)
		ptr = ptr->next;
	Node *new = (Node *)malloc(sizeof(Node));
	new->id = id;
	new->next = NULL;
	new->before = ptr;

	ptr->next = new;
	printf("Push id: %d success\n", id);
	return;
}

int pop(Node *queue)
{
	Node *ptr = queue->next;
	if(ptr == NULL)
	{
		printf("Pop error;\n");
		return -1;
	}
	int ret = ptr->id;
	queue->next = ptr->next;
	ptr->next->before = queue;
	printf("Pop value: %d\n", ret);
	free(ptr);
	return ret;
}

void show_state(Node *queue)
{
	Node *ptr = queue->next;
	while(ptr)
	{
		printf("%d ", ptr->id);
		ptr = ptr->next;
	}
	putchar('\n');
	return;
}

void interactive_mode()
{
	Node *process = (Node *)malloc(sizeof(Node));
	initialization(process);
	int option, element;
	while(1)
	{
		printf("Please select an option below:\n");
		printf("1. Push; 2. Pop; 3. Show state; 4. Exit;\n");
		scanf("%d", &option);
		switch(option){
			case 1:
				printf("Please input your element:\n");
				scanf("%d", &element);
				push(element, process);
				break;
			case 2:
				pop(process);
				break;
			case 3:
				show_state(process);
				break;
			case 4:
				exit(0);
				break;
		}
	
	}
}

int main()
{
	interactive_mode();
	return 0;
}
