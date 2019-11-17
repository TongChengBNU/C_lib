#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned short int uint16_t;
#define POLY        0x1021
/**
 * Calculating CRC-16 in 'C'
 * @para addr, start of data
 * @para num, length of data
 * @para crc, incoming CRC
 */

uint16_t crc16(unsigned char *addr, int num, uint16_t crc)
{
	int i;
    for (; num > 0; num--)              /* Step through bytes in memory */
    {
        crc = crc ^ (*addr++ << 8);     /* Fetch byte from memory, XOR into CRC top byte*/
        for (i = 0; i < 8; i++)             /* Prepare to rotate 8 bits */
        {
            if (crc & 0x8000)            /* b15 is set... */
                crc = (crc << 1) ^ POLY;    /* rotate and XOR with polynomic */
            else                          /* b15 is clear... */
                crc <<= 1;                  /* just rotate */
        }                             /* Loop for 8 bits */
        crc &= 0xFFFF;                  /* Ensure CRC remains 16-bit value */
    }                               /* Loop until num=0 */
    return(crc);                    /* Return updated CRC */
}

int main(int argc, char *argv[])
{

	unsigned char data1[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	unsigned char data2[] = {'5', '6', '7', '8', '9'};
	unsigned short c1, c2;

	c1 = crc16(data1, 9, 0xffff);
	c2 = crc16(data1, 4, 0xffff);
	c2 = crc16(data2, 5, c2);
	printf("%04x\n", c1);
	printf("%04x\n", c2);

    
    return 0;
}
