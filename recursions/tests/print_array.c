#include<stdio.h>

void print_array(int *ptr, int len)
{
	if (len == 0)
		return;

	printf("%d ", ptr[0]);
	print_array(ptr+1, len - 1);
}

int main(void)
{
	int arr[5] = {1, 2, 3, 4, 5};

	print_array(arr, 5);
	printf("\n");
}
