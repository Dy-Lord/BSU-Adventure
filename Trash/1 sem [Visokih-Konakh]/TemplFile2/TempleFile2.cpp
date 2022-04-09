#pragma warning(disable:4996)
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<Windows.h>
#include<algorithm>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* fout = fopen("out.txt", "w");
	FILE* fin = fopen("in.txt", "r");

	if (fin == NULL)
	{
		printf("Ошибка открытия входного файла\n");
		fprintf(fout, "%s", "Ошибка открытия входного файла\n");
		fclose(fout);
		return 0;
	}

	int a[10][10];
	int res = 0, r;
	fscanf(fin, "%d", &r);

	if(feof(fin))
	{
		printf("Входной файл не содержит чисел!\n");
		fprintf(fout, "%s", "Входной файл не содержит чисел!\n");
		fclose(fout);
		fclose(fin);
		return 0;
	}

	if (r < 1 || r>10)
	{
		printf("Неверный размер матрицы!\n");
		fprintf(fout, "%s", "Неверный размер матрицы!\n");
		fclose(fout);
		fclose(fin);
		return 0;
	}

	for (int i = 0; i < r; i++)
		for (int j = 0; j < r; j++)
		{
			fscanf(fin, "%d", &a[i][j]);
			if (feof(fin))
			{
				printf("Недостаточно чисел в матрице!\n");
				fprintf(fout, "%s", "Недостаточно чисел в матрице!\n");
				fclose(fout);
				fclose(fin);
				return 0;
			}
		}
	for (int i = 0; i < r; i++)
		for (int j = r - 1 - i; j >= 0; j--)
			if (a[i][j] > 0)
				res++;
	
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r - i; j++)
		{
				fprintf(fout, "%10d", a[i][j]);
		}
		fprintf(fout, "\n");
	}

	fprintf(fout, "%d\n", res);
	fclose(fout);
	fclose(fin);
	return 0;

}