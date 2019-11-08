/************************************************************************
 > File Name: test.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Fri 08 Nov 2019 06:58:17 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct book{
	int number;
};

int main(int argc, char *argv[])
{
	printf("The size of unsigned short is: %ld\n", sizeof(unsigned short));
	printf("The size of unsigned int is: %ld\n", sizeof(unsigned int));

	unsigned short nr = 0xfff1;
	printf("The value of nr is: %x\n", nr);

	struct book book1;
	book1.number = 0xffd1;
	return 0;
}
