
#ifndef GENERAL_H_
#define GENERAL_H_

	#define DEFAULT 1

	int cmpfunc (const void * a, const void * b);
	int check(int arr[], int size);
	int check_sudoku_cells(int mat[], int const size);
	int check_sudoku_box(int mat[], int startRow, int startCol, int const size);
	int check_sudoku_col(int mat[], int const size) ;
	int check_sudoku_row(int mat[], int const size);
	int read_mat_from_file(int* mat, int size);
	int read_mat(int* mat, int size);
	int read_board_from_user(int* mat, int size);
	void errExit(char str[]);

#endif /* GENERAL_H_ */
