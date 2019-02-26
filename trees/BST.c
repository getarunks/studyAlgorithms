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

struct node * new_node(int value)
{
	struct node *node = malloc(sizeof(struct node));

	node->data = value;
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

struct node * findMax(struct node *node)
{
	if(node == NULL)
		return node;

	if (node->right== NULL)
		return node;
	else
		return findMax(node->right);
}

struct node * delete(struct node *node , int data)
{
	struct node *temp;

	if(node == NULL)
		printf("Element not there in tree");

	else if (data < node->data)
		node->left = delete(node->left, data);
	else if (data > node->data)
		node->right = delete(node->right, data);
	else {
		/* Found data */
		if (node->left && node->right) {
			/* Has two children */
			/* Replace with largest in left subtree */
			temp = findMax(node->left);
			node->data = temp->data;
			node->left = delete(node->left, node->data);
		} else {
			if (node->left || node->right) {
				/*one child*/
				temp = node;
				if(node->left)
					node = node->left;
				if(node->right)
					node = node->right;
				free(temp);
			} else {
				/*no child*/
				free(node);
				node = NULL;
			}
		}
	}
	return node;
}

int main(void)
{
	struct node *root = new_node(5);
	struct node *node;

	root->left = new_node(3);
	root->right = new_node(7);

	root->left->left = new_node(1);
	root->left->right = new_node(4);

	root->left->right->right= new_node(10);

	root->right->left = new_node(6);
	root->right->right = new_node(9);
	print_node(root, 0);
	node = findMax(root);
	printf("Max value = %d\n", node->data);

	node = delete(root, 4);

	print_node(node, 0);

	node = delete(node, 7);
	print_node(node, 0);
}
