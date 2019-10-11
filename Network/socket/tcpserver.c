/*******服务器程序(server.c) ************/
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <errno.h>
int main(int argc, char *argv[])
{
int sockfd, new_fd;
struct sockaddr_in server_addr;
struct sockaddr_in client_addr;
int sin_size, portnumber;
char hello[]="Hello! Are You Fine?\n";
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
/*创建套接字*/
if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
{
fprintf(stderr, "Socket error:%s\n\a",strerror(errno));
exit(1);
}
/*填充服务器的地址结构*/
bzero(&server_addr, sizeof(struct sockaddr_in));
server_addr.sin_family=AF_INET;
server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
server_addr.sin_port=htons(portnumber);
/* 套接字绑定地址*/
if(bind(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr))==-1)
{
fprintf(stderr, "Bind error:%s\n\a", strerror(errno));
exit(1);
}
/* 进入监听状态*/
if(listen(sockfd, 5)==-1)
{
fprintf(stderr, "Listen error:%s\n\a",strerror(errno));
exit(1);
}
while(1)
{
/* 接收客户端的连接 */
sin_size=sizeof(struct sockaddr_in);
if((new_fd=accept(sockfd, (struct sockaddr *)(&client_addr), &sin_size))==-1)
{
/*new_fd是新的连接套接字*/
fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
exit(1);
}
fprintf(stderr,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr));
if(write(new_fd, hello,strlen(hello))==-1)
{
/*发送信息*/
fprintf(stderr,"Write Error:%s\n",strerror(errno));
exit(1);
}
/* */
close(new_fd);
/*关闭该连接*/
}
close(sockfd);
exit(0);
}
