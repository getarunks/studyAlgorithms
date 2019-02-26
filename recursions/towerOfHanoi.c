#include <stdio.h>

void towersOfHanoi(int n, char fromPeg, char toPeg, char auxPeg)
{
	if (n == 1) {
		printf("Move disk 1 from peg %c to peg %c\n", fromPeg, toPeg);
		return;
	}

	towersOfHanoi(n-1, fromPeg, auxPeg, toPeg);

	printf("Move disk %d from peg %c to peg %c\n", n, fromPeg, toPeg);

	towersOfHanoi(n-1, auxPeg, toPeg, fromPeg);
}

int main(void)
{

	towersOfHanoi(3, 'A', 'B', 'C');
}
