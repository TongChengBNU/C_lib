/************************************************************************
 > File Name: date_server.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Fri Dec 13 20:12:08 2019
************************************************************************/

#include <time.h>
#include "date.h"

long * get_date_1_svc(void *argp, struct svc_req *rqstp)
{
    static long result;

    result = time((long *)0);

    return &result;
}
