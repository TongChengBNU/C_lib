#include <stdio.h>
#include "filesys.h"

//static struct dinode block_buf[BLOCKSIZ/DINODESIZ];

// Ok
// functionality: allocate disk inode
// output: 
struct inode * ialloc()
{
	// what if there is no inode available?????????
	struct inode *temp_inode;
	unsigned int cur_di;
	int i,count, block_end_flag;

	/* s_inode full */
	// NICINOD: 50
	if (filsys.s_pinode == NICINOD)  
	{
		// stack empty, need to update stack using new disk inode number 
		i=0; 
		count = 0;
		block_end_flag = 1; 
		filsys.s_pinode = NICINOD-1;
		// begin of next group
		cur_di = filsys.s_rinode;
		for(i=0; i<NICINOD; i++)
		{
			filsys.s_inode[i] = i+cur_di;
		}
		filsys.s_rinode += NICINOD;



		// comment by tong cheng
		/*
		while ((count < NICINOD) && (count <= filsys.s_ninode))
		{
			if (block_end_flag)
			{ 
				memcpy(block_buf, disk+DINODESTART + cur_di*DINODESIZ, BLOCKSIZ);
				block_end_flag = 0;
				i = 0;
			}

			//modified by xiao
			while (i < BLOCKSIZ/DINODESIZ)
			{
				cur_di ++;
				i++;
				
				if (i == BLOCKSIZ/DINODESIZ)
					block_end_flag = 1;
				else
				{
					if (block_buf[i].di_mode != DIEMPTY)
						continue;
					filsys.s_inode[filsys.s_pinode--] = cur_di;
					count++;
				}
			}
			
		}

		filsys.s_rinode = cur_di; */
	}

	unsigned int inode_ino = filsys.s_inode[filsys.s_pinode];
	struct dinode *dinode_ptr = (struct dinode *)malloc(sizeof(struct dinode));	
	dinode_ptr->di_uid = user_id;
	dinode_ptr->di_size = 0;
	// temp_inode sub disk inode is null
	// write back to achieve consistency
	memcpy(disk+DINODESTART+inode_ino*DINODESIZ,
	             dinode_ptr, sizeof(struct dinode));
	free(dinode_ptr);
	printf("Cur: %d\n", cur_path_inode->i_ino);
	temp_inode = iget(inode_ino);
	printf("Cur: %d\n", cur_path_inode->i_ino);

	filsys.s_pinode ++;
	filsys.s_ninode --;   
	filsys.s_fmod = SUPDATE; 

	return temp_inode;
} 

// Ok
// functionality: free disk inode
void ifree(unsigned int dinodeid)
{
	// increment the number of idle disk inode
	filsys.s_ninode ++;

	if (filsys.s_pinode != 0) 
	{
		// idle stack not full
		filsys.s_pinode--;
	}
	else   
	{
		//printf("idle stack full");
		// idle stack full
		filsys.s_rinode += NICINOD;
		filsys.s_pinode = NICINOD-1;
	}
	filsys.s_inode[filsys.s_pinode] = dinodeid;
	return;
}









/*
ifree(dinodeid)
unsigned int dinodeid;   //xiao
{
	filsys.s_ninode ++;
	if (filsys.s_pinode != NICINOD)         //not null
	{
		filsys.s_inode[filsys.s_pinode] = dinodeid;
		filsys.s_pinode++;
	}
	else   //full
	{
		if (dinodeid < filsys.s_rinode)
		{
			filsys.s_inode[NICINOD] = dinodeid;
			filsys.s_rinode = dinodeid;
		}
	}
}
 */





































