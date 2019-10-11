/*客户端程序(client.c) ************/ 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h> 
#include <errno.h>
int main(int argc, char *argv[]) 
{ 
int sockfd; 
char buffer[1024]; 
struct sockaddr_in server_addr; 
int portnumber,nbytes; 
if(argc!=3) 
{ 
fprintf(stderr,"Usage:%s hostname portnumber\a\n",argv[0]); 
exit(1); 
} 
if(inet_aton(argv[1],&server_addr.sin_addr)==0)
{
fprintf(stderr,"the hostip is not right;");
exit(1);
}
if((portnumber=atoi(argv[2]))<0) 
{ 
fprintf(stderr, "Usage:%s hostname portnumber\a\n", argv[0]); 
exit(1); 
} 
/*创建套接字*/ 
if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) 
{ fprintf(stderr,"Socket Error:%s\a\n",strerror(errno)); 
exit(1); 
} 
/*填充服务器的地址信息 */ 
server_addr.sin_family=AF_INET; 
server_addr.sin_port=htons(portnumber); 
/*向服务器发起连接 */ 
if(connect(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr))==-1) 
{ 
/*连接失败退出*/
fprintf(stderr, "Connect Error:%s\a\n",strerror(errno)); 
exit(1); 
} 
/* 连接成功后，从服务器接收信息*/ 
if((nbytes=read(sockfd, buffer, 1024))==-1) 
{ 
fprintf(stderr, "Read Error:%s\n", strerror(errno)); 
exit(1); 
} 
buffer[nbytes]='\0'; 
printf("I have received:%s\n", buffer); 
/* 关闭套接字*/ 
close(sockfd); 
exit(0); 
} 
