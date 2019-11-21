/************************************************************************
 > File Name: request_page.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Sun 10 Nov 2019 05:08:51 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "request_page.h"

int main(int argc, char *argv[])
{
	PageTable_init();
	Memory_init();
	show_queue(queue_length);
	char option;
	CMD *cmd_tmp;
	while(1)
	{
		printf("Do you want to execute a command? (y or n)\n");
		setbuf(stdin, NULL);
		scanf("%c", &option);	
		if(option == 'n')
			exit(0);
		else
		{
			 cmd_tmp = (CMD *)malloc(sizeof(CMD));
			 generate_command(cmd_tmp);
			 ExecuteCommand(cmd_tmp);
		}
		putchar('\n');
	}

	return 0;
}









void generate_command(CMD *cmd)
{
	int logic_number;
	int offset;
	printf("Please input logic number: ");		
	// logic_number < 256
	scanf("%d", &logic_number);
	printf("Please input offset within page: ");
	// offset < 1024
	scanf("%d", &offset);
	cmd->virtual_address = (logic_number<<10)|offset;
	printf("If modify, input 1; Otherwise, input 0: ");
	scanf("%d", &cmd->write);

	printf("New cmd:\nvirtual address: %x\tmodify: %d\n", cmd->virtual_address, cmd->write);
	return;
}

void PageTable_display()
{
	printf("Current content of page table:\n");
	for(int i=0;i<MAX_DISK_NUM;i++)	
	{
		if(page[i].disk_number == -1)
			break;
		printf("page[%d].logic_number=%d\tpage[%d].physical_number=%d\tpage[%d].flag=%d\n", i, page[i].logic_number, i, page[i].physical_number,i, page[i].flag);
	}
	putchar('\n');
}


void PageTable_init()
{
	int disk_number, page_id=0;
	cur_page_table_length = 0;
	printf("Please input information of page table to create one (use -1 to end input)\n\n");	
	do{
		printf("Input peripheral address of No.%d page: ", page_id);
		scanf("%d", &disk_number);	
		page[page_id].logic_number = page_id;	
		page[page_id].disk_number = disk_number;
		page[page_id].flag = 0;
		page_id++;
		cur_page_table_length++;
	}while(disk_number != -1);
	cur_page_table_length--;
	PageTable_display();
}

// sizeOfqueue = 1 + mem_block_num
void push(queue_t logic_number, unsigned int sizeOfqueue)
{
	if((rear+1)%sizeOfqueue == front)
	{
		printf("Queue full error;\n");
		return;
	}
	else
	{
		queue[rear] = logic_number;
		rear = (rear+1)%sizeOfqueue;
	}
	return;
}

queue_t pop(unsigned int sizeOfqueue)
{
	if(front == rear)
	{
		printf("Queue empty error;\n");
		return -1;
	}
	else
	{
		queue_t ret;
		ret = queue[front];
		front = (front+1)%sizeOfqueue;
		return ret;
	}
}

void show_queue(unsigned int sizeOfqueue)
{
	unsigned int ptr = front;	
	printf("\nCurrent queue state:\n");
	printf("Front: ");
	while(ptr != rear)
	{
		printf("%d ", queue[ptr]);
		ptr = (ptr+1)%sizeOfqueue;
	}
	printf("Rear");
	putchar('\n');
}

void Memory_init()
{
	printf("Please input num. of available blocks in memory (less than %d)\n", cur_page_table_length);
	scanf("%d", &mem_block_num);
	queue_length = mem_block_num + 1;
	
	for(int i=0; i<mem_block_num; i++)
	{
		page[i].physical_number = i+1;	
		page[i].flag = 1;
		push(page[i].logic_number, queue_length);
	}
	PageTable_display();
}



physical_address_t generate_physical_address()
{
}

void ExecuteCommand(CMD *cmd)
{
	int logic_number;	
	physical_address_t physical_address;
	logic_number = cmd->virtual_address>>10;
	//if(page[logic_number].flag == 1)
	if(page[logic_number].physical_number == 0)
	{
		PageReplace_FIFO(logic_number);
		// missing page interuption, how to respond???
		// FIFO load page into memory
	}
	// physical_address = generate_physical_address();	
	physical_address = (page[logic_number].physical_number<<10) | (cmd->virtual_address & 0x3ff);
	printf("Physical address: %d %x\n", physical_address, physical_address);
	if(cmd->write)
		page[logic_number].write = 1;
	//return EXEC_SUCCESS;
	return;
}

void PageReplace_FIFO(int logic_number)
{
	int out_logic_number;
	out_logic_number = pop(queue_length);

	page[logic_number].physical_number = page[out_logic_number].physical_number;
	page[logic_number].flag = 1;
	push(logic_number, queue_length);

	page[out_logic_number].physical_number = 0;
	page[out_logic_number].flag = 0;
	if(page[out_logic_number].write == 1)
	{
		PageWrite(out_logic_number);
		page[out_logic_number].write = 0;
	}		
	printf("Out page logic number: %d\n", out_logic_number);
	return;
}


void PageWrite(int logic_number)
{
}





