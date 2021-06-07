#include <stdio.h>
#include <stdlib.h>

/*Try to picturize how these two allocations are implemented in memory */

#define METHOD_ONE

void print_row(int n, int *arr)
{
	printf("printing row....\n");
	for (int i = 0 ; i < n ;i++)
		printf("%d ", arr[i]);
	printf("\n");
}

#ifdef METHOD_ONE

// Method one
// using array of pointers

void print_arr(int n, int **arr)
{
	printf("printing array....\n");
	for (int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < n ; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
}

int main(void)
{
	int n = 4;
	int **arr;

	/*
	 * Need two step allocation of memory
	 * 1. Memory to hold pointers for rows
	 * 2. Memory for rows
	 */
	arr = calloc(sizeof(int *), n);
	for (int i = 0; i < n; i++)
		arr[i] = calloc(sizeof(int), n);

	printf("Method One\n");
	arr[2][3] = 66;
	print_row(n, arr[2]);
	print_arr(n, arr);
	return 0;
}

#else //Method 2
/*
 * Single allocation and use pointer to a array.
 */

// both int (*arr)[n] and int arr[][n] are same.

//void print_arr(int n, int (*arr)[n])
void print_arr(int n, int arr[][n])
{
	printf("printing array....\n");
	for (int i = 0; i < n ; i++) {
		for (int j = 0; j < n ;j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
}

int main(void)
{
	int n = 4;
	int (*arr)[n] = calloc(sizeof(int), n*n);
	printf("Method two\n");
	print_arr(n, arr);
	arr[2][1] = 33;
	print_row(n, arr[2]);
}
#endif
