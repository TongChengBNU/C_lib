#define BLOCKSIZ        512
#define SYSOPENFILE  40
#define DIRNUM 128
#define DIRSIZ 12    //xiao 14->12
#define PWDSIZ 12
#define PWDNUM 32
#define NOFILE   20
#define NADDR  10
#define NHINO 128       /* must be power of 2 */
#define USERNUM 10
#define DINODESIZ 52   //xiao 32->52


/*filesys*/
#define DINODEBLK  32
#define FILEBLK   512
#define NICFREE  50 
#define NICINOD  50
#define DINODESTART  (2*BLOCKSIZ)    /*1024   0x400*/
#define DATASTART  ((2+DINODEBLK)*BLOCKSIZ)     /*d:17408    0x4400*/


/*di_mode*/
#define DIEMPTY   00000
#define DIFILE      01000
#define DIDIR     02000

#define UDIREAD 00001          /* USER */
#define UDIWRITE  00002
#define UDIEXICUTE  00004
#define GDIREAD   00010  /* GROUP */
#define GDIWRITE  00020
#define GDIEXICUTE  00040
#define ODIREAD  00100   /* OTHER */
#define ODIWRITE 00200
#define ODIEXICUTE 00400


#define READ  1
#define WRITE 2
#define EXICUTE 3


#define DEFAULTMODE 00777


/* i_flag */
#define  IUPDATE  00002

/* s_fmod */
#define SUPDATE  00001 

/* f_flag */
#define FREAD   00001
#define FWRITE   00002
#define FAPPEND   00004

/* error */
#define DISKFULL  65535

/* fseek origin */
#define SEEK_SET  0

// index node
struct inode{
	struct inode  *i_forw;
	struct inode  *i_back;
	char i_flag;
	unsigned int  i_ino;          /*����i �ڵ��־*/
	unsigned int  i_count;     /*���ü���*/
	unsigned short  di_number; /*�����ļ�������Ϊ0 ʱ����ɾ�����ļ�*/
	unsigned short  di_mode;  /*��ȡȨ��*/
	unsigned short  di_uid;   //ct: disk index node user id
	unsigned short  di_gid;   //ct: disk index node group id
	unsigned short  di_size;   /*�ļ���С*/
	unsigned int   di_addr[NADDR];   /*������*/
};

// disk index node
struct dinode{
	unsigned short di_number; /*�����ļ���*/
	unsigned short di_mode; /*��ȡȨ��*/
	unsigned short di_uid;  //ct: disk index node user id
	unsigned short di_gid;  //ct: disk index node group id
	unsigned short di_size;  /*�ļ���С*/
	unsigned int di_addr[NADDR];   /*������*/
};

// directory entry
struct direct{
	char d_name[DIRSIZ];  //ct: directory name
	unsigned int d_ino;   //ct: directory number
};

// file system super block
struct filsys{
	unsigned short  s_isize;   /*i�ڵ�����*/
	unsigned long   s_fsize;   /*���ݿ����*/
	unsigned int   s_nfree;    /*���п�*/
	unsigned short  s_pfree;  /*���п�ָ��*/
	unsigned int  s_free[NICFREE];  /*���п��ջ*/
	
	unsigned int  s_ninode;  /*number of free inode in s_inode*/
	unsigned short  s_pinode;  /*pointer of the sinode*/
	unsigned int  s_inode[NICINOD];   /*����i�ڵ�����*/
	unsigned int s_rinode;    /*remember inode*/

	char s_fmod;  /*�������޸ı�־*/
};

// password
struct pwd{
	unsigned short p_uid;
	unsigned short p_gid;
	char password [PWDSIZ];
};

// directory : what's the difference between dir and direct?
struct dir{
	struct direct direct[DIRNUM];
	int size;  /*��ǰĿ¼��С*/
};

// hash table for searching index node in memory
struct hinode{
	struct inode *i_forw;   /*HASG��ָ��*/
};

// system open table
struct file{
	char f_flag;    /*�ļ�������־*/
	unsigned int f_count;  /*���ü���*/
	struct inode *f_inode; /*ָ���ڴ�i�ڵ�*/
	unsigned long f_off;   /*read/write character pointer*/
};

// user open table
struct user{
	unsigned short u_default_mode;
	unsigned short u_uid;
	unsigned short u_gid;
	unsigned short u_ofile[NOFILE];   /*�û����ļ���*/
};

extern struct hinode hinode[NHINO];
extern struct dir dir;  /*��ǰĿ¼(���ڴ���ȫ������)*/
extern struct file sys_ofile[SYSOPENFILE];
extern struct filsys filsys;  /*�ڴ��еĳ�����*/
extern struct pwd pwd[PWDNUM];
extern struct user user[USERNUM];
extern struct file  *fd; /*the file system column of all the system*/    //xiao

extern struct  inode *cur_path_inode;
extern int user_id;

extern char disk[(DINODEBLK+FILEBLK+2)*BLOCKSIZ];

// -----------------------------------------------
// FUNCTION PREDEFINE
//
// defined in igetput.c
// get info about inode with id
extern struct inode *iget();
// free inode info ???
extern void iput();

// defined in ballfre.c 
// disk block allocation
extern unsigned int balloc();
// disk block free
extern void bfree();

// defined in iallfre.c
// allocate index node area
extern struct inode *ialloc();
// free index node area
extern void ifree();

// defined in name.c
// search  directories
extern unsigned int namei();
// search files under current directory
extern unsigned short iname();

// defined in access.c
// access control
extern unsigned int access();

// defined in dir.c
// display current directories and files
extern void _dir();
// create directory
extern void mkdir();
// change directory
extern void chdir();

// defined in open.c
// open file
extern unsigned short open();

// defined in create.c
// create file
extern unsigned short create();

// defined in rdwt.c
// read file
extern unsigned int read();
// write file
extern unsigned int write();

// defined in log.c
// log into filesystem
extern int login();
// log out filesystem
extern void logout();

// defined in install.c
// enter into filesystem
extern void install();

// defined in format.c
// format the whole file system
extern void format();
// may be not used in main.c???
extern void memcpy();

// defined in close.c
// close file
extern void close();
// defined in halt.c
// exit the whole file system
extern void halt();
// defined in delete.c
// delete file
extern void delete();




