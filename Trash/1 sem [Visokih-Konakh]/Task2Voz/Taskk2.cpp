#include<iostream>
#include<Windows.h>
using namespace std;
int main()
{
	SetConsoleOutputCP(1251);
	int N;
	cout << "������� ������������� ����� �����" << endl;
	cin >> N;
	N = abs(N);
	int U, T, H, TH;
	U = N % 10; //�������
	N = N / 10;
	T = N % 10; //�������
	N = N / 10;
	H = N % 10; //�����
	TH = N / 10; //������
	int sum = U + T + H + TH;
	int rith = U * 1000 + T * 100 + H * 10 + TH;
	int left1 = H * 1000 + TH * 100 + U * 10 + T;
	int left2 = TH * 1000 + T * 100 + H * 10 + U;
	int left3 = T * 1000 + U * 100 + TH * 10 + H;
	cout << "����� ���� ����� = " << sum << endl;
	cout << "�����, ���������� ��� ��������� ��� ���� ������ ������ = " << rith << endl;
	cout << "�����, ���������� ��� ������������ ������ � ������, ������� � �������� ���� = " << left1 << endl;
	cout << "�����, ���������� ��� ������������ ������ � ������� ���� = " << left2 << endl;
	cout << "�����, ���������� ��� ������������ ���� ������ � ���� ��������� ���� = " << left3 << endl;
	system("pause");
	return 0;
}