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
int TCP_Server_Port;

char buffer[1024];

int main(int argc, char* argv[])
{
    int recv_count;
    int UDP_port;
    char cmd[50];

    if (argc != 3)
    {
        fprintf(stderr, "Wrong format!\nCorrect Usage: <TCP Server IP> <TCP Server Port>\n");
        exit(1);
    }
    if ( inet_atoi(argv[1], &TCP_Server_addr.sin_addr) == 0 )
    {
        fprintf(stderr, "TCP Server IP Error;\n");
        exit(1);
    }
    if ( (TCP_Server_Port = atoi(argv[2])) < 0 )
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
    TCP_Server_addr.sin_family = AF_INET; 
    TCP_Server_addr.sin_port = htons(TCP_Server_Port);
    
    if ( connect(TCPSock_fd, (struct sockaddr *)(&TCP_Server_addr), sizeof(struct sockaddr)) == -1 )
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
    UDP_port = atoi(buffer);

    if ( (recv_count = read(TCPSock_fd, buffer, sizeof(buffer))) == -1 )
    {
        fprintf(stderr, "Read TCP Server Error;\n"); 
        exit(1);
    }
    strcpy(cmd, buffer);


    char cmd_start[] = "START":
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
        scanf("%d", &option):
        while ( option < 1 || option > 3)
        {
            fprintf(stderr, "Input error;\n");
            scanf("%d", &option):
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
            break;
        }
    }
    exit(0);
}

void Option_1()
{
    char cmd_option_1[] = "GET CUR TIME";
    strcpy(buffer, cmd_option_1);
    if ( write(TCPSock_fd, buffer, sizeof(buffer)) == -1)
    {
        fprintf(stderr, "Write error;\n ");
        exit(1);
    }

}



void Option_2()




void Option_3()



