/************************************************************************
 > File Name: crc_ct.h
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com
 > Created Time: Wed 06 Nov 2019 04:09:34 PM CST
************************************************************************/

#ifndef __CRC_CT__
#define __CRC_CT__

#include <stdlib.h>
#include <stdio.h>

typedef char CRC8_t;
typedef uint16_t CRC16_t;
typedef uint16_t CCITT_t;
typedef int CRC32_t;
typedef unsigned short width_t;

#define WIDTH (8 * sizeof(width_t))
#define TOPBIT (1 << (WIDTH - 1))
#define CRC8 0x31
// generating function 
// 100110001
// x^8 + x^5 + x^4 + 1
#define CCITT 0x1021
// generating function
// 10001000000100001
// x^16 + x^12 + x^5 + 1
#define CRC_32 0x04c11db7
// generating function
// 100000100110000010001110110110111
// x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1





// 2 byte
typedef unsigned short CRC_t;
// 4 byte
typedef unsigned int CRC_wid_t;

struct CRC_GF_2{
	CRC_t polynomial;
	CRC_t initial_remainder;
	CRC_t final_xor_value;
};

struct CRC_GF_4{
	CRC_wid_t polynomial;
	CRC_wid_t initial_remainder;
	CRC_wid_t final_xor_value;
};

struct CRC_GF_2 CRC16 = {0x8005, 0x0000, 0x0000};
//struct CRC_GF_2 CCITT = {0x1021, 0xffff, 0x0000};
struct CRC_GF_4 CRC32 = {0x04c11db7, 0xffffffff, 0xffffffff};



CRC8_t crc8_single(char *data, int length);
CRC8_t crc8_simple(char *data, int length);

CCITT_t ccitt_single(char *data, int length);
CCITT_t ccitt_simple(char *data, int length);

CRC32_t crc32_single(char *data, int length, CRC32_t crc);

width_t *crcInit(struct CRC_GF_2 crc);
width_t crcCompute(unsigned char *message, unsigned int nBytes, struct CRC_GF_2 crc, width_t crcTable[]);

void interactive_crcCompute();





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
