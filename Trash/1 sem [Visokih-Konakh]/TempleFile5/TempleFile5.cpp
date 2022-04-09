#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE 
#pragma warning(disable : 4996)
#include<string>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<Windows.h>
#include<algorithm>
#include<cmath>

using namespace std;

bool find(char* p)
{
	int count = 0;
	string str = p;
	string arr = "0123456789";
	int len = str.length();

	for (int i = 0; i < len; i++)
		for (int j = 0; j < 10; j++)
			if (str[i] == arr[j])
				count++;

	if (count == len)
		return true;
	else
		return false;
}

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
	double a[1000], dd;
	int n = 0;
	char* end_ptr;
	string str, del;
	str = s1;
	int len = 0;

	do
	{
		s1[strlen(s1)] = 0;
		if (strlen(s1) == 0) continue;
		p = strtok(s1, d);
		while (p != 0)
		{
			dd = strtol(p, &end_ptr,10);
			if ((dd != 0) && (find(p)))
			{
				del = p;
				str.erase(str.find(del, len), del.length());
				len++;
			}
			else
			{
				string tmp = p;
				len += tmp.length()+1;
			}
			p = strtok(NULL, d);
		}
	} while (fgets(s1, 256, fin) != NULL);

	char* s2 = new char[str.length() + 1];
	strcpy(s2, str.c_str());

	fputs(s2, fout);

	delete[] s2;
	fclose(fin);
	fclose(fout);
	return 0;
}