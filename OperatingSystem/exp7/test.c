/************************************************************************
 > File Name: test.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Thu 21 Nov 2019 01:54:19 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct{
	int data;
}Node[5];

int main()
{
	Node[0].data = 1;
	printf("%d\n", Node[0].data);
	printf("%d\n", Node[1].data);

	// logic number: 3
	// offset within page: 3
	// 0000 11|00 0000 0011
	// 0000 00 11 1111 1111
	uint16_t tmp = 0x0c03;
	printf("logic number: %d\n", tmp>>10);
	printf("offset within page: %d\n", tmp&0x03ff);
	printf("%x\n", tmp);

	int small;
	uint16_t large = 0xffff;
	small = large;
	printf("%x", small);

	int array[10] = {1,2,3,4,5};
	int *front, *rear;
	front = &array[0];
	for(int i=0;i<10;i++)
	{
		printf("%d\n", *front);
		front++;
	}


	return 0;
}
