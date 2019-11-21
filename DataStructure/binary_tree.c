/************************************************************************
 > File Name: binary_tree.c
 > Author: Tong Cheng
 > Mail: tong.cheng.8819@outlook.com 
 > Created Time: Tue 19 Nov 2019 03:04:58 PM CST
************************************************************************/

/* Demo tree visualization
 *         a
 *        / \
 *       b   c
 *      / \   \
 *     d   e   f
 *
 *     pre_order: abdecf
 *     in_order: dbeacf
 *     post_order: debfca
 * */


#include <stdio.h>
#include <stdlib.h>


typedef unsigned int element_t;

typedef struct node{
	element_t data;
	struct node *left;
	struct node *right;
}Node;

typedef struct queue{
	Node *data;	
	struct queue *next;
}Queue;

void initialization_demo(Node *root);
void pre_order_traversal(Node *root);
void pre_order_traversal_nonrecursive(Node *root, unsigned int tree_depth);
void in_order_traversal(Node *root);
void post_order_traversal(Node *root);
void layer_traversal(Node *root);

int main(int argc, char *argv[])
{
	Node *tree = (Node *)malloc(sizeof(Node));
	tree->data = 1;
	initialization_demo(tree);
	pre_order_traversal(tree);
	putchar('\n');
	pre_order_traversal_nonrecursive(tree, 3);
	putchar('\n');
	//in_order_traversal(tree);
	//putchar('\n');
	//post_order_traversal(tree);
	//putchar('\n');
	layer_traversal(tree);
	putchar('\n');



	return 0;
}













void initialization_demo(Node *root)
{	
	// 2nd 
	Node *left, *right;
	left = (Node *)malloc(sizeof(Node));
	left->data = 2;
	right = (Node *)malloc(sizeof(Node));
	right->data = 3;
	root->left = left;
	root->right = right;

	// 3rd
	left->left = (Node *)malloc(sizeof(Node));
	left->left->data = 4;	
	left->right = (Node *)malloc(sizeof(Node));
	left->right->data = 5;
	
	right->right = (Node *)malloc(sizeof(Node));
	right->right->data = 6;

}
void pre_order_traversal(Node *root)
{
	if (root == NULL)
		return;

	printf("%d", root->data);
	pre_order_traversal(root->left);
	pre_order_traversal(root->right);
}
void in_order_traversal(Node *root)
{
	if (root == NULL)
		return;

	in_order_traversal(root->left);
	printf("%d", root->data);
	in_order_traversal(root->right);
}
void post_order_traversal(Node *root)
{
	if (root == NULL)
		return;

	post_order_traversal(root->left);
	post_order_traversal(root->right);
	printf("%d", root->data);
}

void pre_order_traversal_nonrecursive(Node *root, unsigned int tree_depth)
{
	Node *stack[tree_depth+1];
	stack[0] = NULL; // stack 1st element should be NULL to terminate the loop
	unsigned int top=1;	
	Node *ptr = root;
	while(ptr)
	{
		printf("%d", ptr->data);	

		if(ptr->right)
		{
			stack[top++] = ptr->right;
		}
		if(ptr->left)
		{
			// ptr->left not NULL
			ptr = ptr->left;
		}
		else
		{
			// ptr->left is NULL	
			ptr = stack[--top];
		}
	}
}

void layer_traversal(Node *root)
{
	Queue *queue_tmp = (Queue *)malloc(sizeof(Queue));
	queue_tmp->data = root;
	queue_tmp->next = NULL;

	Queue *front, *rear;
	front = queue_tmp;
	rear = queue_tmp;

	Queue *left, *right, *tmp;
	Node *cur_node;
	while(front)
	{
		cur_node = front->data;
		printf("%d", cur_node->data);
		if(cur_node->left)
		{
			left = (Queue *)malloc(sizeof(Queue));
			left->data = cur_node->left;
			rear->next = left;
			rear = left;
		}
		if(cur_node->right)
		{
			right = (Queue *)malloc(sizeof(Queue));
			right->data = cur_node->right;
			rear->next = right;
			rear = right;
		}
		tmp = front;
		front = front->next;
		//free(tmp);
		// to be continued ...
		// how to manage this queue to save memory??
	}

}
