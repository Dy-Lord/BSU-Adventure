#include<iostream>
using namespace std;
int SUMMNUT(int a)
{
	int S = 0;
	if (a == 0)
		return S;
	if ((a % 10) % 2 == 0)
		S += a % 10;
		a /= 10;
	int t = a;
	count(&c);
	return S = S + SUMMNUT(t);
}

int count(int *c)
{
	*c++;
}
int main()
{
	int b, c = 0;
	setlocale(LC_ALL, "ru");
	cout << "������� ����������� ����� " << endl;
	cin >> b;
	if (b <= 0)
	{
		cout << "������---����� �� �����������!" << endl;
		system("pause");
		return 0;
	}
	if (SUMMNUT(b))
	{
		if (c=1)
			cout << "� ������ ������������ ����� ���� ������ ����� = " << SUMMNUT(b) << endl;
		else
			cout << "����� ������ ���� � ������ ������������ ����� = " << SUMMNUT(b) << endl;
	}
	else
		cout << "� ����� ��� ������ ����!" << endl;
	system("pause");
	return 0;
}