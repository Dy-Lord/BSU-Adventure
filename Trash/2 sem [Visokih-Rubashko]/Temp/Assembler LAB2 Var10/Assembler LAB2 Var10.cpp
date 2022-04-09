#include<iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	cout << "F10(õ, ó) = \n x^2-11x+8, esli x < 5, \n x^3, elsi x = 5, \n 3+5x-(x-x^2+2), esli x > 5\n";
	cout << "x= ";

	int x, Cres, Ares;
	cin >> x;

	if (x < 5)
		Cres = x * x - 11 * x + 8;
	else
		if (x == 5)
			Cres = x * x * x;
		else
			Cres = 1 + 5 * x - x + x * x;

	cout << "C++   " << Cres << endl;

	_asm
	{
		mov eax, x
		mov ebx, x
		imul ebx, eax

		cmp eax, 5
		jne net
		cdq
		imul ebx, eax
		jmp stop

		net:
		cmp eax,5
			jl men

			add ebx, 1
			sub ebx, eax
			imul eax, 5
			add ebx, eax
			jmp stop

			men:

		add ebx, 8
			imul eax, 11
			sub ebx, eax

	stop:
		mov Ares, ebx
	}

	cout << "Assembler   " << Ares << endl;

	return 0;
}