/************************************************************************
 > File Name: dynamic_partition_algorithms.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Wed 13 Nov 2019 08:06:10 PM CST
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "dynamic_partition.h"

void initialization(Node *memory)
{
	// memory has to be allocated on heap
	memory->head = TRUE;
	// record length of memory block
	// memory->length = 1;

	Node *first = (Node *)malloc(sizeof(Node));
	first->begin = 1;
	first->id = IDLE;
	first->length = MAX_MEM_SIZE;
	first->before = memory;
	first->next = NULL;

	memory->next = first;
	memory->before = first;
}

void show_state(Node *memory)
{
	Node *ptr=memory->next;
	printf("Job Id\tBegin\tEnd\tLength\n");
	while(ptr != NULL)
	{
		printf("%d\t%d\t%d\t%d\n", ptr->id, ptr->begin, (ptr->length)+(ptr->begin), ptr->length);
		ptr = ptr->next;
	}
}

void allocate(Job *job, Node *current_node, Node *memory)
{
	if (job->length > current_node->length)
	{
		printf("Error in allocate;\n");
		return;
	}
	
	if(job->length == current_node->length)
	{
		current_node->id = job->id;
	}
	else
	{
		// add new_node with job info before current_node
		Node *new_node = (Node *)malloc(sizeof(Node));
		new_node->id = job->id;
		new_node->length = job->length;
		new_node->begin  = current_node->begin;

		current_node->before->next = new_node;
		new_node->before = current_node->before;
		new_node->next = current_node;
		current_node->before = new_node;
		current_node->begin += job->length;
		current_node->length -= job->length;
	}
	// record next available block
	memory->before = current_node;
	printf("Memory allocation success with job id: %d\n", job->id);
	return;
}

Node *search_id(job_id id, Node *memory)
{
	Node *ptr = memory->next;
	while(ptr)
	{
		if (ptr->id == id)
			return ptr;
		ptr = ptr->next;	
	}
	return NULL;
}

int context_mapping(job_id id, Node *memory)
{
	Node *current_node = search_id(id, memory);
	if(current_node == NULL)
	{
		return -1;
	}
	if(current_node->before->head)
		return 1;
	if(current_node->next == NULL)
		return 2;

	if(current_node->before->id == IDLE)
	{
		if(current_node->next->id == IDLE)
			// 2 IDLE
			return 3;
		else
			// before IDLE next NOT
			return 4;
	}
	else
	{
		if(current_node->next->id == IDLE)
			// before NOT next IDLE
			return 5;
		else
			// 2 NOT
			return 6;
		
	}
}

void mem_free(job_id id, Node *memory)
{
	int status = context_mapping(id, memory);
	if(status == -1)
	{
		printf("Search Failed;\nJob with id: %d does not exist in meomry;\n", id);
		return;
	}

	Node *current_node = search_id(id, memory);
	Node *ptr_tmp;
	switch(status){
		case 1:
			if(current_node->next->id == IDLE)
			{
				ptr_tmp = current_node->next;
				ptr_tmp->length += current_node->length;
				ptr_tmp->before = current_node->before;
				// head has next
				current_node->before->next = ptr_tmp;
				free(current_node);
			}
			else
			{
				current_node->id = IDLE;
			}
			break;
		case 2:
			if(current_node->before->id == IDLE)
			{
				ptr_tmp = current_node->before;
				ptr_tmp->length += current_node->length;
				ptr_tmp->next = current_node->next;
				// NULL has no before
				free(current_node);
			}
			else
			{
				current_node->id = IDLE;
			}
			break;
		case 3:
			ptr_tmp = current_node->before;
			ptr_tmp->length += current_node->length;
			ptr_tmp->length += current_node->next->length;
			ptr_tmp->next = current_node->next->next;
			current_node->next->next->before = ptr_tmp;
			free(current_node->next);
			free(current_node);
			break;
		case 4:
			ptr_tmp = current_node->before;
			ptr_tmp->length += current_node->length;
			ptr_tmp->next = current_node->next;
			current_node->next->before = ptr_tmp;
			free(current_node);
			break;
		case 5:
			ptr_tmp = current_node->next;
			ptr_tmp->length += current_node->length;
			ptr_tmp->before = current_node->before;
			current_node->before->next = ptr_tmp;
			free(current_node);
			break;
		case 6:
			current_node->id = IDLE;
			break;
	}
	printf("Memory free success with job id: %d\n", id);
	return;
}

void mem_allocate_FF(Job *job, Node *memory)
{
	Node *ptr = memory->next;
	while(ptr)
	{
		if(ptr->id == IDLE && ptr->length >= job->length)
		{
			allocate(job, ptr, memory);
			return;
		}
		ptr = ptr->next;
	}
	printf("No memory available for job with id: %d\n", job->id);
	return;
}


void mem_allocate_NF(Job *job, Node *memory)
{
	Node *ptr = memory->before;	
	Node *begin_node = ptr;
	while(ptr)
	{
		if(ptr->id == IDLE && ptr->length >= job->length)	
		{
			allocate(job, ptr, memory);
			return;
		}
		ptr = ptr->next;
	}
	// put ptr in first node
	ptr = memory->next;
	while(ptr != begin_node)
	{
		if(ptr->id == IDLE && ptr->length >= job->length)	
		{
			allocate(job, ptr, memory);
			return;
		}
		ptr = ptr->next;
	}
	printf("No memory available for job with id: %d\n", job->id);
	return;
}

void mem_allocate_BF(Job *job, Node *memory)
{
	Node *ptr = memory->next;
	Node *best_node = (Node *)malloc(sizeof(Node));
	best_node->length = MAX_MEM_SIZE + 1;
	while(ptr)
	{
		if (ptr->id == IDLE && ptr->length >= job->length)
		{
			if (ptr->length < best_node->length)
				best_node = ptr;
		}
		ptr = ptr->next;
	}
	if (best_node->length == MAX_MEM_SIZE+1)
	{
		printf("No memory available for job with id: %d\n", job->id);
		return;
	}
	allocate(job, best_node, memory);
}

void interactive_mode(Node *memory)
{
	int option;
	int algorithm;
	Job *job_tmp = (Job *)malloc(sizeof(Job));
	while(1)
	{
		printf("Please select a option below:\n");
		printf("1. Allocate; 2. Free; 3. Show memory state; 4. Exit\n");
		scanf("%d", &option);
		while(option < 1 || option > 4)
		{
			printf("Input format error, please try again;\n");	
			scanf("%d", &option);
		}
		switch(option){
			case 1:
				printf("Please select an algorithm below:\n");
				printf("1. First Fit; 2. Next Fit; 3. Best Fit;\n");
				scanf("%d", &algorithm);

				printf("Please input job id:\n");
				scanf("%d", &job_tmp->id);

				printf("Please input job length:\n");
				scanf("%d", &job_tmp->length);

				switch(algorithm){
					case 1:
						mem_allocate_FF(job_tmp, memory);
						break;
					case 2:
						mem_allocate_NF(job_tmp, memory);
						break;
					case 3:
						mem_allocate_BF(job_tmp, memory);
						break;
				}

				break;
			case 2:
				printf("Please input job id:\n");
				setbuf(stdin, NULL);
				scanf("%d", &job_tmp->id);

				mem_free(job_tmp->id, memory);
				break;
			case 3:
				show_state(memory);
				break;
			case 4:
				exit(0);
				break;
		}
		putchar('\n');
	}
}
