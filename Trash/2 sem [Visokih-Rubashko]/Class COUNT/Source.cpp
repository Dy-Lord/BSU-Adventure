#include<iostream>
#include<Windows.h>
#include"COUNT.h"
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try
	{
		while (true)
		{
			int task;
			cout << "�������� ����� �������:" << endl << "(1) --- ����������� ��� ����������" << endl << "(2) --- �����" << endl << "(3) --- �����" << endl;
			cin >> task;
			system("cls");

			switch (task)
			{
			case 1:
			{
				int w;
				COUNT test;
				while (true)
				{
					cout << "(1)---�������� ������� � ���������" << endl << "(2)---������� �������� ��������� �� �����" << endl << "(3)---������� ��������� � ���������" << endl << "(4)---�����" << endl;
					cin >> w;
					system("cls");
					switch (w)
					{
					case 1:
					{
						cout << "������� ������� ���������:" << endl;
						int in;
						cin >> in;
						test.ADDelem(in);
						break;
					}
					case 2: cout << test << endl; break;
					case 3:
					{
						cout << "������� ������� ���������:" << endl;
						int in;
						cin >> in;
						bool aim;
						aim = test.ELinclude(in);

						if (!aim)
							cout << "������� �����������!" << endl;
						else
							cout << "������� ������!" << endl;
						break;
					}
					case 4: return 0; break;
					default:
						cout << "������---������������ ����� ����!" << endl;
						cout << endl;
						break;
					}
				}
				break;
			}
			case 2:
			{

				COUNT one, two, tree, five, six;
				cout << six << endl;

				one.ADDelem(0);
				one.ADDelem(12);
				one.ADDelem(55);
				one.ADDelem(1923);
				one.ADDelem(23567);
				one.ADDelem(65535);
				one.ADDelem(65535);

				five.ADDelem(55);
				five.ADDelem(1923);

				two.ADDelem(12);
				two.ADDelem(55);
				two.ADDelem(1923);
				two.ADDelem(0);
				two.ADDelem(88);

				cout << "������� one" << endl;
				cout << one << endl;

				cout << "������� two" << endl;
				cout << two << endl;

				cout << "�������������� ��������" << endl;
				cout << (five < one) << endl;
				cout << (five > one) << endl;

				cout << "tree=one" << endl;
				tree = one;
				tree.Print();

				cout << "�������� ���������" << endl;
				cout << (two == one) << endl;
				cout << (tree == one) << endl;

				cout << "�������� one - two" << endl;
				tree = one - two;
				tree.Print();



				cout << "�������� two - one" << endl;
				tree = two - one;
				tree.Print();

				COUNT four;
				cout << "����������� �������� one & two" << endl;
				four = one & two;
				cout << four;

				cout << "����������� �������� one | two" << endl;
				four = one | two;
				cout << four;


				cout << "�������������� ����� ���������" << endl;
				cout << two.ELinclude(88) << endl;
				cout << two.ELinclude(101) << endl;


				break;
			}
			case 3:
			{
				system("pause");
				return 0;
				break;
			}
			default:
				cout << "������---������������ ����� ����!" << endl;
				cout << endl;
				break;
			}
		}
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	system("pause");
	return 0;
}
