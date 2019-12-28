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

			// 2. read disk inode into memory inode
			temp_inode = iget(dir.direct[i].d_ino);
			printf("inodex_ino:%d ", temp_inode->i_ino);


			 
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
				int temp = ((temp_inode->di_size % BLOCKSIZ)?1:0);
				for (k=0; k<(temp_inode->di_size/BLOCKSIZ)+temp; k++)
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
	if (dirid != NOINODE)
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
 
	// fill the new dir buf
	// set a buffer size of BLOCKSIZ
	struct direct buf[BLOCKSIZ/sizeof(struct direct)];
	memset(buf, 0x00, BLOCKSIZ);  //added by xiao
	strcpy(buf[0]. d_name, "..");
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


	// 更新当前目录的磁盘数据
	// 先写后读, 写的时候注意尾部数据，因为内存变量超出读取，会内存访问出错；但读的时候，因为空间已经预分配，因此可以整块读取
	// 当前目录的内容写入相应数据块
	inode = iget(namei("."));
	// 计算当前目录需要多少个盘块
	int i=0;
	int temp = ((dir.size * (sizeof(struct direct))) % BLOCKSIZ)?1:0;
	unsigned short block_num_need = (dir.size * (sizeof(struct direct))) / BLOCKSIZ + temp;
	unsigned short block_num_exist = (inode->di_size / BLOCKSIZ) + (inode->di_size % BLOCKSIZ > 0)?1:0;
	if(block_num_exist < block_num_need)
	{
		unsigned short block_num_start = block_num_exist;	
		for(i=0; i<(block_num_need - block_num_exist); i++)
		{
			inode->di_addr[block_num_start+i] = balloc();
		}
		// 补充物理块完毕
	}
	unsigned short j=0;
	for(i=0; i<block_num_need-1; i++)
	{
		memcpy(disk+DATASTART+inode->di_addr[i]*BLOCKSIZ, &dir.direct[j], BLOCKSIZ);
		j += (BLOCKSIZ)/(sizeof(struct direct));
	}
	// 处理数据尾部
	memcpy(disk+DATASTART+inode->di_addr[i]*BLOCKSIZ, &dir.direct[j], (sizeof(struct direct))*(dir.size-j));
	inode->di_size = dir.size * (sizeof(struct direct));
	// free memory inode
	iput(inode);

	return;
}

// Ok
// functionality: change directory
// input: name to change to 
void chdir(char *dirname)
{
	struct inode *inode;
	// search dir
	int dirid = namei(dirname);
	if (dirid == NOINODE)
	{
		printf("\n%s does not existed\n", dirname);
		return;
	} 
	
	// 当前内存节点释放
	//iput(cur_path_inode);

	int j, i;
	unsigned short block_num_need;

	// 当前目录写回磁盘
	j = 0;
	inode = cur_path_inode;
	printf("write inode id: %d\n", inode->i_ino);
	block_num_need = size_to_block_num(dir.size * sizeof(struct direct));	
	for (i=0; i<block_num_need; i++)
	{
		memcpy(disk+DATASTART+inode->di_addr[i]*BLOCKSIZ, &dir.direct[j], BLOCKSIZ);
		j += BLOCKSIZ/(sizeof(struct direct));
	}


	// 新目录读入dir
	// read disk inode into memory inode
	inode = iget(dirid); 
	printf("read inode id: %d\n", inode->i_ino);
	cur_path_inode = inode;

	//printf("\ndirid: %d   size: %d\n", dirid, inode->di_size);
	//printf("cur: %d\n", cur_path_inode->i_ino);

	/*read the change dir from disk*/
	// 确定目录数据是否为整块
	// compute upper bound of loop
	// 读数据可以整块读入
	j=0;
	block_num_need = size_to_block_num(inode->di_size);
	for (i=0; i<block_num_need; i++)
	{
		memcpy(&dir.direct[j], disk+DATASTART+inode->di_addr[i]*BLOCKSIZ, BLOCKSIZ);
		j += BLOCKSIZ/(sizeof(struct direct));
	}
		

	//printf("\n Read success;\n");
	//dir.size = (cur_path_inode->di_size)/(sizeof(struct direct));
	//printf("dir size: %d\n", dir.size);

	//for(i=0;i<4;i++)
	//{
    //	printf("%s\n", dir.direct[i].d_name);
	//}
	
	
	return;  
} 



 
 





































