/*udpclient.c */ 
#include <netinet/in.h> 
#include <stdio.h>
#include <errno.h>
#define MAX_BUF_SIZE 1024 
void udpc_requ(int sockfd,const struct sockaddr_in *addr,int len) 
{ 
<<<<<<< HEAD
char buffer[MAX_BUF_SIZE]; 
int n; 
while(1) 
{ /*ѭ��*/
/*�ӿ���̨��������,���͸�udp������*/ 
fgets(buffer,MAX_BUF_SIZE,stdin); 
sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)addr, len);
bzero(buffer,MAX_BUF_SIZE); 
/*�ӷ�������������*/
n=recvfrom(sockfd,buffer,MAX_BUF_SIZE,0,NULL,NULL); 
buffer[n]=0; 
fputs(buffer,stdout); 
} 
=======
	char buffer[MAX_BUF_SIZE]; 
	int n; 
	
	while(1) 
	{  /*ѭ��*/
		/*�ӿ���̨��������,���͸�udp������*/ 
		fgets(buffer,MAX_BUF_SIZE,stdin); 
		sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)addr, len);
		bzero(buffer,MAX_BUF_SIZE); 
		/*�ӷ�������������*/
		n=recvfrom(sockfd,buffer,MAX_BUF_SIZE,0,NULL,NULL); 
		buffer[n]=0; 
		fputs(Sbuffer,stdout); 
	} 
>>>>>>> origin_C_lib/master
} 

int main(int argc,char **argv)
{ 
<<<<<<< HEAD
int sockfd,port; 
struct sockaddr_in addr; 
if(argc!=3) 
{ 
fprintf(stderr,"Usage:%s server_ip server_port\n",argv[0]); 
exit(1); 
}
if((port=atoi(argv[2]))<0) 
{
fprintf(stderr,"Usage:%s server_ip server_port\n",argv[0]); 
/*�ͻ������з�ʽ����Ҫ��������ip�ͷ������Ķ˿�*/
exit(1); 
} 
sockfd=socket(AF_INET, SOCK_DGRAM,0); 
if(sockfd<0) 
{ 
fprintf(stderr,"Socket Error:%s\n",strerror(errno)); 
exit(1); 
} 
/*����������ַ�ṹ*/ 
bzero(&addr,sizeof(struct sockaddr_in)); 
addr.sin_family=AF_INET;
addr.sin_port=htons(port); 
if(inet_aton(argv[1],&addr.sin_addr)<0) 
{ 
fprintf(stderr,"ip error:%s\n",strerror(errno)); 
exit(1); 
}
udpc_requ(sockfd,&addr,sizeof(struct sockaddr_in)); 
close(sockfd); 
=======
	int sockfd,port; 
	struct sockaddr_in addr; 
	if(argc!=3) 
	{ 
		fprintf(stderr,"Usage:%s server_ip server_port\n",argv[0]); 
		exit(1); 
	}
	if((port=atoi(argv[2]))<0) 
	{
		fprintf(stderr,"Usage:%s server_ip server_port\n",argv[0]); 
		/*�ͻ������з�ʽ����Ҫ��������ip�ͷ������Ķ˿�*/
		exit(1); 
	} 
	
	sockfd=socket(AF_INET, SOCK_DGRAM,0); 
	if(sockfd<0) 
	{ 
		fprintf(stderr,"Socket Error:%s\n",strerror(errno)); 
		exit(1); 
	} 
	/*����������ַ�ṹ*/ 
	bzero(&addr,sizeof(struct sockaddr_in)); 
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port); 
	if(inet_aton(argv[1],&addr.sin_addr)<0) 
	{ 
		fprintf(stderr,"ip error:%s\n",strerror(errno)); 
		exit(1); 
	}
	udpc_requ(sockfd,&addr,sizeof(struct sockaddr_in)); 
	close(sockfd); 
>>>>>>> origin_C_lib/master
} 
