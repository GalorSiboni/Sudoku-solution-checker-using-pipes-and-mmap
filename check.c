#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "check.h"
#include "general.h"

int main(int argc, char *argv[]) {
	int size = 9;
	int mat[size * size];
	read(0, mat, sizeof(int) * size * size);
	int check = 1;
	switch (atoi(argv[1])) {
	case 0:
		if (!check_sudoku_row(mat, size))
			check = 0;
		break;

	case 1:
		if (!check_sudoku_col(mat, size))
			check = 0;
		break;

	case 2:
		if (!check_sudoku_cells(mat, size))
			check = 0;
		break;
	}
	write(1, &check, sizeof(int));
}
