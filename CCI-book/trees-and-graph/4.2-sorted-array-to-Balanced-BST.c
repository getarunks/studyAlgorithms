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

struct node *insert_node(struct node *root, struct node *node)
{
	struct node *temp = root;
	if (root == NULL)
		 return node;

	printf("%s data = %d\n", __func__, node->data);
	while (1) {
		if(node->data > root->data) {
			if (root->right == NULL) {
				root->right = node;
				break;
			}
			root = root->right;
		} else {
			if(root->left == NULL) {
				root->left = node;
				break;
			}
			root = root->left;
		}
	}
	return temp;
}

struct node * _createBST(int *array, int min, int max)
{
	static struct node *root = NULL;
	struct node *temp;
	int mid;
	printf("%s min = %d max = %d\n", __func__, min, max);
	if (min == max) {
		temp = new_node(array[min]);
		root = insert_node(root, temp);
		return root;
	}

	mid = (min + max)/2;

	temp = new_node(array[mid]);
	root = insert_node(root, temp);
	_createBST(array, min, mid - 1);
	_createBST(array, mid +1, max);
	return root;
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
