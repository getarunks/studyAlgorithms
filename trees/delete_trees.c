#include <stdio.h>

/* Delete from BST
             4
            /  \
           2    6
          / \   / \
         1   3  5  7

Problems faced when writing:

1. Failed in first attempt to divide problems into sub problems.
	case 0: node without any child
	case 1: node with only one child
	case 2: node with two child
2. Confusion in what to return at multiple places in recursive function.
3. Failed to recollect the property of BST that,
	- max element in a BST tree will not have a right child.
	- min element in a BST tree will not have a left child.

4.
		4
	      /   \
	     2     8
		  / \
		 5   10
	  	  \    \
	           7    5
		  /
		 6

While deleting 8, went to left subtree and find the max. But tried to delete 7
directly than calling delete(8->left, 7)
*/

struct node {
	int data;
	struct node *left, *right;
};

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

struct node * new_node(int data)
{
	struct node *node = calloc(1, sizeof(struct node));

	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
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


struct node * findMax(struct node *node)
{
	while(node->right)
		node = node->right;
	return node;
}

struct node * delete(struct node *node, int data)
{
	struct node *temp;

	if(node == NULL)
		return NULL;

	//printf("%s node->data = %d data = %d\n", __func__, node->data, data);
	if (data > node->data)
		node->right = delete(node->right, data);
	else if (data < node->data)
		node->left = delete(node->left, data);
	else {
		//case 0
		if(!node->right && !node->left) {
			free(node);
			node = NULL;
		// case 1
		} else if (node->right == NULL) {
			free(node);
			node = node->left;
		}else if (node->left == NULL) {
			free(node);
			node = node->right;
		} else {
		//case 2
			temp = findMax(node->left);
			node->data = temp->data;
			node->left = delete(node->left, temp->data);
		}
	}
	return node;
}

int main(void)
{
	struct node *root;
	int array[] = { 1, 2, 4, 5, 6, 7, 10, 11, 12};

	root = createBST(array, sizeof(array)/sizeof(int));
	print_node(root, 0);
	printf("Delete 5\n");
	root = delete(root, 5);
	print_node(root, 0);
	printf("Delete 4\n");
	root = delete(root, 4);
	print_node(root, 0);
	printf("Delete 2\n");
	root = delete(root, 2);
	print_node(root, 0);

}
