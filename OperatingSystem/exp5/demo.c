#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <wait.h>
/*
a buffer is shared between parent and child process;
Child writes while parent reads;
*/

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int emptyid;
int fullid;                                 // sychronous semaphore

int main()
{
    int child;
    
    struct sembuf P, V;
    union semun arg;
    
    int shmid;
    char *viraddr;
    char buffer[BUFSIZ];
    // create 2 semaphore set with 1 element
    emptyid=semget(IPC_PRIVATE,1,IPC_CREAT|0666);
    fullid=semget(IPC_PRIVATE,1,IPC_CREAT|0666);
    // initialize every semaphore
    arg.val=1;
    if(semctl(emptyid,0,SETVAL,arg)==-1)
        perror("semctl setval error");
    arg.val=0;
    if(semctl(fullid,0,SETVAL,arg)==-1)
        perror("semctl setval error");
    
    // define P-V operation
    P.sem_num=0;
    P.sem_op=-1;
    P.sem_flg=SEM_UNDO;
    V.sem_num=0;
    V.sem_op=1;
    V.sem_flg=SEM_UNDO;
    
    // request for shared memory
    shmid=shmget(IPC_PRIVATE,BUFSIZ,0666|IPC_CREAT);
    viraddr=(char*)shmat(shmid,0,0);
    
    while((child=fork())==-1);
    if(child>0)
    {
        // in child process 
        while(1)
        {
            semop(fullid,&P,1);
            printf("Your message is:\n%s",viraddr);
            semop(emptyid,&V,1);
            if(strncmp(viraddr,"end",3)==0)break;
        }
        wait(0);
        shmdt(viraddr);

        // remove semaphore set and release shared memory
        shmctl(shmid,IPC_RMID,0);
        semctl(emptyid,IPC_RMID,0);
        semctl(fullid,IPC_RMID,0);
        printf("Parent exit!\n");
        exit(0);
    }
    else
    {
        // in parent process f
        while(1)
        {
            semop(emptyid,&P,1);
            puts("Enter your text:");
            fgets(buffer,BUFSIZ,stdin);
            strcpy(viraddr,buffer);
            semop(fullid,&V,1);
            if(strncmp(viraddr,"end",3)==0)  // compare the first 3 characters
            {
                sleep(1);
                break;
            }
        }
        printf("Child exit!\n");
        exit(0);
    }
}