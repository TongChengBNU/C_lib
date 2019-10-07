/*******·(tcpserver.c) ************/
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <errno.h>

#include <string.h>
#include <stdlib.h>
#include <unistd.h>  /* write() or read() */

int main(int argc, char *argv[])
{
	int sockfd, new_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int sin_size, portnumber;
	char hello[]="Hello! Are You Fine?\n";

	/* Parameters validation */
	if(argc!=2)
	{
		fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
		exit(1);
	}
	if((portnumber=atoi(argv[1]))<0)
	{
		fprintf(stderr,"Usage:%s portnumber\a\n", argv[0]);
		exit(1);
	}

	/* Step 1: establish socket */
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		fprintf(stderr, "Socket error:%s\n\a",strerror(errno));
		exit(1);
	}

	/* append info in struct server_addr */
	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(portnumber);

	/* Step 2: bind */
	if(bind(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr))==-1)
	{
		fprintf(stderr, "Bind error:%s\n\a", strerror(errno));
		exit(1);
	}

	/* Step 3: listen */
	if(listen(sockfd, 5)==-1)
	{
		fprintf(stderr, "Listen error:%s\n\a",strerror(errno));
		exit(1);
	}

	/* Start the process */
	while(1)
	{
		/* Step 4; accept */
		sin_size=sizeof(struct sockaddr_in);
		if((new_fd=accept(sockfd, (struct sockaddr *)(&client_addr), &sin_size))==-1)
		{
			/* exception during acception */
			fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
			exit(1);
		}

		fprintf(stderr,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr));
		
		/* Step 5: write() or read() */
		if(write(new_fd, hello,strlen(hello))==-1)
		{
			/* exception during writing */
			fprintf(stderr,"Write Error:%s\n",strerror(errno));
			exit(1);
		}
		close(new_fd);
	}
	/* Step 6: close socket */
	close(sockfd);
	exit(0);
}
