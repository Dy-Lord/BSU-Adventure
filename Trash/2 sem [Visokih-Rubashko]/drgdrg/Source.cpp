#include <iostream>
#include <cmath> 
#include <ctime> 
#include<Windows.h>
using namespace std;
//����� ��������� ������� �� ������� [a, b]

//����� ���������� ����������� ������, ��������� �� N �������� ����� ������ �
//����, ������ �� ���� ��� ��������, ������ ������� ��������� � ���������[left, right],
//left � right � ���� ��������� ���������.

//�������������� � ����� ������� ��������
//��������� ������.

//������ - ��������� ���������� � ���������������� � ���������
//������������ ������ �������.

// size - 1 byte
//������ ��������� ����������� ��������� ����� �� �++. ++
//���������� ���������� � ������ ���� � ������������� �������. ++

extern "C" int __fastcall deletelr(signed char* array, int size, signed char a, signed char b);
extern "C" int __stdcall deletelr1(signed char* array, int size, signed char a, signed char b);
extern "C" int __cdecl deletelr2(signed char* array, int size, signed char a, signed char b);

int main() {
	setlocale(LC_ALL, ".1251");
	const int MAX = 10;
	signed char arry[MAX] = { 1,7,3,4,8,4,-1,5,4,7 };
	  srand(time(NULL));
	  for (int i = 0; i < MAX; i++)
		  arry[i] = -10 + rand() % (21);
	 
	cout << "�������� ��������������� ������" << endl;
	int k;
	for (int i = 0; i < MAX; i++)
	{
		k = arry[i];
		cout << k << " ";
	}
	cout << endl;


	signed char left = 2;
	signed char right = 8;
	int l = left;
	int r = right;
	cout << "������ ��� ������: " << l << "-" << r << endl;
	
	signed char s = deletelr(arry, MAX, left, right);
	int ss = s;
	cout << ss << endl;

	cout << "������ ����� ���������" << endl;

	for (int i = 0; i < MAX; i++)
	{
		k = arry[i];
		cout << k << " ";
	}

	cout << endl;

	system("pause");
	return 0;
}