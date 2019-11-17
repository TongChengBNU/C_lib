/************************************************************************
 > File Name: crc.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Fri 08 Nov 2019 06:50:10 PM CST
************************************************************************/

#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED
 

typedef unsigned short CRC_t;
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
struct CRC_GF_2 CCITT = {0x1021, 0xffff, 0x0000};
struct CRC_GF_4 CRC32 = {0x04c11db7, 0xffffffff, 0xffffffff};


/*
* The CRC parameters. Currently configured for CCITT.
* Simply modify these to switch to another CRC Standard.
*/

/*
#define POLYNOMIAL          0x8005
#define INITIAL_REMAINDER   0x0000
#define FINAL_XOR_VALUE     0x0000
*/

// #define CRC_ITU_POLYNOMIAL          0x1021
// #define INITIAL_REMAINDER   0xFFFF
// #define FINAL_XOR_VALUE     0x0000
 
/*
#define POLYNOMIAL          0x1021
#define POLYNOMIAL          0xA001
#define INITIAL_REMAINDER   0xFFFF
#define FINAL_XOR_VALUE     0x0000
*/
 
/*
* The width of the CRC calculation and result.
* Modify the typedef for an 8 or 32-bit CRC standard.
*/

typedef unsigned short width_t;
#define WIDTH (8 * sizeof(width_t))
#define TOPBIT (1 << (WIDTH - 1))
 
/*
 * Initialize the CRC lookup table.
 * This table is used by crcCompute() to make CRC computation faster.
 */
// void crcInit(CRC_GF_2 crc);
 
/**
 * Compute the CRC checksum of a binary message block.
 * @para message, 用来计算的数据
 * @para nBytes, 数据的长度
 * @note This function expects that crcInit() has been called
 *       first to initialize the CRC lookup table.
 */
// width_t crcCompute(unsigned char * message, unsigned int nBytes);
 

#endif
