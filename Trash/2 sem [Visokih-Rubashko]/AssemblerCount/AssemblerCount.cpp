#include<iostream>
#include<Windows.h>

using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	short a, b;
	int result;

	cout << "result = (a^2 + b^3) / 10 + b * (a^2 - 100)" << endl;

	cout << "Input a" << endl;
	cin >> a;

	cout << "Input b" << endl;
	cin >> b;


	if ((a < -32768 || a > 32768) || (b < -32768 || b > 32768))
	{
		cout << "Invalid variable value range!" << endl;
		system("pause");
		return 0;
	}

	result = (a * a + b * b * b) / 10 + b * (a * a - 100);

	cout << "C++ result = " << result << endl;

	_asm
	{
		/////////////////////////////////////////////////////
		movsx eax, b                                       //
		imul eax                                           //
		                                                   //
		movsx ebx, b                                       //    b ^ 3
		imul ebx                                           //
		                                                   //
		mov result, eax                                    //
		/////////////////////////////////////////////////////
		                                                   //
		movsx eax, a                                       //    a ^ 2
		imul eax                                           //
		/////////////////////////////////////////////////////
		add result, eax                                    //    (a ^ 2 + b ^ 3)
		/////////////////////////////////////////////////////
		                                                   //
		mov eax, result                                    //
		mov ebx, 10                                        //    (a ^ 2 + b ^ 3) / 10
		cdq                                                //
		idiv ebx                                           //
		                                                   //
		mov result, eax                                    //
		/////////////////////////////////////////////////////
		movsx eax, a                                       //    b*(a ^ 2 - 100)
		imul eax                                           //
		         										   //
		sub eax, 100                                       //
		                                                   //
		movsx ebx, b                                       //
		imul ebx                                           //
		                                                   //
		add result,eax                                     //
		/////////////////////////////////////////////////////
	}

	cout << "Assembler result = " << result << endl;

	system("pause");
	return 0;
}
