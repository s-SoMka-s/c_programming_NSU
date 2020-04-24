#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define INF 3*1000*1000

int cnt = 0;

typedef struct TreeNode_s
{
	int cnt;
	int value; // ключ/данные
	struct TreeNode* left; // указатель на левого потомка
	struct TreeNode* right; // указатель на правого потомка
}TreeNode;

TreeNode* createNode(int value)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = NULL;
	node->right = NULL;
	node->value = value;
	node->cnt = 1;
	return node;
}

void travers(TreeNode* x, FILE* output) 
{
	if (x != NULL)
	{
		travers(x->left, output);
		for (int i = 0;i<x->cnt;i++)
			fwrite(&x->value, sizeof(int), 1, output);
		travers(x->right, output);
	}
}

TreeNode* insert(TreeNode* x, int value)
{
	if (x == NULL)
		return createNode(value);
	else if (value < x->value)
		x->left = insert(x->left, value);
	else if (value > x->value)
		x->right = insert(x->right, value);
	else if (value == x->value)
		x->cnt++;

	return x;
}


void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int myRand()
{
	return rand() % (500000 - 0 + 1);
}

void randomize(int* arr,int N)
{
	for (int i = 1; i < N; i++)
	{
		int pos = myRand() % i;
		swap(&arr[i], &arr[pos]);
	}
}

int main()
{
	FILE* input = fopen("input.bin", "rb");
	int size;
	fread(&size, sizeof(int), 1, input);
	
	TreeNode* root = NULL;

	int* arr = (int*)malloc(sizeof(int) * size);
	fread(arr, sizeof(int), size, input);

	randomize(arr, size);

	for (int i = 0; i < size; i++)
	{
		int value = arr[i];
		root = insert(root, value);
	}
	FILE* output = fopen("output.bin", "wb");
	travers(root, output);

	return 0;
}