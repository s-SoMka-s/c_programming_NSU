#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node_s {
	char** data;
	int size;
}Node;

Node* arr[1 * 1000 * 1000 + 1];


int main()
{
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		int key;
		char* str = calloc(8, sizeof(char));

		scanf("%d %s", &key, str);

		if (!arr[key])
		{
			arr[key] = malloc(sizeof(Node));

			arr[key]->size = 0;
			arr[key]->data =(char**) malloc(sizeof(char*));

			arr[key]->data[arr[key]->size] = str;
			arr[key]->size++;
		}
		else
		{
			arr[key]->data = (char**)realloc(arr[key]->data, sizeof(char*)*(arr[key]->size + 1));
			arr[key]->data[arr[key]->size] = str;
			arr[key]->size++;
		}
	}

	for (int i = 0; i < (1 * 1000 * 1000 + 1); i++)
	{
		if (!arr[i]) continue;

		for (int j = 0; j < arr[i]->size; j++)
		{
			printf("%d %s\n", i, arr[i]->data[j]);
			free(arr[i]->data[j]);
		}
		free(arr[i]);
	}
	return 0;
}