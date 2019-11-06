/************************************************************************
 > File Name: libct.h
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com
 > Created Time: Wed 06 Nov 2019 04:09:34 PM CST
************************************************************************/

#ifndef __LIBCT_H__
#define __LIBCT_H__

#include <stdlib.h>
#include <stdio.h>

long DecimalToBinary(long decimal)
{
	long ret = 0;
	long multiplier = 1;
	while (decimal)
	{
		ret += multiplier * (decimal%2);
		decimal /= 2;
		multiplier *= 10;
	}
	return ret;
}

#endif
