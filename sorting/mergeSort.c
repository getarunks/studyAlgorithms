#include <stdio.h>

int arr[] = { 23, 45, 3, 23, 4, 3 };

void merge(int a[], int min1, int max1, int min2, int max2)
{
	while(min1 
}

int mergeSort(arr, int min , int max)
{
	int mid = (min + max)/2
	if(min == max)
		return;

	mergeSort(arr, min, mid);
	mergeSort(arr, mid + 1, max);
	merge(arr, min, mid, mid + 1, max);
}

int main(void)
{
	mergeSort(arr, 6);

	for(i = 0; i < 6;i++)
		printf(" %d ", arr[i]);

	printf("\n");
}
