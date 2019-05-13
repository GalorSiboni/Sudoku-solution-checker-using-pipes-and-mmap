#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "v1.h"
#include "general.h"

int main(int argc, char *argv[]) {
	int size = 9, i;
	int mat[size * size], pid[3], pipefd[3][2];
	char* childs_args[] = { "./check", "",	NULL };
	while (read_mat(mat, size)) {
		for (i = 0; i < 3; i++) {
			childs_args[1] = convert_int_to_string(i);
			if (pipe(pipefd[i]) == -1)
				errExit("Failed to create pipe");
			pid[i] = fork();

			if (pid[i] < 0)
				errExit("failed to create the process");
			else if (pid[i] == 0) {
				dup2(pipefd[i][0], 0);
				dup2(pipefd[i][1], 1);
				execve(childs_args[0], childs_args, NULL);
			}

		}

		print_mat_to_sons(pipefd, mat, size);
		while (wait(NULL) > 0) {
		}
		if (is_valid_sudoku(pipefd))
			printf("legal\n");
		else
			printf("not legal\n");
	}
}

char* convert_int_to_string(int n) {
	char* temp = malloc(sizeof(int));
	sprintf(temp, "%d", n);
	return temp;
}

int is_valid_sudoku(int pipefd[3][2]) {
	int i, result[3];
	for (i = 0; i < 3; i++) {
		read(pipefd[i][0], &result[i], sizeof(int));
		if (!result[i])
			return 0;
	}
	return 1;
}

void print_mat_to_sons(int pipefd[3][2], int* mat, int size) {
	int i;
	for (i = 0; i < 3; i++)
		write(pipefd[i][1], mat, sizeof(int) * size * size);
}
