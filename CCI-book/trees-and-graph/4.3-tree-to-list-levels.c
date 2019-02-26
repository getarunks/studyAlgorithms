#include <stdio.h>

/* create and print
             1
            /  \
           2    3
          / \   / \
         4   5  6  7
*/

struct list {
	int data;
	struct list *next;
};

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

void insertList(struct list **list, int data)
{
	struct list *temp = calloc(1, sizeof(struct list));
	struct list *iter = *list;

	printf("%s list = 0x%x *list = 0x%x data = %d\n",__func__, *list, data);
	temp->data = data;
	temp->next = NULL;

	if(*list == NULL) {
		*list = temp;
		return;
	}

	printf("Travesing list to end\n");
	if (iter->next == NULL) printf("%d ", iter->data);
	while(iter->next) {
		printf("%d ", iter->data);
		iter = iter->next;
	}
	printf("%d ", iter->data);
	printf("\n");

	iter->next = temp;
}

int level = -1;
void createLinkList(struct node *node, struct list **ptr)
{
	if(node == NULL)
		return;

	level++;

	insertList((ptr + level), node->data);
	createLinkList(node->left, ptr);
	createLinkList(node->right, ptr);

	level--;
}

void printList(struct list *list)
{
	if (list == NULL)
		return;

	while(list) {
		printf("%d ", list->data);
		list = list->next;
	}
}

int main(void)
{
	struct node *root = new_node(1);
	struct list **listPtr;
	int i = 0;

	root->left = new_node(2);
	root->right = new_node(3);

	root->left->left = new_node(4);
	root->left->right = new_node(5);

	root->right->left = new_node(6);
	root->right->right = new_node(7);

	print_node(root, 0);

#define MAX_LEVELS	10
	listPtr = calloc(MAX_LEVELS, sizeof(struct list *));
	printf("Base **ptr = 0x%x\n", listPtr);
	createLinkList(root, listPtr);

	while(*listPtr) {
		printf("========\nlevel %d\n", i);
		printList(*listPtr);
		i++;
		printf("\n=======\n");
		listPtr++;
	}
}
