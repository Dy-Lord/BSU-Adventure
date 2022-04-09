#include<iostream>
#include<ctime>
#include<limits.h>
using namespace std;
int SUMDEL(int a)
{
	int t = a / 2;
	int S = 0;
	for (int i = 1; i <= t; i++)
		if (a % i == 0)
			S += i;
	return S;
}

int main()
{
	setlocale(LC_ALL, "ru");
	int const SIZE = 4000;
	int const RANDNUM = 10000;
	int arr[SIZE];
	int sov[4]{0};
	int n, i, SORT = 0, j, count = 0, countcount = 0, uo=0;
	cout << "������� ���������� ��������� ������� (�� " << SIZE << " ���������) " << endl;
	cin >> n;
	if (n < 1)
	{
		cout << "������---������� �������� ���������� ��������� �������!" << endl;
		system("pause");
		return 0;
	}
	if (n > SIZE)
	{
		cout << "������---������� ������������ ���������� ��������� �������!" << endl;
		system("pause");
		return 0;
	}
	srand(time(NULL));

	for (i = 0; i < n; i++)
		cout << (arr[i] = rand() % RANDNUM + 1) << '\t';
	cout << endl;


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
		cout << (arr[i]) << '\t';
	cout << endl << endl;
	/////////////////////////////////////////////////////////////////////////
	for (i = 0; i < n; i++)
	{
		if (arr[i] == SUMDEL(arr[i]))
		{
			countcount++;
			for (int t = 0; t < 4; t++)
			{
				uo = 0;
				if (sov[t] != 0)
					continue;
				for (int e = 0; e < 4; e++)
					if (arr[i] == sov[e])
						uo++;
				if(uo)
					break;
				else
					sov[t] = arr[i];
					break;
			}
		}
	}
	if (countcount == false)
		cout << "� ������� ��� ����������� �����!" << endl;
	else
	{
		cout << "����������� ����� � �������: " << endl;
		for (int t = 0; t < 4; t++)
			if (sov[t] != 0)
				cout << sov[t] << endl;;
		cout << "���������� ����������� ����� � ������� = " << countcount << endl;
	}
	system("pause");
	return 0;
}