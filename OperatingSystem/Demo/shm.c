#include<stdio.h> 
#include<stdlib.h>
#include <sys/sem.h>

// define keyword for shared memory
#define SHMKEY 75         

int shmid,p1,p2;
int *addr;
 
void CLIENT()
{
	int i;
	// request shared memory with length 1024 and keyword SHMKEY
	shmid=shmget(SHMKEY,1024,0777);  
	// get beginning of address of shared memory 
	addr=(int *)shmat(shmid,0,0);           
	for(i=9;i>=0;i--)
	{
		while(*addr!=-1);
		printf("(client)sent%d\n",i);      
		*addr=i;                           
	}
	exit(0);
}

void SERVER()
{
	shmid=shmget(SHMKEY,1024,0777|IPC_CREAT);     
	addr=(int *)shmat(shmid,0,0);                 
	do
	{
		*addr=-1;
		while(*addr==-1);
		printf("(server)received %d\n",*addr);	
	}while(*addr);
	shmctl(shmid,IPC_RMID,0);
	exit(0);
}


int main()
{
	
	while ((p1=fork())==-1);                     
	if (!p1) SERVER();                             
	while ((p2=fork())==-1);                         
	if (!p2) CLIENT();                            
	wait(0);
	wait(0);
	return 0;
}