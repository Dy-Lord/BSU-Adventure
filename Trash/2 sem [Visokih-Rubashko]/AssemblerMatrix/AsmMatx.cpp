#include<iostream>
#include<Windows.h>
#include<ctime>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const int m = 5;
	const int n = 6;

	short int arr[m][n] = { {-1,2,0,-12,5,0},
							{9,0,0,7,0,0},
							{9,-5,-8,0,5,0},
							{-7,-6,1,-12,5,0},
							{1,2,0,2,5,0} };

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
			cout<< arr[i][j] << '\t';
		cout << endl;
	}

    int  index[n];
	int plus = 0, min = 0, count = 0;

	_asm
	{
		xor esi, esi
		xor edi, edi
		push 0

		lea eax, arr
		
		S:
		
		
		mov bx, word ptr [eax][edi * 2]

		cmp bx, 0
			je FF

			cmp bx, 0
			jl M
			inc plus
			jmp FF
			M:
		inc min

			FF:
		
		add eax, 12
		inc esi
		cmp esi, m
			jne S

			mov edx,plus

			cmp edx, 0
			je C

			cmp edx, min
			jne C
			pop esi
			mov index[esi * 4], edi
			inc esi
			push esi
			C:

		inc edi
			lea eax, arr
			xor esi, esi
			mov plus, 0
			mov min, 0
			cmp edi, n
			jne S

			pop count
	}

	cout << endl;
	if (count != 0)
	{
		cout << "Индексы столбцов, содержащих равное количество положительных и	отрицательных элементов" << endl;
		cout << endl;

		for (int i = 0; i < count; i++)
			cout << index[i] << '\t';
	}
	else
		cout << "В матрице нет столбцов, содержащих равное количество положительных и отрицательных элементов" << endl;

	cout << endl;

	system("pause");
	return 0;
}