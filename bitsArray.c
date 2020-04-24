#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 312500

// initialize empty array of <num> lenght, sets all it's bits to zero
void bitsetZero(unsigned int* arr, int num)
{
	int len = (num + 8 * sizeof(unsigned int) - 1) / (8 * sizeof(unsigned int));
	memset(arr, 0, sizeof(unsigned int) * len);
}

// returns value of idx bit from bits array (0 or 1)
int bitsetGet(const unsigned int* arr, int indx)
{
	int bwIndx = indx / (8 * sizeof(unsigned int));
	int offset = indx % (8 * sizeof(unsigned int));
	unsigned int current = arr[bwIndx];
	int res = current & (1 << offset);

	if (res == 0)
		return res;
	else
		return 1;
}

// sets the value of idx bit of bits array to newval (0 or 1)
void bitsetSet(unsigned int* arr, int indx, int newval)
{
	int bwIndx = indx / (8 * sizeof(unsigned int));
	int offset = indx % (8 * sizeof(unsigned int));
	unsigned int current = arr[bwIndx];
	int res = current & (1 << offset);

	if (res != 0) res = 1;

	if (res != newval) arr[bwIndx] ^= (1 << offset);
}

// returns 1 if among bits with numbers k
// for left <= k < right there is a 1-valued, and 0 otherwise
int bitsetAny(const unsigned int* arr, int left, int right)
{
	int lbwIndx = left / (8 * sizeof(unsigned int));
	int lOffset = left % (8 * sizeof(unsigned int));
	int rbwIndx = right / (8 * sizeof(unsigned int));
	int rOffset = right % (8 * sizeof(unsigned int));

	if (lbwIndx == rbwIndx)
	{
		for (int i = lOffset; i < rOffset; i++)
		{
			int res = arr[lbwIndx] & (1 << i);

			if (res != 0) return 1;
		}

		return 0;
	}
	else
	{
		for (int i = lOffset; i < (8 * sizeof(unsigned int)); i++)
		{
			int res = arr[lbwIndx] & (1 << i);

			if (res != 0) return 1;
		}

		for (int i = lbwIndx + 1; i < rbwIndx; i++)
			if (arr[i] != 0) return 1;

		for (int i = 0; i < rOffset; i++)
		{
			int res = arr[rbwIndx] & (1 << i);

			if (res != 0) return 1;
		}

		return 0;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

    // number of operations
	int N;
	scanf("%d", &N);

	unsigned int* bwarr = (unsigned int*)malloc(sizeof(unsigned int) * SIZE);

	for (int i = 0; i < N; i++) 
	{
        // t - operation name
        // t = 0 bitsetZer0
        // t = 1 bitsetGet
        // t = 2 bitsetSet
        // t = 3 bitsetAny
		int t;
		scanf("%d", &t);

		if (t == 0) 
		{
			int num;
			scanf("%d", &num);
			bitsetZero(bwarr, num);
		}

		if (t == 1)
		{
			int indx;
			scanf("%d", &indx);
			printf("%d\n", bitsetGet(bwarr, indx));
		}

		if (t == 2)
		{
			int indx, newval;
			scanf("%d %d", &indx, &newval);
			bitsetSet(bwarr, indx, newval);
		}

		if (t == 3) 
		{
			int left, right;
			scanf("%d %d", &left, &right);
			int res = bitsetAny(bwarr, left, right);

			if (res == 1)
				printf("some\n");
			else
				printf("none\n");
		}
	}

	return 0;
}