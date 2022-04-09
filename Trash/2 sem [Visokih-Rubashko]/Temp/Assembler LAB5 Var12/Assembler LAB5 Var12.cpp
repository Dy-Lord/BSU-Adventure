#include<iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	short arr[4][6] = { {-1,2,0,-12,5,-10},{-5,2,1,-4,-16,-13},{-2,-5,-8,-1,5,-4},{-8,-6,1,-12,-5,-3} };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
			cout << arr[i][j] << "  ";
		cout << endl;
	}

	short num = 0;
	int str = 0, col = 0;
	int tstr = 0, tcol = 0;

	_asm
	{
		mov edi, 0
		lea eax, arr
		mov dx, 0
		mov esi, 0

		_while:

		mov bx, word ptr[eax][edi * 2]

			cmp bx, 0
			jge _Con
			cmp bx, dx
				jge _move
			mov dx, bx
				mov tstr, esi
				mov tcol, edi

			_move:

		add eax, 12
			inc esi
			cmp esi, 4
			jne _while

			mov num, dx
			mov ecx, tstr
			mov str, ecx
			mov ecx, tcol
			mov col, ecx

			_Con:
		mov dx, num

		inc edi
			lea eax, arr
			mov esi, 0
			cmp edi, 6
			jne _while
	}
	if (num == 0)
		cout << "Nuzhnih stolbcov net" << endl;
	else
	{
		cout << "Znachenie minimalnogo elementa v otricatelnom stolbce: " << num << endl;
		cout << "Koordinati stroki(nachinaia s nulia):" << str << endl;
		cout << "Koordinati stolbca(nachinaia s nulia): " << col << endl;
	}

	return 0;
}