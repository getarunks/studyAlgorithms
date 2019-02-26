#include <stdio.h>

/* create and print
             1
            /  \
           2    3
          / \   / \
         4   5  6  7
*/

struct node {
	int data;
	struct node *left, *right;
};

struct node * new_node(int data)
{
	struct node *node = malloc(sizeof(struct node));

	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void print_node(struct node *node, int space)
{
	int i;
	if(node == NULL)
		return;

	space += 5;

	print_node(node->right, space);
	printf("\n");
	for(i = 0 ; i < space; i++)
		printf(" ");
	printf("%d\n", node->data);
	print_node(node->left, space);
}

int main(void)
{
	struct node *root = new_node(1);

	root->left = new_node(2);
	root->right = new_node(3);

	root->left->left = new_node(4);
	root->left->right = new_node(5);

	root->right->left = new_node(6);
	root->right->right = new_node(7);

	print_node(root, 0);
}
