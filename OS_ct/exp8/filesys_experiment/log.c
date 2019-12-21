#include <stdio.h>
#include <string.h>
#include "filesys.h"

// Ok
// input: uid, password
// output: 1-success, 0-failed
int login(uid_t uid, char *passwd)
{
	int i,j;

	for (i=0; i<PWDNUM; i++)
	{
		// i is the index of matching struct pwd
		if ((uid == pwd[i].p_uid) && (!strcmp(passwd, pwd[i].password)))
		{
			// linearly search for a idle user
			for (j=0; j<USERNUM; j++)   
				if (user[j].u_uid == 0) 
					break;
 
			if (j == USERNUM)
			{
				printf("\ntoo much user in the systemm, waited to login\n");
				return 0;
			}
			else
			{
				// j is the index of idle struct user
				user[j].u_uid = uid;
				user[j].u_gid = pwd[i].p_gid; 
				// use this mode for new directory mode
				user[j].u_default_mode = DEFAULTMODE;
			}
			break;
		}
	}

	if (i == PWDNUM)
	{
		printf("\nUser does not exist or incorrect password!\n");
		return 0;
	}
	else
	{
		printf("\nLogin success!\n");
		return 1;
	}

}


// Ok
// input: uid
// output: 1-success, 0-failed
int logout(uid_t uid)
{
	int i,j,sys_no;
	struct inode *inode;

	// search current active users in struct user matching uid
	for (i=0; i<USERNUM; i++)
		if (uid == user[i].u_uid)
			break;

	if (i == USERNUM)
	{
		printf("\nNo such user!\n");
		return 0;
	}

	// i is the index of logout user in struct user
	// clear user open table
	for (j=0; j<NOFILE; j++)
	{
		// u_ofile[X] = SYSOPENFILE means null pointer
		if (user[i].u_ofile[j] != SYSOPENFILE)
		{
			/* iput the inode free the sys_ofile and clear the user_ofile*/
			sys_no = user[i].u_ofile[j];
			// if f_count == 0, free memory inode in sys open table
			if(--sys_ofile[sys_no].f_count)
			{
				// free memory inode
				inode = sys_ofile[sys_no].f_inode;
				iput(inode);
			}
			user[i].u_ofile[j] = SYSOPENFILE;
		}
	}

	printf("\nLogout success!\n");
	return 1;
}




































