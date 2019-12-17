/************************************************************************
 > File Name: main_ct.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Tue 17 Dec 2019 11:26:29 AM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "filesys.h"

struct hinode hinode[NHINO];

// current directory
struct dir dir;
// system open table
struct file sys_ofile[SYSOPENFILE];
// system super block
struct filsys filsys;
// passwd container
struct pwd pwd[PWDNUM];
// user container
struct user user[USERNUM];

struct file *fd;   //xiao
// current path inode
struct inode *cur_path_inode;
int user_id;

char disk[(DINODEBLK+FILEBLK+2)*BLOCKSIZ];

int main()
{
	// abstract file descriptor
	unsigned short ab_fd1, ab_fd2, ab_fd3, ab_fd4;
	unsigned short bhy_fd1;
	char *buf;

	printf("\nFormat the disk \n");
    format();
	install();
	_dir();

	login(2118,"abcd");
	user_id = 0; // unused;
	mkdir("a2118");
	_dir(); 

	chdir("a2118");
	// 01777 = 0011 1111 1111
	ab_fd1 = create(2118, "ab_file0.c", 01777);  //xiao
	_dir();

	buf = (char *)malloc(BLOCKSIZ*9+5);
	write(ab_fd1, buf, BLOCKSIZ*9+5);
	close(user_id, ab_fd1);
	free(buf);
	_dir(); 

	mkdir("subdir");
	_dir(); 
	chdir("subdir");
	_dir(); 

	ab_fd2 = create(2118, "ab_file1.c", 01777);  //xiao
	_dir(); 
	buf = (char *)malloc(BLOCKSIZ*4+20);
	write(ab_fd2, buf, BLOCKSIZ*4+20);
	close(user_id, ab_fd2);
	free(buf);
	_dir(); 

	chdir("..");
	_dir(); 
	ab_fd3 = create(2118, "ab_file2.c", 01777);  //xiao
	buf = (char *)malloc(BLOCKSIZ*8+255);
	write(ab_fd3,buf,BLOCKSIZ*8+255);
	close(user_id,ab_fd3);  //xiao
	free(buf);
	_dir(); 

	delete("ab_file0.c");
	_dir(); 
	ab_fd4 = create(2118, "ab_file4.c", 01777);  //xiao
	buf = (char *)malloc(/*BLOCKSIZ*8+*/300);
	write(ab_fd4,buf,/*BLOCKSIZ*8+*/300);
	close(user_id,ab_fd4);  //xiao
	free(buf);
	_dir(); 


	ab_fd3 = open(2118, "ab_file2.c", FAPPEND);  
	buf = (char *)malloc(/*BLOCKSIZ*3+*/100);
	write(ab_fd3,buf,/*BLOCKSIZ*3+*/100);
	close(user_id,ab_fd3);  //xiao
	free(buf);
	_dir();

	chdir("..");
	_dir();

	logout(2118); //xiao
	halt();
	return 0;
}
