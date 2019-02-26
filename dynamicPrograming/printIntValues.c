#include <stdio.h>

void print_place_values(int i)
{
	if (i == 0)
		return;

	if (i < 10) {
		printf(" %d ", i);
		return;
	}

	print_place_values(i/10);
	printf("%d ", i%10);
}

int main (void)
{
	int i = 12345678;

	printf(" Printing %d\n", i);
	print_place_values(i);
	printf("\n");
}
