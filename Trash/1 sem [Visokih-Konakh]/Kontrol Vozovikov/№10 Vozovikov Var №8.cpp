#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
#include<windows.h>
#include<cmath>
using namespace std;

int nut(const string& str)
{
	char* end_ptr;
	int dd;

	char* s = new char[str.length() + 1];
	strcpy(s, str.c_str());

	dd = strtol(s, &end_ptr, 10);

	if (*end_ptr != 0)
	{
		delete[] s;
		return false;
	}

	if (dd < 1)
	{
		delete[] s;
		return false;
	}

	delete[] s;
	return dd;
}

int armnut(const string& str)
{
	char* end_ptr;
	int dd, temp;
	int SUM = 0, count = 0;

	char* s = new char[str.length() + 1];
	strcpy(s, str.c_str());

	dd = strtol(s, &end_ptr, 10);
	temp = dd;
	if (*end_ptr != 0)
	{
		delete[] s;
		return false;
	}

	while (temp)
	{
		count++;
		temp /= 10;
	}
	
	temp = dd;

	while (temp)
	{
		SUM += pow((temp % 10), count);
		temp /= 10;
	}

	if (dd == SUM)
	{
		delete[] s;
		return true;
	}
	else
	{
		delete[] s;
		return false;
	}

}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream input("IN8.txt", ios::in);
	ofstream output("OUT8.txt", ios::out);

	if (!input)
	{
		cout << "ОШИБКА--Отсутствует входной файл" << endl;
		output << "ОШИБКА--Отсутствует входной файл";
		output.close();
		system("pause");
		return 0;
	}

	string str, sub, temp1;
	int poz1 = 0, subpoz1 = 0;
	int len1, count = 0, pust = 0;
	bool aim = false;

	if (input.peek() == EOF)
	{
		cout << "ОШИБКА--Входной файл пустой!" << endl;
		output << "ОШИБКА--Входной файл пустой!";
		input.close();
		output.close();
		system("pause");
		return 0;
	}

	getline(input, sub);

	if (sub == "")
	{
		cout << "ОШИБКА---Во входном файле не определены разделители!" << endl;
		output << "ОШИБКА--Во входном файле не определены разделители!";
		input.close();
	    output.close();
		system("pause");
		return 0;
	}

	for (int i = 0; i < 2; i++)
	{

		while (getline(input, str))
		{
			if (str == "") continue;

			str += ' ';

			while ((poz1 = str.find_first_not_of(sub, poz1)) != string::npos)
			{
				subpoz1 = str.find_first_of(sub, poz1);
				len1 = subpoz1 - poz1;
				temp1 = str.substr(poz1, len1);

				if (i == 0)
					if(nut(temp1))
				{
						count++;
					if (aim)
						output << ';';
					aim = true;
					output << temp1;
				}

				if (i == 1)
				{
					if (nut(temp1))
					{
						if (armnut(temp1))
							output << temp1 << ' ' << "->" << ' ' << "ДА" << endl;
						else
							output << temp1 << ' ' << "->" << ' ' << "НЕТ" << endl;
					}
					
				}
				poz1 = subpoz1;
			}
			poz1 = 0;
		}
		input.close();
		input.open("IN8.txt", ios::in);
		output << endl;
	}

	if (!count)
	{
		output.close();
		output.open("OUT8.txt", ios::out);
		cout << "Во входных строках  отсутствуют натуральные числа!" << endl;
		output<< "Во входных строках отсутствуют натуральные числа!";
		input.close();
		output.close();
		system("pause");
		return 0;
	}

	input.close();
	output.close();
	cout << "Задача выполнена!" << endl;
	system("pause");
	return 0;
}