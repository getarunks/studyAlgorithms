#include <stdio.h>

struct list {
	struct list *next;
	int data;
};

struct list * createList(int data){
	struct list *list = malloc(sizeof(struct list));
	list->next = NULL;
	list->data = data;
	return list;
}

void printList(struct list *list)
{
	while(list){
		printf("%d\t", list->data);
		list = list->next;
	}
	printf("\n");
}

struct list * _reverse(struct list *prev, struct list *list)
{
	struct list *next;
	if(list == NULL)
		return NULL;

	if(list->next == NULL) {
		list->next = prev;
		return list;
	}

	next = list->next;
	list->next = prev;
	return _reverse(list, next);
}

struct list * reverseList(struct list *head) {
	return _reverse(NULL, head);
}

int main()
{
	struct list *head = createList(1);
	head->next = createList(2);
	head->next->next = createList(3);

	printList(head);

	head = reverseList(head);
	printList(head);
}
