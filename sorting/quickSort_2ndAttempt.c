//http://interactivepython.org/courselib/static/pythonds/SortSearch/TheQuickSort.html

#include<stdio.h>


void print(int *a, int len)
{
	int i;
	for(i = 0 ; i < len; i++)
		printf("%d\t", a[i]);
	printf("\n");
}

void swap(int *val1, int *val2)
{
	int temp = *val1;
	*val1 = *val2;
	*val2 = temp;
}

int partition(int *a, int len)
{
	int pivotValue = a[0];
	int left = 1;
	int right = len - 1;
	int temp, loop = 0;

	while(1) {
		printf("looping left = %d right = %d\n", left, right);
		if(loop++>10)
			break;

		while(left <= right && a[left] < pivotValue)
			left++;

		printf("1 : left = %d right = %d\n", left, right);

		while(left <= right && a[right] > pivotValue)
			right--;

		printf("2 : left = %d right = %d\n", left, right);
		if(left>right)
			break;
		else {
			swap(a+left, a+right);
		}
		print(a, len);
	}

	swap(a, a+right);
	print(a, len);
	printf("return %d\n", right);
	return right;
}

void quick_sort(int *a, int len)
{
	int pivot;
	printf("%s len = %d\n", __func__, len);
	if (len == 0 || len == 1)
		return;
	if (len == 2) {
		swap(a, a+1);
		print(a, len);
		return;
	}

	pivot = partition(a, len);
	quick_sort(a, pivot);
	quick_sort(a+pivot+1, len-pivot-1);
}

int main()
{
	int a[10] = { 5, 4, 3, 9, 11 , 34, 7, 45, 9};

	print(a, sizeof(a)/sizeof(int) - 1);
	printf("Hello World\n");
	quick_sort(a, sizeof(a)/sizeof(int) - 1);
	print(a, sizeof(a)/sizeof(int) - 1);

	return 0;
}
