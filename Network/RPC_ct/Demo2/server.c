/************************************************************************
 > File Name: server.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Fri Dec 13 19:40:02 2019
************************************************************************/

#include <rpc/rpc.h>

#include <stdio.h>

#include <stdlib.h>

#include "trans.h"

 

#define MAXNAME 20

#define MAXLENGTH 1024

 

char * readfile(char * name)

{

    FILE *file = fopen(name, "r");

    char * buf = (char *)malloc(sizeof(char)*MAXLENGTH);

    if (file == NULL)

    {

        printf("File Cann't Be Open!");

        return 0;

    }

    printf("The File Content is : /n");

    while (fgets(buf, MAXLENGTH-1, file) != NULL)

    {

        return buf;

    }

    return NULL;

}
