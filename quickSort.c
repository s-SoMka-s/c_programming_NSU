#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void quickSort(int* mas, int size)
{
	//Указатели в начало и в конец массива
	int i = 0;
	int j = size - 1;

	//Центральный элемент массива
	int mid = mas[size / 2];

	//Делим массив
	do {
		//Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
		//В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
		while (mas[i] < mid) {
			i++;
		}
		//В правой части пропускаем элементы, которые больше центрального
		while (mas[j] > mid) {
			j--;
		}

		//Меняем элементы местами
		if (i <= j) {
			int tmp = mas[i];
			mas[i] = mas[j];
			mas[j] = tmp;

			i++;
			j--;
		}
	} while (i <= j);


	//Рекурсивные вызовы, если осталось, что сортировать
	if (j > 0) {
		//"Левый кусок"
		quickSort(mas, j + 1);
	}
	if (i < size) {
		//"Првый кусок"
		quickSort(&mas[i], size - i);
	}
}

int main()
{

	FILE* input = fopen("input.bin", "rb");

	int N;

	fread(&N, sizeof(int), 1, input);
	//scanf("%d", &N);
	int* arr = (int*)malloc(sizeof(int) * N);

	fread(arr, sizeof(int), N, input);

	//for (int i = 0; i < N; i++)
	//	scanf("%d", &arr[i]);

	quickSort(arr, N);

	FILE* output = fopen("output.bin", "wb");
	fwrite(arr, sizeof(int), N, output);

	//for (int i = 0; i < N; i++)
	//	printf("%d", arr[i]);


	free(arr);
	return 0;
}