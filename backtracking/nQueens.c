#include <stdio.h>
#include <stdlib.h>

int is_queen_ok(int n, int arr[][n], int r, int c)
{
	int i, j;
	/*upwards*/
	for (i = r - 1; i >=0 ; i--)
		if (arr[i][c] == 1)
			return -1;
	/*diag left up*/
	for (i = r-1, j = c-1; i >=0 && j >= 0 ; i--,j--)
		if (arr[i][j] == 1)
			return -1;
	/*diag right up*/
	for (i = r - 1, j = c+1; i >= 0 && j < n; i--, j++)
		if (arr[i][j] == 1)
			return -1;
	return 0;
}

int place_queens(int n, int arr[][n], int r)
{
	if (r == n)
		return 0;

	for (int c = 0; c < n ; c++) {
		if(is_queen_ok(n, arr, r, c) == 0) {
			int ret;
			arr[r][c] = 1;
			ret = place_queens(n, arr, r + 1);
			if (ret < 0)
				arr[r][c] = 0;
			else
				return 0;
		}	
	}
	return -1;
}

void print_arr(int n, int arr[][n])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n ;j++)
            printf("%3d", arr[i][j]);
        printf("\n");
    }
}

int main(void) {

	int size = 4;
	int (*arr)[size] = calloc(sizeof(int), size*size);
	place_queens(size, arr, 0);
	print_arr(size, arr);
	return 0;
}


