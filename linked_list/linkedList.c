#include <stdio.h>

struct list{
	int val;
	struct list *next;
};

struct list * create_cell(int val)
{
	struct list *ptr = malloc(sizeof(struct list));
	ptr->val = val;
	ptr->next = NULL;
	return ptr;
}

void append_list(struct list *list, struct list *head)
{
	while(head->next)
		head = head->next;

	head->next = list;
}

void prepend_list(struct list *list, struct list **head)
{
	list->next = *head;
	*head = list;
}

int return_length(struct list *head)
{
	int len = 1;

	while (head->next) {
		head = head->next;
		len++;
	}

	return len;
}

void insert_middle(struct list *list, struct list *head)
{
	int len = 0, index = 0;
	struct list *tmp = head;

	len = return_length(head);
	printf("len = %d\n", len);
	tmp = head;
	while(tmp->next) {
		if (index == len/2)
			break;
		tmp = tmp->next;
		index++;
	}

	list->next = tmp->next;
	tmp->next = list;
}

void delete_cell(struct list **head, int val)
{
	struct list *tmp, *prev;

	tmp = *head;
	if (val == tmp->val)
		return delete_first(head);

	while(tmp->next) {
		if (val == tmp->val)
			break;
		prev = tmp;
		tmp = tmp->next;
	}

	/* cell not found */
	if (val != tmp->val)
		return;
	prev->next = tmp->next;
	free(tmp);
}

void delete_first(struct list **head)
{
	struct list *list = *head;
	*head = list->next;
	free(list);
}

void delete_last(struct list **head)
{
	struct list *prev, *tmp = *head;

	if (!tmp->next) {
		free(tmp);
		*head = NULL;
	}

	while(tmp->next) {
		prev = tmp;
		tmp = tmp->next;
	}

	free(prev->next);
	prev->next= NULL;
}

struct list * reverse_list (struct list *head)
{
	struct list *prev, *next, *tmp;

	prev = head;
	next = prev->next;
	prev->next = NULL;
	while (next != NULL) {
		tmp = next->next;
		next->next = prev;
		prev = next;
		next = tmp;
	}
	return prev;
}

void print_list(struct list *head)
{
	if (head == NULL)
		return;

	do {
		printf("%d\t", head->val);
		head = head->next;
	}while(head != NULL);

	printf("\n");
}

struct list * create_list(int *arr, int len)
{
	struct list *head = NULL;
	int index = 0;

	head = create_cell(arr[0]);
	for (index = 1 ; index < len ; index++)  {
		struct list *list;
		list = create_cell(arr[index]);
//		append_list(list, head);
		prepend_list(list, &head);
		//print_list(head);
	}

	return head;
}


int main()
{
	struct list *head, *list;
	int arr[] = {1, 2, 3, 4};
	head = create_list(arr, 4);
	printf("Adding to list 1, 2, 3, 4\n");
	print_list(head);
	list = create_cell(10);
	printf("insert middle 10\n");
	insert_middle(list, head);
	print_list(head);
	list = create_cell(11);
	insert_middle(list, head);
	printf("insert middle 11\n");
	print_list(head);

	printf("Reverse list\n");
	head = reverse_list(head);
	print_list(head);

	printf("Delete first\n");
	delete_first(&head);
	print_list(head);

	printf("Delete first\n");
	delete_first(&head);
	print_list(head);

	printf("Delete last\n");
	delete_last(&head);
	print_list(head);

	printf("Delete cell 2\n");
	delete_cell(&head, 2);
	print_list(head);

	printf("Reverse list\n");
	head = reverse_list(head);
	print_list(head);

}
