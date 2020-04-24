#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


// ищет по какому шаблону кодируется символ. Работает с первым байтом
int whichMask(unsigned char firstByte)
{
	unsigned char mask1 = 127; // маска под однобайтовый шаблон
	unsigned char mask2 = 223; // маска под двубайтовый шаблон
	unsigned char mask3 = 239; // маска под трёхбайтовый шаблон
	unsigned char mask4 = 247; // маска под четырёхбайтовый шаблон

	// подставляю маску под байт, чтобы опредилить по какому шаблону закодирован байт
	// только для первого байта символа
	
	
	if ((mask1 & firstByte) == firstByte)
		return 1;

	if ((mask2 & firstByte) == firstByte)
		return 2;

	if ((mask3 & firstByte) == firstByte)
		return 3;

	if ((mask4 & firstByte) == firstByte)
		return 4;

	return 0; // если ни одна маска не подошла
}

int hardErrorHandler(unsigned char contByte, int readable)
{
	if (!readable) return 0; //если я читаю символ, а файл закончился

	unsigned char mask = 128;
	if ((mask | contByte) != contByte) return 0; // следующий байт не имеет формат 10xxxxxx

	if ((int)contByte < 128 || (int)contByte >= 192) return 0;

	return 1;
}

int softErrorHandler(unsigned int res)
{
	if (res > 1114111) return 0; // если символ не попадает в таблицу Unicode

	if (res >= 55296 && res <= 57343) return 0; // символ является суррогатом

	return 1;
}

int getAnsw(int type, FILE* input, FILE* output, unsigned int res)
{
	for (int i = 0; i < type-1; i++)
	{
		res = (res << 6);

		unsigned char contByte;
		int readable = 1;

		readable = fread(&contByte, sizeof(unsigned char), 1, input); // читаю второй байт символа. Проверяю могу ли это сделать

		if (!hardErrorHandler(contByte, readable)) 
			return 0; // если мы нашли жесткую ошибку, то завершаемся

		unsigned char mask2Cont = 63; // шаблон для байта продолжения

		unsigned int res2 = (unsigned int)(contByte & mask2Cont); // вырезаю число

		res = res | res2; // добавляю в res

	}

	if (type == 2 && res < 128 || type == 3 && res < 2048 || type == 4 && res < 65536) //проверка на overload encoding
	{
		unsigned int e = 65533;
		fwrite(&e, sizeof(unsigned int), 1, output);
		return 1;
	}

	if (!softErrorHandler(res)) // если нашли мягкую ошибку
	{
		unsigned int e = 65533;
		fwrite(&e, sizeof(unsigned int), 1, output);
		return 1;
	}

	fwrite(&res, sizeof(unsigned int), 1, output);

	return 1; // если удалось успешно считать число
}

int main()
{
	FILE* input = fopen("input.bin", "rb");	
	FILE* output = fopen("output.bin", "wb");

	while (1)
	{
		unsigned char firstByte;
		int smblExists = fread(&firstByte, sizeof(unsigned char), 1, input); // читаю первый байт символа
		if (!smblExists) return 0;
		if ((int)firstByte <128 && (int)firstByte >= 192) return 0;

		int type = whichMask(firstByte);

		if (type == 1) // символ однобайтовый
		{
			unsigned int res = (int)firstByte; // Получаю код символа

			fwrite(&res, sizeof(unsigned int), 1, output);
			continue;
		}
			
		if (type == 2) // символ двухбайтовый
		{
			unsigned char mask2 = 31;
			unsigned int res = (unsigned int)(firstByte & mask2); // маской вырезаю от 2чной записи само число. Получаю его код

			int flag = getAnsw(type, input, output, res);

			if (!flag) return 0;
		}

		if (type == 3) 
		{
			unsigned char mask2 = 15;
			unsigned int res = (unsigned int)(firstByte & mask2); // маской вырезаю от 2чной записи само число. Получаю его код

			int flag = getAnsw(type, input, output, res);

			if (!flag) return 0;
		}


		if (type == 4)
		{
			unsigned char mask2 = 7;
			unsigned int res = (unsigned int)(firstByte & mask2); // маской вырезаю от 2чной записи само число. Получаю его код

			int flag = getAnsw(type, input, output, res);

			if (!flag) return 0;
		}

		if (type == 0) // в байте встретилось 5 или больше старших битов
		{
			return 0;
		}
	}
	return 0;
}