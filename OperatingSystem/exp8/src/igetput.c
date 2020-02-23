#include <stdio.h>
#include "filesys.h"

// OK
// functionality: allocate memory inode
// input: disk inode id
// output: memory inode
struct inode * iget(dinodeid)
unsigned int dinodeid;
{
	int existed = 0, inodeid;
	long addr;
	struct inode *temp_inode_ptr, *newinode;

	// ---------------------------------------------------------
	// hash search
	// NHINO = 128
	inodeid = dinodeid % NHINO;
	// global var: hinode
	if (hinode[inodeid].i_forw == NULL)
		existed = 0;
	else
	{
		temp_inode_ptr= hinode[inodeid].i_forw; 
		while (temp_inode_ptr)
		{
			// i_ino: disk inode ID
			if (temp_inode_ptr->i_ino == dinodeid)  //xiao
			/* existed */
			{
				existed = 1;
				// increment the ref count
				temp_inode_ptr->i_count++;
				return temp_inode_ptr;
			}
			else  /*not existed*/
				temp_inode_ptr = temp_inode_ptr->i_forw;
		}
		// not existed
	}
	// --------------------------------------------------------


	/* not existed */   
	/* 1. calculate the addr of disk inode */
	addr = DINODESTART + dinodeid * sizeof(struct dinode);

	/* 2. malloc the new memory inode*/
	newinode = (struct inode *)malloc(sizeof(struct inode));

	/* 3. read the dinode to the inode*/
	// disk is a global variable declared in main.c
	// memory inode contain a sub dinode from di_type
	// could be improved *************************
	memcpy(&(newinode->di_type), disk+addr, sizeof(struct dinode));

	/* 4. put it into hinode[inodeid] queue*/
	// add the new memory inode at head
	// free the old memory inode at tail
	newinode->i_forw = hinode[inodeid].i_forw;
	newinode->i_back = newinode;
	hinode[inodeid].i_forw = newinode;
	if(newinode->i_forw)
		newinode->i_forw->i_back = newinode;


	/*5. initialize the inode*/
	newinode->i_count = 1;
	newinode->i_flag = 0;   /* flag for not update*/
	newinode->i_ino = dinodeid;

	return newinode;
}


// OK
// functionality: free memory inode 
// pinode: ptr inode
void iput(pinode)
struct inode *pinode;
{
	long addr;
	unsigned int block_num;
	int i;

	if (pinode->i_count > 1)
	{
		// 访问计数-1 
		pinode->i_count--;
		return;
	}
	else
	{
		// i_count == 1
		/*write the memory inode to disk as disk inode */
		addr = DINODESTART + (pinode->i_ino) * DINODESIZ;
		memcpy(disk+addr, &pinode->di_type, DINODESIZ);

		if (pinode->di_number == 0)
		{
			// 没有文件与之关联
			// 释放相应的磁盘索引节点
			ifree(pinode->i_ino);
		}	

		// 释放内存索引节点占用的内存
		free(pinode);
	}

	return;
}













