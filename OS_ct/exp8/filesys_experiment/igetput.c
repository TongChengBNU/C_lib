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
		pinode->i_count--;
		return;
	}
	else
	{
		if (pinode->di_number != 0)
		{
			/*write back the inode*/
			addr = DINODESTART + pinode->i_ino *DINODESIZ;
			/*
			fseek(fd, addr, SEEK_SET);
			fwrite(&pinode->di_number, DINODESIZ, 1, fd);
			*/
			memcpy(disk+addr, &pinode->di_number, DINODESIZ);
		}
		else
		{
			
			//added by xiao 
			addr = DINODESTART + pinode->i_ino *DINODESIZ;
			/*
			fseek(fd, addr, SEEK_SET);
			fwrite(&pinode->di_number, DINODESIZ, 1, fd);
			*/
			memcpy(disk+addr, &pinode->di_number, DINODESIZ);

			/* rm the inode & the block of the file in the disk*/
			#if 0
			block_num = pinode->di_size/BLOCKSIZ;
			for (i=0; i<block_num; i++)
				//balloc(pinode->di_addr[i]);
				bfree(pinode->di_addr[i]);
			#endif
			ifree(pinode->i_ino);
		}

		/*free the inode in the memory*/
		/*
		if (pinode->i_forw == NULL)
			pinode->i_back->i_forw = NULL;
		else
		{
			pinode->i_forw->i_back = pinode->i_back;
			pinode->i_back->i_forw = pinode->i_forw;
		}*/

		//added by xiao 
		{
			int inodeid;
			inodeid = (pinode->i_ino)  % NHINO;

			if (hinode[inodeid].i_forw == pinode)
			{
				hinode[inodeid].i_forw = pinode->i_forw;
				if (pinode->i_forw)
					pinode->i_forw->i_back = pinode->i_forw;
			}
			else
			{
				pinode->i_back->i_forw = pinode->i_forw;
				if (pinode->i_forw)
					pinode->i_forw->i_back = pinode->i_back;
			}
		}
		//end by xiao
		
		free(pinode);
			
	}

	return;
}













