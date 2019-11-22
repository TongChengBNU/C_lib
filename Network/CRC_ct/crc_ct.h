/************************************************************************
 > File Name: crc_ct.h
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com
 > Created Time: Wed 06 Nov 2019 04:09:34 PM CST
************************************************************************/

#ifndef __CRC_CT__
#define __CRC_CT__


typedef char CRC8_t;
typedef uint16_t CRC16_t;
typedef uint16_t CCITT_t;
typedef int CRC32_t;
typedef unsigned short width_t;

// method 1
#define CRC8 0x31
// #define CRC8 0x07
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

CRC8_t crc8_simple(char *data_ori, int length, CRC8_t crc);
CCITT_t ccitt_simple(char *data, int length, CCITT_t crc_last);
CRC32_t crc32_simple(char *data, int length, CRC32_t crc_last);





// method 2
#define WIDTH (8 * sizeof(width_t))
#define TOPBIT (1 << (WIDTH - 1))

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

struct CRC_GF_2 CRC16 = {0x1021, 0xffff, 0x0000};
struct CRC_GF_4 CRC32 = {0x04c11db7, 0xffffffff, 0xffffffff};

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

/* Demo of CRC8
 * 'T' 'O' 0101 0100 0100 1111
 *
 *                  101                              
 *                ---------------------------
 *      100110001/ 010101000100111100000000
 *                  100110001                                     
 *                  -----------------------------                    
 *                  00110000000                                      
 *                    100110001                                   
 *                    -----------------------
 *                    0101100011
 *                     100110001                                   
 *                     ---------------------
 *                     00101001011                                   
 *                       100110001                                  
 *                       ---------------------
 *                       00111101010                                 
 *                         100110001                               
 *                         -------------------
 *                         0110110110                               
 *                          100110001                              
 *                          -----------------
 *                          0100001110
 *                           100110001
 *                           ------------------
 *                           000111111000                             
 *                              100110001                          
 *                              -----------------
 *                              0110010010                          
 *                               100110001                         
 *                               ----------------
 *                               0101000110
 *                                100110001
 *                                -------------------
 *                                001110111  
 *  cksum: 0111 0111 0x77
 * */

/* Demo CCITT (CRC16)
 *  input: 123456789
 *  output: 0x29b1
 * */

/* Demo CRC32
 * 'T' 'O' 0101 0100 0100 1111
 *
 *                                   -----------------------------------------------------------
 * 100000100110000010001110110110111/010101000100111100000000000000000000000000000000
 *                                    100000100110000010001110110110111
 *                                   ----------------------------------
 *									  00101010111111101000111011011011100 
 *                                      100000100110000010001110110110111
 *                                      ---------------------------------
 *                                      00101001100110101011010110110101100
 *                                        100000100110000010001110110110111
 *                                        ---------------------------------
 *                                        00100100000010100101100000001101100
 *                                          100000100110000010001110110110111 
 *                                          ---------------------------------
 *                                          000100100100100111101110111011011000
 *                                             100000100110000010001110110110111
 *                                             ---------------------------------
 *                                             000100000010111111111001101101111000
 *                                                100000100110000010001110110110111
 *                                                ---------------------------------
 *                                                00000011000111110100001101100111100
 * cksum:0001 1000 1111 1010 0001 1011 0011 1100
 *       0x1fa1b3c
 *       But this computation was operated under initial value 0 and final XOR value 0;
 * */

/* http://www.ip33.com/crc.html
CRC算法名称	多项式公式	宽度	多项式	初始值	结果异或值	输入值反转	输出值反转
CRC-4/ITU	x4 + x + 1	4	03	00	00	true	true
CRC-5/EPC	x4 + x3 + 1	5	09	09	00	false	false
CRC-5/ITU	x5 + x4 + x2 + 1	5	15	00	00	true	true
CRC-5/USB	x5 + x2 + 1	5	05	1F	1F	true	true
CRC-6/ITU	x6 + x + 1	6	03	00	00	true	true
CRC-7/MMC	x7 + x3 + 1	7	09	00	00	false	false
CRC-8	x8 + x2 + x + 1	8	07	00	00	false	false
CRC-8/ITU	x8 + x2 + x + 1	8	07	00	55	false	false
CRC-8/ROHC	x8 + x2 + x + 1	8	07	FF	00	true	true
-- CRC-8/MAXIM	x8 + x5 + x4 + 1	8	31	00	00	true	true
CRC-16/IBM	x6 + x5 + x2 + 1	16	8005	0000	0000	true	true
CRC-16/MAXIM	x6 + x5 + x2 + 1	16	8005	0000	FFFF	true	true
CRC-16/USB	x6 + x5 + x2 + 1	16	8005	FFFF	FFFF	true	true
CRC-16/MODBUS	x6 + x5 + x2 + 1	16	8005	FFFF	0000	true	true
CRC-16/CCITT	x6 + x2 + x5 + 1	16	1021	0000	0000	true	true
-- CRC-16/CCITT-FALSE	x6 + x2 + x5 + 1	16	1021	FFFF	0000	false	false
CRC-16/x5	x6 + x2 + x5 + 1	16	1021	FFFF	FFFF	true	true
CRC-16/XMODEM	x6 + x2 + x5 + 1	16	1021	0000	0000	false	false
CRC-16/DNP	x6 + x3 + x2 + x1 + x0 + x8 + x6 + x5 + x2 + 1	16	3D65	0000	FFFF	true	true
CRC-32	x2 + x6 + x3 + x2 + x6 + x2 + x1 + x0 + x8 + x7 + x5 + x4 + x2 + x + 1	32	04C11DB7	FFFFFFFF	FFFFFFFF	true	true
-- CRC-32/MPEG-2	x32 + x6 + x3 + x2 + x6 + x2 + x1 + x0 + x8 + x7 + x5 + x4 + x2 + x + 1	32	04C11DB7	FFFFFFFF	00000000	false	false
 *
 * */
#endif
