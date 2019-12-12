/************************************************************************
 > File Name: test.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Thu 12 Dec 2019 06:43:29 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
 
void memcpy()
{
	printf("Hello World\n");
}


int main()
{
	unsigned short a = 00777;
	printf("%o, %d, %x\n", a, a, a);
	memcpy();


	return 0;
}
