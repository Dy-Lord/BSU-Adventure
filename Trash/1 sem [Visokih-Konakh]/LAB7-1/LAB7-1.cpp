#include<iostream>
using namespace std;
int SUMMNUT(int a)
{
	int S = 0;
	if (a == 0)
		return S;
	if ((a % 10) % 2 == 0)
		S += a % 10;
		a /= 10;
	int t = a;
	count(&c);
	return S = S + SUMMNUT(t);
}

int count(int *c)
{
	*c++;
}
int main()
{
	int b, c = 0;
	setlocale(LC_ALL, "ru");
	cout << "Введите натуральное число " << endl;
	cin >> b;
	if (b <= 0)
	{
		cout << "ОШИБКА---Число не натуральное!" << endl;
		system("pause");
		return 0;
	}
	if (SUMMNUT(b))
	{
		if (c=1)
			cout << "В записи натурального числа одна чётная цифра = " << SUMMNUT(b) << endl;
		else
			cout << "Сумма четных цифр в записи натурального числа = " << SUMMNUT(b) << endl;
	}
	else
		cout << "В числе нет чётных цифр!" << endl;
	system("pause");
	return 0;
}