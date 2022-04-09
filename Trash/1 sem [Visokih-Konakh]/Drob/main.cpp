#include <iostream>
#include <Windows.h>
#include "Header.h"
#include <exception>

using namespace std;

struct DROBARR
{
	DROB dr;
};

void sortrust(DROBARR*& arr, int SIZE)
{
	double fakt = 1.2473309;
	int len = SIZE / fakt;
	int stop = 0;

	if (SIZE == 1)
		return;

	while (true)
	{
		for (int i = 0; (i < SIZE) && (i + len < SIZE); i++)
		{
			if (arr[i].dr > arr[i + len].dr)
				swap(arr[i], arr[i + len]);
		}

		if (len != 1)
			len /= fakt;

		else
		{
			len = 0;
			stop = 1;
		}

		if (stop)
			break;
	}

}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
	DROB one(0, 1, 2);
	DROB two(1, 1, 3);


	cout << "Сложение" << endl;

	cout << one + two;
	cout << one + 2;
	cout << 2 + one;

	cout << "Разность" << endl;

	cout << one - two;
	cout << one - 2;
	cout << 2 - one;

	cout << "Умножение" << endl;

	cout << one * two;
	cout << one * 2;
	cout << 2 * one;

	cout << "Деление" << endl;

	cout << one / two;
	cout << one / 2;
	cout << 2 / one;

	cout << "Инкрименты" << endl;

	cout << one++;
	cout << ++one;

	cout << two--;
	cout << --two;

	cout << "Операции сравнения" << endl;

	cout << (one > two) << endl;
	cout << (one < two) << endl;

	cout << (one == one) << endl;
	cout << (one != two) << endl;

	cout << (one >= two) << endl;
	cout << (one <= two) << endl;

	cout << "Присваивание" << endl;

	one = two;
	cout << one;

	cout << "Операции += -= *= /=" << endl;

	one += two;
	cout << one;

	one -= two;
	cout << one;

	one /= two;
	cout << one;

	one *= two;
	cout << one;


	cout << "Сортировка" << endl;

	DROB q(1, 2, 3), w(4, 3, 2), r(0, -2, -3), t(-3, 1, 1), y(8, -4, 2);
	DROBARR* arrp = new DROBARR[5];
	arrp[0].dr = q;
	arrp[1].dr = w;
	arrp[2].dr = r;
	arrp[3].dr = t;
	arrp[4].dr = y;
	sortrust(arrp, 5);
	for (int i = 0; i < 5; i++)
		cout << arrp[i].dr;
	delete[] arrp;

	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	system("pause");
	return 0;
}