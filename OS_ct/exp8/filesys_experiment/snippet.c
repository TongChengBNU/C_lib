/************************************************************************
 > File Name: snippet.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Sat 21 Dec 2019 05:59:46 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "filesys.h"

unsigned int size_to_block_num(unsigned int size)
{
	int temp = (size % BLOCKSIZ)?1:0;
	return (size/BLOCKSIZ)+temp;
}
