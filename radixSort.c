#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>

#define SIZE 256

typedef struct elem {
	unsigned int key;
	unsigned int value;
}elem;


void count_sort(elem* in, elem* out, int size, int byte)
{
	int table[SIZE] = { 0 };

	for (int i = 0; i < size; i++)
		table[(in[i].key >> 8 * byte) & 0x000000FF]++;

	int t = table[0];
	table[0] = 0;

	// смотрим с какого индекса нужно класть в результирующий массив 
	for (int i = 1; i < SIZE; i++)
	{
		t += table[i];
		table[i] = t - table[i];
	}

	for (int i = 0; i < size; i++)
	{
		int indx = (in[i].key >> 8 * byte) & 0x000000FF;
		out[table[indx]] = in[i];
		table[indx]++;
	}
}


void radix_sort(elem* a, int size)
{
	elem* out = (elem*)malloc(sizeof(elem) * size);

	for (int i = 0; i < 4; i++)
	{
		count_sort(a, out, size, i);

		//костыль на swap
		elem* tmp = out;
		out = a;
		a = tmp;
	}
}



int main()
{
	FILE* input = fopen("input.bin", "rb");
	FILE* output = fopen("output.bin", "wb");
	int N;
	fread(&N, sizeof(int), 1, input);

	elem* arr = (elem*)malloc(sizeof(elem) * N);
	fread(arr, sizeof(elem), N, input);

	radix_sort(arr, N);

	fwrite(arr, sizeof(elem), N, output);

	fclose(input);
	fclose(output);

	return 0;
}