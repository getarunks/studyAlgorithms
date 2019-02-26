#include <stdio.h>

int factVals[100];

/* You can't make it better by dynamic programing. you gain efficentcy only if
 * the method is called several times.*/

int fact(int n)
{
	int factVal;

	if (n <= 1) {
		factVals[n] = 1;
		printf("%d factVal = %d\n", n, 1);
		return 1;
	}

	if(factVals[n-1] != -1)
		return n*factVals[n-1];

	factVal = n * fact(n-1);
	factVals[n] = factVal;
	printf("%d factVal = %d\n", n, factVal);
	return factVal;
}

int main(int argc, char **argv)
{
	int x = atoi(argv[1]);

	int i;
	for (i = 0 ; i < x ;i++)
		factVals[i] = -1;

	printf("Factorial of %d is %d\n", x, fact(x));
}
