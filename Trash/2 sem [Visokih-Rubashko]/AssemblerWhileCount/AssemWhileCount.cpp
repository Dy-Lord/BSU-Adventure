#include<iostream>
#include<Windows.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	W:
	cout << "Введите натуральное число:" << endl;

	int x, result = 0, n = 9;
	
	cin >> x;

	if (x <= 0)
	{
		cout << "Введённое число не натуральное!" << endl << endl;
			goto W;
	}

	while (n>=0)
	{
		int temp = x;
		while (temp != 0)
		{
			if (temp % 10 == n)
			{
				result++;
				break;
			}
			temp /= 10;
		}
		n--;
	}

	cout << "Количество различных цифр в натуральном числе:" << endl;
	cout << "C++ result = " << result << endl;
	result = 0;
	n = 9;

	_asm
	{
		mov ebx, 10
		
		O:
		cmp n, 0
		jl F

		mov eax, x
			C :
		cmp eax, 0
		je T
		
			cdq
			div ebx
			cmp edx, n
			je B
			jmp C

			B:
		inc result
		T:
		dec n
			jmp O

		F:
	}

	cout << "Assembler result = " << result << endl;

	system("pause");
	return 0;
}