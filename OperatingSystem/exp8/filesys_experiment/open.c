#include <stdio.h>
#include "filesys.h"

// Ok
// functionality: open a file
// input: uid, filename, openmode
// output:
// return file descriptor, which is the index of struct user.u_ofile
// or NOINDEX
index_t open(uid_t uid, char *filename, unsigned short openmode)
{
	int i,j;

	// --------------------------------------
	// search user to match uid
	// user_sen is the index of struct user
	int user_sen;
	for (j=0; j<USERNUM; j++)
		if (user[j].u_uid == uid) 
			break;
	if (j == USERNUM)
	{
		printf("\nUser with uid:%d does not exist!\n ", uid);
		return NOINDEX;
	}
	user_sen = j;


	unsigned int dinodeid;
	dinodeid = namei(filename);
	if (dinodeid == NOINODE)   
	{
		printf("\nFile %s does not exist!\n", filename);
		return NOINDEX;
	}
 
	// filename exist
	// allocate memory inode
	struct inode *inode;
	inode = iget(dinodeid);
	

	// alloc the sys_ofile item
	for (i=0; i<SYSOPENFILE; i++) 
	{
		if(sys_ofile[i].f_inode->i_ino = inode->i_ino)
		{
			break;
		}
		
		if (sys_ofile[i].f_count == 0)
		{
			break;
		}
	}
	// i可以是已有的表项索引，也可以是空表项索引

	if (i == SYSOPENFILE)
	{
		printf("\nSystem open table is full!\n");
		iput(inode);
		return NOINDEX;
	}
	
	// alloc the user open file item
	for (j=0; j<NOFILE; j++)
		// u_ofile == SYSOPENFILE means null pointer
		if (user[user_sen].u_ofile[j] == SYSOPENFILE) 
			break;

	if (j == NOFILE)  
	{
		printf("\nUser open table is full!\n");
		iput(inode);
		return NOINDEX;
	}

	// 系统打开表和用户打开表均有空闲条目，进行更新

	// 如果inode原先不在系统打开表中	
	// i is the index of idle object in system open table
	sys_ofile[i].f_inode = inode;
	sys_ofile[i].f_mode = openmode;
	// 进程访问计数加１
	sys_ofile[i].f_count += 1;


	// 如果是追加内容，那么文件偏移等于当前文件大小
	if (openmode & FAPPEND)
		sys_ofile[i].f_off = inode->di_size;
	else
	// 否则，从头开始
		sys_ofile[i].f_off = 0;

	// set pointer
	user[user_sen].u_ofile[j] = i;  

	// return file descriptor, which is the index of struct user.u_ofile
	return j; 
}




