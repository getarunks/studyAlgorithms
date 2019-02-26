#include <stdio.h>
#include <stdlib.h>

int isMultiples(int x, int y)
{
	if (x > y && x%y == 0) {
		printf("x = %d y = %d multiples\n", x, y);
		return y;
	}
	if (y > x && y%x ==0) {
		printf("x = %d y = %d multiples\n", x, y);
		return x;
	}
	return 0;
}

int findSquare(int x, int y)
{

	int multiple;

	if (x == y)
		return x;

	multiple = isMultiples(x, y);
	if(multiple)
		return multiple;

	if (x > y) {
		printf("x = %d y = %d plot %d * %d\n", x, y, y, y);
		return findSquare(x-y, y);
	} else {
		printf("x = %d y = %d plot %d * %d\n", x, y, x, x);
		return findSquare(x, y-x);
	}
}

int main(int argc , char **argv)
{

	int x,y;
	int squareVal;

	if (argc < 3) {
		printf("not sufficient argumetns\n");
		return 0;
	}

	x = atoi(argv[1]);
	y = atoi(argv[2]);

	squareVal = findSquare(x, y);
	printf("square val = %d no of squares = %d\n", squareVal, (x*y)/(squareVal*squareVal));
}
