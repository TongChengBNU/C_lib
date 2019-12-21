#include <stdio.h>
#include "filesys.h"


// Ok
// functinality: free sys_ofile and user, write back super block and say GOODBYE
void halt()
{
	int i,j;

	/*1. write back the current inode */
	iput(cur_path_inode);


	/*2. free sys_ofile and user */
	for (i=0; i<SYSOPENFILE; i++)
	{
		if(sys_ofile[i].f_count != 0)
		{
			sys_ofile[i].f_count = 0;
			iput(sys_ofile[i].f_inode);
		}
	}

	for (i=0; i<USERNUM; i++)
	{
		if (user[i].u_uid != 0)
		{
			for (j=0; j<NOFILE;j++)
			{
				if (user[i].u_ofile[j] != SYSOPENFILE)
				{
					// j is the file descriptor
					close(user[i].u_uid, j);
					user[i].u_ofile[j] = SYSOPENFILE;
				}
			}
		}
	}

	// write back the filesys to the disk
	memcpy(disk+BLOCKSIZ, &filsys, sizeof(struct filsys));

	// say GOOD BYE to all the user
	printf("\nGood Bye. See You Next Time. Please turn off the switch\n");
	exit(0);
}





























