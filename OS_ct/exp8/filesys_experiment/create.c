#include <stdio.h>
#include "filesys.h"

// 90% find the to be continued;
// input: user_id-index of user in global 'user', filename, mode-access mode 9 bits
// output: file descriptor, also index of user open table -- u_ofile
unsigned short create(unsigned int user_id, char *filename, unsigned short mode)
{
	struct inode *inode;
	// j: index of memory var user, which matching user_id
	int i,j;
	// index in user matching user_id
	int user_sen;

	// linearly search user_id
	// return user_sen
	for (j=0; j<USERNUM; j++)   
		if (user[j].u_uid == user_id) 
			break;
	if (j == USERNUM)
	{
		printf("\n have no correspond user_id.\n ");
		return -1;
	}
	user_sen = j;


	// map filename into disk inode index
	di_ino = namei(filename);
	if (di_ino != -1)   
	{
		/*already existed*/

		// read disk inode into memory inode
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


		// ---------------------------
		// to be continued
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
		// ---------------------------
	}
	else
	{
		unsigned int dir_ith, di_ino;
	    /*not existed before*/
		inode = ialloc();
		// 'dir_ith' is the index of an idle directory object in current dir
		// should be iname, not namei
		dir_ith = iname(filename);

		// update 'dir'(current directory)
		dir.size++; 
		dir.direct[dir_ith].d_ino = inode->i_ino;

		inode->di_mode = (mode & 0777) | DIFILE;
		inode->di_uid = user[user_sen].u_uid;
		inode->di_gid = user[user_sen].u_gid; 
		inode->di_size = 0;
		inode->di_number = 0;

		// search system open table where f.count = 0
		// 访问计数为0, 说明该表项为空
		for (i=0; i<SYSOPENFILE; i++)
			if (sys_ofile[i].f_count == 0)
				break; 

		// user open table
		// u_ofile等于SYSOPENFILE, 说明该表项为空
		for (j=0; j<NOFILE; j++)   //xiao
			// u_ofile[X] was inited as SYSOPENFILE
			if (user[user_sen].u_ofile[j] == SYSOPENFILE)
				break;

		// j is index of idle u_ofile
		// i is index of idle sys_ofile

		user[user_sen].u_ofile[j] = i;
		sys_ofile[i].f_mode = mode;
		// 访问计数为 1
		sys_ofile[i].f_count = 1;  
		// offset is 0
		sys_ofile[i].f_off = 0;
		sys_ofile[i].f_inode = inode;

		// return index in user open table
		// which is the file descriptor
		return j;
	}
}




