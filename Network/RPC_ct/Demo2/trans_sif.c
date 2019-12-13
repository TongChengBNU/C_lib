/************************************************************************
 > File Name: trans_sif.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Fri Dec 13 19:45:10 2019
************************************************************************/

#include <rpc/rpc.h>

#include <stdio.h>

#include "trans.h"

 

char * readfile(char *);

static char * retcode;

 

char ** readfile_1(char ** w, CLIENT *clnt)

{

   retcode = readfile(*(char**)w);

   return &retcode;

}
