/************************************************************************
 > File Name: CRC_table.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Fri 08 Nov 2019 06:49:30 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crc.h"


/*
* An array containing the pre-computed intermediate result for each
* possible byte of input. This is used to speed up the computation.
*/
// static width_t crcTable[256];

/**
 * Initialize the CRC lookup table.
 * This table is used by crcCompute() to make CRC computation faster.
 */
width_t *crcInit(struct CRC_GF_2 crc);
/**
 * Compute the CRC checksum of a binary message block.
 * @para message, 用来计算的数据
 * @para nBytes, 数据的长度
 * @note This function expects that crcInit() has been called
 *       first to initialize the CRC lookup table.
 */
width_t crcCompute(unsigned char *message, unsigned int nBytes, struct CRC_GF_2 crc, width_t crcTable[]);

void interactive_crcCompute()
{
	printf("Do you need to compute crc? (Y or n)\n");
	char option;
	getc(&option);
	if 
}

int main(int argc, char *argv[])
{
	char data1[] = "HelloWorld";
	char data2[] = "TongCheng";
	width_t *Table_CRC16, *Table_CCITT;

	Table_CRC16 = crcInit(CRC16);
	Table_CCITT =  crcInit(CCITT);


	printf("The cksum(CRC16) of data1 is: %x\n", crcCompute(data1, strlen(data1), CRC16, Table_CRC16));
	printf("The cksum(CCITT) of data1 is: %x\n", crcCompute(data1, strlen(data1), CCITT, Table_CCITT));
	// printf("The cksum of data2 is: %x\n", crcCompute(data2, strlen(data2), CCITT, Table_CCITT));


	return 0;
}




width_t *crcInit(struct CRC_GF_2 crc)
{
	static width_t crcTable[256];

    width_t remainder;
    width_t dividend;
    int bit;
    /* Perform binary long division, a bit at a time. */
    for(dividend = 0; dividend < 256; dividend++)
    {
        /* Initialize the remainder.  */
        remainder = dividend << (WIDTH - 8);
        /* Shift and XOR with the polynomial.   */
        for(bit = 0; bit < 8; bit++)
        {
            /* Try to divide the current data bit.  */
            if(remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^ crc.polynomial;
            }
            else
            {
                remainder = remainder << 1;
            }
        }
        /* Save the result in the table. */
        crcTable[dividend] = remainder;
    }
	return crcTable;
} /* crcInit() */

width_t crcCompute(unsigned char *message, unsigned int nBytes, struct CRC_GF_2 crc, width_t crcTable[])
{
    unsigned int offset;
    unsigned char byte;
    width_t remainder = crc.initial_remainder;
    /* Divide the message by the polynomial, a byte at a time. */
    for( offset = 0; offset < nBytes; offset++)
    {
        byte = (remainder >> (WIDTH - 8)) ^ message[offset];
        remainder = crcTable[byte] ^ (remainder << 8);
    }
    /* The final remainder is the CRC result. */
    return (remainder ^ crc.final_xor_value);
} /* crcCompute() */
