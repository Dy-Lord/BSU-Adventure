// x=-8 ---- �������� ������� �� ����������
// x=-7 ---- y=2
// x=-6 ---- y=-6 b y=-1
// x=-5 ---- y=-0.75
// x=-2 ---- y=0
// x=-1 ---- y= 0.267949
// x=0 ---- y=2
// x=1 ---- y=1.73205
// x=2 ---- y=0
// x=3 ---- y=-1
// x=4 ---- �������� ������� �� ����������
#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, ".1251");
	int R;
	double x, y;
	cout << "������� �������� ���������" << endl;
	cin >> x;
	if((x < -7)||(x>3))
	{
		cout << "�������� ������� �� ����������! " << endl;
		system("pause");
		return 0;
	}
	if (x == -6)
	{
		y = 2;
		cout << "�������� ������� = " << y << endl;
		y = (x + 2) / 4;
		cout << "� " << y << endl;
	}
	else
	if (x < -6)
	{
		y = 2;
		cout << "�������� ������� = " << y << endl;
	}
	else
	if (x <= -2)
	{
		y = (x + 2) / 4;
		cout << "�������� ������� = " << y << endl;
	}
	else
		if (x <= 0)
		{
			y = 2-sqrt(4 - (x + 2) * (x + 2));
			cout << "�������� ������� = " << y << endl;
		}
		else
			if (x <= 2)
			{
				y = sqrt(4 - x * x);
				cout << "�������� ������� = " << y << endl;
			}
			else
				if (x <= 3)
				{
					y = 2 - x;
					cout << "�������� ������� = " << y << endl;
				}
	system("pause");
	return 0;

}
