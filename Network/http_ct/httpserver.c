#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#define BUF_LEN 1028
#define SERVER_PORT 8888
//定义好的html页面，实际情况下web server基本是从本地文件系统读取html文件
const static char http_error_hdr[] = "HTTP/1.1 404 Not Found\r\nContent-type: text/html\r\n\r\n";
const static char http_error_html[]= "<html><body><p>404 not found.</body></html>";
const static char http_html_hdr[]  = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
const static char http_index_html[] =
"<html><head><title>Congrats!</title></head>"
"<body><h1>Welcome to our HTTP server demo!</h1>"
"<p>This is a just small test page.</body></html>";

//解析到HTTP请求的文件后，发送本地文件系统中的文件
//这里，我们处理对index文件的请求，发送我们预定好的html文件
//一切从简！
int http_send_file(char *filename, int sockfd)
{
	if(!strcmp(filename, "/")) {
		//通过write函数发送http响应报文；报文包括HTTP响应头和响应内容--HTML文件
		write(sockfd,http_html_hdr,   strlen(http_html_hdr));
		write(sockfd,http_index_html, strlen(http_index_html));
	}
	else {
		// 文件未找到情况下发送404error响应
		printf("%s:xmz file not find!\n",filename);
		write(sockfd,http_error_hdr,strlen(http_error_hdr));
                write(sockfd,http_error_html,strlen(http_error_html));
	}
}

//HTTP请求解析
void serve(int sockfd){
  char buf[BUF_LEN];
  read(sockfd,buf,BUF_LEN);
  printf("read http request:\n\n\n%s\n",buf);
  if(!strncmp(buf,"GET", 3)){
	char *file = buf + 4;
	char *space = strchr(file, ' ');
	if(space != NULL) //这个地方要处理一下，不然会core dump
	{
		*space = '\0';
	}
	else {
		strcpy(file, "");
	}
	printf("file:\n%s\n", file);
	http_send_file(file, sockfd);
  }
  else{
	//其他HTTP请求处理，如POST，HEAD等 。这里我们只处理GET 
	printf("unsupported request!\n");
  }
}

int main() {
  int sockfd,err,newfd;
  struct sockaddr_in addr;
  struct sockaddr_in client_addr;
  int sin_size;
	//建立TCP套接字 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));

	listen(sockfd, 128);

	for(;;) {
		//不间断接收HTTP请求并处理，这里使用单线程，在实际情况下考虑到效率一般多线程 
	    	sin_size=sizeof(struct sockaddr_in);
		newfd = accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size);
        fprintf(stderr, "Connection established;\n");
		serve(newfd);
		close(newfd);
	}

	close(sockfd);
}
