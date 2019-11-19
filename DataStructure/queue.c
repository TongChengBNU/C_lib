/************************************************************************
 > File Name: queue.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Tue 19 Nov 2019 02:10:59 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

typedef unsigned int element_t;

typedef struct queue{
	element_t data[MAX_SIZE];
	int front;
	int rear;
}Queue;

void initialization(Queue *queue);
void push(element_t ele, Queue *queue);
element_t pop(Queue *queue);
void show_state(Queue *queue);
void interactive_mode(Queue *queue);

int main(int argc, char *argv[])
{
	Queue *test = (Queue *)malloc(sizeof(Queue));
	initialization(test);
	interactive_mode(test);
	

	 

	return 0;
}


void initialization(Queue *queue)
{
	queue->front = 0;
	queue->rear = 0; 
}
void push(element_t ele, Queue *queue)
{
	if( (queue->rear+1) % MAX_SIZE != queue->front)
	{
		queue->data[queue->rear] = ele;
		queue->rear = (queue->rear+1)%MAX_SIZE;
		return;
	}
	printf("Queue full error;\n");
	return;
}
element_t pop(Queue *queue)
{
	element_t ret;	
	if(queue->front != queue->rear)
	{
		ret = queue->data[queue->front];
		queue->front = (queue->front+1)%MAX_SIZE;
		return ret;
	}
	printf("Queue empty error\n");
	return -1;
}
void show_state(Queue *queue)
{
	int tmp_ptr = queue->front;
	while( (tmp_ptr%MAX_SIZE) != queue->rear)
	{
		printf("%d ", queue->data[tmp_ptr]);
		tmp_ptr = (tmp_ptr+1)%MAX_SIZE;	
	}
	putchar('\n');
	return;
}
void interactive_mode(Queue *queue)
{
	short option;
	element_t ele;
	while(1)
	{
		printf("Please select an option below:\n");	
		printf("1. Push; 2. Pop; 3. Show; 4. Exit\n");
		scanf("%hd", &option);
		switch(option)
		{
			case 1:
				printf("Please input the ele:\n");
				scanf("%d", &ele);
				push(ele, queue);
				break;
			case 2:
				printf("Result: %d\n", pop(queue));
				break;
			case 3:
				show_state(queue);
				break;
			case 4:
				exit(0);
				break;
		}
		putchar('\n');	
	}
	return;
}
