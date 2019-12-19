#include <stdio.h>
#include <string.h>
#include "filesys.h"

// OK
// functionality: show current directory
void _dir()
{
	unsigned short di_mode;
	int i, one;
	int j, k;          //xiao  
	struct inode *temp_inode;

	printf("\nCURRENT DIRECTORY:\n"); 

	for (i=0; i<dir.size; i++)
	{ 
		// a deleted file should have no corresponding inode
		//if (dir.direct[i].d_ino != DIEMPTY)  
		if (dir.direct[i].d_ino != NOINODE)  // by Tong Cheng
		{
			// 1. name
			printf("%-14s", dir.direct[i].d_name); 

			// 2. inode number
			temp_inode = iget(dir.direct[i].d_ino);
			printf("inodex_ino:%d ", temp_inode->i_ino);
			//printf("inodex_ino:%d ", dir.direct[i].d_ino);
			 
			// 3. access vector
			// dimode binary representation
			// rxzrxzrxz
			// 1 is file while 0 is directory
			if(temp_inode->di_mode>>9)
				printf("d");
			else
				printf("-");
			di_mode = temp_inode->di_mode & 00777;
			for (j=0; j<9; j++)
			{
				one = di_mode%2;
				di_mode = di_mode/2;

				if (one)  
					switch(j%3){
						case 0:
							printf("r");
							break;
						case 1:
							printf("w");
							break;
						default:
							printf("x");
							break;
					}
				else
					printf("-");
			}

			// 4. show additional info
			if (!(temp_inode->di_mode>>9))   
			{
				// display file info
				printf(" %-5d ", temp_inode->di_size);
				// show numbers of disk block this file occupies
				printf("Disk block chain:"); 

				for (k=0; k<temp_inode->di_size/BLOCKSIZ+1; k++)
					printf("%3d", temp_inode->di_addr[k]);
				printf("\n");
			}
			else
			{
				// display directory info
				printf(" <dir>\n");
			}
			iput(temp_inode);
		} 
	}
	return;
}


// OK
// functionality: make directory
// input: new dirname
void mkdir(char *dirname)
{
	// inode id, idle index in dir.direct
	int dirid, dirpos;
	struct inode *inode;

	dirid = namei(dirname);

	// if dirid = -1, then dirname not found;
	// if dirname found, either a directory or file
	if (dirid != -1)
	{
		inode = iget(dirid);
		// dir: 001X XXXX XXXX
		if (inode->di_mode>>9)
			printf("\n%s directory already existed!!", dirname); //xiao
		else
			printf("\n%s is a file name, can't create a dir the same name", dirname);
		iput(inode);
		return;
	}

	// if dirname not found, then new directory
	// find a idle index in dir.direct
	dirpos = iname(dirname);
	// allocate disk inode 
	inode = ialloc();
	dir.direct[dirpos].d_ino = inode->i_ino;
	dir.size++; 
 
	/*fill the new dir buf*/
	// set a buffer size of BLOCKSIZ
	struct direct buf[BLOCKSIZ/sizeof(struct direct)];
	memset(buf, 0x00, BLOCKSIZ);  //added by xiao
	strcpy(buf[0].d_name, "..");
	buf[0].d_ino = cur_path_inode->i_ino;
	strcpy(buf[1].d_name, ".");
	// global cur_path_inode
	buf[1].d_ino = inode->i_ino;
	// allocate data block, block is the number of data block
	unsigned int block_id = balloc();
	// write buffer into data block with id=block_id 
	// if BLOCKSIZ 不能整除目录项大小，那么这里会出现内存越界
	// 但是，一个块内恰好能放32个目录项
	memcpy(disk+ DATASTART+ block_id*BLOCKSIZ, buf, BLOCKSIZ);

	inode->di_size = 2*sizeof(struct direct);
	inode->di_number = 1; 
	// directory mode
	// user is a global container
	inode->di_mode = user[user_id].u_default_mode | DIDIR;
	inode->di_uid = user[user_id].u_uid;
	inode->di_gid = user[user_id].u_gid;
	inode->di_addr[0] = block_id;

	iput(inode);

	return;
}

// Ok
// functionality: change directory
// input: name to change to 
void chdir(char *dirname)
{
	// search dir
	int dirid = namei(dirname);
	if (dirid == -1)
	{
		printf("\n%s does not existed\n", dirname);
		return;
	} 
	// read disk inode into memory inode
	struct inode *inode = iget(dirid); 

	cur_path_inode = inode;

	/*read the change dir from disk*/
	// compute upper bound of loop
	int temp = (inode->di_size%BLOCKSIZ)?1:0;
	unsigned short j=0;
	for (int i=0; i<inode->di_size/BLOCKSIZ+temp; i++)
	{
		memcpy(&dir.direct[j], disk+DATASTART+inode->di_addr[i]*BLOCKSIZ, BLOCKSIZ);
		j += BLOCKSIZ/(sizeof(struct direct));
	}
		

	dir.size = cur_path_inode->di_size/(sizeof(struct direct));
	
	return;  
} 



 
 





































