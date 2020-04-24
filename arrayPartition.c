#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>



int partition(int* a, int n, int pivot)
{
	int i = 0;
	int j = n - 1;
	int cnt = 0;
	while (i <= j)
	{
		while (a[i] < pivot)
			i++;
		while (a[j] > pivot)
			j--;
		if (a[i] == pivot) {
			cnt++;
			if (cnt % 2 == 0)
			{
				i++;
				continue;
			}
		}

		if (a[j] == pivot) {
			cnt++;
			if (cnt % 2 != 0)
			{
				j--;
				continue;
			}
		}

		if (i >= j)
			break;
		int tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
		i++;
		j--;
	}
	return i;
}


int main()
{
	FILE* input = fopen("input.bin", "rb");
	int N;
	fread(&N, sizeof(int), 1, input);
	int pivot;
	fread(&pivot, sizeof(int), 1, input);

	int* a = (int*)malloc(sizeof(int) * N);
	fread(a, sizeof(int), N, input);

	fclose(input);

	int k = partition(a, N, pivot);

	FILE* output = fopen("output.bin", "wb");
	fwrite(&k, sizeof(int), 1, output);
	fwrite(a, sizeof(int), N, output);

	free(a);
	return 0;
}