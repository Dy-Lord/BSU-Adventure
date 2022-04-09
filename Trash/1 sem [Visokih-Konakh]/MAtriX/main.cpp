#include<iostream>
#include<Windows.h>
#include<exception>
#include"MatX.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try {
		MatX a(3, 3, 1), b(3, 4, 2), c(3,3,0), h;

		cout << 'a' << endl;
		cout << a << endl;  
		
		cout << 'b' << endl;
		cout << b << endl;            

		cout << "hПрисваивание матрицы a матрице h" << endl;
		h = a;                      
		cout << h << endl;


		cout << "Умножение матриц" << endl;
		cout << a * b << endl;       

		cout << "Умножение матрицы на константу" << endl;
		cout << a * 4 << endl;

		cout << "Умножение константы на матрицу" << endl;
		cout << 4 * a << endl;

		b *= 2;
		a *= b;

		cout << "b*=2" << endl;
		cout << b << endl;

		cout << "a*=b" << endl;
		cout << a << endl;

		cout << "Сумма матриц" << endl;
		cout << a + b << endl;

		cout << "Сумма константы и матрицы" << endl;
		cout << 10 + a << endl;

		cout << "Сумма матрицы и константы" << endl;
		cout << a + 10 << endl;

		cout << "Сравнение матриц" << endl;
		cout << (a == b) << endl;
		cout << (a != b) << endl;

	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	system("pause");
	return 0;
}