#include <stdio.h>
#include "filesys.h"

// functionality: generate a new inode or get a existed inode
// input: disk inode id
// output: a struct inode
struct inode * iget(dinodeid)
unsigned int dinodeid;
{
	int existed = 0, inodeid;
	long addr;
	struct inode *temp_inode_ptr, *newinode;

	inodeid = dinodeid % NHINO;
	if (hinode[inodeid].i_forw == NULL)
		existed = 0;
	else
	{
		temp_inode_ptr= hinode[inodeid].i_forw; 
		while (temp_inode_ptr)
		{
			// i_ino: disk inode flag
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

	/* not existed */   
	/* 1. calculate the addr of dinode in the file sys column*/
	addr = DINODESTART + dinodeid * DINODESIZ;

	/* 2. malloc the new inode*/
	newinode = (struct inode *)malloc(sizeof(struct inode));

	/* 3. read the dinode to the inode*/
	/*
	fseek(fd, addr, SEEK_SET);
	fread(&(newinode->di_number), DINODESIZ, 1, fd);
	*/
	// disk is a global variable declared in main.c
	// di_number: ref file count
	memcpy(&(newinode->di_number), disk+addr, DINODESIZ);

	/* 4. put it into hinode[inodeid] queue*/
	//???
	newinode->i_forw = hinode[inodeid].i_forw;
	newinode->i_back = newinode;
	if (newinode->i_forw)
	newinode->i_forw->i_back = newinode;
	hinode[inodeid].i_forw = newinode; 

	/*5. initialize the inode*/
	newinode->i_count = 1;
	newinode->i_flag = 0;   /* flag for not update*/
	newinode->i_ino = dinodeid;

	return newinode;
}


// put away inode??????
// pinode: ptr inode
iput(pinode)
struct inode *pinode;
{
	long addr;
	unsigned int block_num;
	int i;

	if (pinode->i_count > 1)
	{
		// at least 2 filename linking to this inode
		pinode->i_count--;
		return;
	}
	else
	{
		// i_count == 1
		if (pinode->di_number != 0)
		{
			/*write back the inode*/
			addr = DINODESTART + pinode->i_ino *DINODESIZ;
			memcpy(disk+addr, &pinode->di_number, DINODESIZ);
		}
		else
		{
			// no disk block linking to this inode	
			/*free the inode in the memory*/

			addr = DINODESTART + pinode->i_ino *DINODESIZ;
			memcpy(disk+addr, &pinode->di_number, DINODESIZ);
			ifree(pinode->i_ino);
		}
		
		free(pinode);
	}

	return;
}













