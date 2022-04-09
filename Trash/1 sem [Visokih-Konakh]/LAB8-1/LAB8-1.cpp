#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE 
#pragma warning(disable : 4996)
#include<iostream>
#include<cstring>
#include<windows.h>
using namespace std;

char* _strstr(const char* string, const char* string2)
{
	int i = 0, j = 0, temp = -1, COUNT = 0, z, k;

	int len2 = strlen(string2);
	int len1 = strlen(string);
	
	char* string2_ptr = new char[len1 + 1];
	char* string_ptr = new char[len2 + 1];

	strcpy(string2_ptr, string2);
	strcpy(string_ptr, string);
	
	for (int i = 0; i < len1; i++)
	{
		if (temp == -1)

			for (int j = 0; j < len2; j++)
				if (temp == -1)
					if (string2_ptr[j] == string_ptr[i])
					{
						temp = i;

						for (int k = 0, z = 0; k < len2; k++, z++)
							if (string2_ptr[k] == string_ptr[temp + z])
								continue;
							else
								temp = -1;
					}
					else
						break;
				else break;

		else break;
	}
	if (temp != -1)	
		return &string_ptr[temp];
	else
		return 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const int size = 300;
	char str[size + 1];
	char SUBstr[size + 1];
	char* p;
	cout << "Введите первую строку" << endl;
	cin.getline(str, size + 1);
	cout << "Введите вторую строку" << endl;
	cin.getline(SUBstr, size + 1);

	char* one = strtok(str, " ");
	char* oneone = strtok(SUBstr, " ");

	if ((one == 0) || (oneone == 0))
	{
		cout << "Строка пустая!" << endl;
		system("pause");
		return 0;
	}

	cout << "Результат библиотечной функции" << endl;
	p = strstr(str, SUBstr);
	if (p == NULL)
		cout << "В строке нет подстроки!" << endl;
	else
		cout << p << endl;

	p = _strstr(str, SUBstr);
	cout << "Результат реализованной функции" << endl;
	if (p == NULL)
		cout << "В строке нет подстроки!" << endl;
	else
	cout << p << endl;
	system("pause");
	return 0;
}