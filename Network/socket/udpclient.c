/*udpclient.c */ 
#include <netinet/in.h> 
#include <stdio.h>
#include <errno.h>

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_BUF_SIZE 1024    

void udpc_requ(int sockfd, const struct sockaddr_in *addr, int len) 
{ 
	char buffer[MAX_BUF_SIZE]; 
	int n; 
	
    /* Loop begin */
	while(1) 
	{  
		/* input data and send it to udp server */ 
		fgets(buffer, MAX_BUF_SIZE, stdin); 
		sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)addr, len);
		bzero(buffer,MAX_BUF_SIZE); 

		/* receive data from udp server */
		n=recvfrom(sockfd, buffer, MAX_BUF_SIZE, 0, NULL, NULL); 
		buffer[n]=0; 
		fputs(buffer, stdout); 
	} 
} 


int main(int argc,char **argv)
{ 
	int sockfd, port; 
	struct sockaddr_in addr; 

    /* 3 params needed; */
	if(argc!=3) 
	{ 
		fprintf(stderr, "Usage:%s server_ip server_port\n", argv[0]); 
		exit(1); 
	}
	if( (port=atoi(argv[2])) < 0 ) 
	{
		fprintf(stderr,"Usage:%s server_ip server_port\n",argv[0]);
		/*客户端运行方式，需要服务器的ip和服务器的端口*/
        /* server_ip server_port */
		exit(1); 
	} 
	
	sockfd=socket(AF_INET, SOCK_DGRAM, 0); 
	if(sockfd<0) 
	{ 
		fprintf(stderr,"Socket Error:%s\n",strerror(errno)); 
		exit(1); 
	} 

    /* Complete server address structure. */
	bzero(&addr,sizeof(struct sockaddr_in)); 
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port); 
	if(inet_aton(argv[1],&addr.sin_addr)<0) 
	{ 
		fprintf(stderr,"ip error:%s\n",strerror(errno)); 
		exit(1); 
	}
	udpc_requ(sockfd, &addr, sizeof(struct sockaddr_in)); 
	close(sockfd); 
} 
