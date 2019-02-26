#include<stdio.h>

struct list {
	int val;
	struct list *next;
};

struct list * create_cell(int val)
{
	struct list *list = malloc(sizeof(struct list));
	list->val = val;
	list->next = NULL;
	return list;
}

void print_list(struct list *head)
{
	while(head->next) {
		if(head->val != -1 && head->val !=650000)
			printf("%d\t", head->val);
		head = head->next;
	}
	printf("\n");
}

void add_sorted_list(int val, struct list *head)
{
	struct list *curr = head, *tmp;
	while (curr->next->val < val)
		curr = curr->next;

	tmp = create_cell(val);
	tmp->next = curr->next;
	curr->next = tmp;
}

void remove_sorted_list(int val, struct list *head)
{
	struct list *curr = head;
	while( curr->next->val < val)
		curr = curr->next;

	if (curr->next->val == val) {
//		free(curr->next);
		curr->next = curr->next->next;
	}
}

int main(void)
{
	int arr[] = { 4, 6, 3, 45, 31, 26, 47, 7};
	struct list *tmp, *head;
	int len, i;

	/* create top sentinal */
	tmp = create_cell(-1);
	head = tmp;

	/* create bottom sentinel */
	tmp = create_cell(650000);
	head->next = tmp;

	len = 8;
	print_list(head);
	i = 0;
	while (len) {
		printf("adding %d\n", arr[i]);
		add_sorted_list(arr[i], head);
		len--;
		i++;
	}

	print_list(head);

	printf("Remove 45\n");
	remove_sorted_list(45, head);

	print_list(head);
}

