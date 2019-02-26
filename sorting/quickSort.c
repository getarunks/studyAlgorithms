#include <stdio.h>

int arr[] = { 3, 12, 35,67, 87, 4, 56, 32, 3, 78};
//int arr[] = { 3, 1, 31,67, 87, 4, 56, 32, 39, 78};
//int arr[] = { 56, 32, 3, 78};
//int arr[] = { 56, 32};

void print_array(int *ptr, unsigned long len)
{
	int i;
	for (i = 0 ; i < len ; i++)
		printf("%d\t", ptr[i]);

	printf("\n");
}


void swap(int x, int y, int *ptr)
{
	int tmp = ptr[x];
	ptr[x] = ptr[y];
	ptr[y] = tmp;
}

void quick_sort(int *ptr, unsigned long len)
{
	int pivot = ptr[0];
	int left_index = 1, right_index = len-1;
	int hole_index = 0;
	int src_index, skip_swap=0;

	if(len < 2) {
		printf("return <---------\n");
		return;
	}

	printf("start -----------> pivot = %d left_index = %d right_index = %d len = %lu\n", pivot, left_index, right_index, len);
	print_array(ptr, len);
	while (left_index <= right_index) {
		if (hole_index < left_index) {
			src_index =  right_index;
			right_index--;
			if (ptr[src_index] > pivot)
				skip_swap = 1;
		} else {
			src_index =  left_index;
			left_index++;
			if (ptr[src_index] < pivot)
				skip_swap = 1;
		}

		if(!skip_swap) {
			swap(src_index, hole_index, ptr);
			hole_index = src_index;
		}
		skip_swap = 0;
		print_array(ptr, len);
		printf("hole = %d left = %d right = %d\n", hole_index, left_index, right_index);
	}

	printf("hole_index = %d val = %d\n", hole_index, ptr[hole_index]);

	if(hole_index >= 2)
		quick_sort(ptr, hole_index);
	else if(len-hole_index >= 2)
		quick_sort(ptr+hole_index+1, len-hole_index-1);
}

int main(void)
{
	int *ptr = arr;
	int x = 10, y = 20;

	print_array(ptr, sizeof(arr)/sizeof(int));
	printf("length = %lu\n", sizeof(arr)/sizeof(int));
	quick_sort(ptr, sizeof(arr)/sizeof(int));
	print_array(ptr, sizeof(arr)/sizeof(int));
}
