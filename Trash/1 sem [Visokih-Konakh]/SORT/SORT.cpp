#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<windows.h>
#include<ctime>
#include<chrono>
#include<algorithm>
#include"Header1.h"

using namespace std;
using namespace std::chrono;

extern unsigned long long swotch = 0, sravn = 0;

	int main()
	{
		setlocale(LC_ALL, "ru");
		int w;
		cout << "�������� ������ ���������� �������:" << endl << "� ������� ����������---(1)" << endl << "�������������� ��������---(2)" << endl << "��������� ������ �� �����---(3)" << endl;
		cin >> w;
		switch (w)
		{
		case 1: {InputGenSort(); break; }
		case 2: {RandGenSort(); break; }
		case 3: {FileGenSort(); break; }
		default: 
		{
			cout << "������---������������ ������ ���������� �������!" << endl;
			system("pause");
			return 0;
		}
		}
		system("pause");
		return 0;
	}
