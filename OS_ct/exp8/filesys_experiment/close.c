#include <stdio.h>
#include "filesys.h"

// Ok
// functionality: close a file
// input: uid, cfd-current file descriptor 
// output:
status_t close(uid_t uid, unsigned short cfd)
{
	// --------------------------------------
	// search user to match uid
	// user_sen is the index of struct user
	int j, user_sen;
	for (j=0; j<USERNUM; j++)
		if (user[j].u_uid == uid) 
			break;
	if (j == USERNUM)
	{
		printf("\nUser with uid:%d does not exist!\n ", uid);
		return ERROR;
	}
	user_sen = j;

	struct inode *inode;
 
	inode = sys_ofile[user[user_sen].u_ofile[cfd]].f_inode; 
	iput(inode);
	sys_ofile[user[user_sen].u_ofile[cfd]].f_count -- ;
	user[user_sen].u_ofile[cfd] = SYSOPENFILE;

	return SUCCESS; 
}









