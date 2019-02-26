#include <stdio.h>

void printSolution(int arr[8][8])
{
	int i, j;
	for ( i = 0 ; i < 8; i++)
		printf(" %d  ", i);
	printf("\n");
	for (i = 0; i < 8; i++) {
		printf("---------------------------------\n");
		for (j = 0; j < 8; j++) {
			if(arr[i][j])
				printf(" %c |", 'Q');
			else
				printf("   |");
		}
	printf("\n");
	}
}

int isInRange(int row, int col, int n)
{
	if (row >=0 && row < n && col >=0 && col < n)
		return 1;
	return 0;
}

int checkDiagonal(int arr[8][8], int row, int col){
	int i, j;

	/* Check down right */
	for ( i = row, j = col; isInRange(i, j, 8); i++, j++)
		if(arr[i][j])
			return 0;

	/* Check up left */
	for (i = row, j = col; isInRange(i, j, 8); i--, j--)
		if (arr[i][j])
			return 0;

	/* check down left */
	for (i = row, j = col; isInRange(i, j, 8); i++, j--)
		if (arr[i][j])
			return 0;

	/* check up right */
	for (i = row, j = col; isInRange(i, j, 8); i--, j++)
		if (arr[i][j])
			return 0;

	return 1;
}

int isSafe(int arr[8][8], int row, int col)
{
	int i;

	/* check for horizontal */
	for (i = 0; i < 8; i++) {
		if (arr[row][i])
			return 0;
	}

	/* check for vertical */
	for (i = 0; i < 8; i++) {
		if (arr[i][col])
			return 0;
	}
	return checkDiagonal(arr, row, col);
}

/* We start in an assumption that we will place only one Queen per col */
int placeQueens(int arr[8][8], int numQueens, int col)
{
	int i, ret;
	printf("numQueens = %d col = %d\n", numQueens, col);

	if (numQueens == 0)
		return 1;

	for (i = 0 ; i < 8 ; i++) {
		if (isSafe(arr, i , col)) {
			arr[i][col] = 1;
			printf("Place Queen at (%d, %d)\n", i, col);
			ret = placeQueens(arr, numQueens - 1, col + 1);
			if (ret == 0) {
				arr[i][col] = 0;
				printf("Remove Queen at (%d, %d)\n", i, col);
			} else
				return ret;
		}
	}
	return 0;
}

int main(void)
{
	static int arr[8][8];
	static int num_attacks[8][8];
	int ret;

	ret = placeQueens(arr, 8, 0);
	if(ret == 0)
		printf("Cannot find a solution\n");
	else
		printSolution(arr);
	return 0;
}
