#include"Header.h"
#include<iostream>
#include<string>
#include<Windows.h>

using namespace std;

struct pamag
{
	PRAM pr;
	double S;
};

void SORTSHELL(pamag*& arr, int SIZE);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	PRAM first, second, third;
	double g,l;
	int w, p, aim = 1;
	cout << "Введите координаты правой верхней вершины прямоугольника" << endl;
	cout << "X = ";
	cin >> g;
	first.SetX1(g);
	cout << "Y = ";
	cin >> g;
	first.SetY1(g);

	cout << "Введите координаты левой нижней вершины прямоугольника" << endl;
	cout << "X = ";
	cin >> g;
	first.SetX2(g);
	cout << "Y = ";
	cin >> g;
	first.SetY2(g);

	while (aim)
	{
		
		cout << "(1) --- Вывести площадь прямоугольника" << endl << "(2) --- Параллельно перенести прямоугольник относительно оси Ox" << endl << "(3) --- Параллельно перенести прямоугольник относительно оси Oy" << endl << "(4) --- Изменить координату Х правой стороны прямоугольника" << endl << "(5) --- Изменить координату Х левой стороны прямоугольника" << endl << "(6) --- Изменить координату Y верхней стороны прямоугольника" << endl << "(7) --- Изменить координату Y нижней стороны прямоугольника" << endl << "(8) --- Вывести координаты прямоугольника " << endl << "(9) --- Вывести прямоугольник" << endl << "(10) --- Построение наименьшего прямоугольника, содержащего два заданных прямоугольника" << endl << "(11) --- Выйти и вывести прямоугольники отсортированные по площади" << endl;
		cin >> w;
		system("cls");
		switch (w)
		{
		case 1: l = first.SSS(); cout << l << endl; break;
		case 2:
		{
			cout << "Введите значение сдвига" << endl;
			cin >> p;
			first.POX(p);
			cout << "Операция выполнена успешно!" << endl;
			break;
		}
		case 3:
		{
			cout << "Введите значение сдвига" << endl;
			cin >> p;
			first.POY(p);
			cout << "Операция выполнена успешно!" << endl;
			break;
		}
		case 4: 
		{
			cout << "Введите координату Х" << endl;
			cin >> g;
			first.SetX1(g);
			cout << "Операция выполнена успешно!" << endl;
			break;
		}
		case 5:
		{
			cout << "Введите координату Х" << endl;
			cin >> g;
			first.SetX2(g);
			cout << "Операция выполнена успешно!" << endl;
			break;
		}
		case 6: 
		{
			cout << "Введите координату Y" << endl;
			cin >> g;
			first.SetY1(g);
			cout << "Операция выполнена успешно!" << endl;
			break;
		}
		case 7: 
		{
			cout << "Введите координату Y" << endl;
			cin >> g;
			first.SetY2(g);
			cout << "Операция выполнена успешно!" << endl;
			break;
		}
		case 8: cout << endl; first.print(); cout << endl; break;
		case 9: cout << first << endl; break;
		case 10: 
		{
			cout << "Введите координаты второго прямоугольника" << endl;
			cout << "Введите координаты правой верхней вершины прямоугольника" << endl;
			cout << "X = ";
			cin >> g;
			second.SetX1(g);
			cout << "Y = ";
			cin >> g;
			second.SetY1(g);

			cout << "Введите координаты левой нижней вершины прямоугольника" << endl;
			cout << "X = ";
			cin >> g;
			second.SetX2(g);
			cout << "Y = ";
			cin >> g;
			second.SetY2(g);

			third.BUILD(first, second);

			cout << "Координаты наименьшего построенного прямоугольника:" << endl;
			cout << endl;
			third.print();
			cout << endl;
			cout << endl;
			break;
		}
		case 11: aim=0; break;
		default:
		{
			cout << "ОШИБКА --- Некорректный пункт меню!";
			break;
		}
		}
	}

	cout << endl;

	PRAM q(2, 2, 1, 1), b(5, 6, 3, 2), r(9, 7, 1, 1), y(-1, -1, -10, -10), o(43, 23, 12, 12);
	pamag* arrp=new pamag[5];

	arrp[0].pr = q;
	arrp[0].S = q.SSS();

	arrp[1].pr = b;
	arrp[1].S = b.SSS();

	arrp[2].pr = r;
	arrp[2].S = r.SSS();

	arrp[3].pr = y;
	arrp[3].S = y.SSS();

	arrp[4].pr = o;
	arrp[4].S = o.SSS();

	SORTSHELL(arrp, 5);

	for (int i = 0; i < 5; i++)
		cout << arrp[i].S << endl;

	delete[] arrp;
	system("pause");
	return 0;
}

void SORTSHELL(pamag*& arr, int SIZE)
{
	double fakt = 1.6473309;
	int len = SIZE / fakt;
	int stop = 0;
	if (SIZE == 1)
		return;

	while (true)
	{
		for (int i = 0; (i < SIZE) && (i + len < SIZE); i++)
			if (arr[i].S > arr[i + len].S)
				swap(arr[i], arr[i + len]);

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