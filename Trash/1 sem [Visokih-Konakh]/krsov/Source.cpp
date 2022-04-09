#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
#include<stdio.h>

using namespace std;

int nut(const string& str)
{
	char* end_ptr;
	int dd;

	char* s2 = new char[str.length() + 1];
	strcpy(s2, str.c_str());
	
	dd = strtol(s2, &end_ptr, 10);

	if (*end_ptr != 0)
	{
		delete[] s2;
		return false;
	}

	if (dd < 1)
	{
		delete[] s2;
		return false;
	}

	delete[] s2;
	return dd;
}


int sov(const string& str)
{
	char* end_ptr;
	int dd;
	int S = 0;

	char* s2 = new char[str.length() + 1];
	strcpy(s2, str.c_str());

	dd = strtol(s2, &end_ptr, 10);

	if (dd <= 1)
		return false;

	if (*end_ptr == 0)
	{
		for (int i = 1; i <= dd / 2; i++)
			if (dd % i == 0)
				S += i;
	}
	else
		return false;

	if (dd == S)
		return dd;
	else
		return false;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream input("input.txt", ios::in);
	ofstream output("output.txt", ios::out);

	if (!input)
	{
		cout << "Ошибка---входной файл не найден!" << endl;
		output << "Ошибка---входной файл не найден!";
		output.close();
		return 0;
	}

	string str;
	string sub;
	string temp1;
	int poz1 = 0;
	int subpoz1 = 0;
	int len1, count = 0;

	string MAXSTR, MINSTR;
	int num;
	int MAX, MIN;
	int MAXLEN, MINLEN;
	int MAXPOZ, MINPOZ;

	bool aim = 0;

	if (input.eof())
	{
		output << "Ошибка---входной файл пустой!";
		input.close();
		output.close();
		return 0;
	}

	getline(input, sub);

	if (sub == "")
	{
		output << "Ошибка---Не определены разделители между словами!";
		input.close();
		output.close();
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
				{
					if (nut(temp1))
					{
						count++;
						if (aim)
							output << ',';
						output << temp1;
						aim = true;
					}
				}

				if (i == 1)
				{
					if(nut(temp1))
					if (sov(temp1))
						output << temp1 << "->" << "SOVERSHENNOE" << endl;
					else
						output << temp1 << "->" << "NENESOVERSHENNOE" << endl;
				}
				poz1 = subpoz1;
			}
			poz1 = 0;
		}
		input.close();
		input.open("input.txt", ios::in);
		output << endl;
	}

	if (count == 0)
	{
		output.close();
		output.open("output.txt", ios::out);
		output << "Во входном файле нет натуральных чисел!";
	}

	input.close();
	output.close();
	return 0;
}
