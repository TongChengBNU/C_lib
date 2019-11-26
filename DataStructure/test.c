/************************************************************************
 > File Name: test.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Sat 23 Nov 2019 06:11:14 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef enum{
	Left=0,
	Right=1
}Type;

void swap(int *a, int *b)
{
	int tmp=*a;	
	*a = *b;
	*b = tmp;
}

int main(int argc, char *argv[])
{
	//Type tmp;
	//tmp = Right;
	//printf("%d\n", tmp);

	int data[3] = {1,2,3};
	int *a = &data[0], *b = &data[1];
	swap(a, b);
	printf("%d %d\n", data[0], data[1]);
	printf("%d %d\n", *a, *b);




	return 0;

}
