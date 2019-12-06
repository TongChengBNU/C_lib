#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int client_sock_fd;
    struct sockaddr_in server_sock_addr, client_sock_addr;
    int server_port_number;

    if (argc != 3)
    {
        fprintf(stderr, "Correct usage: ./httpclient <server ip> <server port>\n");
        exit(1);
    }
    if (inet_aton(argv[1], &server_sock_addr.sin_addr) == 0)
    {
        fprintf(stderr, "Read ip error;\n");
        exit(1);
    }
    if ((server_port_number = atoi(argv[2])) < 0)
    {
        fprintf(stderr, "Read port number error;\n");
        exit(1);
    }

    if ((client_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "create client socket error;\n");
        exit(1);
    }
    server_sock_addr.sin_family = AF_INET;
    server_sock_addr.sin_port = htons(server_port_number);


    if (connect(client_sock_fd, (struct sockaddr *)(&server_sock_addr), sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr, "Connect to server error;\n");
        exit(1);
    }

    char request[] = "GET / HTTP/1.1\r\nUser-Agent:\r\nHost:\r\nAccpet-Language: en\r\n";
    if ( write(client_sock_fd, request, sizeof(request)) == -1) 
    {
        fprintf(stderr, "Request error;\n");
        exit(1);
    }

    char response[50];
    char recv_message[1024];
    read(client_sock_fd, response, sizeof(response));
    read(client_sock_fd, recv_message, sizeof(recv_message));

    //printf("Response: %s\n", response);
    //printf("Recv: %s\n", recv_message);
    FILE *fp = NULL;
    fp = fopen("./recv.html", "w+");
    fprintf(fp, "%s", response);
    fprintf(fp, "%s", recv_message);
    fclose(fp);

    close(client_sock_fd);



    return 0;

}
