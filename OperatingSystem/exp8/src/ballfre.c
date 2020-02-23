#include <stdio.h>
#include "filesys.h"

// 成组链接法中的缓冲区
static unsigned int block_buf[BLOCKSIZ];
/*
 * 空闲块栈示意图
 * 0  1  2  3  4  5
 * X  X  O  O  O  O
 *      ptr
 * */



// Ok
// 成组链接法
// functionality: allocate free block
// return ID number of idle block with update
index_t balloc()
{
	unsigned int free_block, free_block_num;
	int i;

	// s_nfree: number of idle block
	if (filsys.s_nfree == 0)
	{
		printf("\nDisk Full!\n");
		return NOINDEX;
	}


	
	// free_block: index of next block
	free_block = filsys.s_free[filsys.s_pfree]; 
	if (filsys.s_pfree == NICFREE-1)
	{ 
		// 空闲块栈只剩一个位置, 最后一个块的内容是下一组空闲块的编号
		// 把最后一块的内容读入缓冲区 
		memcpy(block_buf, disk+DATASTART+filsys.s_free[filsys.s_pfree]*BLOCKSIZ, BLOCKSIZ);
		// 原有栈底的号分配出去, free_block在之前已经更新
		// free_block = filsys.s_free[filsys.s_pfree];
		// 将缓冲区内的号入栈
		for (i=0; i<NICFREE; i++)
			filsys.s_free[i] = block_buf[i];
		// 栈指针从头开始
		filsys.s_pfree = 0;
	}  
	else 
		filsys.s_pfree++;

	// 更新系统超级块
	filsys.s_nfree --;
	filsys.s_fmod = SUPDATE;

	return (int)free_block;
}



// Ok
// functionality: free used block
void bfree(unsigned int block_num)
{
	int i;
	 
	if (filsys.s_pfree == 0)   /* s_free full*/
	{
		// 空闲块栈满, 当前栈内容入缓冲区
		for(i=0; i<NICFREE; i++)
			block_buf[i] = filsys.s_free[i];
		// 缓冲区写入当前盘块
		memcpy(disk+DATASTART+block_num*BLOCKSIZ, block_buf, BLOCKSIZ);
		// 新建栈
		filsys.s_pfree = NICFREE-1;
		// 新盘快号作为尾部元素
		filsys.s_free[filsys.s_pfree] = block_num;
	}
	else
	{
		filsys.s_pfree--;
		filsys.s_free[filsys.s_pfree] = block_num;
	}
	
	// 更新超级块	
	filsys.s_nfree++;
	filsys.s_fmod = SUPDATE;

	return;
}





























