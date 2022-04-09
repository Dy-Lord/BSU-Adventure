#include<iostream>
#include<cmath>
using namespace std;
double f1(double x)
{
	return x * atan(x);
}

double f2(double x)
{
	return 1 / (1 + sqrt(x));
}

double f3(double x)
{
	return 2 / (1 - 4 * x);
}

double integ(double a, double b, double eps, double ptr(double))
{
	int i = 0;
	double S2 = 0, S1 = 0, h, n = 1;

	h = (b - a) / n; //Шаг сетки
	S2 = ptr(a + h * (i + 0.5));
	eps = pow(10, -eps);
	do
	{
		S1 = S2;
		S2 = 0;
		n *= 2;
		h = (b - a) / n;
		for (i = 0; i < n; i++)
		{
			S2 += ptr(a + h * (i + 0.5)); //Вычисляем в средней точке и добавляем в сумму
		}
		S2 *= h;
	} while (fabs(S1 - S2) >= eps);
	return S2;
}

int main()
{
	const double eps = 6;
	setlocale(LC_ALL, "ru");
	cout << "Значения библиотечных функций интегралов:" << endl;
	cout << "F1=1,1709955" << endl;
	cout << "F2=1,06568" << endl;
	cout << "F3=0,21968333" << endl;
	cout << "Значения расчитанных функций интегралов:" << endl;
	cout << "F1=";
	printf("%f10", integ(0, 1.7, eps, f1));
	cout << endl;
	cout << "F2=";
	printf("%f10", integ(0, 2, eps, f2));
	cout << endl;
	cout << "F3=";
	printf("%f10", integ(-2, -1.2, eps, f3));
	cout << endl;
	system("pause");
	return 0;
}