#include<iostream>
#include<ctime>
using namespace std;
int main()
{
	setlocale(LC_ALL, "ru");
	int i, j, ROWS, COLL, w, a, b, k, SORT, TEMP, SORTZ;
	int** arr;
	int S = 0;
	cout << "������� ����������� ������������� �������: " << endl;

	cout << "���������� �����:" << endl;;
	cin >> ROWS;
	cout << "���������� ��������:" << endl;
	cin >> COLL;

	if ((ROWS <= 0) || (COLL <= 0))
	{
		cout << "������---������������ ������ �������!" << endl;
		system("pause");
		return 0;
	}

	arr = new int* [ROWS];
	for (i = 0; i < ROWS; i++)
		arr[i] = new int[COLL];

	srand(time(NULL));

	cout << "�������� ������ ����� ���������� �������: " << endl;
	cout << "1-���� � ������� ���������� " << endl << "2-���� � ������� ������� " << endl;
	cin >> w;


	if ((w != 1) && (w != 2))
	{
		cout << "������---������������ ������!" << endl;
		system("pause");
		return 0;
	}

	//���� ������� � ������� ����������
	if (w == 1)
		for (i = 0; i < ROWS; i++)
		{
			for (j = 0; j < COLL; j++)
				cin >> arr[i][j];
			cout << endl;
		}

	//���� ������� � ������� �������
	if (w == 2)
	{
		cout << "������� ������� ��������� �������" << endl;
		cin >> a;
		cin >> b;
		cout << endl;
		if (a > b)
		{
			cout << "������---������������ ��������!" << endl;
			system("pause");
			return 0;
		}
		for (i = 0; i < ROWS; i++)
			for (j = 0; j < COLL; j++)
				arr[i][j] = (a + (rand() % (b - a + 1)));
	}


	// ����� �������
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLL; j++)
			printf("%-5d", arr[i][j]);
		cout << endl;
	}

	//���������� �����
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
		cout << "� ������� ��� �������� ��������!" << endl;
	else
		cout << "����� ��������� ����� ���� ��������� ��� ��������, ������� �������� ���� �� ���� ���� = " << S << endl;

	cout << endl << "���������� �������---�������� ������ ����� ������� ����������� �� �����������, � �������� - �� ��������" << endl;

	//���������� �������
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

	// ����� �������
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLL; j++)
			printf("%-5d", arr[i][j]);
		cout << endl;
	}

	for (i = 0; i < ROWS; i++)
		delete[] arr[i];
	delete[] arr;

	cout << endl << "��������� ���������!" << endl;

	system("pause");
	return 0;
}