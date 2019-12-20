/* server.c */
#include <netinet/in.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
// if on Mac-OS, comment this header file
//#include <wait.h>
#include <signal.h>

// why 65535 ? 
#define MAX_BUF_SIZE 65535

#define UDP_PORT_NUMBER 8888

char ClientBuffer[MAX_BUF_SIZE];
const char START_CMD[] = "START";
const char GET_CURRENT_TIME_CMD[] = "GET CURRENT TIME";

void EXIT();

void *listening_thread(void *arg);
void *UDP_service_thread(void *arg);
void *TCP_service_thread(void *arg);


// socket file descriptor; 
int Server_TCPSock_fd, Server_UDPSock_fd;
int Client_TCPSock_fd, Client_UDPSock_fd;

// 3 struct address 
struct sockaddr_in Server_TCP_addr, Server_UDP_addr;
struct sockaddr_in Client_TCP_addr, Client_UDP_addr;

int Server_UDP_port = UDP_PORT_NUMBER;


int main(int argc, char* argv[])
{
    char buffer[1024];


    // Step 1: check argv[]
    if (argc != 2) 
    {
        fprintf(stderr, "Wrong format;\nCorrect usage: %s <TCP Server Port>\n ", argv[0]);
        exit(1);
    }


    // Step 2: port argv[1]
    int Server_TCP_Port;
    if ( (Server_TCP_Port = atoi(argv[1])) < 0 )
    {
        fprintf(stderr, "Port number Error;\nCorrect usage: %s <TCP Server Port>\n ", argv[0]);
        exit(1);
    }


    // Step 3: create 2 sockets: client_TCPSocket, client_UDPSocket 
    if ( (Server_TCPSock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
        fprintf(stderr, "Server TCP socket file descriptor error;\n"); 
        exit(1);
    }
    if ( (Server_UDPSock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    {
        fprintf(stderr, "Server UDP socket file descriptor error;\n"); 
        exit(1);
    }


    /* Step 4: Complete server address structure. */
    bzero(&Server_TCP_addr, sizeof(struct sockaddr_in));
    Server_TCP_addr.sin_family = AF_INET;
    Server_TCP_addr.sin_port = htons(Server_TCP_Port);
    Server_TCP_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

    bzero(&Server_UDP_addr, sizeof(struct sockaddr_in));
    Server_UDP_addr.sin_family = AF_INET;
    Server_UDP_addr.sin_port = htons(Server_UDP_port);
    Server_UDP_addr.sin_addr.s_addr = htonl(INADDR_ANY); 


    /* Step 5: TCP, UDP binding */
    if ( bind(Server_TCPSock_fd, (struct sockaddr *)(&Server_TCP_addr), sizeof(struct sockaddr)) == -1 )
    {
        fprintf(stderr, "TCP Bind error;\n ");
        exit(1);
    }

    if ( bind(Server_UDPSock_fd, (struct sockaddr *)(&Server_UDP_addr), sizeof(struct sockaddr)) == -1 )
    {
        fprintf(stderr, "UDP Bind error;\n ");
        exit(1);
    }



    /* Step 6: create a TCP listening thread */
    //pthread_t listening_thread_id;
    //if ( pthread_create(&listening_thread_id, NULL, listening_thread, NULL) != 0)
    //{
    //    fprintf(stderr, "Listening thread creation failed;\n");
    //    exit(1);
    //}
    
    long listening_pid;
    if ( (listening_pid = fork()) < 0 )
    {
        fprintf(stderr, "Listening process creation failed;\n");
        exit(1);
    }
    else if ( listening_pid == 0)
    {
        // in listening process 

        listening_thread(NULL);
    }
    
    
    // sleep(10);
    // wait(0);

    int status;
    if (waitpid(-1, &status, 0) == -1)
    {
        fprintf(stderr, "Wait pid error;\n");
    }
    else
    {
        if (WIFEXITED(status))
        {
            printf("Child process with status code %d has terminated;\n", WEXITSTATUS(status));
        }
    }

    // printf("Hello\n");
    close(Server_TCPSock_fd);
    close(Server_UDPSock_fd);
    close(Client_TCPSock_fd);
    close(Client_UDPSock_fd);

    return 0;
}



void *listening_thread(void *arg)
{
    signal(SIGINT, EXIT); 

    int backlog_num = 5;
    if ( listen(Server_TCPSock_fd, backlog_num) == -1)
    {
        fprintf(stderr, "TCP listen error;\n ");
        exit(1);
    }

    // only one service thread is allowed.
    // pthread_t TCP_service_thread_id;
    char cmd[] = " START";

    // accept and create TCP service thread for every loop
    while(1)
    {
        socklen_t addr_len = sizeof(struct sockaddr);
        if( (Client_TCPSock_fd = accept(Server_TCPSock_fd, (struct sockaddr *)(&Client_TCP_addr), &addr_len)) == -1)
        {
            //fprintf(stderr, "TCP accept error:\s\n\a ", strerror(errno));
            fprintf(stderr, "TCP accept error;\n");
            exit(1);
        }
        fprintf(stdout, "Get connection from %s.\n", inet_ntoa(Client_TCP_addr.sin_addr));
        fflush(stdout);


        //if ( pthread_create(&TCP_service_thread_id, NULL, TCP_service_thread, NULL) != 0)
        //{
        //    fprintf(stderr, "TCP service thread creation failed with IP: %s;\n", inet_ntoa(Client_TCP_addr.sin_addr));
        //    exit(1);
        //}

        long TCP_service_pid;
        if ( (TCP_service_pid = fork()) < 0)
        {
            fprintf(stderr, "TCP service process failed;\n");
            exit(1);
        }
        else if (TCP_service_pid == 0)
        {
            // in TCP service process
            fprintf(stderr, "TCP service creation success;\n");
            TCP_service_thread(NULL);
        }

    }

    // no out entry
    // to be continued ...
    printf("Child is about to terminate;\n");
    exit(0);
}

void *TCP_service_thread(void *arg)
{
    // to be continued ...
    //
    int recv_count;
    char cmd[] = "START";
    char option_1[] = "GET CUR TIME";
    char buffer[1024];


    /* Send UDP_port */
    sprintf(buffer, "%d", Server_UDP_port);
    if ( write(Client_TCPSock_fd, buffer, sizeof(buffer)) == -1 )
    {
        fprintf(stderr, "Write error;\n ");
        exit(1);
    }
    /* Send start cmd */
    strcpy(buffer, cmd);
    if ( write(Client_TCPSock_fd, buffer, sizeof(buffer)) == -1 )
    {
        fprintf(stderr, "Write error;\n ");
        exit(1);
    }

    pid_t UDP_service_pid; 
    if ( (UDP_service_pid=fork()) < 0 )
    {
        fprintf(stderr, "UDP service creation failed;\n");
        exit(1);
    }
    else if ( UDP_service_pid == 0 )
    {
        fprintf(stderr, "UDP service creation success;\n");
        UDP_service_thread(NULL);
    }

    time_t now;
    while (1)
    {
        if ( (recv_count = read(Client_TCPSock_fd, buffer, sizeof(buffer))) == -1 )
        {
            fprintf(stderr, "Read Client Error;\n"); 
            exit(1);
        }
        // buffer[recv_count] = "\0";
        if ( strcmp(option_1, buffer) == 0)
        {
            // sent local system time
            now = time(NULL);
            sprintf(buffer, "%s", ctime(&now));
            if ( write(Client_TCPSock_fd, buffer, sizeof(buffer)) == -1 )
            {
                fprintf(stderr, "Write current time error;\n ");
                exit(1);
            }

        }

        
    }

    // no out entry
    // to be continued ...
}

void *UDP_service_thread(void *arg)
{
    // to be continued ...
	struct sockaddr_in addr; 
	int addrlen, recv_count; 
	char buffer[1024]; 
    socklen_t addr_len = sizeof(struct sockaddr);
	while(1) 
	{  
        /* read data from internet; */
		recv_count = recvfrom(Server_UDPSock_fd, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_len);

        fprintf(stderr, "Received message:%s", buffer);

        /* send info received back to client; */
		sendto(Server_UDPSock_fd, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(struct sockaddr)); 

        printf("Send back to client;\n");
	} 

    // no out entry
    // to be continued ...
}

void EXIT()
{
    exit(0);
}
