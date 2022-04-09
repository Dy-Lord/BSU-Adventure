#include<iostream>
#include<ctime>
using namespace std;
int main()
{
	setlocale(LC_ALL, "ru");
	int i, j, ROWS, COLL, w, a, b, k, SORT, TEMP, SORTZ;
	int** arr;
	int S = 0;
	cout << "Введите размерность прямоугольной матрицы: " << endl;

	cout << "Количество строк:" << endl;;
	cin >> ROWS;
	cout << "Количество столбцов:" << endl;
	cin >> COLL;

	if ((ROWS <= 0) || (COLL <= 0))
	{
		cout << "ОШИБКА---Некорректный размер матрицы!" << endl;
		system("pause");
		return 0;
	}

	arr = new int* [ROWS];
	for (i = 0; i < ROWS; i++)
		arr[i] = new int[COLL];

	srand(time(NULL));

	cout << "Выберите способ ввода заполнения массива: " << endl;
	cout << "1-Ввод с помощью клавиатуры " << endl << "2-Ввод с помощью рандома " << endl;
	cin >> w;


	if ((w != 1) && (w != 2))
	{
		cout << "ОШИБКА---Неопознанный способ!" << endl;
		system("pause");
		return 0;
	}

	//Ввод массива с помощью клавиатуры
	if (w == 1)
		for (i = 0; i < ROWS; i++)
		{
			for (j = 0; j < COLL; j++)
				cin >> arr[i][j];
			cout << endl;
		}

	//Ввод массива с помощью рандома
	if (w == 2)
	{
		cout << "Введите границы интервала рандома" << endl;
		cin >> a;
		cin >> b;
		cout << endl;
		if (a > b)
		{
			cout << "ОШИБКА---Некорректный интервал!" << endl;
			system("pause");
			return 0;
		}
		for (i = 0; i < ROWS; i++)
			for (j = 0; j < COLL; j++)
				arr[i][j] = (a + (rand() % (b - a + 1)));
	}


	// Вывод массива
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLL; j++)
			printf("%-5d", arr[i][j]);
		cout << endl;
	}

	//Нахождение суммы
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLL; j++)
		{
			if (arr[i][j] == 0)
			{
				for (k = 0; k < ROWS; k++)
					S += arr[k][j];
			}
		}


	if (S == 0)
		cout << "В стобцах нет нулевого элемента!" << endl;
	else
		cout << "Сумма элементов среди всех элементов тех столбцов, которые содержат хотя бы один ноль = " << S << endl;

	cout << endl << "Сотрировка матрицы---элементы четных строк матрицы расположены по возрастанию, а нечетных - по убыванию" << endl;

	//Сортировка матрицы
	k = 0;
	for (i = 0; i < ROWS; i++)
	{
		if ((i % 2) != 0)
		{
			for (j = 0; j < COLL; j++)
			{
				SORTZ = arr[i][j];
				SORT = 0;
				for (k = j; k < COLL; k++)
					if (arr[i][k] > SORTZ)
					{
						SORT = k;
						SORTZ = arr[i][k];
					}
				if (SORT == 0)
					continue;
				TEMP = arr[i][j];
				arr[i][j] = arr[i][SORT];
				arr[i][SORT] = TEMP;
			}
		}
		else
		{
			for (j = 0; j < COLL; j++)
			{
				SORTZ = arr[i][j];
				SORT = 0;
				for (k = j; k < COLL; k++)
					if (arr[i][k] < SORTZ)
					{
						SORT = k;
						SORTZ = arr[i][k];
					}
				if (SORT == 0)
					continue;
				TEMP = arr[i][j];
				arr[i][j] = arr[i][SORT];
				arr[i][SORT] = TEMP;
			}
		}
	}

	// Вывод массива
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLL; j++)
			printf("%-5d", arr[i][j]);
		cout << endl;
	}

	for (i = 0; i < ROWS; i++)
		delete[] arr[i];
	delete[] arr;

	cout << endl << "Программа завершена!" << endl;

	system("pause");
	return 0;
}