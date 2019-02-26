#include <stdio.h>
#define GOLDEN_RATIO_64 0x61C8864680B583EBull

unsigned int get_random(unsigned long val, unsigned int bits)
{
	return val * GOLDEN_RATIO_64 >> (64 - bits);
}

void print_array(int *a)
{
	int i;
	for(i = 0; i < 9; i++)
		printf("%d ", a[i]);
	printf("\n");
}

printSudoku(int a[9][9])
{
	int row, col;
	for (row = 0 ; row < 9 ; row++){
		if(row%3 == 0)
			printf("--------------------------\n");

		for(col = 0 ; col < 9 ; col++) {
			if(col%3 == 0)
				printf(" | ");
			if ( a[row][col] == 0)
				printf( "  ");
			else
				printf("%d ", a[row][col]);
		}
		printf("\n");
	}
	printf("--------------------------\n");
}


/* Fill sub grid randomly */
void fillSubGrid(int a[9][9])
{
	int random = 23;
	unsigned int i,j,k, tmp;
	int arr[9];

	for(i = 1; i < 10; i++)
		arr[i-1] = i;


	/* shuffle arr */
	for(i = 0; i < 4; i++) {
		j = get_random((unsigned long)&random + random, 4);
		j = j % 9;
		k = get_random((unsigned long)&random + ++random, 4);
		k = k % 9;

//		printf("Swap loc %d and %d\n", j, k);
		tmp = arr[j];
		arr[j] = arr[k];
		arr[k] = tmp;

//		print_array(arr);
	}
	//print_array(arr);

	k=0;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++,k++)
			a[i][j] = arr[k];
}

int isRowSafe(int val, int a[9][9], int row)
{
	int i;
	for(i = 0; i < 9; i++)
		if (a[row][i] == val)
			return 0;
	return 1;
}

int isColSafe(int val, int a[9][9], int col)
{
	int i;
	for (i = 0 ; i < 9 ;i++)
		if (a[i][col] == val)
			return 0;
	return 1;
}

void fillFirstRow(int a[9][9])
{
	int i,j;
	int random = 23;
	int maxCount=0;

	for (i = 3; i < 9; i++) {
		if(a[0][i] == 0)
			break;
	}

	if(i == 9)
		return;

findRandom:
	j = get_random((unsigned long)&random + random, 4);
	j = j % 9;
	j++;
//	printf("j=%d ", j);
	if(isRowSafe(j, a, 0)) {
//		printf("fill (%d %d) = %d\n", 0, i, j);
		a[0][i] = j;
		fillFirstRow(a);
	}else {
		random +=7;
		if(maxCount++>100) {
		//	printf("cannot get the requried value\n");
			return;
		}
		goto findRandom;
	}
}

void fillFirstCol(int a[9][9])
{
	int i, maxCount=0, j;
	int random = 23;

	for(i = 3 ; i < 9; i++)
		if(a[i][0] == 0)
			break;

	if (i == 9)
		return;
findRandom:
	j = get_random((unsigned long)&random + random, 4);
	j = j%9;
	j++;
	//printf("j = %d ",j);

	if(isColSafe(j, a, 0)) {
	//	printf("fill (%d %d) = %d\n", 0, i, j);
		a[i][0] = j;
		fillFirstCol(a);
	}else {
		random +=7;
		if(maxCount++>100) {
	//		printf("cannot get the requried value\n");
			return;
		}
		goto findRandom;
	}

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
int isSafe(int a[9][9], int val, int row, int col)
{
	if(isRowSafe(val, a, row) && isColSafe(val, a, col) && isSquareSafe(a, val, (row / 3)*3, (col/3)*3))
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
				//printf("insert (%d, %d) = %d \n", row, col, val);
				a[row][col] = val;
				if(sudokuSolver(a))
					return 1;
				//printf("Back track (%d %d)\n", row, col);
				a[row][col] = 0;
			}
	}
	return 0;
}

int main(void)
{
	int a[9][9],i,j,k;
	int nr_blanks = 15;
	int random = 23;

	for(i = 0 ; i < 9; i++)
		for(j=0; j < 9; j++)
			a[i][j] = 0;

	fillSubGrid(a);
//	printSudoku(a);
	fillFirstRow(a);
//	printSudoku(a);
	fillFirstCol(a);
//	printSudoku(a);
	sudokuSolver(a);
//	printSudoku(a);

	while(nr_blanks) {
		j = get_random((unsigned long)&random + random, 4);
		printf ("j = %d ", j);
		j = j % 9;
		printf ("j = %d ", j);
		k = get_random((unsigned long)&random + ++random, 4);
		printf ("k = %d ", k);
		k = k % 9;
		printf ("k = %d\n", k);
		a[j][k] = 0;
		nr_blanks--;
	};

	printSudoku(a);
}
