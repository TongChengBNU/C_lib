#include <stdio.h>
#include "filesys.h"


unsigned short create(unsigned int user_id, char *filename, unsigned short mode)
{
	unsigned int di_ith, di_ino;
	struct inode *inode;
	int i,j;
	int user_sen;

	// linearly search user_id
	//added by xiao user_id-->user_sen
	for (j=0; j<USERNUM; j++)   //xiao
		if (user[j].u_uid == user_id) 
			break;
	if (j == USERNUM)
	{
		printf("\n have no correspond user_id.\n ");
		return -1;
	}
	user_sen = j;
	//end by xiao


	// map filename into disk inode index
	di_ino = namei(filename);
	if (di_ino != -1)    /*already existed*/
	{
		// disk inode
		inode = iget(di_ino);
		// 0 means access denied;
		if (access(user_sen, inode, mode) == 0)
		{
			iput(inode);
			printf("\nCreate access denied;\n");
			return -1;
		}

		/* free all the block of the old file */
		for (i=0; i<inode->di_size/BLOCKSIZ+1; i++)
			bfree(inode->di_addr[i]);

		/* to do: add code here to update the pointer of the sys_ofile*/
		for (i=0; i<SYSOPENFILE; i++)
			if (sys_ofile[i].f_inode == inode)
				sys_ofile[i].f_off = 0;

		for (i=0; i<NOFILE; i++)
		{
			if (user[user_sen].u_ofile[i] == SYSOPENFILE+1)
			{
				user[user_sen].u_uid = inode->di_uid;
				user[user_sen].u_gid = inode->di_gid;

				for (j=0; j<SYSOPENFILE; j++)
					if (sys_ofile[j].f_count == 0)   //xiao
					{
						user[user_sen].u_ofile[i] = j;
						sys_ofile[j].f_flag = mode;
					}

				return j;
			}
		}
	}
	else   /*not existed before*/
	{
		inode = ialloc();
		// should be iname, not namei
		di_ith = iname(filename);

		// update 'dir'(current directory)
		dir.size++; 
		dir.direct[di_ith].d_ino = inode->i_ino;

		inode->di_mode = mode;
		inode->di_uid = user[user_sen].u_uid;
		inode->di_gid = user[user_sen].u_gid; 
		inode->di_size = 0;
		// ref file number 0 or 1?
		inode->di_number = 0;
		//inode->di_number = 1; 

		// system open table
		for (i=0; i<SYSOPENFILE; i++)
			if (sys_ofile[i].f_count == 0)
				break; 

		// user open table
		for (j=0; j<NOFILE; j++)   //xiao
			// why SYSOPENFILE + 1??????
			if (user[user_sen].u_ofile[j] == SYSOPENFILE+1)
				break;

		user[user_sen].u_ofile[j] = i;
		sys_ofile[i].f_flag = mode;
		sys_ofile[i].f_count = 1;  //xiao 0-->1 
		sys_ofile[i].f_off = 0;
		sys_ofile[i].f_inode = inode;

		// return index in user open table
		return j;
	}
}




