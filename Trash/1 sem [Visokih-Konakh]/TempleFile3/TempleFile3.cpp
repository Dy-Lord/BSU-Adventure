#pragma warning(disable:4996)
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<Windows.h>
#include<algorithm>
#include<cmath>

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

	char d[257], s1[256];

	if (fgets(d, 256, fin) == NULL)
	{
		printf("Входной файл пуст!\n");
		fprintf(fout, "%s", "Входной файл пуст!\n");
		fclose(fin);
		fclose(fout);
		return 0;
	}

	d[strlen(d) - 1] = 0;
	if (d[0] == 0)
	{
		printf("Не определены разделители между словами!\n");
		fprintf(fout, "%s", "Не определены разделители между словами!\n");
		fclose(fin);
		fclose(fout);
		return 0;
	}

	if (fgets(s1, 256, fin) == NULL)
	{
		printf("Входной файл содержит только одну строку!\n");
		fprintf(fout, "%s", "Входной файл содержит только одну строку!\n");
		fclose(fin);
		fclose(fout);
		return 0;
	}

	char* p;
	double a[1000],dd;
	int n = 0;
	char* end_ptr;

	do
	{
		s1[strlen(s1)] = 0;
		if (strlen(s1) == 0) continue;
		p = strtok(s1, d);
		while (p != 0)
		{
			dd = strtod(p, &end_ptr);
			if (*end_ptr == '\0')
				if(int(dd)!=dd)
				a[n++] = dd;
			p = strtok(0, d);
		}
	} while (fgets(s1, 256, fin) != NULL);

	if (n == 0)
	{
		printf("В тексте нет ни одного вещественного числа!\n");
		fprintf(fout, "%s", "В тексте нет ни одного вещественного числа!\n");
		fclose(fin);
		fclose(fout);
		return 0;
	}
	else
	{
		for (int i = 0; i < n; i++)
			fprintf(fout, "%f ", a[i]);
		fprintf(fout, "\n");

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n - 1 - i; j++)
				if (fabs(a[j]) > fabs(a[j + 1]))
					swap(a[j], a[j + 1]);

		for (int i = 0; i < n; i++)
			fprintf(fout, "%f ", a[i]);
	}

	fclose(fin);
	fclose(fout);
	return 0;
}