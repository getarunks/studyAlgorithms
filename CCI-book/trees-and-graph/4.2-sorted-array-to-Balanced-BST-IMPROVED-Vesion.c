#include <stdio.h>
#include <stdlib.h>

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
	struct node *node = calloc(1, sizeof(struct node));

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

struct node * _createBST(int *array, int min, int max)
{
	struct node *node;
	int mid;
	printf("%s min = %d max = %d\n", __func__, min, max);
	if (min > max) {
		return NULL;
	}

	mid = (min + max)/2;
	node = new_node(array[mid]);
	node->left = _createBST(array, min, mid - 1);
	node->right = _createBST(array, mid +1, max);
	return node;
}

struct node * createBST(int *array, int len)
{
	return _createBST(array, 0, len - 1);
}

int main(void)
{
	struct node *root;
	int array[] = { 1, 2, 3, 4, 5, 6, 7};

	root = createBST(array, sizeof(array)/sizeof(int));
	print_node(root, 0);
}
