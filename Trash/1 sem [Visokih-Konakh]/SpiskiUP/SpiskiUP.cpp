#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include<cstdio>
#include<cstring>

using namespace std;

struct ListItem
{
	char* Info;
	ListItem* Next;
};

ListItem* first(char* infor);//������������� ������� �������� ������
ListItem* m1(ListItem* P, char* infor); //���������� �������� � ������ ������
void m2(ListItem* First);  //����� ��������� ������ �� �����
ListItem* m3(ListItem* First);//�������� �������� �� ������ ������
ListItem* m4(ListItem* First);//������� ������
void m5(ListItem* First, char* finder);//����� ������� �������� ������ �� ��������� ��������
void m6(ListItem* First, char* finder);//���������� ���������� ��������� � ������ �� ��������� ��������
ListItem* m7(ListItem* First, char* finder); //�������� ������� �������� �� ������ �� ��������� ��������
ListItem* m8(ListItem* First, char* finder);//�������� ���� ��������� �� ������ �� ��������� ��������
ListItem* tempm7(ListItem* First, char* finder);
bool sravn(ListItem* First1, ListItem* First2);


ListItem* first(char* infor) 
{
	ListItem* lst;
	lst = new ListItem;
	lst->Info = infor;
	lst->Next = NULL; 
	return(lst);
}

ListItem *m1(ListItem* P,char* infor)
{
	P->Next = new ListItem;
	P = P->Next;
	P->Info = infor;
	P->Next = NULL;
	return P;
}

void m2(ListItem* First)
{
	ListItem* P = First;
	bool aim = 0;
	while (P != NULL)
	{
		aim = 1;
		cout << P-> Info << endl;
		P = P->Next;
	}
	if (!aim)
		cout << "������ ����!" << endl;
}

ListItem* m3(ListItem* First)
{
	if (First == NULL)
		return NULL;
	ListItem* P = First;
	First = First->Next;
	delete P;
	return First;
}

ListItem* m4(ListItem* First)
{
	while (First != NULL)
	{
		ListItem* P = First;
		First = First->Next;
		delete P;
	}
	cout << "������� ��������� �������!" << endl;
	return NULL;
}

void m5(ListItem* First, char* finder)
{
	ListItem* P = First;
	bool aim = 0;
	int count = 0;
	while (P != NULL)
	{
		count++;
		if (!strcmp(finder, P->Info))
		{
			cout << "���������� �������!" << endl << "����� �������� ������ --- " << count << endl << "�������� ���� �������� --- " << P->Info << endl;
			aim = 1;
			break;
		}
		else
			P = P->Next;
	}
	if (!aim)
		cout << "���������� �� �������!" << endl;
}

void m6(ListItem* First, char* finder)
{
	ListItem* P = First;
	int count = 0;
	while (P != NULL)
	{
		if (!strcmp(finder, P->Info))
			count++;
			P = P->Next;
	}
	if (count)
		cout << "���������� �������� �� ���� ��������� ������ --- " << count << endl;
	else
		cout << "���������� �� �������!" << endl;
}

ListItem* m7(ListItem* First, char* finder)
{
	ListItem* P = First;
	bool aim = 0;
	int count = 0;
	while (P != NULL)
	{
		count++;
		if (!strcmp(finder, P->Info))
		{
			aim = 1;
			break;
		}
		P = P->Next;
	}

	if (!aim)
	{
		cout << "���������� �� �������!" << endl;
		return First;
	}

	if (count == 1)
	{
		First = m3(First);
		cout << "�������� �������!" << endl;
		return First;
	}
	
	ListItem* Prep = First;
	for (int i = 0; i < count - 2; i++)
		Prep = Prep->Next;

	Prep->Next = P->Next;
	delete P;
	cout << "�������� �������!" << endl;
	return First;

}

ListItem* m8(ListItem* First, char* finder)
{
	ListItem* P = First;
	bool aim = 0;
	int count = 0;
	while (P != NULL)
	{
		if (!strcmp(finder, P->Info))
		{
			count++;
			First = tempm7(First, finder);
			P = First;
		}
		else
		P = P->Next;
	}
	cout << "������� --- " << count << " --- �������(��) �� ��������� ��������!" << endl;
	return First;
}

ListItem* tempm7(ListItem* First, char* finder)
{
	ListItem* P = First;
	bool aim = 0;
	int count = 0;
	while (P != NULL)
	{
		count++;
		if (!strcmp(finder, P->Info))
		{
			aim = 1;
			break;
		}
		P = P->Next;
	}

	if (!aim)
		return First;

	if (count == 1)
	{
		First = m3(First);
		return First;
	}

	ListItem* Prep = First;
	for (int i = 0; i < count - 2; i++)
		Prep = Prep->Next;

	Prep->Next = P->Next;
	delete P;
	return First;
}

