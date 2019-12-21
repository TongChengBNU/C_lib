#include <stdio.h>
#include <string.h>
#include "filesys.h"

// Ok
// functionality: delete a file by di_number-- and d_ino = NOINODE
void delete(char *filename)
{
	int dinodeid;
	struct inode *inode;
	unsigned short mark_delete_node=0;

	dinodeid = namei(filename);
	// if dinodeid != -1, then read disk inode into memory inode
	if (dinodeid != NOINODE)
		inode = iget(dinodeid);
	else
	{
		printf("File %s does not exist;\n", filename);
		return;
	}

	// 关联文件数-1，如果没有关联的文件，那么释放掉数据块和磁盘索引节点
	if(!(--inode->di_number))
		mark_delete_node = 1;
	
	printf("File to be deleted: inode->di_number %d\n", inode->di_number);
	// if di_number == 0, free data blocks and disk inode
	if(mark_delete_node)
	{
		for(int i=0; i<NADDR; i++)
		{
			if(inode->di_addr[i] != NOINDEX)
			{
				printf("Free block number: %d\n", inode->di_addr[i]);
				bfree(inode->di_addr[i]);
				inode->di_addr[i] = NOINDEX;
			}
			else
				// 一旦出现一个数据块没用，后面的都没用
				break;
		}
		// release memory inode
		iput(inode);
		ifree(dinodeid);
	}


	// delete the link between filename and inode
	for(int i=0; i<dir.size; i++)
	{
		if(!(strcmp(dir.direct[i].d_name, filename)))
		{
			dir.direct[i].d_ino = NOINODE;
			break;
		}
	}
	return;
}

