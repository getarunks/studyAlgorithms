#include <stdio.h>

int a[] = { 3 ,4, 5, 6,7,10};

void printArray(int *ptr, int len)
{
	int i;
	for(i = 0 ; i < len ; i++)
		printf("%d\t", ptr[i]);
	printf("\n");
}

void _heapify(int *ptr, int parentIndex, int len)
{
	int leftChildIndex = parentIndex*2 + 1;
	int rightChildIndex = parentIndex*2 + 2;
	int largestIndex;

	if(parentIndex < 0)
		return;

	if(rightChildIndex < len - 1)
		largestIndex = ptr[leftChildIndex] - ptr[rightChildIndex] < 0 ? rightChildIndex : leftChildIndex;
	else
		largestIndex = leftChildIndex;

	if(ptr[largestIndex] > ptr[parentIndex]) {
		int temp = ptr[largestIndex];
		ptr[largestIndex] = ptr[parentIndex];
		ptr[parentIndex] = temp;
	}

	printf("parentIndex = %d ", parentIndex);
	printArray(a, sizeof(a)/sizeof(int));
	_heapify(ptr, parentIndex - 1, len);
}

void heapify(int *ptr, int len)
{
	int parentIndex = len/2 - 1;
	_heapify(ptr, parentIndex, len);
}

int main(void)
{
	printArray(a, sizeof(a)/sizeof(int));
	heapify(a, sizeof(a)/sizeof(int));
	printArray(a, sizeof(a)/sizeof(int));
	return 0;
}
