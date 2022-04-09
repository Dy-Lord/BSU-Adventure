#include <iostream>
#include "Spiski.h"
#include <Windows.h>
#include<fstream>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream input("input1.txt", ios::in);

	try
	{
	Spisok one,two,tree;
	
	one.ADDINFO("first", "1234", "12.12.12", "1");
	one.ADDINFO("second", "2234", "1.2.12", "2");
	one.ADDINFO("third", "3234", "152.562.1562", "4");

	two.ADDINFO("first", "1234", "12.12.12", "1");
    two.ADDINFO("first", "3234", "12.12.12", "1");
	two.ADDINFO("second", "3234", "1.2.12", "2");
	two.ADDINFO("third", "3234", "152.562.1562", "4");

	two = two + "Возовиков Никита Александрович 232323 12.12.12 32";
	cout << two << endl;

	two = two - "first";
	cout << two << endl;

	cout << endl;

	cout << (two == two) << endl;
	cout << (two == one) << endl;

	cout << endl;

	tree.IMPORT(input);
	cout << tree;
	cout << endl;

	tree.FINDDATA("11.12.2020");
	cout << endl;

	tree.FINDNUM("80293038811");
	cout << endl;

	tree.SORTINGDATA();
	cout << tree << endl;

	Spisok ew, re;

	cout << ew << endl;

	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

	input.close();
	system("pause");
	return 0;
}