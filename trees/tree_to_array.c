#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
	int key;
	struct node *left;
	struct node *right;
};

struct pair {
	struct node *head, *tail;
};

struct node * new_node(int key)
{
	struct node *n = malloc(sizeof(struct node));
	assert(n);

	n->key = key;
	n->left = NULL;
	n->right = NULL;
	return n;
}

/*
 * Method 1:
int convert_tree_to_array(struct node *node, int *array)
{
	int ret;
	if (node == NULL)
		return 0;

	ret = convert_tree_to_array(node->left, array);
	array[ret] = node->key;
	ret += convert_tree_to_array(node->right, array + ret + 1);
	return ret + 1;
}*/

/*
 * Method 2:
int convert_tree_to_array(struct node *node, int *array)
{
	int ret;
	if (node == NULL)
		return 0;

	ret = convert_tree_to_array(node->left, array);
	array += ret;
	array[0] = node->key;
	array++;
	ret += convert_tree_to_array(node->right, array);
	return ret + 1;
}*/

//Method 3:
void  __convert_tree_to_array(struct node *node, int **array)
{
	if(node == NULL)
		return;
	__convert_tree_to_array(node->left, array);
	**array = node->key;
	*array = *array + 1;
	__convert_tree_to_array(node->right, array);
}

void convert_tree_to_array(struct node *node, int *array)
{
	__convert_tree_to_array(node, &array);
}

int main(void)
{
	struct node *root;
	int *array = calloc(sizeof(int), 7);
	root = new_node(4);
	root->left = new_node(2);
	root->right = new_node(6);
	root->left->left = new_node(1);
	root->left->right = new_node(3);
	root->right->left = new_node(5);
	root->right->right = new_node(7);

	convert_tree_to_array(root, array);
	for (int i = 0 ; i < 7; i++)
		printf(" %d ", array[i]);
}
