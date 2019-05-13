#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "general.h"

int check_sudoku_row(int mat[], int const size) {
	int i, j;
	int row[size];
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			row[j] = mat[(i * size) + j];
		}

		if (!check(row, size))
			return 0;
	}
	return 1;
}

int check_sudoku_col(int mat[], int const size) {
	int i, j;
	int col[size];
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			col[j] = mat[(j * size) + i];
		}
		if (!check(col, size))
			return 0;
	}
	return 1;
}

int check_sudoku_box(int mat[], int startRow, int startCol, int const size) {
	int i, j, index = 0;
	int cell[size];
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			cell[index++] = mat[((i + startRow) * size) + j + startCol];
		}
	}
	if (!check(cell, size))
		return 0;
	return 1;
}

int check_sudoku_cells(int mat[], int const size) {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (!check_sudoku_box(mat, i * 3, j * 3, size))
				return 0;
		}
	}
	return 1;
}

int check(int arr[], int size) {
	qsort(arr, size, sizeof(int), cmpfunc);
	for (int i = 1; i <= size; i++) {
		if (arr[i - 1] != i)
			return 0;
	}
	return 1;
}

int cmpfunc(const void * a, const void * b) {
	return (*(int*) a - *(int*) b);
}

int read_mat_from_file(int* mat, int size) {
	int num, i = 0;
	char filename[100];
	printf("Enter file name: ");
	scanf("%s", filename);
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("failed to load: %s \nProgram now closing.", filename);
		return 0;
	} else {
		fscanf(fp, "%d", &num);
		while (num != EOF && i < size * size) {
			mat[i++] = num;
			fscanf(fp, "%d", &num);
		}
		fclose(fp);
	}
	return 1;
}

void errExit(char str[]) {
	printf("%s", str);
	exit(-1);
}

int read_board_from_user(int* mat, int size) {
	int i, num;
	printf("Enter Soduko (Number by Number):\n");
	for (i = 0; i < size * size; i++) {
		scanf("%d", &num);
		if (num >= 1 && num <= 9)
			*(mat + i) = num;
		else
			*(mat + i) = DEFAULT;
	}
	return 1;
}

int read_mat(int* mat, int size) {
	int num;
	while (1) {
		printf("Enter '0' to load from file or '1' to load manully:\n");
		scanf("%d", &num);
		if (num == 1)
			return read_board_from_user(mat, size);
		else if(num == 0)
			return read_mat_from_file(mat, size);
		printf("Wrong input\n");
	}
}
