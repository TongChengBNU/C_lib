/************************************************************************
 > File Name: main_ct.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Tue 17 Dec 2019 11:26:29 AM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesys.h"

// hash inode
struct hinode hinode[NHINO];

// current directory
struct dir dir;
// system open table
struct file sys_ofile[SYSOPENFILE];
// system super block
struct filsys filsys;
// passwd container
struct pwd pwd[PWDNUM];
// user open table container
struct user user[USERNUM];

struct file *fd;  
// current path inode
struct inode *cur_path_inode;
// index of current user in user array
int user_id;

// disk space: boot block, super block, inode block, data block 
char disk[(2+DINODEBLK+FILEBLK)*BLOCKSIZ];

void interactive_mode();

int main()
{
	//login(2118,"abcd");
	printf("\nFormat the disk \n");
    format();
	install();
	//_dir();

	interactive_mode();
	//struct direct *tmp;
	//tmp = (struct direct *)(disk+DATASTART);
	//memcpy(tmp, disk+DATASTART, sizeof(struct direct));
	//printf("%s", tmp->d_name);
	//printf("%d", tmp->d_ino);

	//login(2118,"abcd");
	//interactive_mode();
	/*
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
	*/


//	buf = (char *)malloc(/*BLOCKSIZ*8+*/300);
//	write(ab_fd4,buf,/*BLOCKSIZ*8+*/300);
//	close(user_id,ab_fd4);  //xiao
//	free(buf);
//	_dir(); 
//
//
//	ab_fd3 = open(2118, "ab_file2.c", FAPPEND);  
//	buf = (char *)malloc(/*BLOCKSIZ*3+*/100);
//	write(ab_fd3,buf,/*BLOCKSIZ*3+*/100);
//	close(user_id,ab_fd3);  //xiao
//	free(buf);
//	_dir();
//
//	chdir("..");
//	_dir();
//
//	logout(2118); //xiao
//	halt();
	
	return 0;
}

void interactive_mode()
{
	unsigned short num_option;
	unsigned short option;
	unsigned short uid;
	char passwd[PWDSIZ], dirname[DIRSIZ];
	char *filename = dirname;
	fd_t fd=-1;
	status_t status;
	char buffer[1024];
	unsigned int size;
	

	// login
	printf("Welcome to memory file system! Please log in -- \n");
	printf("uid: ");	
	scanf("%hd", &uid);
	printf("password: ");	
	// could add hidden feature ?????????
	scanf("%s", passwd);
	printf("%d %s\n", uid, passwd);

	if((login(uid, passwd)) == 1)
	{
		printf("Log in success!\n");
	}
	else
	{
		// exit
		printf("Goodbye!\n");
		return;	
	}

	// operation
	while(1)
	{

		printf("Please select an option below:\n");
		printf("Current file descriptor: %d\n", fd);
		printf("1. dir; 2. change dir; 3. makefile; 4. makedir; 5. Delete file 6. logout and halt\n");
		printf("7. Open; 8. Close; 9. Read; 10. Write;\n");
		printf("11. Show sys open table; 12. Show user open table;\n");
		num_option = 12;
		scanf("%hd", &option);
		while(option<1 || option > num_option){
			printf("Option error! Please input again;\n");
			scanf("%hd", &option);
		}

		switch(option){
			case 1:
				_dir();
				putchar('\n');
				break;
			case 2:
				printf("Directory name: ");
				scanf("%s", dirname);
				chdir(dirname);
				printf("Change directory success!\n");
				putchar('\n');
				break;
			case 3:
				printf("New file name: ");
				scanf("%s", filename);
				fd = create(uid, filename, 01777);
				putchar('\n');
				break;
			case 4:
				printf("New directory name: ");
				scanf("%s", dirname);
				mkdir(filename);
				putchar('\n');
				break;
			case 5:
				printf("Delete file name: ");
				scanf("%s", filename);
				delete(filename);
				putchar('\n');
				break;
			case 6:
				logout(uid);
				halt();
				exit(0);
				break;
			case 7:
				printf("Open filename: ");
				scanf("%s", filename);
				fd = open(uid, filename, FAPPEND);
				printf("Open success\n");
				putchar('\n');
				break;
			case 8:
				printf("Close filename: ");
				scanf("%s", filename);
				status = close(uid, fd);
				if(status)
					printf("Close success\n");
				else
					printf("Close error\n");
				putchar('\n');
				break;
			case 9:
				printf("Read size: ");
				scanf("%d", &size);
				unsigned short mark = read(fd, buffer, size);
				printf("Read %d bytes;\n", mark);
				if(mark)
					printf("Content: %s\n", buffer);
				putchar('\n');
				break;
			case 10:
				printf("Write size: ");
				scanf("%d", &size);
				printf("Write content: ");
				memset(buffer, 0x00, 1024);
				scanf("%s", buffer);
				mark = write(fd, buffer, size);
				printf("Write %d bytes;\n", mark);
				putchar('\n');
				break;
			case 11:
				show_sys_open_table();
				putchar('\n');
				break;
			case 12:
				show_user_open_table();
				putchar('\n');
				break;
			default:
				break;
		}
	}



	return;
}




void show_sys_open_table()
{
	printf("index f_count offset inode ID\n");
	for(int i=0; i<SYSOPENFILE; i++)
	{
		if(sys_ofile[i].f_count)
		{
			printf("%10d%10d%10ld%10d\n", i, sys_ofile[i].f_count, sys_ofile[i].f_off, sys_ofile[i].f_inode->i_ino);
		}
	}
	return;
}

void show_user_open_table(uid_t uid)
{
	int j, user_sen;
	for(j=0; j<USERNUM; j++)
	{
		if(user[j].u_uid == uid)
			break;
	}
	if(j == USERNUM)
	{
		printf("User with uid:%d not found!", uid);
		return;
	}
	user_sen = j;
	printf("fd ptr\n");
	for(int i=0; i<NOFILE; i++)
	{
		if(user[user_sen].u_ofile[i] != SYSOPENFILE)
		{
			printf("%5d%5d\n", i, user[user_sen].u_ofile[i]);
		}
	}
	return;
}
