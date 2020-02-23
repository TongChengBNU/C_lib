#include <stdio.h>
#include "filesys.h"

// OK
// input: user id(note that it's the index in user, not uid), inode, mode{READ, WRITE, EXECUTE}
// output: 1 or 0
// access from public to private: Other->Group->User
unsigned int access(unsigned int user_id,  struct inode *inode,  unsigned short mode)
{
	switch (mode)
	{
		case READ:
			if (inode->di_mode & ODIREAD)
				return 1;
			if ((inode->di_mode & GDIREAD) && (user[user_id].u_gid == inode->di_gid))
				return 1;
			if ((inode->di_mode & UDIREAD) && (user[user_id].u_uid == inode->di_uid))
				return 1;
			return 0;

		case WRITE:
			if (inode->di_mode & ODIWRITE)
				return 1;
			if ((inode->di_mode & GDIWRITE) && (user[user_id].u_gid == inode->di_gid))
				return 1;
			if ((inode->di_mode & UDIWRITE) && (user[user_id].u_uid == inode->di_uid))
				return 1;
			return 0;

		case EXECUTE:
			if (inode->di_mode & ODIEXECUTE)
				return 1;
			if ((inode->di_mode & GDIEXECUTE) && (user[user_id].u_gid == inode->di_gid))
				return 1;
			if ((inode->di_mode & UDIEXECUTE) && (user[user_id].u_uid == inode->di_uid))
				return 1;
			return 0;

		default:
			return 0;
			
	}
}



































