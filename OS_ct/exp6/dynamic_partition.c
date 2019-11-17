/************************************************************************
 > File Name: dynamic_partition.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Wed 13 Nov 2019 07:52:37 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "dynamic_partition.h"



int main(int argc, char *argv[])
{
	Node *memory_link_list = (Node *)malloc(sizeof(Node));
	initialization(memory_link_list);
	printf("%d\n", memory_link_list->next->length);
	interactive_mode(memory_link_list);







	return 0;
}
