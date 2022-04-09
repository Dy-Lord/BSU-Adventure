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
	int n, i, SORT = 0, j, count=0;
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
	cout << "����������� ����� � �������:" << endl;
	for (i = 0; i < n; i++)
	{
		if (arr[i] == SUMDEL(arr[i]))
		{
			if (count == arr[i])
				continue;
			cout << arr[i] << endl;
			count=arr[i];
		}
	}
	if (count == false)
		cout << "� ������� ��� ����������� �����!" << endl;
	system("pause");
	return 0;
}