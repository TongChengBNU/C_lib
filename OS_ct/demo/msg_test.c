#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

struct msgbuf
{
	int mtype;
	char mtext[1];
};
 
int main()
{
	int msqid;
	struct msqid_ds info;
	struct msgbuf buf;
	msqid=msgget(IPC_PRIVATE,0777|IPC_CREAT);
	printf("0777|IPC_CREAT:%o\n",0777|IPC_CREAT);
	printf("IPC_CREAT:%o\n",IPC_CREAT);
	printf("IPC_EXCL:%o\n",IPC_EXCL);
	printf("IPC_NOWAIT:%o\n",IPC_NOWAIT);
	buf.mtype=1;
	buf.mtext[0]='a';
	msgsnd(msqid,&buf,1,0);
	msgctl(msqid,IPC_STAT,&info);
	printf("read-write:%o\n",info.msg_perm.mode);
	printf("msqid:%d\n",msqid);
	system("ipcs -q");
	msgctl(msqid,IPC_RMID,0);
	system("ipcs -q");
	exit(0);
}

