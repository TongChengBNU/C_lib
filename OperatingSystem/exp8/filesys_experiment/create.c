#include <stdio.h>
#include "filesys.h"

// Ok
// input: uid, filename, mode-access mode 9 bits
// output: file descriptor, also index of user open table -- u_ofile
index_t create(uid_t uid, char *filename, unsigned short mode)
{
	//printf("Cur path inode: %d\n", cur_path_inode->i_ino);

	struct inode *inode;
	// j: index of memory var user, which matching uid
	int i,j;
	// index in user matching uid
	int user_sen;

	// linearly search uid
	// return user_sen
	for (j=0; j<USERNUM; j++)   
		if (user[j].u_uid == uid) 
			break;
	if (j == USERNUM)
	{
		printf("\nNo correspond uid.\n ");
		return NOINDEX;
	}
	user_sen = j;


	// map filename into disk inode index
	int di_ino = namei(filename);
	if (di_ino != NOINODE)   
	{
		/*already existed*/

		// read disk inode into memory inode
		inode = iget(di_ino);
		// 0 means access denied;
		if (access(user_sen, inode, mode) == 0)
		{
			iput(inode);
			printf("\nCreate access denied;\n");
			return NOINDEX;
		}

		/* free all the block of the old file */
		for (i=0; i<size_to_block_num(inode->di_size); i++)
			bfree(inode->di_addr[i]);


		// ---------------------------
		for (i=0; i<SYSOPENFILE; i++)
			if (sys_ofile[i].f_inode == inode)
				sys_ofile[i].f_off = 0;

		for (j=0; j<NOFILE; j++)
		{
			// u_ofile[X] was inited as SYSOPENFILE
			if (user[user_sen].u_ofile[j] == SYSOPENFILE)
			{
				user[user_sen].u_uid = inode->di_uid;
				user[user_sen].u_gid = inode->di_gid;

				for (i=0; i<SYSOPENFILE; i++)
				{
					if (sys_ofile[i].f_count == 0)
					{
						user[user_sen].u_ofile[j] = i;
						sys_ofile[i].f_mode = mode;
					}
				}

				// return file descriptor, index in user
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

		// init
		for(int i=0; i<NADDR; i++)
		{
			inode->di_addr[i] = NOINDEX;
		}

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
		// 关联文件为新建的这个文件
		inode->di_number = 1;

		// search system open table where f.count = 0
		// 访问计数为0, 说明该表项为空
		for (i=0; i<SYSOPENFILE; i++)
			if (sys_ofile[i].f_count == 0)
				break; 
		if(i == SYSOPENFILE)
		{
			printf("System open table full!\n");
			return NOINDEX;
		}

		// user open table
		// u_ofile等于SYSOPENFILE, 说明该表项为空
		for (j=0; j<NOFILE; j++)  
			// u_ofile[X] was inited as SYSOPENFILE
			if (user[user_sen].u_ofile[j] == SYSOPENFILE)
				break;
		if(j == NOFILE)
		{
			printf("User open table full!\n");
			return NOINDEX;
		}

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




