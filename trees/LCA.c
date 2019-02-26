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
#if 1
int isElementPresent(struct node *node, int data)
{
	int ret;

	if(node == NULL)
		return 0;

	if (node->data == data)
		return 1;
	ret = isElementPresent(node->left, data);
	if(ret)
		return ret;
	return isElementPresent(node->right, data);
}

/* Search both elements on left node first. If they are on different subtree
 * then that is the LCA. If both are present on left subtree, do the same on
 * left child. If both are not present on left subtree, do the same on right
 * child.
 *
 * both founds can takes N/2 in first stage
 * then N/4 in second stage
 * Total N = (N/2)*2 + (N/4)*2 + (N/8)*2 .... = 2N = O(N)
 * */

int findLCA(struct node *node, int a, int b)
{
	int foundA, foundB;

	if(node == NULL)
		return NULL;

	foundA = isElementPresent(node->left, a);
	foundB = isElementPresent(node->left, b);

	if(foundA != foundB)
		return node->data;

	if (foundA)
		return findLCA(node->left, a, b);
	else
		return findLCA(node->right, a, b);
}
#else
int index, found;
int findPath(struct node *node, int a, int *ptr)
{
	int ret;

	if(!node)
		return 0;
	index++;

	ret = index;

	if(node->data == a){
		found = 1;
		index--;
		return ret;
	}

	ret = findPath(node->left, a, ptr);
	if(found == 0)
		ret = findPath(node->right, a, ptr);
	if(found) {
		ptr[index] = node->data;
	}
	index--;
	return ret;
}

/* Solution #2
 * find path for a and b - store in sepearte array.
 * Then go throughi the arrays find the fist deviation.
 *
 * Finding Paths = N + N
 * Then going though the arrays will have logN setps.
 * Total N = 2N  + log N = O(N)
 */
int findLCA(struct node  *node, int a, int b)
{
	int Path1[10], Path2[10];
	int len1, len2, len, i;

	index = -1;
	found = 0;
	len1 = findPath(node, a, Path1);

	index = -1;
	found = 0;
	len2 = findPath(node, b, Path2);

	len = len1 > len2 ? len1 : len2;

	for(i = 0; i < len ; i++)
		if(Path1[i] != Path2[i])
			break;
	return Path1[i-1];
}
#endif

int printAllAncestors(struct node *root, struct node *node)
{
	if(root==NULL)
		return 0;

	if(root->left == node || root->right == node || printAllAncestors(root->left, node) || printAllAncestors(root->right, node)) {
		printf("%d ",root->data);
		return 1;
	}
}

int main(void)
{
	struct node *root = new_node(1);
	struct node *node;

	root->left = new_node(2);
	root->right = new_node(3);

	root->left->left = new_node(4);
	root->left->right = new_node(5);

	root->right->left = new_node(6);
	root->right->right = new_node(7);

	print_node(root, 0);
#define ELE1	4
#define ELE2	7
#if 0
	node = findLCA(root, ELE1, ELE2);
	printf("LCA of %d and %d is %d\n", ELE1, ELE2, node->data);
#else
	printf("LCA of %d and %d is %d\n", ELE1, ELE2, findLCA(root, ELE1, ELE2));
#endif
	printAllAncestors(root, root->right->right);
	printf("\n");
}
