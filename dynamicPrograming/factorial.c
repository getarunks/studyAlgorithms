#include <stdio.h>

int fact(int n)
{
	int factVal;

	if (n <= 1) {
		printf("%d factVal = %d\n", n, 1);
		return 1;
	}

	factVal = n * fact(n-1);
	printf("%d factVal = %d\n", n, factVal);
	return factVal;
}

int main(int argc, char **argv)
{
	int x = atoi(argv[1]);

	printf("Factorial of %d is %d\n", x, fact(x));
}
