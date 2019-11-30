/************************************************************************
 > File Name: test.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Sat 30 Nov 2019 05:22:55 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, int *argv[])
{
	int a = 100;
	int b = 200;
	int *ptr = &a;
	ptr = ptr+1;
	printf("%x\n", *ptr);
	printf("%d\n", *ptr);


	return 0;
}
