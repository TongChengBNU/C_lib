#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <wait.h>

#define SHMKEY 20
#define BUFFER_NUM 10
#define BUFFER_PER_LENGTH 1024

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
} arg;

void Option1();
void Option2();
void Option3();


int empty_sem_id, full_sem_id, mutex_sem_id;  
int shm_id;
char *begin_addr;
int sem_key, shm_key;


int main()
{
    shm_key = SHMKEY;

    if ( (sem_key = ftok("producer.c", 0x66)) < 0)
    {
        perror("ftok semaphore key error;\n");
        exit(1);
    }
    

    if ( (shm_id = shmget(shm_key, (BUFFER_NUM+2)*BUFFER_PER_LENGTH, 0777|IPC_CREAT)) < 0)
    {
        fprintf(stderr, "Request for shared memory error;\n");
        exit(0);
    }
    begin_addr = (char *)shmat(shm_id, 0, 0);
    printf("Shared memory id: %d\n", shm_id);


    empty_sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT|0666);
    printf("Semaphore empty id %d\n", empty_sem_id);
    // empty_sem_id = semget(sem_key, 1, IPC_CREAT|0666);
    full_sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT|0666);
    printf("Semaphore full id %d\n", full_sem_id);
    mutex_sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT|0666);
    printf("Semaphore mutex id %d\n", mutex_sem_id);

    arg.val = 1;
    if (semctl(empty_sem_id, 0, SETVAL, arg)==-1)
        perror("empty_sem initialization error;\n");
    arg.val = 0;
    if (semctl(full_sem_id, 0, SETVAL, arg)==-1)
        perror("full_sem initialization error;\n");
    arg.val = 1;
    if (semctl(mutex_sem_id, 0, SETVAL, arg)==-1)
        perror("mutex_sem initialization error;\n");

    int option;
    while(1)
    {
        printf("1. Produce;\n");
        printf("2. Exit;\n");
        printf("3. Delete semaphores and shared memory;\n");
        fgets(option, 4, stdin);
        while (option<1 | option>3)
        {
            fprintf(stderr, "Option error;\n");
            fgets(option, 4, stdin);
        }

        switch(option)
        {
            case 1: 
                Option1();
                break;
            case 2:
                Option2();
                break;
            case 3:
                Option3();
                break;
            break;
        }
    }

    return 0;
}



void Option1()
{
    char buffer[1024];
    printf("Please input strings:\n");
    fgets(buffer, 1024, stdin);
    
    // mutex
    // full
    // ptr in


    return;
}

void Option2()
{
    exit(0);
}

void Option3()
{
    shmctl(shm_id, IPC_RMID, 0);
    semctl(empty_sem_id, 0, IPC_RMID, 0);
    semctl(full_sem_id, 0, IPC_RMID, 0);
    semctl(mutex_sem_id, 0, IPC_RMID, 0);
}
