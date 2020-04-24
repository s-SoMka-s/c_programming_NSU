#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Vector_s {
	int* arr;
	int size;
	int indx;
}Vector;

typedef struct Vertex_s {
	int incommingEdgesCnt;
}Vertex;

void push_back(Vector* vec, int value)
{
	if (!vec->size)
		vec->arr = (int*)malloc(sizeof(int));
	else
		vec->arr = (int*)realloc(vec->arr, sizeof(int) * (vec->size + 1));

	vec->arr[vec->size] = value;
	vec->size++;
}

int remove(Vector* vec)
{
	//for (int i = 0; i < vec->size; i++)
	//	printf("%d ", vec->arr[i]);

	int val = vec->arr[vec->indx];
	vec->indx++;
	//vec->arr = (int*)realloc(vec->arr, sizeof(int) * (vec->size - 1));
	//vec->size--;

	return val;
}

void toposort(Vertex* v_list, int start, Vector* answ, Vector* S, int nodesCnt, int** matrix)
{
	int* used = (int*)calloc(nodesCnt,sizeof(int));
	for (int i = 0;i<nodesCnt;i++)
	{
		
		if (used[i]==0 && v_list[i].incommingEdgesCnt == 0) {
			int n = i;
			used[i] = 1;
			push_back(answ, n);

			for (int to = 0; to < nodesCnt; to++)
			{
				if (matrix[n][to] == 1) {
					if (v_list[to].incommingEdgesCnt > 0)
					{
						matrix[n][to] = 0;
						v_list[to].incommingEdgesCnt--;
					}
				}
			}
			i = -1;
		}
		
	}

	for (int i = 0; i < nodesCnt; i++)
	{
		if (v_list[i].incommingEdgesCnt != 0)
		{
			printf("bad course");
			exit(0);
		}
	}

	
}

int main()
{

	freopen("input.txt", "r", stdin);

	int nodes, links;
	scanf("%d %d", &nodes, &links);

	Vertex* v_list = (Vertex*)malloc(sizeof(Vertex) * nodes);

	for (int i = 0; i < nodes; i++)
	{
		v_list[i].incommingEdgesCnt = 0;
	}

	int** matrix = (int**)malloc(sizeof(int*) * nodes);
	for (int i = 0; i < nodes; i++)
		matrix[i] = (int*)calloc(nodes, sizeof(int));

	for (int i = 0; i < links; i++)
	{
		int from, to;
		scanf("%d %d", &from, &to);
		from--;
		to--;

		if (matrix[from][to] == 0)
		{
			matrix[from][to] = 1;
			v_list[to].incommingEdgesCnt++;
		}
	}

	Vector* answ = (Vector*)malloc(sizeof(Vector));
	answ->size = 0;

	Vector* S = (Vector*)malloc(sizeof(Vector));
	S->size = 0;
	S->indx = 0;

	for (int i = 0;i<nodes;i++)
		if (v_list[i].incommingEdgesCnt == 0)
			push_back(S, i);


	toposort(v_list, S->arr[0], answ, S, nodes, matrix);

	for (int i = 0; i < answ->size; i++)
	{
		printf("%d ", (answ->arr[i] + 1));
	}

	for (int i = 0; i < nodes; i++)
		free(matrix[i]);

	free(matrix);
	free(v_list);
	free(S);
	free(answ);
	return 0;
}