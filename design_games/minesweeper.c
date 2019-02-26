#include <stdio.h>
#include <stdlib.h>

#define BOMB 0x9
struct ms {
	int rows;
	int cols;
	int closed_cells;
	int **array_val;
	int **array_show;
};

int random1(int val)
{
	return 0x1235671 * val;
}

int random2(int val)
{
	return 0xC235671 * val;
}

void adjust_bomb_near_cells(int row, int col, struct ms *ms)
{
	int baserow = row - 1;
	int basecol = col -1;
	int i, j;

	for (i = baserow; i < baserow + 3 ; i++)
		for(j = basecol ; j < basecol +3 ; j++) {
			if (i < 0 || j < 0 || i >= ms->rows || j >= ms->cols)
				continue;
			/* missed this while paper coding */
			if(ms->array_val[i][j] == BOMB)continue;
			if (i == row && j == col)continue;
			ms->array_val[i][j] += 1;
		}
}

void print_data(struct ms *ms, int force)
{
	int i, j;

	printf("  ");
	for (i = 0 ; i < ms->rows ; i++)
		printf(" %d ", i);
	printf("\n");
	for (i = 0 ; i < ms->rows ; i++)
		printf("===");
	printf("\n");

	for (i = 0 ; i < ms->rows ; i++) {
		printf("%d|", i);
		for (j = 0 ; j < ms->cols ; j++)
			if (force || ms->array_show[i][j])
				printf(" %d ", ms->array_val[i][j]);
			else
				printf("   ");
		printf("\n");
	}
	printf("\n");
	printf("\n");
}

int is_valid_index(int row, int col, struct ms *ms)
{
	if (row < 0 || row >= ms->rows || col < 0 || col >= ms->cols)
		return 0;
	return 1;
}

void open_cell(int row, int col, struct ms *ms)
{
	if(!is_valid_index(row, col, ms) || ms->array_show[row][col])
		return;

	ms->array_show[row][col] = 1;
	ms->closed_cells--;
}

void open_adjacent(int row, int col, struct ms *ms)
{
	int base_row = row - 1;
	int base_col = col - 1;
	int i, j;

	if(!is_valid_index(row, col, ms))
		return;

	for (i = base_row ; i < base_row + 3 ; i++)
		for (j = base_col ; j < base_col + 3 ; j++) {
			/* Avoid recursion on same cell */
			if ( i == row && j == col)
				continue;
			if (!is_valid_index(i, j, ms))
				continue;
			/* continue if cell is already opened */
			if (ms->array_show[i][j] == 1)
				continue;
			/* continue if cell is boundary cell */
			if (ms->array_val[i][j] !=  0){
				open_cell(i, j, ms);
				continue;
			}
			open_cell(i, j, ms);
			open_adjacent(i, j, ms);
		}
}

void process_entry(int row, int col, struct ms *ms)
{
	int value = ms->array_val[row][col];

	if (value == BOMB) {
		printf("you are busted\n");
		print_data(ms, 1);
		exit(-1);
	}

	/* return if already opened */
	if (ms->array_show[row][col] == 1)
		return;

	/* if clicked on a bomb boundary. open that alone */
	if (value != 0) {
		open_cell(row,col, ms);
		return;
	}

	/* clicked on a empty cell. open adajcent cells aswell*/
	open_cell(row, col, ms);
	open_adjacent(row, col, ms);
}

void minesweeper(int rows, int cols)
{
	struct ms *ms = malloc(sizeof(struct ms));
	int no_bombs, temp_row, temp_col, i, rand_int = 0;

	ms->rows = rows;
	ms->cols = cols;
	ms->closed_cells = rows*cols;

	/* missed int * while paper coding
	 * http://www.firmcodes.com/write-c-code-dynamically-allocate-one-two-three-dimensional-arrays-using-malloc/
	 */
	ms->array_val = calloc(rows, sizeof(int*));
	ms->array_show = calloc(rows, sizeof(int*));

	/* missed this while paper coding */
	for(i = 0 ; i < rows ; i++) {
		ms->array_val[i] = calloc(cols, sizeof(int));
		ms->array_show[i] = calloc(cols, sizeof(int));
	}

	no_bombs = rows/3 + cols/3;
	no_bombs = 10;
	printf("no_bombs = %d\n", no_bombs);
	i = no_bombs;
	while(i) {
		if (i%1) {
			temp_row = abs(random1((int)ms->array_val[i + rand_int +1])% rows);
			temp_col = abs(random2((int)ms->array_val[i+ rand_int])% rows);
		} else {
			temp_row = abs(random1((int)ms->array_val[i + rand_int +1])% rows);
			temp_col = abs(random1((int)ms->array_show[i+ rand_int])% rows);
		}

		printf("row = %d col = %d\n", temp_row, temp_col);
		/* missed this while paper coding */
		if(ms->array_val[temp_row][temp_col] == BOMB){
			rand_int++;
			continue;
		}

		i--;
		printf("->>>row = %d col = %d\n", temp_row, temp_col);
		ms->array_val[temp_row][temp_col] = BOMB;
		adjust_bomb_near_cells(temp_row, temp_col, ms);
	}

	print_data(ms, 1);

	while (1) {
		int row, col;
		print_data(ms, 0);
		printf("please enter row number:");
		scanf("%d", &row);
		printf("please enter col number:");
		scanf("%d", &col);

		printf(" row col (%d %d)\n", row, col);
		if (!is_valid_index(row, col, ms))
			continue;
		process_entry(row, col, ms);
		printf("closed cells = %d\n", ms->closed_cells);
		if (ms->closed_cells == no_bombs) {
			printf("Congratulations..... You won!!!!!!!!\n");
			print_data(ms, 1);
			return;
		}
	}
}

int main(void)
{
	printf("rand %d\n", rand());
	minesweeper(10, 10);
}
