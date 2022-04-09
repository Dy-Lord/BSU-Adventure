#include <iostream>
#include<ctime>
#include<Windows.h>

using namespace std;
extern "C" int __stdcall AreaSearchone(short*, short*, short, short);
extern "C" int __fastcall AreaSearchtwo(short*, short*, short, short);
extern "C" int __cdecl AreaSearchthree(short*, short*, short, short);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	short N;
	short V;
	int count = 0;

	cout << "������� ����������� �������:" << endl;
	cin >> N;
	cout << endl;

	cout << "������� �������� ������:" << endl;
	cin >> V;
	cout << endl;

	if (N <= 0 || N >= 32767 || V <= -32767 || V >= 32767)
	{
		system("cls");
		cout << "������������ ��������!" << endl;
		system("pause");
		return 0;
	}

	

	V = abs(V);

	short* array = new short[N];
	short* result = new short[N];

	for (int i = 0; i < N; i++)
		array[i] = rand() % 200-100;

	cout << "��������������� ������:" << endl;
	cout << endl;

	for (int i = 0; i < N; i++)
		printf("%d  ", array[i]);
	cout << endl;

	cout << "�������� ������� ��������������� ������� -V < a[i] < V:" << endl;
	cout << endl;
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	count = AreaSearchone(array, result, N, V);
	cout << "��������� _stdcall:" << endl;
	if (count != 0)
	{
		for (int i = 0; i < count; i++)
			printf("%d  ", result[i]);
		cout << endl;
	}
	else
		cout << "��������� ��������������� ������� ��������� �� �������!" << endl;
	cout << endl;
	count = 0;
	delete[] result;
	short* result1 = new short[N];
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	count = AreaSearchtwo(array, result1, N, V);
	cout << "��������� _fastcall:" << endl;
	if (count != 0)
	{
		for (int i = 0; i < count; i++)
			printf("%d  ", result1[i]);
		cout << endl;
	}
	else
		cout << "��������� ��������������� ������� ��������� �� �������!" << endl;
	cout << endl;
	count = 0;
	delete[] result1;
	short* result2 = new short[N];
	////////////////////////////////////////////////////////////////////////////////////////////////////
	count = AreaSearchthree(array, result2, N, V);
	cout << "��������� _cdecl:" << endl;
	if (count != 0)
	{
		for (int i = 0; i < count; i++)
			printf("%d  ", result2[i]);
		cout << endl;
	}
	else
		cout << "��������� ��������������� ������� ��������� �� �������!" << endl;
	cout << endl;

	delete[] array;
	delete[] result2;

	system("pause");
	return 0;
}