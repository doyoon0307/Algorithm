#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void printarray(int n, int **A) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%d ", A[i][j]);
		printf("\n");
	}
}
int multiplication = 0, addition = 0, subtraction = 0;
void standard(int n, int **A, int **B, int **C) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (k == 0) {
					C[i][j] = A[i][k] * B[k][j];
					multiplication++;
				}
				else {
					C[i][j] = C[i][j] + A[i][k] * B[k][j];
					multiplication++, addition++;
				}
			}
		}
	}
}
int **rmatrix_addition(int n, int **A, int **B, int **C) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			C[i][j] = A[i][j] + B[i][j];
			addition++;
		}
	}
	return C;
}
int **matrixmerge(int n, int **c11, int **c12, int **c21, int **c22) {
	int row = 0, column = 0;
	int **C = (int **)malloc(sizeof(int *) * n);
	for (int i = 0; i < n; i++)
		C[i] = (int *)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		column = 0;
		for (int j = 0; j < n; j++) {
			if (i < n / 2 && j < n / 2)
				C[i][j] = c11[i][j];
			else if (i >= n / 2 && j >= n / 2)
				C[i][j] = c22[row][column];
			else if (i >= n / 2 && j < n / 2)
				C[i][j] = c21[row][j];
			else if (i < n / 2 && j >= n / 2)
				C[i][j] = c12[i][column];
			if (j >= n / 2)
				column++;
		}
		if (i >= n / 2)
			row++;
	}
	return C;
}
int **recursion(int n, int **A, int **B) {
	int i, j, k;
	if (n == 1) {
		int **result = (int **)malloc(sizeof(int *) * n);
		for (i = 0; i < n; i++)
			result[i] = (int *)malloc(sizeof(int) * n);
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				result[i][j] = 0;
				for (k = 0; k < n; k++) {
					result[i][j] = A[i][k] * B[k][j];
					multiplication++;
				}
			}
		}
		return result;
	}
	else {
		int row = 0, column = 0;
		int **a11 = (int **)malloc(sizeof(int *) * (n / 2));
		int **a12 = (int **)malloc(sizeof(int *) * (n / 2));
		int **a21 = (int **)malloc(sizeof(int *) * (n / 2));
		int **a22 = (int **)malloc(sizeof(int *) * (n / 2));
		int **b11 = (int **)malloc(sizeof(int *) * (n / 2));
		int **b12 = (int **)malloc(sizeof(int *) * (n / 2));
		int **b21 = (int **)malloc(sizeof(int *) * (n / 2));
		int **b22 = (int **)malloc(sizeof(int *) * (n / 2));
		int **c11 = (int **)malloc(sizeof(int *) * (n / 2));
		int **c12 = (int **)malloc(sizeof(int *) * (n / 2));
		int **c21 = (int **)malloc(sizeof(int *) * (n / 2));
		int **c22 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m1 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m2 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m3 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m4 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m5 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m6 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m7 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m8 = (int **)malloc(sizeof(int *) * (n / 2));
		for (i = 0; i < n / 2; i++) {
			a11[i] = (int *)malloc(sizeof(int) * (n / 2));
			a12[i] = (int *)malloc(sizeof(int) * (n / 2));
			a21[i] = (int *)malloc(sizeof(int) * (n / 2));
			a22[i] = (int *)malloc(sizeof(int) * (n / 2));
			b11[i] = (int *)malloc(sizeof(int) * (n / 2));
			b12[i] = (int *)malloc(sizeof(int) * (n / 2));
			b21[i] = (int *)malloc(sizeof(int) * (n / 2));
			b22[i] = (int *)malloc(sizeof(int) * (n / 2));
			c11[i] = (int *)malloc(sizeof(int) * (n / 2));
			c12[i] = (int *)malloc(sizeof(int) * (n / 2));
			c21[i] = (int *)malloc(sizeof(int) * (n / 2));
			c22[i] = (int *)malloc(sizeof(int) * (n / 2));
			m1[i] = (int *)malloc(sizeof(int *) * (n / 2));
			m2[i] = (int *)malloc(sizeof(int *) * (n / 2));
			m3[i] = (int *)malloc(sizeof(int *) * (n / 2));
			m4[i] = (int *)malloc(sizeof(int *) * (n / 2));
			m5[i] = (int *)malloc(sizeof(int *) * (n / 2));
			m6[i] = (int *)malloc(sizeof(int *) * (n / 2));
			m7[i] = (int *)malloc(sizeof(int *) * (n / 2));
			m8[i] = (int *)malloc(sizeof(int *) * (n / 2));
		}
		for (i = 0; i < n; i++) {
			column = 0;
			for (j = 0; j < n; j++) {
				if (i < n / 2 && j < n / 2) {
					a11[i][j] = A[i][j], b11[i][j] = B[i][j];
					c11[i][j] = 0, c12[i][j] = 0, c21[i][j] = 0, c22[i][j] = 0;

				}
				else if (i >= n / 2 && j >= n / 2)
					a22[row][column] = A[i][j], b22[row][column] = B[i][j];
				else if (i >= n / 2 && j < n / 2)
					a21[row][j] = A[i][j], b21[row][j] = B[i][j];
				else if (i < n / 2 && j >= n / 2)
					a12[i][column] = A[i][j], b12[i][column] = B[i][j];
				if (j >= n / 2)
					column++;
			}
			if (i >= n / 2)
				row++;
		}
		row = 0, column = 0;
		m1 = recursion(n / 2, a11, b11);
		m2 = recursion(n / 2, a12, b21);
		m3 = recursion(n / 2, a11, b12);
		m4 = recursion(n / 2, a12, b22);
		m5 = recursion(n / 2, a21, b11);
		m6 = recursion(n / 2, a22, b21);
		m7 = recursion(n / 2, a21, b12);
		m8 = recursion(n / 2, a22, b22);
		rmatrix_addition(n / 2, m1, m2, c11);
		rmatrix_addition(n / 2, m3, m4, c12);
		rmatrix_addition(n / 2, m5, m6, c21);
		rmatrix_addition(n / 2, m7, m8, c22);

		int **C = matrixmerge(n, c11, c12, c21, c22);
		free(a11[0]), free(a11), free(a12[0]), free(a12), free(a21[0]), free(a21), free(a22[0]), free(a22);
		free(b11[0]), free(b11), free(b12[0]), free(b12), free(b21[0]), free(b21), free(b22[0]), free(b22);
		free(c11[0]), free(c11), free(c12[0]), free(c12), free(c21[0]), free(c21), free(c22[0]), free(c22);
		free(m1[0]), free(m1), free(m2[0]), free(m2), free(m3[0]), free(m3), free(m4[0]), free(m4);
		free(m5[0]), free(m5), free(m6[0]), free(m6), free(m7[0]), free(m7), free(m8[0]), free(m8);
		return C;
	}
}
void matrix_addition(int n, int **A, int **B, int **C) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			C[i][j] = A[i][j] + B[i][j];
			addition++;
		}
	}
}
void matrix_subtraction(int n, int **A, int**B, int**C) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			C[i][j] = A[i][j] - B[i][j];
			subtraction++;
		}
	}
}
void strassen(int n, int **A, int **B, int **C) {
	int i, j, k;
	if (n < 2) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				C[i][j] = 0;
				for (k = 0; k < n; k++) {
					if (k == 0) {
						C[i][j] = A[i][k] * B[k][j];
						multiplication++;
					}
					else {
						C[i][j] = C[i][j] + A[i][k] * B[k][j];
						multiplication++, addition++;
					}
				}
			}
		}
	}
	else {
		int row = 0, column = 0;
		int **a11 = (int **)malloc(sizeof(int *) * (n / 2));
		int **a12 = (int **)malloc(sizeof(int *) * (n / 2));
		int **a21 = (int **)malloc(sizeof(int *) * (n / 2));
		int **a22 = (int **)malloc(sizeof(int *) * (n / 2));
		int **b11 = (int **)malloc(sizeof(int *) * (n / 2));
		int **b12 = (int **)malloc(sizeof(int *) * (n / 2));
		int **b21 = (int **)malloc(sizeof(int *) * (n / 2));
		int **b22 = (int **)malloc(sizeof(int *) * (n / 2));
		int **c11 = (int **)malloc(sizeof(int *) * (n / 2));
		int **c12 = (int **)malloc(sizeof(int *) * (n / 2));
		int **c21 = (int **)malloc(sizeof(int *) * (n / 2));
		int **c22 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m1 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m2 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m3 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m4 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m5 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m6 = (int **)malloc(sizeof(int *) * (n / 2));
		int **m7 = (int **)malloc(sizeof(int *) * (n / 2));
		int **temp1 = (int **)malloc(sizeof(int *) * (n / 2));
		int **temp2 = (int **)malloc(sizeof(int *) * (n / 2));
		for (i = 0; i < n / 2; i++) {
			a11[i] = (int *)malloc(sizeof(int) * (n / 2));
			a12[i] = (int *)malloc(sizeof(int) * (n / 2));
			a21[i] = (int *)malloc(sizeof(int) * (n / 2));
			a22[i] = (int *)malloc(sizeof(int) * (n / 2));
			b11[i] = (int *)malloc(sizeof(int) * (n / 2));
			b12[i] = (int *)malloc(sizeof(int) * (n / 2));
			b21[i] = (int *)malloc(sizeof(int) * (n / 2));
			b22[i] = (int *)malloc(sizeof(int) * (n / 2));
			c11[i] = (int *)malloc(sizeof(int) * (n / 2));
			c12[i] = (int *)malloc(sizeof(int) * (n / 2));
			c21[i] = (int *)malloc(sizeof(int) * (n / 2));
			c22[i] = (int *)malloc(sizeof(int) * (n / 2));
			m1[i] = (int *)malloc(sizeof(int *) * (n / 2));
			m2[i] = (int *)malloc(sizeof(int *) * (n / 2));
			m3[i] = (int *)malloc(sizeof(int *) * (n / 2));
			m4[i] = (int *)malloc(sizeof(int *) * (n / 2));
			m5[i] = (int *)malloc(sizeof(int *) * (n / 2));
			m6[i] = (int *)malloc(sizeof(int *) * (n / 2));
			m7[i] = (int *)malloc(sizeof(int *) * (n / 2));
			temp1[i] = (int *)malloc(sizeof(int *) * (n / 2));
			temp2[i] = (int *)malloc(sizeof(int *) * (n / 2));
		}
		for (i = 0; i < n; i++) {
			column = 0;
			for (j = 0; j < n; j++) {
				if (i < n / 2 && j < n / 2) {
					a11[i][j] = A[i][j], b11[i][j] = B[i][j];
					temp1[i][j] = 0, temp2[i][j] = 0;
					c11[i][j] = 0, c12[i][j] = 0, c21[i][j] = 0, c22[i][j] = 0;

				}
				else if (i >= n / 2 && j >= n / 2)
					a22[row][column] = A[i][j], b22[row][column] = B[i][j];
				else if (i >= n / 2 && j < n / 2)
					a21[row][j] = A[i][j], b21[row][j] = B[i][j];
				else if (i < n / 2 && j >= n / 2)
					a12[i][column] = A[i][j], b12[i][column] = B[i][j];
				if (j >= n / 2)
					column++;
			}
			if (i >= n / 2)
				row++;
		}
		row = 0, column = 0;
		matrix_addition(n / 2, a11, a22, temp1);

		matrix_addition(n / 2, b11, b22, temp2);
		strassen(n / 2, temp1, temp2, m1);

		matrix_addition(n / 2, a21, a22, temp1);
		strassen(n / 2, temp1, b11, m2);

		matrix_subtraction(n / 2, b12, b22, temp2);
		strassen(n / 2, a11, temp2, m3);

		matrix_subtraction(n / 2, b21, b11, temp2);
		strassen(n / 2, a22, temp2, m4);

		matrix_addition(n / 2, a11, a12, temp1);
		strassen(n / 2, temp1, b22, m5);

		matrix_subtraction(n / 2, a21, a11, temp1);
		matrix_addition(n / 2, b11, b12, temp2);
		strassen(n / 2, temp1, temp2, m6);

		matrix_subtraction(n / 2, a12, a22, temp1);
		matrix_addition(n / 2, b21, b22, temp2);
		strassen(n / 2, temp1, temp2, m7);

		matrix_addition(n / 2, m1, m4, temp1);
		matrix_subtraction(n / 2, temp1, m5, temp2);
		matrix_addition(n / 2, temp2, m7, c11);

		matrix_addition(n / 2, m3, m5, c12);

		matrix_addition(n / 2, m2, m4, c21);

		matrix_addition(n / 2, m1, m3, temp1);
		matrix_subtraction(n / 2, temp1, m2, temp2);
		matrix_addition(n / 2, temp2, m6, c22);

		for (i = 0; i < n; i++) {
			column = 0;
			for (j = 0; j < n; j++) {
				if (i < n / 2 && j < n / 2)
					C[i][j] = c11[i][j];
				else if (i >= n / 2 && j >= n / 2)
					C[i][j] = c22[row][column];
				else if (i >= n / 2 && j < n / 2)
					C[i][j] = c21[row][j];
				else if (i < n / 2 && j >= n / 2)
					C[i][j] = c12[i][column];
				if (j >= n / 2)
					column++;
			}
			if (i >= n / 2)
				row++;
		}
		free(a11[0]), free(a11), free(a12[0]), free(a12), free(a21[0]), free(a21), free(a22[0]), free(a22);
		free(b11[0]), free(b11), free(b12[0]), free(b12), free(b21[0]), free(b21), free(b22[0]), free(b22);
		free(c11[0]), free(c11), free(c12[0]), free(c12), free(c21[0]), free(c21), free(c22[0]), free(c22);
		free(m1[0]), free(m1), free(m2[0]), free(m2), free(m3[0]), free(m3), free(m4[0]), free(m4);
		free(m5[0]), free(m5), free(m6[0]), free(m6), free(m7[0]), free(m7);
		free(temp1[0]), free(temp1), free(temp2[0]), free(temp2);
	}
}

