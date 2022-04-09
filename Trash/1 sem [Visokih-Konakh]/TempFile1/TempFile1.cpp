#pragma warning(disable:4996)
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<Windows.h>
#include<algorithm>

using namespace std;

bool prost(int n)
{
	if (n <= 1)
		return false;
	for (int i = 2; i <= n / 2; i++)
		if (n % i == 0)
			return false;
	return true;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* fout = fopen("out.txt", "w");
	FILE* fin = fopen("in.txt", "r");

	if (fin == NULL)
	{
		printf("ќшибка открыти€ входного файла\n");
		fprintf(fout, "%s", "ќшибка открыти€ входного файла\n");
		fclose(fout);
		return 0;
	}

	int kol = 0, val;

	fscanf(fin, "%d", &val);
	if (feof(fin))
	{
		printf("¬ходной файл не содержит чисел!\n");
		fprintf(fout, "%s", "¬ходной файл не содержит чисел!\n");
		fclose(fout);
		fclose(fin);
		return 0;
	}

	while (!feof(fin))
	{
		if (prost(val))
			kol++;
		fscanf(fin, "%d", &val);
	}

	if (kol == 0)
	{
		printf("¬ходной файл не содержит простых чисел!\n");
		fprintf(fout, "%s", "¬ходной файл не содержит простых чисел!\n");
		fclose(fout);
		fclose(fin);
		return 0;
	}

	fclose(fin);
	fopen("in.txt","r");


	int* a = new int[kol];
	int k = 0;
	fscanf(fin, "%d", &val);
	while (!feof(fin))
	{
		if (prost(val))
			a[k++] = val;
			fscanf(fin, "%d", &val);
	}

	for (int i = 0; i < kol; i++)
		for (int j = 0; j < kol - 1 - i; j++)
			if (a[j] > a[j + 1])
				swap(a[j], a[j + 1]);

	for (int i = 0; i < kol; i++)
		fprintf(fout, "%d ", a[i]);

	delete[] a;

	fclose(fin);
		fclose(fout);
	return 0;
}