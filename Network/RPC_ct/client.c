/************************************************************************
 > File Name: client.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Fri Dec 13 19:39:24 2019
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <rpc/rpc.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <unistd.h>

#include "trans.h"



#define WSVERS MAKEWORD(0, 2)

#define RMACHINE "localhost"

CLIENT *handle;



#define MAXNAME 20

#define MAXLENGTH 1024



char * readfile(char *);



int main()

{

    char name[MAXNAME];

    char * buf;

    printf("Enter File Name: ");

    scanf("%s", name);

   handle = clnt_create(RMACHINE, FILETRANSPROG, FILETRANSVERS,"tcp");

   if (handle == 0) {

         printf("Could Not Connect To Remote Server./n");

         exit(1);

   }

    buf = readfile(name);

    printf("%s", buf);

    return 0;

}
