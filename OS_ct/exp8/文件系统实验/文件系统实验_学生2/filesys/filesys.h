#ifndef _FILESYS_H
#define _FILESYS_H

#define delete 		dele     		//delete ��c++���Ǳ�����  by tangfl
//#define exit(a)		return			//����ʹ�� return         by tangfl

//All Defines
#define BLOCKSIZ        512			//ÿ����Ĵ�С
#define SYSOPENFILE     40
#define DIRNUM          128			//һ��Ŀ¼�� ��� ��Ŀ¼��
#define DIRSIZ          12			//Ŀ¼������ windows32��int����Ϊ4 xiao 14->12
#define PWDSIZ 			12			//������󳤶�
#define PWDNUM 			32
#define NOFILE   		20			//�û������ļ���
#define NADDR  			10			//i�ڵ��ڴ洢
#define NHINO 			128			//hash��  ?????????/* must be power of 2 */
#define USERNUM 		10
#define DINODESIZ 		52			//?????? int=4 �ʶ���2*NADRR ��Դ������Ϊlong������short Ӧ��Ϊ50�ֽڣ��˴�����ϵͳΪ�˶����ڴ棬����˵���xiao 32->52


/*filesys*/
#define DINODEBLK  		32							//i�ڵ�ռ�õĿ���
#define FILEBLK   		512							//���ݿ���
#define NICFREE  		50							//�������ڿ��п��ջ��С
#define NICINOD  		50							//�������ڿ���i�ڵ������С
#define DINODESTART  	(2*BLOCKSIZ)				//i�ڵ㿪ʼ��ַ �ճ�1024����һ��Ϊ���������ڶ���Ϊ������
#define DATASTART  		((2+DINODEBLK)*BLOCKSIZ)	//��������ʼ��ַ DINODESTART+DINODEBLK*BLOCKSIZ	/*d:17408    0x4400*/


/*di_mode*/
#define DIEMPTY   		00000						//��Ȩ��
#define DIFILE      	01000						//���� �ļ�
#define DIDIR     		02000						//���� Ŀ¼

#define UDIREAD 		00001						//�û�Ȩ��
#define UDIWRITE  		00002
#define UDIEXICUTE  	00004
#define GDIREAD   		00010						//�û���Ȩ��
#define GDIWRITE  		00020
#define GDIEXICUTE  	00040
#define ODIREAD  		00100						//pubilcȨ��
#define ODIWRITE 		00200
#define ODIEXICUTE 		00400


#define READ  			1
#define WRITE 			2
#define EXICUTE 		3


#define DEFAULTMODE 	00777					//Ĭ��Ȩ��


/* i_flag */
#define  IUPDATE  		00002

/* s_fmod */
#define SUPDATE  		00001 

/* f_flag */
#define FREAD   		00001
#define FWRITE   		00002
#define FAPPEND   		00004

//Includes
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

/* error */
#define DISKFULL  		65535

/* fseek origin */
//#define SEEK_SET  		0


struct inode{
	struct inode  	*i_forw;
	struct inode  	*i_back;
	char 			i_flag;
	int  	i_ino;          /*����i �ڵ��־*/
	int  	i_count;     	/*���ü���*/
	short  di_number; 		/*�����ļ�������Ϊ0 ʱ����ɾ�����ļ�*/
	short  di_mode;  		/*��ȡȨ��*/
	short  di_uid;
	short  di_gid;
	short  di_size;   		/*�ļ���С*/
	int   	di_addr[NADDR];   /*������*/
};

struct dinode{
	short 	di_number; 		/*�����ļ���*/
	short 	di_mode; 		/*��ȡȨ��*/
	short 	di_uid;
	short 	di_gid;
	short 	di_size;  		/*�ļ���С*/
	int 	di_addr[NADDR];   /*������*/
};


struct direct{
	char d_name[DIRSIZ];
	int d_ino;
};

struct filsys{
	short  	s_isize;   			/*i�ڵ�����*/
	long   	s_fsize;   			/*���ݿ����*/
	int   		s_nfree;    		/*���п�*/
	short  	s_pfree;  			/*���п�ָ��*/
	int  		s_free[NICFREE];  	/*���п��ջ*/
	
	int  		s_ninode;  			/*number of free inode in s_inode*/
	short int 			s_pinode;  			/*pointer of the sinode*/
	int  		s_inode[NICINOD];   /*����i�ڵ�����*/
	int 		s_rinode;    		/*remember inode*/

	char 				s_fmod;  			/*�������޸ı�־*/
	};

struct pwd{
	short 		p_uid;
	short 		p_gid;
	char 				password [PWDSIZ];
};

struct dir{
	struct direct 		direct[DIRNUM];
	int 				size;  				/*��ǰĿ¼��С*/
};

struct hinode{
	struct inode 		*i_forw;   /*HASG��ָ��*/
};

struct file{
	char 			f_flag;    		/*�ļ�������־*/
	int 	f_count;  		/*���ü���*/
	struct inode 	*f_inode; 		/*ָ���ڴ�i�ڵ�*/
	long 	f_off;   		/*read/write character pointer*/
};

struct user{
	short 	u_default_mode;
	short 	u_uid;
	short 	u_gid;
	short 	u_ofile[NOFILE];   /*�û����ļ���*/
};
	
//all variables
extern struct hinode   hinode[NHINO];
extern struct dir      dir;           /*��ǰĿ¼(���ڴ���ȫ������)*/
extern struct file     sys_ofile[SYSOPENFILE];
extern struct filsys   filsys;        /*�ڴ��еĳ�����*/
extern struct pwd      pwd[PWDNUM];
extern struct user     user[USERNUM];
//extern struct file     *fd;           /*the file system column of all the system*/    //xiao
extern struct inode    *cur_path_inode;
extern int             user_id;
extern char            disk[(DINODEBLK+FILEBLK+2)*BLOCKSIZ];

// all functions
extern struct        inode *iget(int);
extern void          iput(struct inode *);
extern int  balloc(int);
extern int  balloc();
extern void          bfree(int);
extern struct inode* ialloc();
extern void          ifree(int);
extern int			 namei(char *);
extern short iname(char *);
extern int  access(int,struct inode *,short);
extern void          _dir();
extern void          mkdir(char *);
extern void          chdir(char *);
extern short		 open(int,char*,char);
extern int           creat(int,char *,short);
extern int  read(int fd, char *buf, int size);
extern int  write(int fd,char *buf,int size);
extern int           login(short, char *);
extern int           logout(short);
extern void          install();
extern void          format();
extern void          close(int,short);
extern void          halt();
extern void          delete(char *);
extern int 			 shell(int user_id,char *str);
extern void          useradd(int ,unsigned short);
extern void          userdel(int ,unsigned short);
extern void          userauth(int ,unsigned short,unsigned short);
extern void          passwd(int ,char*);
extern void          usershow(int);

#endif