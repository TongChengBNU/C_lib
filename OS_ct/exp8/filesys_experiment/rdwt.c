#include <stdio.h>
#include "filesys.h"


// Ok
// functionality: read file content into buf
// input: fd-file descriptor, buf-buffer, size
// output; read size or ERROR
unsigned int read(int fd, char *buf, unsigned int size)
{
	int block_num, block_off, i, j;

	// user_id is a global var, meaning current user index in user
	struct inode *inode = sys_ofile[user[user_id].u_ofile[fd]].f_inode;
	// check f_mode
	if (!(sys_ofile[user[user_id].u_ofile[fd]].f_mode & FREAD))
	{
		printf("\nThe file is not opened for read\n");
		return ERROR;
	}

	// memory buffer pointer
	char *temp_buf = buf;
	// offset
	unsigned long off = sys_ofile[user[user_id].u_ofile[fd]].f_off;
	// 如果超出文件范围，则从当前位置读到末尾即可
	if ((off+size) > inode->di_size)
		size = inode->di_size - off;

	// 1. 前一部分数据
	unsigned short start_block = off / BLOCKSIZ;
	int start_off = off % BLOCKSIZ;
	memcpy(temp_buf, disk+DATASTART+inode->di_addr[start_block]*BLOCKSIZ+start_off, BLOCKSIZ-start_off);
	temp_buf += BLOCKSIZ-start_off;

	// 2. 中间整块数据
	block_off = (size-start_off) % BLOCKSIZ;
	block_num = (size-start_off) / BLOCKSIZ;
	for(int i=0; i<block_num; i++)
	{
		memcpy(temp_buf, disk+DATASTART+inode->di_addr[i]*BLOCKSIZ, BLOCKSIZ);
		temp_buf += BLOCKSIZ;
	}
	// 3. 最后一部分数据
	memcpy(temp_buf, disk+DATASTART+inode->di_addr[block_num]*BLOCKSIZ, block_off);

	return size;
}


// Ok
// functionality: write buf into file content
// input: fd-file descriptor, buf-buffer, size
// output: write size of ERROR
unsigned int write(int fd, char *buf, unsigned int size)
{
	struct inode *inode = sys_ofile[user[user_id].u_ofile[fd]].f_inode;
	unsigned int remain_size = size;

	if  (!(sys_ofile[user[user_id].u_ofile[fd]].f_mode & FWRITE)
		&& !(sys_ofile[user[user_id].u_ofile[fd]].f_mode & FAPPEND))   
	{
		printf("\nThe file is not opened for write\n");
		return ERROR;
	}   





	/*
	 * 分析
	 * 如果数据小于等于偏移块的剩余，那么直接写入；
	 * 如果大于偏移块的剩余，
	 *　　　计算需要多少块，不足则补充
	 *　　　补充完成后，整块写入
	 *　　　最后处理尾部
	 **/

	char *temp_buf = buf;
	unsigned long off = sys_ofile[user[user_id].u_ofile[fd]].f_off;
	unsigned short start_block = off / BLOCKSIZ;
	int start_off = off % BLOCKSIZ;

	// 1
	if(remain_size <= (BLOCKSIZ - (off%BLOCKSIZ)))
	{
		memcpy(disk+DATASTART+inode->di_addr[start_block]*BLOCKSIZ+start_off, temp_buf, remain_size); 
		return size;
	}

	// 2
	int temp;
	unsigned short block_num_need = size_to_block_num(off+remain_size);
	unsigned short block_num_exist = size_to_block_num(inode->di_size);
	if(block_num_need > block_num_exist)
	{
		// 补充块
		unsigned short num_new = block_num_need - block_num_exist;
		unsigned short ptr = block_num_exist;
		for(int i=0; i<num_new; i++)
		{
			inode->di_addr[ptr] = balloc();
			ptr++;
		}
		// 补充完毕	
	}

	// 3
	unsigned short current_block = start_block;
	unsigned short i, j;

	// 3.1 head
	memcpy(disk+DATASTART+inode->di_addr[current_block]*BLOCKSIZ+start_off, temp_buf, BLOCKSIZ-start_off);
	remain_size -= (BLOCKSIZ-start_off);
	temp_buf += (BLOCKSIZ-start_off);
	current_block = current_block+1;

	// 3.2 block unit
	while(remain_size > BLOCKSIZ)
	{
		memcpy(disk+DATASTART+inode->di_addr[current_block]*BLOCKSIZ, temp_buf, BLOCKSIZ);
		remain_size -= BLOCKSIZ;
		temp_buf += BLOCKSIZ;
		current_block = current_block+1;
	}

	// 3.3. tail
	memcpy(disk+DATASTART+inode->di_addr[current_block]*BLOCKSIZ, temp_buf, remain_size);

	// 4. update inode di_size
	inode->di_size += size;


	return size;
}







