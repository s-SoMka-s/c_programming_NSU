#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int merge(const int* a, int ak, const int* b, int bk, int* res)
{
	int it1 = 0;
	int it2 = 0;
	int iter = 0;

	for (int i = 0; i < ak + bk; i++)
	{
		if (it1 >= ak) {
			res[i] = b[it2++];
			continue;
		}

		if (it2 >= bk) {
			res[i] = a[it1++];
			continue;
		}
		

		if (a[it1] < b[it2])
		{
			res[i] = a[it1];
			it1++;
		}
		else
		{
			res[i] = b[it2];
			it2++;
		}
	}

	return 0;
}


int main()
{
	FILE* input = fopen("input.bin", "rb");
	int N;
	fread(&N, sizeof(int), 1, input);
	int M;
	fread(&M, sizeof(int), 1, input);

	int* a = (int*)malloc(sizeof(int) * N);
	fread(a, sizeof(int), N, input);

	int* b = (int*)malloc(sizeof(int) * M);
	fread(b, sizeof(int), M, input);

	int* res = (int*)malloc(sizeof(int) * (N + M));

	merge(a, N, b, M, res);

	FILE* output = fopen("output.bin", "wb");
	fwrite(res, sizeof(int), N+M, output);
}