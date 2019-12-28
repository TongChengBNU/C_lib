#include <stdio.h>
#include "filesys.h"

//-----------------------------------------
// Functionality:
// init password array buffer;
// init system super block;
//-----------------------------------------
void format()
{
	// every buffer should be no more than 1 block
	
	struct inode *inode;
	// every block could contain BlOCKSIZ/(sizeof(struct direct)) struct direct;
	// ------------ DIRSIZ+4 is so arcane -.-!
	// struct direct dir_buf[BLOCKSIZ/(DIRSIZ+4)];
	struct direct dir_buf[BLOCKSIZ/(sizeof(struct direct))];

	// every block could contain BlOCKSIZ/(sizeof(struct pwd)) struct pwd;
	// ------------ PWDSIZ+4 is so arcane -.-!
	//struct pwd passwd[BLOCKSIZ/(PWDSIZ+4)];
	struct pwd passwd[PWDNUM];

	//	struct filsys;  xiao
	unsigned int block_buf[BLOCKSIZ/sizeof(int)];

	char *buf;
	int i,j;

	// disk is a global variable declared in main.c
	// there are (DINODEBLK+FILEBLK+2) disk block
	// Preparation: initialize the memory to 0x00
	memset(disk, 0x00, ((2+DINODEBLK+FILEBLK)*BLOCKSIZ));


	/* 0.initialize the passwd */
	// 5 users in total
	passwd[0].p_uid = 2116;
	passwd[0].p_gid = 03;
	strcpy(passwd[0].password, "dddd");

	passwd[1].p_uid = 2117;
	passwd[1].p_gid = 03;
	strcpy(passwd[1].password, "bbbb");

	passwd[2].p_uid = 2118;
	passwd[2].p_gid = 04;
	strcpy(passwd[2].password, "abcd");  

	passwd[3].p_uid = 2119;
	passwd[3].p_gid = 04;
	strcpy(passwd[3].password, "cccc");

	passwd[4].p_uid = 2120;
	passwd[4].p_gid = 05;
	strcpy(passwd[4].password, "eeee");


	// --------------------------------------------------------------------------
	/* 1. creat the main directory
	 * and its sub dir etc 
	 * and the file password */

	// 0 inode for deleting link
	// for what ?????????
	inode = iget(0);   /* 0 empty dinode id*/
	inode->di_type = 100;  // empty dinode
	inode->di_number = 1;
	iput(inode);

	// inode 1#: main dir
	inode = iget(1);   
	inode->di_mode = DEFAULTMODE | DIDIR;
	// 关联文件为 /
	inode->di_number = 1;
	inode->di_size = 3*sizeof(struct direct);
	// block 0# is used by the main directory
	inode->di_addr[0] = 0; 
	
	strcpy(dir_buf[0].d_name, "..");
	dir_buf[0].d_ino = 1;
	strcpy(dir_buf[1].d_name, ".");
	dir_buf[1].d_ino = 1;
	strcpy(dir_buf[2].d_name,"etc");
	dir_buf[2].d_ino = 2;

	// write content into block 0#
	// put 3 element in direct buffer into disk
	memcpy(disk+DATASTART, dir_buf, 3*(sizeof(struct direct)));
	iput(inode);


	// inode 2#: etc dir 
	inode = iget(2); 
	inode->di_mode = DEFAULTMODE | DIDIR;
	// 关联文件为 etc
	inode->di_number = 1;
	inode->di_size = 3*sizeof(struct direct);
	// block 1# is used by the etc directory
	inode->di_addr[0] = 1;
	
	strcpy(dir_buf[0].d_name,"..");
	dir_buf[0].d_ino = 1;
	strcpy(dir_buf[1].d_name,".");
	dir_buf[1].d_ino = 2;
	strcpy(dir_buf[2].d_name,"password");
	dir_buf[2].d_ino = 3;

	// write content into block 1#
	memcpy(disk+DATASTART+BLOCKSIZ*1, dir_buf, 3*(sizeof(struct direct)));
	iput(inode);


	// inode 3#: password dir 
	inode = iget(3); 
	inode->di_mode = DEFAULTMODE | DIFILE;
	// 关联文件为 password
	inode->di_number = 1;
	inode->di_size = BLOCKSIZ;
	// block 2# is used by the password file
	inode->di_addr[0] = 2;

	// Besides first 5 pwds, set others to Null
	for (i=5; i<PWDNUM; i++)
	{
		passwd[i].p_uid = 0;
		passwd[i].p_gid = 0;
		strcpy(passwd[i].password, "            ");
	}

	// write content into block 2#
	// passwd is a global array
	memcpy(disk+DATASTART+BLOCKSIZ*2, passwd, BLOCKSIZ);

	
	// put buffer passwd into memory variable pwd for easy access
	// maybe a redundancy
	memcpy(pwd, passwd, 32*sizeof(struct pwd));

	iput(inode);
	// --------------------------------------------------------------------------







	// --------------------------------------------------------------------------
	/*2. initialize the system super block */

	// set number of inode block 
	filsys.s_isize = DINODEBLK;
	// set number of data block
	filsys.s_fsize = FILEBLK;

	// set number of idle block, used 3 blocks above
	filsys.s_nfree = FILEBLK - 3;
	// set ptr of idle block
	filsys.s_pfree = 0;	
	// 成组链接法
	// init stack of idle block
	for(i=0; i<NICFREE; i++)
	{
		filsys.s_free[i] = 3+i;
	}
	// NICFREE个盘块为1组，将下一组的盘块号存在最后1块里
	unsigned short block_num_start = 3;
	unsigned short block_num = filsys.s_fsize - block_num_start;
	unsigned short group_num = block_num/NICFREE;
	// in ballfre.c static var
	unsigned int *block_buf_ptr = block_buf;
	unsigned short last_group_block_num = block_num % NICFREE;
	unsigned int block_num_write;
	if(last_group_block_num > 0)
	{
		// 写最后一组的号
		memset(block_buf_ptr, 0x00, BLOCKSIZ);
		for(int i=0; i<last_group_block_num; i++)
		{
			*block_buf_ptr = i+block_num_start+group_num*NICFREE;
			block_buf_ptr++;
		}
		block_num_write = block_num_start+group_num*NICFREE - 1;
		block_buf_ptr = block_buf;	
		memcpy(disk+DATASTART+block_num_write*BLOCKSIZ, block_buf_ptr, BLOCKSIZ);
	}
	// 写前面整组的号
	// 注意第1组的号不能写到2号块上去
	for(int j=group_num; j>1; j--)
	{
		memset(block_buf_ptr, 0x00, BLOCKSIZ);
		for(int i=0; i<NICFREE; i++)
		{
			*block_buf_ptr = i+block_num_start+(j-1)*NICFREE;
			block_buf_ptr++;
		}
		block_num_write = block_num_start+(j-1)*NICFREE - 1;
		block_buf_ptr = block_buf;	
		memcpy(disk+DATASTART+block_num_write*BLOCKSIZ, block_buf_ptr, BLOCKSIZ);
	}



	// set number of idle inode, used 4 inodes above 
	filsys.s_ninode = DINODEBLK * (BLOCKSIZ/DINODESIZ) - 4;
	// set array of idle inode
	// note: NICINOD should be no more than filsys.s_ninode
	for (i=0; i < NICINOD; i++)
	{
		/* begin with 4,    0,1,2,3, is used by main,etc,password */
		filsys.s_inode[i] = 4+i;
	}
	// set ptr of idle inode
	filsys.s_pinode = 0;
	// for further extension
	filsys.s_rinode = NICINOD + 4; 



  

	// write filesys in memory into second block within disk
	memcpy(disk+BLOCKSIZ, &filsys, sizeof(struct filsys));


	// --------------------------------------------------------------------------

	return;
}	


