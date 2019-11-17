/************************************************************************
 > File Name: dynamic_partition.h
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Wed 13 Nov 2019 07:55:04 PM CST
************************************************************************/

#ifndef __DYNAMIC_PARTITION__
#define __DYNAMIC_PARTITION__

#define MAX_MEM_SIZE 1000
#define TRUE 1
#define FALSE 0
#define IDLE -1

typedef unsigned int address;
typedef int job_id;
typedef unsigned int job_length;
typedef unsigned int head_type;

typedef struct cell{
	address begin;
	job_id id;
	job_length length;
	head_type head;	
	struct cell *before;
	struct cell *next;	
}Node;

typedef struct element{
	job_id id;
	job_length length;
}Job;

void initialization(Node *memory);
void show_state(Node *memory);

void allocate(Job *job, Node *current_node, Node *memory);
Node *search_id(job_id id, Node *memory);
int context_mapping(job_id id, Node *current_node);

void mem_allocate_FF(Job *job, Node *memory);
void mem_allocate_NF(Job *job, Node *memory);
void mem_allocate_BF(Job *job, Node *memory);

void mem_free(job_id id, Node *memory);



void interactive_mode(Node *memory);




#endif
