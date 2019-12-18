#include <stdio.h>
#include <string.h>
#include "filesys.h"

// OK
// functionality: init some memory var
void install()
{
	int i,j;

	/* 2. initialize the inode hash chain*/
	for (i=0; i<NHINO; i++)
		hinode[i].i_forw = NULL;

	/*3. initialize the sys_ofile*/
	for (i=0; i<SYSOPENFILE; i++)
	{
		// sys_ofile is global declared in main.c
		sys_ofile[i].f_count = 0;
		sys_ofile[i].f_inode = NULL;
	}

	/*4. initialize the user open table*/
	for (i=0; i<USERNUM; i++)
	{
		// user is global declared in main.c
		user[i].u_uid = 0;
		user[i].u_gid = 0;
		for (j=0; j<NOFILE; j++)
			user[i].u_ofile[j] = SYSOPENFILE+1;
	}

	// 5. read the main directory to initialize the 'dir'
	cur_path_inode = iget(1);
	dir.size = cur_path_inode->di_size/(sizeof(struct direct));

	// null the dir.direct
	for (i=0; i<DIRNUM; i++)
	{
		strcpy(dir.direct[i].d_name, "            ");
		dir.direct[i].d_ino = 0;
	}
 
	// read main dir from block #0
	memcpy(dir.direct, disk+DATASTART, 3*(sizeof(struct direct)));
	

	return;
}

