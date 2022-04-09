#include<iostream>
#include<ctime>
using namespace std;

//Верхний предел
bool up(int i,int ROWS)
{
	if ((i - 1) < 0)
		return false;
	else
		return true;
}

//Нижний предел
bool down(int i,int ROWS)
{
	if ((i + 1) > (ROWS-1))
		return false;
	else
		return true;
}

//Левый предел
bool left(int j, int ROWS)
{
	if ((j - 1) < 0)
		return false;
	else
		return true;
}

//Правый предел
bool right(int j, int ROWS)
{
	if ((j + 1 > (ROWS-1)))
		return false;
	else
		return true;
}

int main()
{
	setlocale(LC_ALL, "ru");
	int i, j, ROWS, w, a, b, k,z,m,COUNT=0,COUNTPRE=0,MIN=0;
	int** arr;
	int S = 0;
	cout << "Введите размерность квадратной матрицы: " << endl;
	cin >> ROWS;
	

	if (ROWS <= 0)
	{
		cout << "ОШИБКА---Некорректный размер матрицы!" << endl;
		system("pause");
		return 0;
	}

	arr = new int* [ROWS];
	for (i = 0; i < ROWS; i++)
		arr[i] = new int[ROWS];

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
			for (j = 0; j < ROWS; j++)
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
			for (j = 0; j < ROWS; j++)
				arr[i][j] = (a + (rand() % (b - a + 1)));
	}


	// Вывод массива
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < ROWS; j++)
			printf("%-5d", arr[i][j]);
		cout << endl;
	}

	//Локальные минимумы
	int iup=0, idown=0;
	int jleft=0, jright=0;
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < ROWS; j++)
		{
			if (up(i, ROWS))
			{
				iup = 1;
				COUNTPRE++;
			}

			if (down(i, ROWS))
			{
				idown = 1;
				COUNTPRE++;
			}

			if (left(j, ROWS))
			{
				jleft = 1;
				COUNTPRE++;
			}

			if (right(j, ROWS))
			{
				jright = 1;
				COUNTPRE++;
			}

			if(up(i, ROWS)&& left(j, ROWS))
				COUNTPRE++;

			if (up(i, ROWS) && right(j, ROWS))
				COUNTPRE++;

			if (down(i, ROWS) && left(j, ROWS))
				COUNTPRE++;

			if (down(i, ROWS) && right(j, ROWS))
				COUNTPRE++;

		

			for (k = i - iup; k <= (i + idown); k++)
				for (m = j - jleft; m <= (j + jright); m++)
					if ((arr[i][j]) < (arr[k][m]))
					COUNT++;
			if (COUNT == COUNTPRE)
			{
				MIN++; //Количество соседей
				cout << arr[i][j] <<"\t"<<"i= "<<i<< "\t" << "j= "<<j<<endl; //Значение и координаты
			}
			COUNTPRE = 0;
			COUNT = 0;
		}
	for (i = 0; i < ROWS; i++)
		delete[] arr[i];
	delete[] arr;

	system("pause");
	return 0;
}