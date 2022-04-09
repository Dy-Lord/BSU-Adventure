#include<stdlib.h> 
#include<stdio.h>
#include<iostream>
#include <ctime>
#include<chrono>
#include <fstream>
#include <string>
#include<windows.h>
#include <algorithm>
#include"Header1.h"
#pragma warning(disable:4996)

using namespace std;

void InputGenSort(void)
{
	setlocale(LC_ALL, "ru");
	int length;
	ofstream input;
	input.open("C:\\Users\\User01\\Desktop\\Labs\\LabsOne\\SORT\\input.txt");
	cout << "������� ����������� �������: " << endl;

	cin >> length;

	if (length < 1)
	{
		cout << "������---������������ ������ �������!" << endl;
		return;
	}

	int* arr = new int[double(length) + 1];

	cout << "������� �������� �������: " << endl;


	for (int i = 0; i < length; i++)
	{
		cin >> arr[i];
		input << arr[i] << " ";
	}

	input.close();

	SORTTIME(length);

	
	delete[] arr;
}

void RandGenSort(void)
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	int a, b, length, w;
	ofstream input;

	input.open("C:\\Users\\User01\\Desktop\\Labs\\LabsOne\\SORT\\input.txt");
	cout << "������� ����������� �������: " << endl;

	cin >> length;

	if (length < 1)
	{
		cout << "������---������������ ������ �������!" << endl;
		return;
	}


	int* arr = new int[double(length) + 1];

	cout << "�������� ���������� �������:"<<endl<<"������� �� �����������---(1)"<<endl<<"������� �� ��������---(2)"<<endl<<"���������� �������---(3)"<<endl;

	cin >> w;

	switch (w)
	{
	case 1:
	{
		for (int i = 0; i < length; i++)
		{
			arr[i] = i + 1;
			input << arr[i] << " ";
		}
		input.close();
		break;
	}
	case 2:
	{
		for (int i = 0; i < length; i++)
		{
			arr[i] = length - i;
			input << arr[i] << " ";
		}
		input.close();
		break;
	}
	case 3:
	{
		cout << "������� ���������� ��������� ����� [a,b]"<<endl;
		cin >> a >> b;
		if (a > b)
		{
			cout << "������---������������ ����������!" << endl;
			return;
		}
		for (int i = 0; i < length; i++)
		{
			arr[i] = a + rand() % (b - a + 1);
			input << arr[i] << " ";
		}
		input.close();
		break;
	}
	default:
	{
		cout << "������---������������ ������� ���������� �������!";
		return;
	}
	}

	SORTTIME(length);
	

	delete[] arr;
}

void FileGenSort(void)
{
	setlocale(LC_ALL, "ru");
	int i = 0, length = 0, pos = 0, nach = 0, kon = 0;

	string str, slovo;
	ifstream input;

	input.open("C:\\Users\\User01\\Desktop\\Labs\\LabsOne\\SORT\\input.txt");

	if (input.is_open())
	{
		getline(input, str);
		while (str.find_first_of(' ', pos) != 0 && pos != -1)
		{
			pos = str.find_first_of(' ', double(pos) + 1);
			length += 1;
		}
		

		SORTTIME(length);
		
		
		input.close();
		

	}
	else
		cout << "������---�� ������� ������� ����!" << endl;
}