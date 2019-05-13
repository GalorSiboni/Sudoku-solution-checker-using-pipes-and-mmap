Authors: Galor Siboni and Shahar Nissan

# Sudoku-solution-checker-using-pipes-and-mmap
Sudoku solution checker using pipes and mmap in C

#v1 - pipes and execv.

we check the sudoku solution with 3 process for rows,columns and 3v3 cells.

then we read the matrix from file to variable name mat.

and then we use execv to send the matrix to "checks.c" then send via pipes the checks resoult of each process beck to v1 and check if the 

solution is ligal or not. 


#v2 - mmap.

we check the sudoku solution with 3 process for rows,columns and 3v3 cells as well.

but now we store struct call Shared in mmap.

the struct hold the matrix and the status of each process.

we check ech process and store the resoults at the status.

and in a simple loop we check if the solution is ligal or not.
