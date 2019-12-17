#include <stdio.h>
#include <string.h>
#include "filesys.h"

// show current directory
void _dir()
{
	unsigned short di_mode;
	int i, one;
	int j, k;          //xiao  
	struct inode *temp_inode;

	printf("\nCURRENT DIRECTORY:\n"); 

	for (i=0; i<dir.size; i++)
	{ 
		// a deleted file should have DIEMPTY
		if (dir.direct[i].d_ino != DIEMPTY)  
		{
			printf("%-14s", dir.direct[i].d_name); 
			temp_inode = iget(dir.direct[i].d_ino);
			di_mode = temp_inode->di_mode & 00777;
			 
			// access vector
			// dimode binary representation
			// rxzrxzrxz
			for (j=0; j<9; j++)
			{
				one = di_mode%2;
				di_mode = di_mode/2;

				if (one)  
					printf("x");
				else
					printf("-");
			}

			if (temp_inode->di_mode & DIFILE)   //by xiao
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


// make directory
void mkdir(char *dirname)
{
	int dirid, dirpos;
	struct inode *inode;
	struct direct buf[BLOCKSIZ/(DIRSIZ+4)];
	unsigned int block;

	dirid = namei(dirname);
	// if dirid = -1, then dirname not found;
	if (dirid != -1)
	{
		inode = iget(dirid);
		//if (inode->di_mode & DIDIR)
		if (!(inode->di_mode>>9))
			printf("\n%s directory already existed!!", dirname); //xiao
		else
			printf("\n%s is a file name, can't create a dir the same name", dirname);
		iput(inode);
		return;
	}

	dirpos = iname(dirname);
	inode = ialloc(); 
	//inode->i_ino = dirid;
	
	dir.direct[dirpos].d_ino = inode->i_ino;
	dir.size++; 
 
	/*fill the new dir buf*/
	memset(buf, 0x00, BLOCKSIZ);  //added by xiao
	strcpy(buf[0].d_name,".");
	//buf[0].d_ino = dirid;  //by xiao
	buf[0].d_ino = inode->i_ino;
	strcpy(buf[1].d_name, "..");
	buf[1].d_ino = cur_path_inode->i_ino;

	block = balloc();
	/*
	fseek(fd, DATASTART+block*BLOCKSIZ, SEEK_SET);
	fwrite(buf, 1, BLOCKSIZ, fd);
	*/
	memcpy(disk+DATASTART+block*BLOCKSIZ, buf, BLOCKSIZ);

	inode->di_size = 2*(DIRSIZ+4);
	inode->di_number = 1; 
	// directory mode
	inode->di_mode = user[user_id].u_default_mode;
	inode->di_uid = user[user_id].u_uid;
	inode->di_gid = user[user_id].u_gid;
	inode->di_addr[0] = block;

	iput(inode);

	return;
}


// change directory
void chdir(char *dirname)
{
	unsigned int dirid;
	struct inode *inode; 
	unsigned short block;
	int i,j,low=0, high=0;

	dirid = namei(dirname);
	if (dirid == NULL)
	{
		printf("\n%s does not existed\n", dirname);
		return;
	} 
	inode = iget(dirid); 
/*
	if (!access(user_id, inode, user[user_id].u_default_mode))
	{
		printf("\nhas not access to the directory %s",dirname);
		iput(inode); 
		return;
	}
*/
	/*pack the current directory*/
	#if 0
	for (i=0; i<dir.size; i++)
	{
		for (; j<DIRNUM; j++)
			if (dir.direct[j].d_ino == 0) 
				break;
		memcpy(&dir.direct[i], &dir.direct[j], DIRSIZ+4);  //xiao
		dir.direct[j].d_ino = 0;
	}

	/* write back the current directory */
	for (i=0; i<cur_path_inode->di_size/BLOCKSIZ+1; i++)
		bfree(cur_path_inode->di_addr[i]);

	for (i=0; i<dir.size; i+=BLOCKSIZ/(DIRSIZ+4))
	{
		block = balloc();
		cur_path_inode->di_addr[i] = block;
		/*
		fseek(fd, DATASTART+block*BLOCKSIZ, SEEK_SET);
		fwrite(&dir.direct[i], 1, BLOCKSIZ, fd);
		*/
		memcpy(disk+DATASTART+block*BLOCKSIZ, &dir.direct[i], BLOCKSIZ);
	}
	#endif

	memcpy(disk+DATASTART+cur_path_inode->di_addr[0]*BLOCKSIZ, &dir.direct[0], BLOCKSIZ);  //for a while

	cur_path_inode->di_size = dir.size*(DIRSIZ+4);
	iput(cur_path_inode); 

	cur_path_inode = inode;

	/*read the change dir from disk*/
	j=0; 

	for (i=0; i<inode->di_size/BLOCKSIZ+1; i++)
	{
		/*
		fseek(fd, DATASTART+inode->di_addr[i]*BLOCKSIZ, SEEK_SET);
		fread(&dir.direct[j], 1, BLOCKSIZ, fd);
		*/
		memcpy(&dir.direct[j],  disk+DATASTART+inode->di_addr[i]*BLOCKSIZ, BLOCKSIZ);
		j+=BLOCKSIZ/(DIRSIZ+4);
	}

	//added by xiao
	dir.size = cur_path_inode->di_size/(DIRSIZ+4);
	for (i=dir.size; i<DIRSIZ; i++) 
		dir.direct[i].d_ino = 0; 
	
	//end by xiao

	return;  
} 



 
 





































