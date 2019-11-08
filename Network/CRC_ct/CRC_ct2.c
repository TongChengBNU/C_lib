#include <stdio.h>
#include <stdlib.h>
#include "libct.h"

typedef char CRC8_t;
typedef int CRC_ITU_t;
#define CRC8 0x31;
// generating function 
// 100110001
// x^8 + x^5 + x^4 + 1
#define CRC_ITU 0x1021;
// generating function
// 10001000000100001
// x^16 + x^12 + x^5 + 1
#define CRC_32 0x04c11db7;
// generating function
// 100000100110000010001110110110111
// x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1

CRC8_t crc8_simple(char *data, int length);

int main(int argc, char *argv[])
{
	char data1[] = {'T', 'o', 'n', 'g'};
	char data2[] = {'T', 'o'};
	// bit series
	// 0101 0100 
	// 0110 1111
	// 0110 1110
	// 0110 0111
	//
	printf("char T's binary representation: %ld\n", DecimalToBinary(data2[0]));
	CRC8_t ret = crc8_simple(data2, 2);
	printf("data2[0] | 0x1: %x\n", data2[0]|0x1);
	printf("size of short: %ld\n", sizeof(char));
	printf("%x\n", ret);
	return 0;
}

CRC8_t crc8_simple(char *data, int length)
{
	CRC8_t crc_reg = *data++;
 	unsigned short count;
	for (; length>1; length--)
	{
		for(count=0;count<8;count++)
		{
			if (crc_reg & 0x80)	
			{
				crc_reg <<= 1;
				if ( *data & (0x80>>count) )
					crc_reg |= 0x1;
				crc_reg ^= CRC8;
			}
			else
			{
				crc_reg <<= 1;
				if ( *data & (0x80>>count) )
					crc_reg |= 0x1;
			}
		}
		data++;
	}
	
	return crc_reg;
}
