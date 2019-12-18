// system open file number
#define SYSOPENFILE  40
#define DIRNUM 128
// directory name maximum length
#define DIRSIZ 12    //xiao 14->12
// password maximum length
#define PWDSIZ 12
// password number * sizeof(struct pwd)
// 32 * (12+2+2) = 2^9 = 512 = BLOCKSIZ
#define PWDNUM 32
// number of opened file in user open table
#define NOFILE   20
// number of address
#define NADDR  10
// number of hash inode
#define NHINO 128       /* must be power of 2 */
#define USERNUM 10

// block size
#define BLOCKSIZ 512
// disk inode size, should be sizeof(struct inode)
#define DINODESIZ 128 //xiao 32->52 tongcheng 52->128





/*di_mode*/
// disk empty, 
#define DIEMPTY   00000
// disk file type: binary 0000 0000 0000
#define DIFILE  00000
// disk directory type: binary 0010 0000 0000
//#define DIDIR     02000
#define DIDIR  01000      // by Tong Cheng
// default mode: binary 0001 1111 1111
// file default mode is 0001 1111 1111
// dir default mode is  0011 1111 1111
#define DEFAULTMODE 00777

// no inode
#define NOINODE -1

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

/* i_flag */
#define  IUPDATE  00002


/* f_flag */
#define FREAD   00001
#define FWRITE   00002
#define FAPPEND   00004

/* error */
#define DISKFULL  65535

/* fseek origin */
#define SEEK_SET  0



/*system super block*/
// number of disk inode block 
#define DINODEBLK  32
// number of file block
#define FILEBLK   512
// size of free block stack
#define NICFREE  50 
// size of free inode stack
#define NICINOD  50
// disk inode start
#define DINODESTART  (2*BLOCKSIZ)    /*1024   0x400*/
// offset of data start in disk
#define DATASTART  ((2+DINODEBLK)*BLOCKSIZ)     /*d:17408    0x4400*/
/* s_fmod */
#define SUPDATE  00001 

// -----------------------------------------------
// PREDEFINED STRUCT 
//
// file system super block �ļ�ϵͳ������
struct filsys{
	// block
	unsigned short  s_isize;   /*i�ڵ�����*/
	unsigned long   s_fsize;   /*���ݿ����*/

	unsigned int   s_nfree;    /*���п����*/
	unsigned short  s_pfree;  /*���п�ָ��*/
	unsigned int  s_free[NICFREE];  /*���п��ջ*/
	
	// inode
	unsigned int  s_ninode;  /*����i�ڵ��� number of free inode in s_inode*/
	unsigned short  s_pinode;  /*����i�ڵ�ָ�� pointer of the sinode*/
	unsigned int  s_inode[NICINOD];   /*����i�ڵ�����*/
	unsigned int s_rinode;    /*���������ڵ�remember inode*/

	char s_fmod;  /*�������޸ı�־*/
};

// index node
// size 8+8+1+4+4+2+2+2+2+2+4*10 = 75
struct inode{
	struct inode  *i_forw;    // inode forward
	struct inode  *i_back;    // inode backward
	char i_flag;             // flag for not update
	unsigned int  i_ino;     // inode ID, begin at 0 ����i�ڵ��־
	unsigned int  i_count;   // ref count ���ü���
	unsigned short  di_mode;  // 10 bits access vector 

	unsigned short  di_uid;   // disk index node user id
	unsigned short  di_gid;   // disk index node group id

	unsigned short  di_number; // disk block number
	unsigned short  di_size;  // size of file �ļ���С
	// NADDR = 10
	unsigned int   di_addr[NADDR];   // number of physical number /*������*/
	// DINODESIZ 128 - 75 = 53
	char options[53];
};

// maybe unused------------------
// disk index node
struct dinode{
	unsigned short di_number; /*�����ļ���*/
	unsigned short di_mode; /*��ȡȨ��*/
	unsigned short di_uid;  //ct: disk index node user id
	unsigned short di_gid;  //ct: disk index node group id
	unsigned short di_size;  /*�ļ���С*/
	unsigned int di_addr[NADDR];   /*������*/
};

// directory object Ŀ¼��
struct direct{
	char d_name[DIRSIZ];  // directory name
	unsigned int d_ino;   // inode ID
};

// directory Ŀ¼
struct dir{
	struct direct direct[DIRNUM];
	int size;  /*��ǰĿ¼��С*/
};


// password
// struct pwd corresponds to user using (uid, gid)
struct pwd{
	unsigned short p_uid; // user id
	unsigned short p_gid; // group id
	char password [PWDSIZ]; // password
};

// hash table for searching index node in memory
struct hinode{
	struct inode *i_forw;   /*HASG��ָ��*/
};

// system open table element
struct file{
	char f_flag;    /*�ļ�������־*/
	unsigned int f_count;  /*���ü���*/
	struct inode *f_inode; /*ָ���ڴ�i�ڵ�*/
	unsigned long f_off;   /*read/write character pointer*/
};

// user open table
struct user{
	// least 9 bits
	unsigned short u_default_mode;
	unsigned short u_uid;
	unsigned short u_gid;
	unsigned short u_ofile[NOFILE];   /*�û����ļ���*/
};
// -----------------------------------------------









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
// PREDEFINED FUNCTION 
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
//extern unsigned int namei();
extern int namei();
// search files under current directory
extern unsigned short iname();

// defined in access.c
// access control
//extern unsigned int access();
extern unsigned int access(unsigned int user_id,  struct inode *inode,  unsigned short mode);

// defined in dir.c
// display current directories and files
extern void _dir();
// create directory
extern void mkdir();
// change directory
extern void chdir();

// defined in open.c
// open file
extern unsigned short open(int user_id, char *filename, unsigned short openmode);

// defined in create.c
// create file
extern unsigned short create(unsigned int user_id, char *filename, unsigned short mode);

// defined in rdwt.c
// read file
extern unsigned int read();
// write file
extern unsigned int write();

// defined in log.c
// log into filesystem
extern int login(unsigned short uid, char *passwd);
// log out filesystem
//extern void logout();
extern int logout(unsigned short uid);

// defined in install.c
// enter into filesystem
extern void install();

// defined in format.c
// format the whole file system
extern void format();
// may be not used in main.c???
//extern void memcpy();

// defined in close.c
// close file
extern void close(unsigned int user_id, unsigned short cfd);
// defined in halt.c
// exit the whole file system
extern void halt();
// defined in delete.c
// delete file
extern void delete();




