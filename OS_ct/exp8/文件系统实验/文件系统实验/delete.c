#include <stdio.h>
#include "filesys.h"

void delete(char *filename)
{
	unsigned int dinodeid;
	struct inode *inode;

	dinodeid = namei(filename);
	if (dinodeid != NULL)
		inode = iget(dinodeid);
	inode->di_number--;
	iput(inode);
	return;
}











