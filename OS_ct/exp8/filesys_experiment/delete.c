#include <stdio.h>
#include <string.h>
#include "filesys.h"

// how to denote a file has been deleted?
void delete(char *filename)
{
	unsigned int dinodeid;
	struct inode *inode;

	dinodeid = namei(filename);
	// if dinodeid == -1, then filename does not exist
	if (dinodeid != -1)
		inode = iget(dinodeid);
	inode->di_number--;
	//printf("File to be deleted: inode->di_number %d\n", inode->di_number);
	iput(inode);


	// -------- added by Tong Cheng
	// delete the link between filename and inode
	for(int i=0; i<dir.size; i++)
	{
		if(!(strcmp(dir.direct[i].d_name, filename)))
		{
			dir.direct[i].d_ino = -1;
			break;
		}
	}
	return;
}

