#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE 
#pragma warning (disable :4996)
#include <iostream>
#include <cstring>
#include <Windows.h>
using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const int MaxLength = 300;
	char str[MaxLength + 1];
	cout << "Введите строку символов\n";
	cin.get(str, MaxLength + 1);
	int len = strlen(str);
	char** mas_str = new char* [len + 1];
	char* str_copy = new char[len + 1];
	strcpy(str_copy, str);
	char* p;
	int k = 0;
	p = strtok(str, ".,?!:;() ");
	while (p != NULL)
	{
		mas_str[k++] = p;
		p = strtok(NULL, ".,?!:;() ");

	}
	cout << "По словам" << endl;
	for (int i = 0; i < k; i++)
		cout << mas_str[i] << endl;
	cout << endl;

	if (k > 0)
	{
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < k - i - 1; j++)
				if (strcmp(mas_str[j], mas_str[j + 1]) > 0)
				{
					p = mas_str[j];
					mas_str[j] = mas_str[j + 1];
					mas_str[j + 1] = p;

				}
		}
		cout << "По алфавиту" << endl;
		for (int i = 0; i < k; i++)
			cout << mas_str[i] << endl;
		cout << endl;

		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < k - i - 1; j++)
				if (strlen(mas_str[j]) > strlen(mas_str[j + 1]))
				{
					p = mas_str[j];
					mas_str[j] = mas_str[j + 1];
					mas_str[j + 1] = p;

				}

		}
		cout << "Слова по длине" << endl;
		for (int i = 0; i < k; i++)
			cout << mas_str[i] << endl;
		cout << endl;
	}
	else
		cout << "В строке нет слов" << endl;

	system("pause");
	return 0;
}