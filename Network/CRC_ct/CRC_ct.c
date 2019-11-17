#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "crc_ct.h"



int main(int argc, char *argv[])
{
	char data1[] = {'1','2','3','4','5','6','7','8','9'};

	//printf("%x\n", crc8_single(data3, 9));
	//printf("%x\n", crc8_simple(data3, 9));
	//printf("%04x\n", ccitt_single(data3, 9));
	//printf("%04x\n", ccitt_simple(data3, 9));
	
	interactive_crcCompute();

	return 0;
}

CRC8_t crc8_single(char *data, int length)
{
	CRC8_t crc_reg = *data++;
 	unsigned short count;
	for (; length>1; length--)
	{
		for(count=0;count<8;count++)
		{
			crc_reg <<= 1;
			if ( *data & (0x80>>count) )
				crc_reg |= 0x1;
			crc_reg ^= CRC8;
		}
		data++;
	}
	
	return crc_reg;
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

CCITT_t ccitt_single(char *data, int length)
{
	CCITT_t crc = 0xffff;
	int i;

	for(; length>0; length--)
	{
		crc = crc ^ (*data++ <<8);
		for(i=0;i<8;i++)
			crc = (crc << 1) ^ (CCITT * ((crc&0x8000)>>15));
		crc &= 0xffff;
	}
	return crc;
}

CCITT_t ccitt_simple(char *data, int length)
{
	// why initial value shoud be ffff????
	CCITT_t crc = 0xffff;
	int i;

	for(; length>0; length--)
	{
		crc = crc ^ (*data++ <<8);
		for(i=0;i<8;i++)
		{
			if (crc & 0x8000)	
				crc = (crc << 1) ^ CCITT;
			else
				crc <<= 1;
		}
		// crc &= 0xffff;
	}

	return crc;
}

CRC32_t crc32_single(char *data, int length, CRC32_t crc)
{
	int i;
	for(;length>0;length--)
	{
		crc = crc ^(*data++ <<24);
	}

	return crc;
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

void interactive_crcCompute()
{
	char option_continue;
	printf("Do you need to compute crc? (y or n)\n");
	scanf("%c", &option_continue);
	while(option_continue == 'y')
	{
		int option;
		char buffer[1024];
		int cksum;
		printf("Please input your message:\n");
		setbuf(stdin, NULL);
		fgets(buffer, 1024, stdin);
		printf("Please select a method below:\n");
		printf("1. CRC8; 2. CCITT; 3. CRC32;\n");
		scanf("%d", &option);
		switch(option){
			case 1:
				cksum = crc8_simple(buffer, strlen(buffer));
				printf("cksum:%02x\n", cksum);
				break;
			case 2:
				cksum = ccitt_simple(buffer, strlen(buffer));
				printf("cksum:%04x\n", cksum);
				break;
			case 3:
				printf("Not finished;\n");
				break;
		}

		printf("Do you need to compute crc? (y or n)\n");
		setbuf(stdin, NULL);
		scanf("%c", &option_continue);
	}
	return;
}
