#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int col_max(double** matrix, int col, int n)
{
	double maxE = matrix[col][col];
	int maxPos = col;

	for (int i = col + 1; i < n; i++)
	{
		double elem = fabs(matrix[i][col]);

		if (elem > maxE)
		{
			maxE = elem;
			maxPos = i;
		}
	}

	return maxPos;
}

void printMatrix(double** matrix, int n)
{
	printf("Test matrix\n\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
			printf("%0.3f ", matrix[i][j]);
		printf("\n");
	}
	printf("\nEnd test matrix\n\n");
}

int triangulation(double** matrix, int n)
{
	int column = 0;

	for (int i = 0; i < n; i++, column++)
	{
		int imax = col_max(matrix, i, n);

		double* t = matrix[i];
		matrix[i] = matrix[imax];
		matrix[imax] = t;

		if (matrix[i][column] == 0)
		{
			i--;
			continue;
		}

		for (int j = i + 1; j < n; j++)
		{
			double mul = matrix[j][i] / matrix[i][i];
			for (int k = i; k < n + 1; k++)
			{
				matrix[j][k] -= matrix[i][k] * mul;
			}
		}

		//printMatrix(matrix, n);
	}

	//printMatrix(matrix, n);

}

int cntNotZero(double* str, int n)
{
	for (int i = 0; i < n + 1; i++)
	{
		//printf("str[i]: %0.30f\n        %0.30f\n", fabs(str[i]), 1e-16);
		if (fabs(str[i]) > 1e-14)
		{
			//printf("indx: %d\n", i);
			return i;
		}
	}

	return -1;
}

void gauss(double** matrix, int n)
{
	double* X = (double*)calloc(sizeof(double), n);
	int* d = (int*)malloc(sizeof(int) * n);

	for (int j = 0; j < n; j++)
		d[j] = cntNotZero(matrix[j], n);

	//printMatrix(matrix, n);

	for (int i = n - 1; i >= 0; i--)
	{
		double sum = 0.0;

		if (d[i] != -1)
		{
			for (int j = d[i] + 1; j < n; j++)
				sum += matrix[i][j] * X[j];

			X[d[i]] = (matrix[i][n] - sum) / matrix[i][d[i]];
		}
	}

	for (int i = 0; i < n; i++)
	{
		printf("%0.15f\n", X[i]);
	}

	free(X);
	free(d);
}

int main()
{
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int N;
	scanf("%d", &N);

	double** matrix = (double**)malloc(sizeof(double*) * N);

	for (int i = 0; i < N; i++)
		matrix[i] = (double*)malloc(sizeof(double) * (N + 1));

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N + 1; j++)
		{
			double x;
			scanf("%lf", &x);
			matrix[i][j] = x;
		}


	triangulation(matrix, N);

	gauss(matrix, N);

	for (int i = 0; i < N; i++)
		free(matrix[i]);
	free(matrix);

	return 0;
}