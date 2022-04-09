#include"Header.h"
#include<iostream>
#include<string>
#include<Windows.h>

using namespace std;

struct pamag
{
	PRAM pr;
	double S;
};

void SORTSHELL(pamag*& arr, int SIZE);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	PRAM first, second, third;
	double g,l;
	int w, p, aim = 1;
	cout << "������� ���������� ������ ������� ������� ��������������" << endl;
	cout << "X = ";
	cin >> g;
	first.SetX1(g);
	cout << "Y = ";
	cin >> g;
	first.SetY1(g);

	cout << "������� ���������� ����� ������ ������� ��������������" << endl;
	cout << "X = ";
	cin >> g;
	first.SetX2(g);
	cout << "Y = ";
	cin >> g;
	first.SetY2(g);

	while (aim)
	{
		
		cout << "(1) --- ������� ������� ��������������" << endl << "(2) --- ����������� ��������� ������������� ������������ ��� Ox" << endl << "(3) --- ����������� ��������� ������������� ������������ ��� Oy" << endl << "(4) --- �������� ���������� � ������ ������� ��������������" << endl << "(5) --- �������� ���������� � ����� ������� ��������������" << endl << "(6) --- �������� ���������� Y ������� ������� ��������������" << endl << "(7) --- �������� ���������� Y ������ ������� ��������������" << endl << "(8) --- ������� ���������� �������������� " << endl << "(9) --- ������� �������������" << endl << "(10) --- ���������� ����������� ��������������, ����������� ��� �������� ��������������" << endl << "(11) --- ����� � ������� �������������� ��������������� �� �������" << endl;
		cin >> w;
		system("cls");
		switch (w)
		{
		case 1: l = first.SSS(); cout << l << endl; break;
		case 2:
		{
			cout << "������� �������� ������" << endl;
			cin >> p;
			first.POX(p);
			cout << "�������� ��������� �������!" << endl;
			break;
		}
		case 3:
		{
			cout << "������� �������� ������" << endl;
			cin >> p;
			first.POY(p);
			cout << "�������� ��������� �������!" << endl;
			break;
		}
		case 4: 
		{
			cout << "������� ���������� �" << endl;
			cin >> g;
			first.SetX1(g);
			cout << "�������� ��������� �������!" << endl;
			break;
		}
		case 5:
		{
			cout << "������� ���������� �" << endl;
			cin >> g;
			first.SetX2(g);
			cout << "�������� ��������� �������!" << endl;
			break;
		}
		case 6: 
		{
			cout << "������� ���������� Y" << endl;
			cin >> g;
			first.SetY1(g);
			cout << "�������� ��������� �������!" << endl;
			break;
		}
		case 7: 
		{
			cout << "������� ���������� Y" << endl;
			cin >> g;
			first.SetY2(g);
			cout << "�������� ��������� �������!" << endl;
			break;
		}
		case 8: cout << endl; first.print(); cout << endl; break;
		case 9: cout << first << endl; break;
		case 10: 
		{
			cout << "������� ���������� ������� ��������������" << endl;
			cout << "������� ���������� ������ ������� ������� ��������������" << endl;
			cout << "X = ";
			cin >> g;
			second.SetX1(g);
			cout << "Y = ";
			cin >> g;
			second.SetY1(g);

			cout << "������� ���������� ����� ������ ������� ��������������" << endl;
			cout << "X = ";
			cin >> g;
			second.SetX2(g);
			cout << "Y = ";
			cin >> g;
			second.SetY2(g);

			third.BUILD(first, second);

			cout << "���������� ����������� ������������ ��������������:" << endl;
			cout << endl;
			third.print();
			cout << endl;
			cout << endl;
			break;
		}
		case 11: aim=0; break;
		default:
		{
			cout << "������ --- ������������ ����� ����!";
			break;
		}
		}
	}

	cout << endl;

	PRAM q(2, 2, 1, 1), b(5, 6, 3, 2), r(9, 7, 1, 1), y(-1, -1, -10, -10), o(43, 23, 12, 12);
	pamag* arrp=new pamag[5];

	arrp[0].pr = q;
	arrp[0].S = q.SSS();

	arrp[1].pr = b;
	arrp[1].S = b.SSS();

	arrp[2].pr = r;
	arrp[2].S = r.SSS();

	arrp[3].pr = y;
	arrp[3].S = y.SSS();

	arrp[4].pr = o;
	arrp[4].S = o.SSS();

	SORTSHELL(arrp, 5);

	for (int i = 0; i < 5; i++)
		cout << arrp[i].S << endl;

	delete[] arrp;
	system("pause");
	return 0;
}

void SORTSHELL(pamag*& arr, int SIZE)
{
	double fakt = 1.6473309;
	int len = SIZE / fakt;
	int stop = 0;
	if (SIZE == 1)
		return;

	while (true)
	{
		for (int i = 0; (i < SIZE) && (i + len < SIZE); i++)
			if (arr[i].S > arr[i + len].S)
				swap(arr[i], arr[i + len]);

		if (len != 1)
			len /= fakt;

		else
		{
			len = 0;
			stop = 1;
		}

		if (stop)
			break;
	}
}