bool sravn(ListItem* First1, ListItem* First2)
{
	ListItem* P1 = First1;
	ListItem* P2 = First2;

	while (P2 != NULL)
	{
		if (!strcmp(P2->Info, P1->Info))
		{
			P1 = P1->Next;
			P2 = P2->Next;
		}
		else
			return false;
	}
	return true;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int w;
	bool aim = 1;
	int task;

	while (true)
	{

		cout << "�������� ����� �������:" << endl << "(1) --- ����������� ��� �������" << endl << "(2) --- �������� �� ��������� ������ L2 � ������ ������ L1" << endl << "(3) --- �����" << endl;
		cin >> task;
		system("cls");

		switch (task)
		{
		case 1:
		{
			ListItem* B = NULL;
			ListItem* F = NULL;
			while (true)
			{
				cout << "(1)---�������� ������� � ������" << endl << "(2)---������� �������� ������ �� �����" << endl << "(3)---������� ������� �� ������ ������" << endl << "(4)---�������� ������" << endl << "(5)---����� ������� �������� ������ �� ��������� ��������" << endl << "(6)---���������� ���������� ��������� � ������ �� ��������� ��������" << endl << "(7)---������� ������ ������� �� ������ �� ��������� ��������" << endl << "(8)---������� ��� �������� �� ������ �� ��������� ��������" << endl << "(9)---�����" << endl;
				cin >> w;
				system("cls");
				switch (w)
				{
				case 1:
				{
					cout << "������� ������� ������:" << endl;
					char* info = new char[200];
					scanf("%s", info);
					if (aim)
					{
						B = first(info);
						F = B;
						aim = 0;
					}
					else
						F = m1(F, info);
					break;
				}
				case 2: m2(B); cout << endl; break;
				case 3:
				{
					B = m3(B);
					if (B == NULL)
						cout << "������ ����!" << endl;
					else
						cout << "�������� �������!" << endl;
					cout << endl;
					break;
				}
				case 4: aim = 1; B = m4(B); break;
				case 5:
				{
					cout << "������� ������� ������ ��� ������:" << endl;
					char* finder = new char[200];
					scanf("%s", finder);
					cout << endl;
					m5(B, finder);
					cout << endl;
					delete[] finder;
					break;
				}
				case 6:
				{
					cout << "������� ������� ������ ��� ������:" << endl;
					char* finder = new char[200];
					scanf("%s", finder);
					cout << endl;
					m6(B, finder);
					cout << endl;
					delete[] finder;
					break;
				}
				case 7:
				{
					cout << "������� ������� ������ ��� ��������:" << endl;
					char* finder = new char[200];
					scanf("%s", finder);
					cout << endl;
					B = m7(B, finder);
					cout << endl;
					delete[] finder;
					break;
				}
				case 8:
				{
					cout << "������� ������� ������ ��� ��������:" << endl;
					char* finder = new char[200];
					scanf("%s", finder);
					cout << endl;
					B = m8(B, finder);
					cout << endl;
					delete[] finder;
					break;
				}
				case 9: return 0; break;
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
			ListItem* B1 = NULL;
			ListItem* F1 = NULL;
			ListItem* B2 = NULL;
			ListItem* F2 = NULL;

				int y = 1, x = 1;
				cout << "������� ��������� ������� ������ L1" << endl;

				while (y)
				{
					int t;
					int aim = 1;
					while (y)
					{
						cout << "�������� ��������:" << endl << "(1) --- �������� ������� ������ " << endl << "(2) --- ������� � ����� ��������� ������� ������ " << endl;
						cin >> t;
						system("cls");
						switch (t)
						{
						case 1: 
						{
							cout << "������� ������� ������:" << endl;
							char* info = new char[200];
							scanf("%s", info);
							if (aim)
							{
								B1 = first(info);
								F1 = B1;
								aim = 0;
							}
							else
								F1 = m1(F1, info);
							break;
						}
						case 2: y = 0; break;
						default:
						{
							cout << "������---������������ ����� ����!" << endl;
							cout << endl;
							break;
						}
						}
					}
				}

				cout << "������� ��������� ������� ������ L2" << endl;

				while (x)
				{
					int t;
					int aim = 1;
					while (x)
					{
						cout << "�������� ��������:" << endl << "(1) --- �������� ������� ������ " << endl << "(2) --- ������� � �������� " << endl;
						cin >> t;
						system("cls");
						switch (t)
						{
						case 1:
						{
							cout << "������� ������� ������:" << endl;
							char* info = new char[200];
							scanf("%s", info);
							if (aim)
							{
								B2 = first(info);
								F2 = B2;
								aim = 0;
							}
							else
								F2 = m1(F2, info);
							break;
						}
						case 2: x = 0; break;
						default:
						{
							cout << "������---������������ ����� ����!" << endl;
							cout << endl;
							break;
						}
						}
					}
				}

				if (sravn(B1, B2))
					cout << "������ L2 �������� ������� ������ L1!" << endl;
				else
					cout << "������ L2 �� �������� ������� ������ L1!" << endl;
				system("pause");
				return 0;

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
	system("pause");
	return 0;
}
