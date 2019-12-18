#include <stdio.h>
#include <string.h>
#include "filesys.h"

// show current directory
// OK
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


// make directory
void mkdir(char *dirname)
{
	// inode id, idle index in dir.direct
	int dirid, dirpos;
	struct inode *inode;
	struct direct buf[BLOCKSIZ/sizeof(struct direct)];
	unsigned int block;

	dirid = namei(dirname);

	// if dirid = -1, then dirname not found;
	// if dirname found
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
	// generate inode with update
	inode = ialloc(); 
	dir.direct[dirpos].d_ino = inode->i_ino;
	dir.size++; 
 
	/*fill the new dir buf*/
	memset(buf, 0x00, BLOCKSIZ);  //added by xiao
	strcpy(buf[0].d_name,".");
	buf[0].d_ino = inode->i_ino;
	strcpy(buf[1].d_name, "..");
	// global cur_path_inode
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
	inode->di_mode = user[user_id].u_default_mode | DIDIR;
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
	if (dirid == -1)
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



 
 





































