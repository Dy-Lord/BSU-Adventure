#pragma warning(disable:4996)
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<Windows.h>
#include<algorithm>
#include<cmath>

using namespace std;

int sunnum(int x)
{
	int S = 0;
	while (x != 0)
	{
		S += x % 10;
		x /= 10;
	}
	return S;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* fout = fopen("out.txt", "w");
	FILE* fin = fopen("in.txt", "r");
	int MAX = 0, arr[1000], l = 0, count = 2, MAXPOZ = 0;
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
	int a[1000], dd;
	int n = 0;
	char* end_ptr;

	do
	{
		s1[strlen(s1)] = 0;
		if (strlen(s1) == 0) continue;
		p = strtok(s1, d);
		while (p != 0)
		{
			dd = strtol(p, &end_ptr, 10);
			if (*end_ptr == '\0')
					a[n++] = dd;
			p = strtok(0, d);
		}
	} while (fgets(s1, 256, fin) != NULL);

	if (n == 0)
	{
		printf("В тексте нет ни одного целого числа!\n");
		fprintf(fout, "%s", "В тексте нет ни одного целого числа!\n");
		fclose(fin);
		fclose(fout);
		return 0;
	}
	else
	{
		for (int i = 0; i < n; i++)
			fprintf(fout, "%d ", a[i]);
		fprintf(fout, "\n");

		for (int i = 0; i < n; i++)
			fprintf(fout, "%d ", sunnum(a[i]));
		fprintf(fout, "\n");

		MAX = sunnum(a[0]);
		MAXPOZ = a[0];
		arr[l] = MAX;
		arr[++l] = a[0];

		for (int i = 1; i < n; i++)
			if (sunnum(a[i]) > MAX)
			{
				MAX = sunnum(a[i]);
				l = 0;
				count = 2;
				MAXPOZ = a[i];
				arr[l] = MAX;
				arr[l + 1] = MAXPOZ;
			}
		else
		{
				if (sunnum(a[i]) == MAX)
				{
					arr[++l] = MAX;
					MAXPOZ = a[i];
					arr[++l] = MAXPOZ;
					count+=2;
				}
		}

		if (count == 2)
		{
			fprintf(fout, "%d ", MAXPOZ);
			fprintf(fout, "%d ", MAX);
		}
		else
		{
			for (l = 0; l < count; l+=2)
			{
				fprintf(fout, "%d ", arr[l+1]);
				fprintf(fout, "%d ", arr[l]);
				fprintf(fout, "\n");
			}
		}
	}

	fclose(fin);
	fclose(fout);
	return 0;
}