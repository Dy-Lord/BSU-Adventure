#include <iostream>
#include "DEREVO.h"
#include <Windows.h>
#include<fstream>

using namespace std;

void CONSOLEDATA(ROOT* list)
{
	cout << list->Info << '\t' << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream input("INPUT.txt", ios::in);
	ofstream output("OUTPUT.txt", ios::out);

	try
	{
		DEREVO one, two, tree;
		one.IMPORT(input, output);

		two.ADDINFO(13, cout);
		two.ADDINFO(16, cout);
		two.ADDINFO(1, cout);
		two.ADDINFO(2, cout);

		tree = two;
		tree.PRAMOBHOD(CONSOLEDATA);
		tree.DELINFO(13, cout);

		two.PRAMOBHOD(CONSOLEDATA);
		two.DELINFO(13, cout);
		two.PRAMOBHOD(CONSOLEDATA);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

	input.close();
	output.close();
	system("pause");
	return 0;
}