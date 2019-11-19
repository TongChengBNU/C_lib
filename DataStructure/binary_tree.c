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

void initialization_demo(Node *root);
void pre_order_traversal(Node *root);
void in_order_traversal(Node *root);
void post_order_traversal(Node *root);
void show_state(Node *root);

int main(int argc, char *argv[])
{
	Node *tree = (Node *)malloc(sizeof(Node));
	tree->data = 1;
	initialization_demo(tree);
	pre_order_traversal(tree);
	putchar('\n');
	in_order_traversal(tree);
	putchar('\n');
	post_order_traversal(tree);
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

void show_state(Node *root)
{
}

