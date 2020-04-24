#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define INF 3*1000*1000

typedef struct Heap_s {
	int* arr;
	int size;
}Heap;

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void add(int value, Heap* heap)
{
	heap->arr[heap->size] = value;
	heap->size++;

	int i = heap->size - 1;
	int parent = (i - 1) / 2;

	while (i > 0 && heap->arr[parent] > heap->arr[i])
	{
		swap(&heap->arr[i], &heap->arr[parent]);

		i = parent;
		parent = (i - 1) / 2;
	}
}

void heapify(int i, Heap* heap)
{
	int leftChild;
	int rightChild;
	int largestChild;

	for (; ; )
	{
		leftChild = 2 * i + 1;
		rightChild = 2 * i + 2;
		largestChild = i;

		if (leftChild < heap->size && heap->arr[leftChild] < heap->arr[largestChild])
		{
			largestChild = leftChild;
		}

		if (rightChild < heap->size && heap->arr[rightChild] < heap->arr[largestChild])
		{
			largestChild = rightChild;
		}

		if (largestChild == i)
		{
			break;
		}

		swap(&heap->arr[i], &heap->arr[largestChild]);

		i = largestChild;
	}
}

int getMin(Heap* heap)
{
	int result = heap->arr[0];
	swap(&heap->arr[0], &heap->arr[heap->size - 1]);
	heap->size--;
	return result;
}

int main()
{
	FILE* input = fopen("input.bin", "rb");
	int size;
	fread(&size, sizeof(int), 1, input);

	Heap* heap = (Heap*)malloc(sizeof(Heap));
	heap->arr = malloc(sizeof(int) * size);
	heap->size = 0;

	for (int i = 0; i < size; i++)
	{
		int value;
		fread(&value, sizeof(int), 1, input);
		add(value, heap);
	}

	FILE* output = fopen("output.bin", "wb");
	for (int i = size - 1; i >= 0; i--)
	{
		int val = getMin(heap);
		fwrite(&val, sizeof(int), 1, output);
		heapify(0, heap);
	}

	return 0;
}