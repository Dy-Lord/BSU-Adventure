// x=-8 ---- Значение функции не определено
// x=-7 ---- y=2
// x=-6 ---- y=-6 b y=-1
// x=-5 ---- y=-0.75
// x=-2 ---- y=0
// x=-1 ---- y= 0.267949
// x=0 ---- y=2
// x=1 ---- y=1.73205
// x=2 ---- y=0
// x=3 ---- y=-1
// x=4 ---- Значение функции не определено
#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, ".1251");
	int R;
	double x, y;
	cout << "Введите значение аргумента" << endl;
	cin >> x;
	if((x < -7)||(x>3))
	{
		cout << "Значение функции не определено! " << endl;
		system("pause");
		return 0;
	}
	if (x == -6)
	{
		y = 2;
		cout << "Значение функции = " << y << endl;
		y = (x + 2) / 4;
		cout << "и " << y << endl;
	}
	else
	if (x < -6)
	{
		y = 2;
		cout << "Значение функции = " << y << endl;
	}
	else
	if (x <= -2)
	{
		y = (x + 2) / 4;
		cout << "Значение функции = " << y << endl;
	}
	else
		if (x <= 0)
		{
			y = 2-sqrt(4 - (x + 2) * (x + 2));
			cout << "Значение функции = " << y << endl;
		}
		else
			if (x <= 2)
			{
				y = sqrt(4 - x * x);
				cout << "Значение функции = " << y << endl;
			}
			else
				if (x <= 3)
				{
					y = 2 - x;
					cout << "Значение функции = " << y << endl;
				}
	system("pause");
	return 0;

}
