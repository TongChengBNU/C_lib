/* server.c */
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <iostream>

using namespace std;

// why 65535 ? 
#define MAX_BUF_SIZE 65535

#define ERROR 0
#define NORMAL 1

char ClientBuffer[MAX_BUF_SIZE];
const char START_CMD[] = "START";
const char GET_CURRENT_TIME_CMD[] = "GET CURRENT TIME";


// Output user prompt; 
void UserPrompt()
{

}

int main(int argc, char* argv[])
{
    unsigned short ServerUDPPort;

    // socket file descriptor; 
    int client_TCPSocket, client_UDPSocket;
    // 3 struct address 
    struct sockaddr_in TCPServer, UDPServer, RecvFrom;

    int RecvFromLength = sizeof(RecvFrom);
    char UserChoice;
    char portnum[5];
    unsigned long BytesReceived, BytesSent;
    int RetValue;


    // Step 1: check argv[]
    if (argc != 3) 
    {
        cout << "Wrong format!" << endl << "Correct usage: ./client <TCP Server IP> <TCP Server Port>" << endl;
        return ERROR;
    }


    // Step 2: process argv[1]-ip, argv[2]-port
    u_long ServerIP;
    u_short ServerPort;
    if ( (ServerIP = inet_aton(argv[1], &TCPServer.sin_addr)) < 0)
    {
        cout << "Wrong format!" << endl << "Correct usage: ./client <TCP Server IP> <TCP Server Port>" << endl;
        // return ERROR;
        exit(1);
    }

    if ( (ServerPort = atoi(argv[2])) < 0 )
    {
        cout << "Wrong format!" << endl << "Correct usage: ./client <TCP Server IP> <TCP Server Port>" << endl;
        // return ERROR;
        exit(1);
    }


    // Step 3: create 2 sockets: client_TCPSocket, client_UDPSocket 
    client_TCPSocket = socket(AF_INET, SOCK_DGRM, 0); 
    if (client_TCPSocket < 0)
    {
        cout << "cerr: client_TCPSocket Error: " << strerror(errno) << endl; 
        return ERROR;
    }
    client_UDPSocket = socket(AF_INET, SOCK_DGRM, 0); 
    if (client_UDPSocket < 0)
    {
        cout << "cerr: client_UDPSocket Error: " << strerror(errno) << endl; 
        return ERROR;
    }
    

    /* Step 4: Complete server address structure. */
    TCPServer.sin_family = AF_INET;
    TCPServer.sin_port = htons(ServerPort);
    TCPServer.addr_var.sin_addr.s_addr = ServerIP; 

    return 0;
}



