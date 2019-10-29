#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <wait.h>

#define SHMKEY 20
#define SEMKEY 123400
#define BUFFER_NUM 10
#define BUFFER_PER_LENGTH 1024

struct block{
    char buffer[BUFFER_PER_LENGTH];
};

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
} arg;

void Option1();
void Option2();
void Option3();
void clean();

int sem_id;
int shm_id;
int sem_key, shm_key;

struct sembuf P[3], V[3];
struct block *block_ptr;
struct block *shm_ptr[BUFFER_NUM+2];


int main()
{
    signal(SIGINT, clean);

    // get semaphore set created by writer
    sem_id = semget(SEMKEY, 3, 0666);
    printf("Semaphore set id:%d;\n", sem_id);

    int tmp;
    if ((tmp = semctl(sem_id, 0, GETVAL)) != -1)
        printf("Empty sema value:%d\n", tmp);
    if ((tmp = semctl(sem_id, 1, GETVAL)) != -1)
        printf("Full sema value:%d\n", tmp);
    if ((tmp = semctl(sem_id, 2, GETVAL)) != -1)
        printf("Mutex sema value:%d\n", tmp);


    // get shared memory created by writer
    if ( (shm_id = shmget(SHMKEY, 0, 0)) == -1)
    {
        perror("Get shared memory error;\n");
        exit(1);
    }
    printf("Shared memory id:%d\n", shm_id);

    block_ptr = (struct block *)shmat(shm_id, 0, 0);
    for (int i=0; i<BUFFER_NUM+2; i++)
    {
       shm_ptr[i] = block_ptr;
       block_ptr++;
    }

    for (int i=0; i<3; i++)
    {
        P[i].sem_num = i;
        P[i].sem_op = -1;
        P[i].sem_flg = SEM_UNDO;
        V[i].sem_num = i;
        V[i].sem_op = 1;
        V[i].sem_flg = SEM_UNDO;
    }

    int option;
    while(1)
    {
        printf("1. Consume;\n");
        printf("2. Exit;\n");
        printf("3. Delete semaphores and shared memory;\n");
        scanf("%d", &option);
        while (option<1 | option>3)
        {
            fprintf(stderr, "Option error;\n");
            scanf("%d", &option);
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

    semop(sem_id, &P[0], 1);
    semop(sem_id, &V[0], 1);

    int index;
    index = atoi(shm_ptr[11]->buffer);
    strcpy(buffer, shm_ptr[index]->buffer);
    printf("Read from shared memory: %s;\n", buffer);

    return;
}

void Option2()
{
    exit(0);
}

void Option3()
{
    shmctl(shm_id, IPC_RMID, 0);
    semctl(sem_id, 0, IPC_RMID);
    semctl(sem_id, 1, IPC_RMID);
    semctl(sem_id, 2, IPC_RMID);
    printf("Clean success.\n");
}

void clean()
{
    shmctl(shm_id, IPC_RMID, 0);
    // semctl(empty_sem_id, 0, IPC_RMID, 0);
    // semctl(full_sem_id, 0, IPC_RMID, 0);
    // semctl(mutex_sem_id, 0, IPC_RMID, 0);
    semctl(sem_id, 0, IPC_RMID);
    semctl(sem_id, 1, IPC_RMID);
    semctl(sem_id, 2, IPC_RMID);
    printf("Clean success.\n");
}




