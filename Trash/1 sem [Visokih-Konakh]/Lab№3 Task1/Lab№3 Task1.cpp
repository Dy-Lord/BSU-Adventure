/*
Введите значение аргумента x 12
Введите точность вычислений 8
Значение библиотечной функции ch(12.00000000) =
81377.39571257
Значение суммы ряда =
81377.39571257
---------------------------
Введите значение аргумента x 1
Введите точность вычислений 0
Значение библиотечной функции ch(1) =
2
Значение суммы ряда =
2
----------------------------
*/
#include <iostream>
#include <math.h>
#include<iomanip>
	using namespace std;
	int main()
	{
		setlocale(LC_ALL, ".1251");
		double x, eps;
		int k;
		cout << "Введите значение аргумента x ";
		cin >> x;
		cout << "Введите точность вычислений ";
		cin >> k;
		eps = pow(10,-(k+1));
		cout.setf(ios::fixed);
		cout << "Значение библиотечной функции ";
		cout << "ch(" << setprecision(k) << x << ") =" << endl <<
			cosh(x) << endl;
		double s = 0, a = 1;
		int n = 0;
		for (n = 1; abs(a) >= eps;n=n+2)
		{
			s += a;
			a = a * x *x/ (n * (n + 1));
		}
		cout << "Значение суммы ряда =\n" << setprecision(k) << s <<
			endl;
		system("pause");
		return 0;
	}