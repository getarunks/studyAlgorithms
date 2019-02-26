/*Calculate a raised to the power of b*/
#include <stdio.h>

int raise(int v, int pow)
{
	if (pow == 0)
		return 1;
	return v * raise(v , pow - 1);
}

int main(void)
{
	printf(" 5 ^ 3 = %d\n", raise(5, 3));
	printf(" 10 ^ 3 = %d\n", raise(10, 3));
}

