#include<iostream>
#include<Windows.h>
using namespace std;
int main()
{
	SetConsoleOutputCP(1251);
	int N;
	cout << "Введите четырёхзначное целое число" << endl;
	cin >> N;
	N = abs(N);
	int U, T, H, TH;
	U = N % 10; //Еденицы
	N = N / 10;
	T = N % 10; //Десятки
	N = N / 10;
	H = N % 10; //Сотни
	TH = N / 10; //Тысячи
	int sum = U + T + H + TH;
	int rith = U * 1000 + T * 100 + H * 10 + TH;
	int left1 = H * 1000 + TH * 100 + U * 10 + T;
	int left2 = TH * 1000 + T * 100 + H * 10 + U;
	int left3 = T * 1000 + U * 100 + TH * 10 + H;
	cout << "Сумма цифр числа = " << sum << endl;
	cout << "Число, полученное при прочтении его цифр справа налево = " << rith << endl;
	cout << "Число, образуемое при перестановке первой и второй, третьей и четвёртой цифр = " << left1 << endl;
	cout << "Число, образуемое при перестановке второй и третьей цифр = " << left2 << endl;
	cout << "Число, образуемое при перестановке двух первых и двух последних цифр = " << left3 << endl;
	system("pause");
	return 0;
}