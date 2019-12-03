/************************************************************************
 > File Name: test.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Sat 23 Nov 2019 06:11:14 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX 0x7fffffff

typedef enum{
	Left,
	Right
}Type;

void swap(int *a, int *b)
{
	int tmp=*a;	
	*a = *b;
	*b = tmp;
}

int main(int argc, char *argv[])
{
	Type tmp[2]={Left, Right};
	//tmp = Right;
	printf("%d\n", tmp[0]);
	printf("%d\n", tmp[1]);

	printf("\n%d\n", MAX);

	// int data[3] = {1,2,3};
	// int *a = &data[0], *b = &data[1];
	// swap(a, b);
	// printf("%d %d\n", data[0], data[1]);
	// printf("%d %d\n", *a, *b);

	// int a = 10;
	// int *ptr = NULL;
	// if(!ptr)
	// 	printf("123\n");
	int a = 1;
	if(!a)
		printf("123");


	return 0;

}
