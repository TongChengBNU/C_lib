/************************************************************************
 > File Name: test.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Thu 12 Dec 2019 06:43:29 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 


int main()
{
	unsigned short *a;
	int *b;
	char buffer[10] = "Hello";
	char name[10];
	//strcpy(name, buffer);
	//memcpy(name, buffer, 10);
	memset(name, 0x00, 10);
	printf("%s %s", buffer, name);


	return 0;
}
