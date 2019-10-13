#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/msg.h>
#include <sys/ipc.h>
#include <wait.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <signal.h>

#define MSGKEY 75
#define MSGLENGTH 1024
#define RESPONSE_TYPE 99

void Client();
void Server();
void cleanup_msgq(); /* clean up message queue (ipc resource) */

struct msgform
{
    long msg_type;
    char msg_content[MSGLENGTH];
};

int main()
{
    int client_process, server_process;


    while ( (server_process=fork())==-1 ); /* create server process until success */
    if (!server_process)
    {
        /* server process */
        Server();
    }
    else
    {
        /* parent process */
        while ( (client_process=fork())==-1 ); /* create client process until success */
        if (!client_process) Client(); /* client process */
    }

    /* wait until server and cilent  processes end */
    if (server_process && client_process)
    {
        /* parent process */
        wait(0);
        wait(0);
    }

    printf("Exit the Parent process. \n"); 

    return 0;
}

int msg_queue_id;

void Client()
{
    struct msgform msg[10]; /* sent message var */
    struct msgform msg_rcv; /* receive message var */
    int pid;

    
    
    if ( (msg_queue_id = msgget(MSGKEY, 0777))==-1 )
    {
        /* exception response */
        printf("This message queue with KEY %d does not exist. \n", MSGKEY);
        exit(1); /* exit with exception; */
        return;
    }
    

    pid = getpid();
    const char middle_string[] = {'P', 'I', 'D', ':', '\0'};
    time_t now;
    char pid_str[10];

    for (int i=10;i>0;i--)
    {
        /* create a messge msg[i-1] */
        msg[i-1].msg_type = i;
        now = time(NULL);
        strcpy(msg[i-1].msg_content, ctime(&now) ); /* copy content s2 into s1 */
        strcat(msg[i-1].msg_content, middle_string);
        sprintf(pid_str, "%d", pid); /* convert int into string */
        strcat(msg[i-1].msg_content, pid_str );


        /* send and wait for response */
        msgsnd(msg_queue_id, &msg[i-1], MSGLENGTH, 0);
        printf("(Client)sent;\n");
        msgrcv(msg_queue_id, &msg_rcv, MSGLENGTH, RESPONSE_TYPE, 0);
        printf("(Client)received;\n");

        printf("\n");
    }
    printf("Exit the Client process.\n");
    exit(0);
    return;
}

void Server()
{
    struct msgform msg_rcv; /* received message var */
    struct msgform msg_response;
    size_t count; /* check every type receiver */

    signal(SIGINT, cleanup_msgq);

    if ( (msg_queue_id = msgget(MSGKEY, 0777|IPC_CREAT|IPC_EXCL))==-1 )
    {
        /* exception response */
        printf("This message queue with KEY %d already exist. \n", MSGKEY);
        exit(1); /* exit with exception; */
        return;
    }

    
    for (int i=10;i>0;i--)
    {
        msgrcv(msg_queue_id, &msg_rcv, MSGLENGTH, i, 0); 
        printf("(Server)received;\n");
        printf("message type:%ld \n", msg_rcv.msg_type);
        printf("%s \n", msg_rcv.msg_content);

        msg_response.msg_type = RESPONSE_TYPE;
        msgsnd(msg_queue_id, &msg_response, MSGLENGTH, 0);
        printf("(Server)sent;\n");
        printf("message type:%ld \n", msg_response.msg_type);
    }
    

    /*
    while (1)
    {
        for (int i=10; i>0; i--)
        {
            count = msgrcv(msg_queue_id, &msg_rcv, MSGLENGTH, i, 0); 
            if (count == MSGLENGTH)
                break;
        }
        printf("(Server)received;\n");
        printf("message type:%ld \n", msg_rcv.msg_type);
        printf("%s \n", msg_rcv.msg_content);

        msg_response.msg_type = RESPONSE_TYPE;
        msgsnd(msg_queue_id, &msg_response, MSGLENGTH, 0);
        printf("(Server)sent;\n");
        if (msg_rcv.msg_type == 1)
            break;
        
    }
    */

    /* remove message queue */
    msgctl(msg_queue_id, IPC_RMID, 0);
    printf("Exit the Server process.\n"); 
    exit(0);
    return;
}

void cleanup_msgq()
{
    msgctl(msg_queue_id, IPC_RMID, 0);
    exit(0);
}

