/* client.c */
#include <netinet/in.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Output user prompt; 
void UserPrompt();
void Option_1();
void Option_2();
void Option_3();

int Server_TCP_fd;
int TCPSock_fd, UDPSock_fd;
int Server_TCP_Port, Server_UDP_Port;

struct sockaddr_in Server_TCP_addr, Server_UDP_addr; 


int main(int argc, char* argv[])
{
    int recv_count;
    char cmd[50];
    char buffer[1024];

    if (argc != 3)
    {
        fprintf(stderr, "Wrong format!\nCorrect Usage: <TCP Server IP> <TCP Server Port>\n");
        exit(1);
    }
    if ( inet_aton(argv[1], &Server_TCP_addr.sin_addr) == 0 )
    {
        fprintf(stderr, "TCP Server IP Error;\n");
        exit(1);
    }
    if ( (Server_TCP_Port = atoi(argv[2])) < 0 )
    {
        fprintf(stderr, "TCP Server Port Error;\n");
        exit(1);
    }


    /* create 2 sockets for TCP and UDP */
    if ( (TCPSock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
        fprintf(stderr, "TCP socket file descriptor error;\n"); 
        exit(1);
    }
    if ( (UDPSock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    {
        fprintf(stderr, "UDP socket file descriptor error;\n"); 
        exit(1);
    }

    /* complete struct of TCP_Server_addr */
    Server_TCP_addr.sin_family = AF_INET; 
    Server_TCP_addr.sin_port = htons(Server_TCP_Port);
    
    if ( connect(TCPSock_fd, (struct sockaddr *)(&Server_TCP_addr), sizeof(struct sockaddr)) == -1 )
    {
        fprintf(stderr, "Connect to TCP Server Error;\n"); 
        exit(1);
    }

    /* connection success */
    if ( (recv_count = read(TCPSock_fd, buffer, sizeof(buffer))) == -1 )
    {
        fprintf(stderr, "Read TCP Server Error;\n"); 
        exit(1);
    }

    Server_UDP_Port = atoi(buffer);
    /* complete struct of UDP_Server_addr */
    Server_UDP_addr.sin_family = AF_INET; 
    Server_UDP_addr.sin_port = htons(Server_UDP_Port);
    // Server_UDP_addr.sin_addr = 
    inet_aton(argv[1], &Server_UDP_addr.sin_addr);

    fprintf(stderr, "Get UDP port number from server: %d\n", Server_UDP_Port);

    if ( (recv_count = read(TCPSock_fd, buffer, sizeof(buffer))) == -1 )
    {
        fprintf(stderr, "Read TCP Server Error;\n"); 
        exit(1);
    }
    strcpy(cmd, buffer);


    char cmd_start[] = "START";
    if ( strcmp(cmd, cmd_start) == 0)
        UserPrompt();

    return 0;
}



void UserPrompt()
{
    int option;
    while (1)
    {
        fprintf(stdout, "1. Get current time(TCP)\n");
        fprintf(stdout, "2. Echo Mode(UDP)\n");
        fprintf(stdout, "3. Exit the program\n");
        fprintf(stdout, "Please select an option [1/2/3]:\n");
        scanf("%d", &option);
        while ( option < 1 || option > 3)
        {
            fprintf(stderr, "Input error;\n");
            scanf("%d", &option);
        }

        switch(option)
        {
            case 1:
                Option_1();
                break;
            case 2:
                Option_2();
                break;
            case 3:
                Option_3();
                break;
        }
    }
    exit(0);
}

void Option_1()
{
    char cmd_option_1[] = "GET CUR TIME";
    int recv_count;
    char buffer[1024];
    
    strcpy(buffer, cmd_option_1);
    if ( write(TCPSock_fd, buffer, sizeof(buffer)) == -1)
    {
        fprintf(stderr, "Write error;\n ");
        exit(1);
    }
    
    if ( (recv_count = read(TCPSock_fd, buffer, sizeof(buffer))) == -1 )
    {
        fprintf(stderr, "Read TCP Server Error;\n"); 
        exit(1);
    }
    fprintf(stderr, "Current time from server:\n");
    fprintf(stderr, "%s", buffer);
    
}

void Option_2()
{
	char buffer[1024]; 
	int recv_count; 
    char cache[1024];
    socklen_t addr_len = sizeof(struct sockaddr);


    /* input data and send it to udp server */ 
    fprintf(stdout, "Please input message to be sent to Server:\n");
    setbuf(stdin, NULL);

    // getchar();
	fgets(buffer, 1024, stdin); 
    strcpy(cache, buffer);

    
	sendto(UDPSock_fd, buffer, 1024, 0, (struct sockaddr*)(&Server_UDP_addr), sizeof(struct sockaddr));
	bzero(buffer, 1024); 

	/* receive data from udp server */
	recv_count = recvfrom(UDPSock_fd, buffer, 1024, 0, (struct sockaddr*)(&Server_UDP_addr), &addr_len); 
	// buffer[recv_count] = 0; 
    printf("Response:%s", buffer);

    // validation
    if ( strcmp(buffer, cache) == 0)
    {
        fprintf(stderr, "Correct read and write;\n");
    }
    else
    {
        fprintf(stderr, "Error during UDP read and write;\n");
        exit(1);
    }
}



void Option_3()
{
    exit(0);
}



