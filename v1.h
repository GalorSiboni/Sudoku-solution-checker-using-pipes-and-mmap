
#ifndef SOURCE_V1_H_
#define SOURCE_V1_H_

void print_mat_to_sons(int pipefd[3][2], int* mat, int size);
char* convert_int_to_string(int n);
int is_valid_sudoku(int pipefd[3][2]);

#endif /* SOURCE_V1_H_ */
