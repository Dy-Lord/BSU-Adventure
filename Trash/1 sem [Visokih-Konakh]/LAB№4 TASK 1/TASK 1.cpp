#include<iostream>
#include<limits.h>
#include<ctime>
using namespace std;
int SD(int z)
{
	int s = 0;
	for (int i = 1; i <= z / 2; i++)
		if (z % i == 0) 
			s += i;
	return s;
}
int main()
{
	setlocale(LC_ALL,".1251");
	unsigned N, count;
	unsigned long long i=1, b, c;
	cout << "Введите число пар дружественных числел, которое требуется найти " << endl;
	cin >> N;
	if (N <= 0)
	{
		cout << "ОШИБКА---Вы ввели не натуральное число! " << endl;
		system("pause");
		return 0;
	}
	unsigned t1 = time(0);
	cout << "Дружественные числа : " << endl;
	for (count = 0; count < N;)
	{
		b = SD(i);
		c = SD(b);
		if (i == c && c != b)
		{
			cout << i << " и " << b << endl;
			count++;
		}
		i++;
	}
	unsigned t2 = time(0);
	cout << "Время работы = "<<t2-t1<<"мс"<< endl;
	if (count < N)
		cout << "Не удалось вывести все требуемые пары дружественных числел !" << endl;
	else
		cout << "Были найдены все пары дружественных числел !" << endl;
	system("pause");
	return 0;
}