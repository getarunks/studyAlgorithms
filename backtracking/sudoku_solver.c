#include <stdio.h>

printSudoku(int a[9][9])
{
	int row, col;
	for (row = 0 ; row < 9 ; row++){
		if(row%3 == 0)
			printf("--------------------------\n");

		for(col = 0 ; col < 9 ; col++) {
			if(col%3 == 0)
				printf(" | ");
			printf("%d ", a[row][col]);
		}
		printf("\n");
	}
	printf("--------------------------\n");
}

int isSquareSafe(int a[9][9], int val, int row, int col)
{
	int i, j;
	for (i = row; i < row+3 ; i++)
		for(j = col; j < col+3; j++)
			if(a[i][j] == val)
				return 0;
	return 1;
}

int isColSafe(int a[9][9], int val, int col)
{
	int i;
	for(i = 0; i <9; i++)
		if(a[i][col] == val)
			return 0;
	return 1;
}

int isRowSafe(int a[9][9], int val, int row)
{
	int i;
	for(i = 0; i < 9 ; i++)
		if(a[row][i] == val)
			return 0;
	return 1;
}

int isSafe(int a[9][9], int val, int row, int col)
{
	if(isRowSafe(a, val, row) && isColSafe(a, val, col) && isSquareSafe(a, val, (row / 3)*3, (col/3)*3))
		return 1;
}

int sudokuSolver(int a[9][9])
{
	int row, col, val;
	for (row = 0 ; row < 9 ; row++) {
		for(col = 0; col < 9; col++) {
			if (a[row][col] == 0)
				goto fill_val;
		}
	}
fill_val:
	if (row == 9 && col == 9)
		return 1;
	else {
		for(val = 1; val < 10 ; val++)
			if(isSafe(a, val, row, col)) {
				printf("insert (%d, %d) = %d \n", row, col, val);
				a[row][col] = val;
				if(sudokuSolver(a))
					return 1;
				printf("Back track (%d %d)\n", row, col);
				a[row][col] = 0;
			}
	}
	return 0;
}

int main(void)
{
	int sudokuGrid[9][9] = {
  //{5, 3, 0, 0, 7, 0, 0, 0, 0},
  {5, 3, 0, 0, 7, 0, 0, 0, 0},
  {6, 0, 0, 1, 9, 5, 0, 0, 0},
  {0, 9, 8, 0, 0, 0, 0, 6, 0},
  {8, 0, 0, 0, 6, 0, 0, 0, 3},
  {4, 0, 0, 8, 0, 3, 0, 0, 1},
  {7, 0, 0, 0, 2, 0, 0, 0, 6},
  {0, 6, 0, 0, 0, 0, 2, 8, 0},
  {0, 0, 0, 4, 1, 9, 0, 0, 5},
  {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

	printSudoku(sudokuGrid);
	sudokuSolver(sudokuGrid);
	printSudoku(sudokuGrid);

}
