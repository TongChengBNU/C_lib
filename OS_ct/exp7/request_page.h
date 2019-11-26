/************************************************************************
 > File Name: request_page.h
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Thu 21 Nov 2019 04:56:32 PM CST
************************************************************************/

#ifndef __PAGE_REQUEST__
#define __PAGE_REQUEST__


#define MAX_DISK_NUM 64
#define MAX_MEM_NUM 64
#define MISSING_INTERRUPT 400
#define EXEC_SUCCESS 200
#define TRUE 1
#define FALSE 0

typedef uint16_t virtual_address_t;
typedef unsigned int physical_address_t;
typedef unsigned int queue_t;

typedef struct page{
	int logic_number; // page number
	int physical_number; // physical block number, initial value->0
	int disk_number;  // position on disk
	int write; // modification flag, initial value->0
	int flag; //  memory existence flag
	/*
	 * flag = 0 is equivelant to physical_number = 0;
	 * why bother?
	 * */
}Page;

Page page[MAX_DISK_NUM];
queue_t queue[MAX_MEM_NUM];
unsigned int front=0, rear=0;

typedef struct cmd{
	virtual_address_t virtual_address;
	int write;
}CMD;


unsigned int mem_block_num;
unsigned int queue_length;
unsigned int cur_page_table_length;



void generate_command(CMD *cmd);
void PageTable_display();
void PageTable_init();
void push(queue_t logic_number, unsigned int sizeOfqueue);
queue_t pop(unsigned int sizeOfqueue);
void show_queue(unsigned int sizeOfqueue);
void Memory_init();
physical_address_t generate_physical_address();
void ExecuteCommand(CMD *cmd);
void PageReplace_FIFO(int logic_number);
void PageWrite(int logic_number);










#endif
