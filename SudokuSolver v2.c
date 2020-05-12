/*
* Sudoku Solving Algorithm based on backtracking algorithm
* using a recursion
*/
#include <stdio.h>
#include <stdbool.h>

#define MAXC 9
#define MAXR 9

//Source array (World's Hardest Sudoku board)
//0 means unassigned cells
int arr[MAXR][MAXC] =
{
	8,0,0,0,0,0,0,0,0,
	0,0,3,6,0,0,0,0,0,
	0,7,0,0,9,0,2,0,0,
	0,5,0,0,0,7,0,0,0,
	0,0,0,0,4,5,7,0,0,
	0,0,0,1,0,0,0,3,0,
	0,0,1,0,0,0,0,6,8,
	0,0,8,5,0,0,0,1,0,
	0,9,0,0,0,0,4,0,0
};

//Checks whether it will be ok  
//to assign num to the given row, col 
bool success;
void check(int row, int col, int array[MAXR][MAXC], int prediction)
{
	int x0, y0;
	success = true;

	//checks rows
	for (int i = 0; i < MAXR; i++)
		if (array[i][col] == prediction)
			success = false;

	//checks cols
	for (int i = 0; i < MAXC; i++)
		if (array[row][i] == prediction)
			success = false;

	x0 = (col / 3) * 3;
	y0 = (row / 3) * 3;

	//checks the 3x3 board 
	//which contains the estimated number
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (array[y0 + i][x0 + j] == prediction)
				success = false;
}

/* Takes a partially filled-in grid and attempts
to assign values to all unassigned locations in
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */
bool solve(void)
{
	for (int i = 0; i < MAXR; i++)
		for (int j = 0; j < MAXC; j++)
			if (arr[i][j] == 0) {	//makes sure that is cell is unassigned
				for (int pred = 1; pred < 10; pred++) {
					//consider digits 1 to 9 
					check(i, j, arr, pred);
					if (success) {

						//assign and call recursively 
						printf("Number %d (%d;%d) successed\n", pred, i, j);
						arr[i][j] = pred;

						if (solve(arr))
							return true;

						printf("Something wrong, go back and try again\n");
						arr[i][j] = 0;
					}
				}
				return false;
			}
}

//Simple function to print the array
void PrintArray(int array[MAXR][MAXC])
{
	for (int i = 0; i < 9; i++) { 
		if (i == (i / 3) * 3) {
			for (int k = 0; k < 9; k++)
				printf(" -");

			printf("\n");

			for (int j = 0; j < 9; j++) {
				if (j == (j / 3) * 3) {
					printf(" |");
					printf(" %d", array[i][j]);
				} 
				else
					printf(" %d", array[i][j]);
			}
		} 
		else
		{
			for (int j = 0; j < 9; j++) {
				if (j == (j / 3) * 3) {
					printf(" |");
					printf(" %d", array[i][j]);
				}
				else
					printf(" %d", array[i][j]);
			}
		}

		printf("\n");
	}
}

//driver function
int main(void)
{
	solve();
	PrintArray(arr);
	getchar();
	return 0;
}