int main() {
	int i, j, k;
	int **A = (int **)malloc(sizeof(int *) * 4);
	int **B = (int **)malloc(sizeof(int *) * 4);
	int **C = (int **)malloc(sizeof(int *) * 4);
	int **x = (int **)malloc(sizeof(int *) * 8);
	int **y = (int **)malloc(sizeof(int *) * 8);
	int **z = (int **)malloc(sizeof(int *) * 8);
	for (i = 0; i < 4; i++) {
		A[i] = (int *)malloc(sizeof(int) * 4);
		B[i] = (int *)malloc(sizeof(int) * 4);
		C[i] = (int *)malloc(sizeof(int) * 4);
	}
	for (i = 0; i < 8; i++) {
		x[i] = (int *)malloc(sizeof(int) * 8);
		y[i] = (int *)malloc(sizeof(int) * 8);
		z[i] = (int *)malloc(sizeof(int) * 8);
	}
	srand(time(NULL));
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			A[i][j] = rand() % 1000;
			B[i][j] = rand() % 1000;
			C[i][j] = 0;
		}
	}
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			x[i][j] = rand() % 1000;
			y[i][j] = rand() % 1000;
			z[i][j] = 0;
		}
	}
	printf("A[4][4] matrix is \n"), printarray(4, A);
	printf("\nB[4][4] matrix is \n"), printarray(4, B);
	printf("\nx[8][8] matrix is \n"), printarray(8, x);
	printf("\ny[8][8] matrix is \n"), printarray(8, y);

	//Standard algorithm
	printf("\n< Standard algorithm > \n");
	standard(4, A, B, C);
	printf("C[4][4] matrix is \n"), printarray(4, C);
	printf("In 4 * 4 matrix, the number of multiplication is %d, addition is %d and subtraction is %d.\n", multiplication, addition, subtraction);
	printf("In 4 * 4 matrix, the number of total computations is %d.\n", multiplication + addition + subtraction);
	multiplication = 0, addition = 0, subtraction = 0;
	standard(8, x, y, z);
	printf("\nz[8][8] matrix is \n"), printarray(8, z);
	printf("In 8 * 8 matrix, the number of multiplication is %d, addition is %d and subtraction is %d.\n", multiplication, addition, subtraction);
	printf("In 8 * 8 matrix, the number of total computations is %d.\n", multiplication + addition + subtraction);

	//Recursion
	printf("\n< Recursion > \n");
	multiplication = 0, addition = 0, subtraction = 0;
	int **D = recursion(4, A, B); //just answer matrix is D, not affecting to answer
	printf("C[4][4] matrix is \n"), printarray(4, D);
	printf("In 4 * 4 matrix, the number of multiplication is %d, addition is %d and subtraction is %d.\n", multiplication, addition, subtraction);
	printf("In 4 * 4 matrix, the number of total computations is %d.\n", multiplication + addition + subtraction);
	multiplication = 0, addition = 0, subtraction = 0;
	int **E = recursion(8, x, y); //just answer matrix is E, not affecting to answer
	printf("\nz[8][8] matrix is \n"), printarray(8, E);
	printf("In 8 * 8 matrix, the number of multiplication is %d, addition is %d and subtraction is %d.\n", multiplication, addition, subtraction);
	printf("In 8 * 8 matrix, the number of total computations is %d.\n", multiplication + addition + subtraction);

	//Strassen's method
	printf("\n< Strassen's method > \n");
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
			C[i][j] = 0;
	}
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++)
			z[i][j] = 0;
	}
	multiplication = 0, addition = 0, subtraction = 0;
	strassen(4, A, B, C);
	printf("C[4][4] matrix is \n"), printarray(4, C);
	printf("In 4 * 4 matrix, the number of multiplication is %d, addition is %d and subtraction is %d.\n", multiplication, addition, subtraction);
	printf("In 4 * 4 matrix, the number of total computations is %d.\n", multiplication + addition + subtraction);
	multiplication = 0, addition = 0, subtraction = 0;
	strassen(8, x, y, z);
	printf("\nz[8][8] matrix is \n"), printarray(8, z);
	printf("In 8 * 8 matrix, the number of multiplication is %d, addition is %d and subtraction is %d.\n", multiplication, addition, subtraction);
	printf("In 8 * 8 matrix, the number of total computations is %d.\n", multiplication + addition + subtraction);

	free(A[0]), free(A), free(B[0]), free(B), free(C[0]), free(C);
	free(x[0]), free(x), free(y[0]), free(y), free(z[0]), free(z);
}