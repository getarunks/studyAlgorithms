#include <stdio.h>
/*
 * Producer is free running
 * consumer can stop
 * Ref: https://embeddedartistry.com/blog/2017/4/6/circular-buffers-in-cc
 */
struct circ_buffer_t {
	void *buffer;
	int head;
	int tail;
	int max;
	int full;
	int size;
};

struct circ_buffer_t * init_allocator(int size, int count);
void * dequeueBuffer(struct circ_buffer_t *cbuffer);
void queueBuffer(struct circ_buffer_t* cbuf);
void * accquireBuffer(struct circ_buffer_t *cbuf);
void releaseBuffer(struct circ_buffer_t *cbuf);

struct circ_buffer_t * init_allocator(int size, int count)
{
	struct circ_buffer_t *cbuf = malloc(sizeof(struct circ_buffer_t));
	cbuf->buffer = malloc(size*count);
	cbuf->head = 0;
	cbuf->tail = 0;
	cbuf->max = count;
	cbuf->full = 0;
	cbuf->size = size;
	return cbuf;
}

void * dequeueBuffer(struct circ_buffer_t *cbuf)
{
	return cbuf->buffer + (cbuf->head * cbuf->size);
}

void queueBuffer(struct circ_buffer_t *cbuf)
{
	if(cbuf->full)
		cbuf->tail = (cbuf->tail + 1) % cbuf->max;

	cbuf->head = (cbuf->head + 1) % cbuf->max;
	cbuf->full = (cbuf->head == cbuf->tail);

	printf("%s head = %d tail = %d full = %d\n", __func__, cbuf->head, cbuf->tail, cbuf->full);
}

int isEmpty(struct circ_buffer_t *cbuf)
{
	return (cbuf->head == cbuf->tail) && !cbuf->full;
}

void * accquireBuffer(struct circ_buffer_t *cbuf)
{
	if(isEmpty(cbuf))
		return NULL;

	return cbuf->buffer + (cbuf->tail * cbuf->size);
}

void releaseBuffer(struct circ_buffer_t *cbuf)
{
	cbuf->tail = (cbuf->tail + 1) % cbuf->max;
	cbuf->full = 0;
	printf("%s head = %d tail = %d full = %d\n", __func__, cbuf->head, cbuf->tail, cbuf->full);
}

int main(void)
{
	struct circ_buffer_t *cbuf = init_allocator(10, 3);
	int val;
	char *buf;
	char name[10];

	while (1){
		printf("What would you like to do:\n");
		printf("q. Queue Data\n");
		printf("d. Dequeue Data\n");

		gets(name);
		if(name[0] == 'q'){
			printf("Enter name less than 10 chars:\n");
			gets(name);
			printf("%s\n", name);
			buf = dequeueBuffer(cbuf);
			memcpy(buf, name, 9);
			queueBuffer(cbuf);
		} else if (name[0] == 'd') {
			buf = accquireBuffer(cbuf);
			if(!buf) {
				printf("Empty\n");continue;
			}
			printf("%s\n", buf);
			releaseBuffer(cbuf);
		}
	}
}
