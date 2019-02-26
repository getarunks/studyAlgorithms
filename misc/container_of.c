#include <stdio.h>
#include <stdlib.h>

#define OFFSET_OF(type, element)	(unsigned long)(&((type *)0)->element)
#define CONTAINER_OF(ptr, type, element) ({ \
		 void *base = (void *)ptr;	\
		 (type *)(base - OFFSET_OF(type, element));	\
		})

struct page {
	int i;
	int z[20];
	int list;
};

int main(void)
{
	struct page *p = malloc(sizeof(struct page));
	void *ptr;
	int list;
	struct page *p1;

	p->list = 33;
	ptr = OFFSET_OF(struct page, list);
	printf("%p\n", OFFSET_OF(struct page, list));
	printf("list = %d\n", *(int *)((void*)p + (int)ptr));
	p1 = CONTAINER_OF(&p->list, struct page, list);
	printf("%p %p\n", p, p1);
	printf("List = %d\n", p1->list);
}
