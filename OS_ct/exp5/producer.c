#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
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
    shm_key = SHMKEY;

    // get key for semaphore set
    // if ( (sem_key = ftok("producer.c", 0x66)) < 0)
    // {
    //     perror("ftok semaphore key error;\n");
    //     exit(1);
    // }
    
    // create shared memory with id (shm_id)
    if ( (shm_id = shmget(shm_key, (BUFFER_NUM+2)*BUFFER_PER_LENGTH, 0777|IPC_CREAT|IPC_EXCL)) < 0)
    {
        
        if ( (shm_id = shmget(shm_key, 0, 0)) < 0 )
        {
            fprintf(stderr, "shmget shared memory error;\n");
            exit(1);
        }
        else
        {   
            // get shm initialization
            block_ptr = (struct block *)shmat(shm_id, 0, 0);
            for (int i=0; i<BUFFER_NUM+2; i++)
            {
                shm_ptr[i] = block_ptr;
                block_ptr++;
            }
        }
            
    }
    else
    {
        // create new shm initialization
        block_ptr = (struct block *)shmat(shm_id, 0, 0);
        for (int i=0; i<BUFFER_NUM+2; i++)
        {
            shm_ptr[i] = block_ptr;
            block_ptr++;
        }
        strcpy(shm_ptr[10]->buffer, "0");
        strcpy(shm_ptr[11]->buffer, "0");
    }

    printf("Shared memory id: %d\n", shm_id);
    


    // create 3 semaphore for empty, full, mutex
    sem_id = semget(SEMKEY, 3, IPC_CREAT|0666);
    printf("Semaphore set id:%d\n", sem_id);

    arg.val = 10;
    if (semctl(sem_id, 0, SETVAL, arg)==-1)
        perror("empty_sem initialization error;\n");
    arg.val = 0;
    if (semctl(sem_id, 1, SETVAL, arg)==-1)
        perror("full_sem initialization error;\n");
    arg.val = 1;
    if (semctl(sem_id, 2, SETVAL, arg)==-1)
        perror("mutex_sem initialization error;\n");

    // define P-V operation
    for (int i=0; i<3; i++)
    {
        P[i].sem_num = i;
        P[i].sem_op = -1;
		// when a process terminates, the semaphore will return to its original value
        // P[i].sem_flg = SEM_UNDO;

        V[i].sem_num = i;
        V[i].sem_op = 1;
        // V[i].sem_flg = SEM_UNDO;
    }

    

    int option;
    while(1)
    {
        printf("1. Produce;\n");
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
    
    // empty -1
    semop(sem_id, &P[0], 1);
    // mutex -1
    semop(sem_id, &P[2], 1);
    

    printf("Please input strings:\n");
    setbuf(stdin, NULL);
    fgets(buffer, 1024, stdin);
    int index, next;
    index = atoi(shm_ptr[10]->buffer);

    if (index < 10)
    {
        strcpy(shm_ptr[index]->buffer, buffer);
        fprintf(stderr, "Write into position %d;\n", index);
        printf("\n");
        next = index+1;
        if (next > 9)
        {
            next = next % 10;
        }
        sprintf(shm_ptr[10]->buffer, "%d", next);
    }
   
    
    // release mutex
    semop(sem_id, &V[2], 1);
    // full + 1
    semop(sem_id, &V[1], 1);

    return;
}

void Option2()
{
    exit(0);
}

void Option3()
{
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
    semctl(sem_id, 1, IPC_RMID);
    semctl(sem_id, 2, IPC_RMID);
    printf("Clean success.\n");
}

void clean()
{
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
    semctl(sem_id, 1, IPC_RMID);
    semctl(sem_id, 2, IPC_RMID);
    printf("Clean success.\n");
}


