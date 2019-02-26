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

void insertList(struct list *list, int data)
{
	struct list *temp = calloc(1, sizeof(struct list));

	temp->data = data;
	temp->next = NULL;

	printf("Travesing list to end\n");
	while(list->next) {
		printf("%d ", list->data);
		list = list->next;
	}
	printf("%d ", list->data);
	printf("\n");

	list->next = temp;
}

int level = -1;
void createLinkList(struct node *node, struct list **ptr)
{
	if(node == NULL)
		return;

	level++;

	if(ptr[level] == NULL) {
		printf(" level = %d memory allocate data = %d\n", level, node->data);
		ptr[level] = calloc(1, sizeof(struct list));
		ptr[level]->data = node->data;
		ptr[level]->next = NULL;
	} else
		insertList((ptr[level]), node->data);
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
