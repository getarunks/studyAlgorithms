#include <stdio.h>

struct node {
	int data;
	struct node *next;
};

struct nodeHead {
	int bcount;
	struct node *head;
};

struct hashTable {
	/* total number of node data elements */
	int count;
	int tsize;
	struct nodeHead **table;
};

struct hashTable * create_hashTable(int tsize)
{
	struct hashTable *h = malloc(sizeof(struct hashTable));
	int i;

	h->count = 0;
	h->tsize = 11;

	printf("%d %d %d\n", sizeof(struct nodeHead *), sizeof(struct nodeHead), sizeof(struct nodeHead)*tsize);
	h->table = calloc(tsize, sizeof(struct nodeHead *));
	for (i = 0 ; i < tsize ; i++)
		h->table[i] = calloc(1, sizeof(struct nodeHead));

	for (i = 0 ; i < tsize ; i++) {
		struct nodeHead *nodeHead = *(h->table + i);
		h->table[i]->head = NULL;
		printf("table = %x nodeHead = %x\n", h->table, nodeHead);
		nodeHead->head = NULL;
		h->table[i]->bcount = 0;
	}
}

int main(void)
{
	create_hashTable(11);
}
