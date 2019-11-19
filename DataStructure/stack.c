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

typedef struct stack{
	element_t data[MAX_SIZE];
	int top;
}Stack;

void initialization(Stack *stack);
void push(element_t ele, Stack *stack);
element_t pop(Stack *stack);
void show_state(Stack *stack);
void interactive_mode(Stack *stack);

int main(int argc, char *argv[])
{
	Stack *test = (Stack *)malloc(sizeof(Stack));
	initialization(test);
	interactive_mode(test);
	

	 

	return 0;
}


void initialization(Stack *stack)
{
	stack->top = 0;
}
void push(element_t ele, Stack *stack)
{
	if( stack->top != MAX_SIZE )
	{
		stack->data[stack->top++] = ele;
		return;
	}
	printf("Stack full error;\n");
	return;
}
element_t pop(Stack *stack)
{
	element_t ret;	
	if(stack->top != 0)
	{
		ret = stack->data[--stack->top];
		return ret;
	}
	printf("Queue empty error\n");
	return -1;
}
void show_state(Stack *stack)
{
	int tmp_ptr = 0;
	while(tmp_ptr != stack->top) 
	{
		printf("%d ", stack->data[tmp_ptr++]);
	}
	putchar('\n');
	return;
}
void interactive_mode(Stack *stack)
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
				push(ele, stack);
				break;
			case 2:
				printf("Result: %d\n", pop(stack));
				break;
			case 3:
				show_state(stack);
				break;
			case 4:
				exit(0);
				break;
		}
		putchar('\n');	
	}
	return;
}
