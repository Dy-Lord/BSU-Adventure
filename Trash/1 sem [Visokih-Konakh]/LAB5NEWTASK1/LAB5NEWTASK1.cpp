#include<iostream>
#include<ctime>
#include<limits.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "ru");
	int const SIZE = 30;
	int const RANDNUM = 10;
	int arr[SIZE];
	int n, i, MAX, MIN , MAXC, MINC, SORT = 0, j, w;
	int p = 1;
	cout << "Введите количество элементов массива (до " << SIZE << " элементов) " << endl;
	cin >> n;
	if (n < 1)
	{
		cout << "ОШИБКА---введено неверное количество элементов массива!" << endl;
		system("pause");
		return 0;
	}
	if (n > SIZE)
	{
		cout << "ОШИБКА---введено запредельное количество элементов массива!" << endl;
		system("pause");
		return 0;
	}
	cout << "Выберите способ ввода массива" << endl << "1-С помощью рандома" << endl << "2-С помощью клавиатуры " << endl;
	cin >> w;
	if ((w != 1) && (w != 2))
	{
		cout << "ОШИБКА---Введён неправильный способ! " << endl;
		system("pause");
		return 0;
	}
	if (w == 1)
	{
		srand(time(NULL));
		cout << endl;
		for (i = 0; i < n; i++)
			printf("%-5d", arr[i] = rand() % RANDNUM + 1);
		cout << endl;
	}
	if (w == 2)
	{
		cout << "Введите элементы массива:" << endl;
		for (i = 0; i < n; i++)
			cin >> arr[i];
		cout << endl;
		for (i = 0; i < n; i++)
			printf("%-5d",arr[i]);
		cout << endl;
	}
	
	MAX = arr[n-1];
	MIN = arr[0];
	MAXC = n-1;
	MINC = 0;

	for (i = n - 1; i >= 0; i--)
		if (arr[i] >= MAX)
		{
			MAX = arr[i];
			MAXC = i;
		}

	for (i = 0; i < n; i++)
		if (arr[i] <= MIN)
		{
			MIN = arr[i];
			MINC = i;
		}
	if (MINC < MAXC)
	{
		cout << "Первый минимальный элемент стоит перед первым максимальным элементом массива! Расчёт произведения невозможен!" << endl;
		cout << endl;
		cout << "Сортировка массива:" << endl;

		/////////////////////////////////////////////////////////////////////////////////
		for (int i = 1; i < n; i += 2)
		{
			SORT = i;
			for (j = i + 2; j < n; j += 2)
				if (arr[j] > arr[SORT]) SORT = j;
			if (i == SORT) continue;
			int temp = arr[i];
			arr[i] = arr[SORT];
			arr[SORT] = temp;                                         ///////////SORT/////////
		}

		cout << endl << endl;

		for (i = 0; i < n; i++)
			printf("%-5d", arr[i]);
		cout << endl;
		cout << endl;
		/////////////////////////////////////////////////////////////////////////

		cout << "Программа завершена!" << endl;
		system("pause");
		return 0;
	}
	if (MAXC + 1 == MINC)
		cout << "Между первым максимальным и последним минимальным элементами нет элементов!" << endl;
	else
	{
		if (MAXC + 2 == MINC)
			cout << "Между первым максимальным и последним минимальным элементами один элемент --- " << arr[MAXC + 1] << endl;
		else
		{
			for (i = MAXC + 1; i < MINC; i++)
			{
				p *= arr[i];
			}
			cout << "Произведение элементов массива, расположенных между первым максимальным и последним минимальным элементами = " << p << endl;
		}
	}
	cout << "Первый максимальный элемент = " << MAX << endl;
	cout << "Последний минимальный элемент = " << MIN << endl;

	cout << endl;
	cout << "Сортировка массива:" << endl;

	/////////////////////////////////////////////////////////////////////////////////
	for (int i = 1; i < n; i += 2)
	{
		SORT = i;
		for (j = i + 2; j < n; j += 2)
			if (arr[j] > arr[SORT]) SORT = j;
		if (i == SORT) continue;
		int temp = arr[i];
		arr[i] = arr[SORT];
		arr[SORT] = temp;                                         ///////////SORT/////////
	}

	cout << endl << endl;

	for (i = 0; i < n; i++)
		printf("%-5d", arr[i]);
	cout << endl;
	cout << endl;
	/////////////////////////////////////////////////////////////////////////

	cout << "Программа завершена!" << endl;
	system("pause");
	return 0;
}