#include<iostream>
#include<Windows.h>
#include<exception>
#include"MatX.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try {
		MatX a(3, 3, 1), b(3, 4, 2), c(3,3,0), h;

		cout << 'a' << endl;
		cout << a << endl;  
		
		cout << 'b' << endl;
		cout << b << endl;            

		cout << "h������������ ������� a ������� h" << endl;
		h = a;                      
		cout << h << endl;


		cout << "��������� ������" << endl;
		cout << a * b << endl;       

		cout << "��������� ������� �� ���������" << endl;
		cout << a * 4 << endl;

		cout << "��������� ��������� �� �������" << endl;
		cout << 4 * a << endl;

		b *= 2;
		a *= b;

		cout << "b*=2" << endl;
		cout << b << endl;

		cout << "a*=b" << endl;
		cout << a << endl;

		cout << "����� ������" << endl;
		cout << a + b << endl;

		cout << "����� ��������� � �������" << endl;
		cout << 10 + a << endl;

		cout << "����� ������� � ���������" << endl;
		cout << a + 10 << endl;

		cout << "��������� ������" << endl;
		cout << (a == b) << endl;
		cout << (a != b) << endl;

	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	system("pause");
	return 0;
}