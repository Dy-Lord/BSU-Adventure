#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>
#include <cstring>
#include <Windows.h>
#include "Student.h"

using namespace std;

void studsearch(Person** arrp, int group, int cource, int num1)
{
	bool aim = false;
	int tempgroup, tempcource;

	for (int i = 0; i <= num1; i++)
	{
		if (typeid (*arrp[i]) == typeid(Student))
		{
			Student* S = dynamic_cast<Student*>(arrp[i]);
			tempgroup = S->GetGroup();
			tempcource = S->GetCourse();

			if (tempgroup == group && cource == tempcource)
			{
				cout << *arrp[i] << endl;
				aim = true;
			}
		}
	}

	if (aim == false)
		cout << "������ �� �������!" << endl;
	
}

void teachsearch(Person** arrp, const char* kaf, int num1)
{
	char* tempkaf = new char[200];
	bool aim = false;

	for (int i = 0; i <= num1; i++)
	{
		if (typeid (*arrp[i]) == typeid(Teacher))
		{
			Teacher* S = dynamic_cast<Teacher*>(arrp[i]);
			S->GetDepart(tempkaf);
			if (strcmp(kaf, tempkaf) == 0)
			{
				cout << *arrp[i] << endl;
				aim = true;
			}
		}
	}

	if (aim == false)
		cout << "������ �� �������!" << endl;
	
	delete[] tempkaf;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int w;
	bool aim = false;
	int group, cource;
	int num1 = -1;

	Person* arrp[200];

	while (true)
	{
			while (true)
			{
				cout << "(1)---�������� ��������" << endl << "(2)---�������� �������������" << endl << "(3)---������� ������ ���������" << endl << "(4)---������� ������ ��������������" << endl << "(5)---����� ��������� �� ������ � �����" << endl << "(6)---����� �������������� �� �������" << endl << "(7)---�����" << endl;
				cin >> w;
				system("cls");
				switch (w)
				{
				case 1:
				{
					cout << "������� ��� ��������:" << endl;
					char* info = new char[200];
					scanf("%s", info);

					cout << "������� ���� ��������:" << endl;
					cin >> cource;
					cout << "������� ������ ��������:" << endl;
					cin >> group;
					
					arrp[++num1] = new Student(info, cource, group);

					delete[] info;
					break;
				}
				case 2: 
				{
					cout << "������� ��� �������������:" << endl;
					char* info = new char[200];
					scanf("%s", info);

					cout << "������� ������� �������������:" << endl;
					char* info1 = new char[200];
					scanf("%s", info1);

					arrp[++num1] = new Teacher(info, info1);
					
					delete[] info;
					delete[] info1;
					break;
				}
				case 3:
				{
					for (int i = 0; i <= num1; i++)
					{
						if (typeid (*arrp[i]) == typeid(Student))
						{
							cout << *arrp[i] << endl;
							aim = true;
						}
					}

					if (aim == false)
						cout << "������ ����!" << endl;
					aim = false;
					break;
				}
				case 4: 
				{
					for (int i = 0; i <= num1; i++)
					{
							if (typeid (*arrp[i]) == typeid(Teacher))
							{
								cout << *arrp[i] << endl;
								aim = true;
							}
					}

					if (aim == false)
						cout << "������ ����!" << endl;
					aim = false;
					break;
				}
				case 5:
				{
					int group, cource;
					cout << "������� ����:" << endl;
					cin >> cource;
					cout << "������� ����� ������:" << endl;
					cin >> group;
					studsearch(arrp, group, cource, num1);
					break;
				}
				case 6:
				{
					cout << "������� ������� �������������:" << endl;
					char* kaf = new char[200];
					scanf("%s", kaf);
					teachsearch(arrp, kaf, num1);
					delete[] kaf;
					break;
				}
				case 7: 
				{
					for (int i = 0; i <= num1; i++)
						delete arrp[i];
					system("pause"); 
					return 0; 
				}
				default:
					cout << "������---������������ ����� ����!" << endl;
					cout << endl;
					break;
				}
			}
			break;
	}
}
