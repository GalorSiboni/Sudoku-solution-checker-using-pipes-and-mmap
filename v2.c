#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include "v2.h"
#include "general.h"

int main(int argc, char* argv[]) {
	int size = 9, i;
	int mat[size * size], pid[3];
	shared* sudoku = (shared*) mmap(NULL, sizeof(shared),
			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
	if (sudoku == MAP_FAILED)
		errExit("v2 mmap");

	while (read_mat(mat, size)) {
		memcpy(sudoku->mat, mat, sizeof(int) * size * size);
		for (i = 0; i < 3; i++) {
			pid[i] = fork();
			if (pid[i] < 0)
				errExit("failed to create the process");
			else if (pid[i] == 0) {
				switch (i) {
				case 0:
					sudoku->status[0] = check_sudoku_row(sudoku->mat, size);
					exit(0);
					break;
				case 1:
					sudoku->status[1] = check_sudoku_col(sudoku->mat, size);
					exit(0);
					break;
				case 2:
					sudoku->status[2] = check_sudoku_cells(sudoku->mat, size);
					exit(0);
					break;
				}
			}
		}
		while (wait(NULL) > 0) {
		}
		int check = 1;
		for (i = 0; i < 3; i++) {
			if (sudoku->status[i] == 0) {
				check = 0;
			}
		}
		if (check)
			printf("legal\n");
		else
			printf("not legal\n");
	}
	munmap(sudoku, sizeof(shared));
}

