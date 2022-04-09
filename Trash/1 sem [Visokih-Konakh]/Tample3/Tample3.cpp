#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE 
#pragma warning(disable : 4996)
#include<iostream>
#include<cstring>
#include<float.h>
#include<windows.h>
using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char str[301];
	cout << "Введите строку"<< endl;
	cin.getline(str, 301);
	int sum, ni, nd, vi;
	double max, vd;
	char* p;
	sum = 0;
	nd = 0;
	ni = 0;
	max = -DBL_MAX;
	p = strtok(str, " ");
	char* end;
	while (p != NULL)
	{
		vi = strtol(p, &end, 10);
		if (*end == '\0')
		{
			sum = sum + vi;
			ni++;
		}
		else
		{
			vd = strtod(p, &end);
			if (*end == '\0')
			{
				if (vd > max)
					max = vd;
				nd++;
			}
		}
		p = strtok(NULL, " ");
	}
	if (ni == 0)
		cout << "Целых чисел нет!" << endl;
	else
	{
		cout << "sum = " << sum << endl;
		cout << "ave = " << (double)sum / ni << endl;

	}
	if (ni == 0)
		cout << "Вещественных чисел нет" << endl;
	else
		cout << "max = " << max << endl;
	system("pause");
	return 0;
}