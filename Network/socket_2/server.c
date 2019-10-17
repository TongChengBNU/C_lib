/* server.c */
#include <netinet/in.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// why 65535 ? 
#define MAX_BUF_SIZE 65535

#define ERROR 0
#define NORMAL 1
#define UDP_PORT_NUMBER 8888

char ClientBuffer[MAX_BUF_SIZE];
const char START_CMD[] = "START";
const char GET_CURRENT_TIME_CMD[] = "GET CURRENT TIME";




int main(int argc, char* argv[])
{

    // socket file descriptor; 
    int server_TCPSock_fd, server_UDPSock_fd;
    int client_TCPSock_fd, client_UDPSock_fd;

    // 3 struct address 
    struct sockaddr_in Server_TCP_addr, Server_UDP_addr;
    struct sockaddr_in Client_TCP_addr, Client_UDP_addr;

    int UDP_port = UDP_PORT_NUMBER;
    char buffer[1024];


    // Step 1: check argv[]
    if (argc != 3) 
    {
        fprintf(stderr, "Wrong format;\nCorrect usage: ./%s <TCP Server Port>\n ", argv[0]);
        exit(1);
    }


    // Step 2: port argv[1]
    int Server_TCP_Port;
    if ( (Server_TCP_Port = atoi(argv[1])) < 0 )
    {
        fprintf(stderr, "Wrong format;\nCorrect usage: ./%s <TCP Server Port>\n ", argv[0]);
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

    /* Step 5: binding */
    if ( bind(Server_TCPSock_fd, (struct sockaddr *)(&Server_TCP_addr), sizeof(struct sockaddr)) == -1 )
    {
        fprintf(stderr, "TCP Bind error;\n ");
        exit(1);
        return ERROR;
    }

    /* Step 6: listening */
    int backlog_num = 5;
    if ( listen(Server_TCPSock_fd, backlog_num) == -1)
    {
        fprintf(stderr, "TCP listen error;\n ");
        exit(1);
    }

    /* Step 7: TCP accept */
    char cmd[] = " START";
    while(1)
    {
        if( (Client_TCPSock_fd = accept(Server_TCPSock_fd, (struct sockaddr *)(&Client_TCP_addr), sizeof(struct sockaddr))) == -1)
        {
            fprintf(stderr, "TCP accept error:\s\n\a ", strerror(errno));
            exit(1);
        }
        fprintf(stdout, "Get connection from %s.\n", inet_ntoa(Client_TCP_addr.sin_addr));
        fflush(stdout);

        /* Send UDP_port */
        sprintf(buffer, "%d", UDP_port);
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




    }
    return 0;
}



