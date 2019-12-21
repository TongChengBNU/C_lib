#include <stdio.h>
#include <string.h>
#include "filesys.h"

// Ok
// mapp filename into disk inode ID
// input: file or directory name
// output: -1 or disk inode ID
int namei(char *name)
{
	for (int i=0; i<dir.size; i++)
	{
		// disk inode 0# is empty
		if ((!strcmp(dir.direct[i].d_name, name)) && (dir.direct[i].d_ino != 0))
		{
			return (dir.direct[i].d_ino);  
		}
	}
	// not found
	return NOINODE;
} 
   
// Ok
// input: new name
// output: return -1 or a index of directory object with no connection to inode
int iname(char *name)
{
	int i, notfound = 1;

	// search dir
	for (i=0; ((i<DIRNUM) && (notfound)); i++)
	{
		if (dir.direct[i].d_ino == 0)
		{
			notfound = 0;
			break;
		}
	}

	if (notfound)
	{
		// every dir.direct[X] has a inode, which means that dir is full
		printf("\nThe current directory is full!!!\n");
		return -1;
	}
	else
	{
		strcpy(dir.direct[i].d_name, name); 
		// return a index of directory object with no connection to inode
		return i;
	} 
}










































