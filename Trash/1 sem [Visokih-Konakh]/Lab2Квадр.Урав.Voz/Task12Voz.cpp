// a=0 b=0 c=0 ---- ������ ����� �����
// a=0 b=0 c!=0 ---- ��� ������
// a=0 b!=0 ---- ���� ������
// a!=0 ----- D>=0 ----- ��� �����
// a!=0 ----- D<0 ----- ��� ������
#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	setlocale(LC_ALL,".1251");
	double a,b,c,D,x;
	cout << "������� ���������� a,b,c ����������� ��������� " << endl;
	cin >> a>>b>>c;
	if (a == 0)
	{
		if (b == 0)
		{
			if (c == 0)
				cout << "������ �������� ����� �������������� ������" << endl;
			else
				cout << "��� ������" << endl;
		}
		else
		{
			x = (-c) / b;
			cout << "���� ������ " << x << endl;
		}
		}
	else
	{
		D = b * b - 4 * a * c;
		if (D >= 0)
		{
			x = ((-b) + sqrt(D)) / 2 * a;
			cout << "��� ����� " << x << endl;
			x = ((-b) - sqrt(D)) / 2 * a;
			cout << x << endl;
		}
		else
			cout << "��� ������ " << endl;
	}
system("pause");
return 0;
}



