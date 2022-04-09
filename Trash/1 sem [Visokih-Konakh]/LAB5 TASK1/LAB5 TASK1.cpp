#include<iostream>
#include<ctime>
#include<limits.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "ru");
	int const SIZE=100;
	int const RANDNUM = 10;
	int arr[SIZE];
	int n, i, MAX = 0, MIN = 0, MAXC, MINC, SORT = 0, j;
	unsigned long long p = 1;
	cout << "Введите количество элементов массива (до "<<SIZE<<" элементов) " << endl;
	cin >> n;
	if (n < 1)
	{
		cout<<"ОШИБКА---введено неверное количество элементов массива!" << endl;
		system("pause");
		return 0;
	}
	if (n > SIZE)
	{
		cout << "ОШИБКА---введено запредельное количество элементов массива!" << endl;
		system("pause");
		return 0;
	}
	srand(time(NULL));

	for (i = 0; i < n; i++)
		cout<<(arr[i] = rand() % RANDNUM + 1)<< '\t';
	cout << endl;
/////////////////////////////////////////////////////////////////////////////////
	for (int i = 1; i < n; i+=2)
	{
		 SORT = i;
			for (j = i + 2; j < n; j+=2)
				if (arr[j] > arr[SORT]) SORT = j;
			if (i == SORT) continue;
		int temp = arr[i];
		arr[i] = arr[SORT];
		arr[SORT] = temp;                                         ///////////SORT/////////
	}

	cout << endl<<endl;

	for (i = 0; i < n; i++)
		cout << (arr[i]) << '\t';
	cout << endl;
	/////////////////////////////////////////////////////////////////////////

	for (i = n-1; i >= 0; i--)
		if (arr[i] >= MAX)
		{
			MAX = arr[i];
			MAXC = i;
		}

	for (i = MAXC+1; i < n; i++)
		if (arr[i] <= RANDNUM + 1)
		{
			MIN = arr[i];
	        MINC = i;
		}
	if (MINC < MAXC)
	{
		cout << "Первый минимальный элемент стоит перед первым максимальным элементом массива! Расчёт произведения невозможен!" << endl;
		system("pause");
		return 0;
	}
	if (MAXC + 1 == MINC)
		cout << "Между первым максимальным и последним минимальным элементами нет элементов!" << endl;
	else
	{
		for (i = MAXC + 1; i < MINC; i++)
	{
			if (p == 0)
			{
				cout << "ПЕРЕМЕННАЯ ПЕРЕГРУЖЕНА!" << endl;
				system("pause");
				return 0;
			}
		p *= arr[i];
	}
		cout << "Произведение элементов массива, расположенных между первым максимальным и последним минимальным элементами = " << p << endl;
	}
	system("pause");
	return 0;
}