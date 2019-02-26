#include <stdio.h>
#include <stdlib.h>

/* You can't make it better by dynamic programing. you gain efficentcy only if
 * the method is called several times.*/

int fibSeries[100];

int fib(int n)
{
	int fibVal;
	if (n == 1 || n == 0) {
		printf("index : val %d : %d \n" , n, n);
		fibSeries[n] = 0 ;
		return 1;
	}

	fibSeries[n] = fib(n-1) + fib(n-2);
	printf("index : val %d : %d \n" , n, fibSeries[n]);
	return fibSeries[n];
}

int main(int argc , char **argv)
{
	int x, i;
	x = atoi(argv[1]);

	printf("Fib upto  %d \n", x);

	fib(x-1);
	for(i = 0 ; i < x ; i++)
		printf("%d ", fibSeries[i]);

	printf("\n");
}
