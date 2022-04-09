// a=0 b=0 c=0 ---- Корень любое число
// a=0 b=0 c!=0 ---- Нет корней
// a=0 b!=0 ---- Один корень
// a!=0 ----- D>=0 ----- Два корня
// a!=0 ----- D<0 ----- Нет корней
#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	setlocale(LC_ALL,".1251");
	double a,b,c,D,x;
	cout << "Введите переменные a,b,c квадратного уравнения " << endl;
	cin >> a>>b>>c;
	if (a == 0)
	{
		if (b == 0)
		{
			if (c == 0)
				cout << "Корень является любым действительным числом" << endl;
			else
				cout << "Нет корней" << endl;
		}
		else
		{
			x = (-c) / b;
			cout << "Один корень " << x << endl;
		}
		}
	else
	{
		D = b * b - 4 * a * c;
		if (D >= 0)
		{
			x = ((-b) + sqrt(D)) / 2 * a;
			cout << "Два корня " << x << endl;
			x = ((-b) - sqrt(D)) / 2 * a;
			cout << x << endl;
		}
		else
			cout << "нет корней " << endl;
	}
system("pause");
return 0;
}



