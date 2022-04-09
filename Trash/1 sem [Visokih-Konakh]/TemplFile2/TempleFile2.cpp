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
		printf("������ �������� �������� �����\n");
		fprintf(fout, "%s", "������ �������� �������� �����\n");
		fclose(fout);
		return 0;
	}

	int a[10][10];
	int res = 0, r;
	fscanf(fin, "%d", &r);

	if(feof(fin))
	{
		printf("������� ���� �� �������� �����!\n");
		fprintf(fout, "%s", "������� ���� �� �������� �����!\n");
		fclose(fout);
		fclose(fin);
		return 0;
	}

	if (r < 1 || r>10)
	{
		printf("�������� ������ �������!\n");
		fprintf(fout, "%s", "�������� ������ �������!\n");
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
				printf("������������ ����� � �������!\n");
				fprintf(fout, "%s", "������������ ����� � �������!\n");
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