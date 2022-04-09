#include<iostream>
#include<Windows.h>
#include<ctime>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

Ret:

	cout << "Часть А" << endl;
	cout << endl;

	cout << "Введите положительный предел поиска больше 0 , меньше (10 000), так как большие автоморфные числа найти невозможно из-за ограничения длины переменных (unsigned int):" << endl;

	unsigned int x;
	cin >> x;

	if (x <= 0 || x>10000)
	{
		system("cls");
		cout << endl;
		cout << "Неверный предел!" << endl << endl;
		goto Ret;
	}

	unsigned int array1[9];
	unsigned int count1 = 1;
	unsigned int count2 = 0;

	_asm
	{
		mov array1[0], 0
		cmp x, 1
		je Z

		mov ecx, 1
		mov esi, 1
		X:

		mov eax, ecx
			mov count2, 0
			T :
			cmp eax, 0
			je K

			mov ebx, 10
			cdq
			idiv ebx
			inc count2
			jmp T
			K:

		mov eax, ecx
			imul eax

			mov ebx, 1
			G:
		imul ebx, 10
			dec count2
			cmp count2, 0
			jne G

			cdq
			idiv ebx

			cmp ecx, edx
			jne V
			inc count1
			mov array1[esi * 4], ecx
			inc esi
			V:

		inc ecx
		cmp ecx, x
		jne X

			Z:
	}
	
	cout << endl;
	cout << "Автоморфные числа на заданном ограничении: " << endl;

	for (int i = 0; i < count1; i++)
		cout << array1[i] << " ";
	cout << endl;

	short int array2[100];
	
	srand(time(NULL));

	for (int i = 0; i < 100; i++)
		array2[i] = rand() % 200 - 100;

	////////////////////////////////////////////////////////////////////////////////

	cout << endl;
	cout << "Часть B" << endl;
	cout << endl;

	cout << "Сгенерированный массив:" << endl;
	for (auto el : array2)
		cout << el << ' ';
	cout << endl;

	_asm
	{
		mov eax, 0
		mov ebx, 0
		mov dx, array2[0]
		mov esi, 0
		L:
	S:
		cmp dx, array2[esi*2]
			jl C
			mov dx, array2[esi * 2]
			mov eax, esi
			C :

		inc esi
			cmp esi, 100
			jne S

			cmp ebx, eax
			je U
			mov cx, array2[ebx * 2]
			mov array2[ebx * 2], dx
			mov array2[eax * 2], cx
			U:

			inc ebx
			cmp ebx, 100
			je E
		
			mov esi, ebx
			mov dx, array2[esi * 2]
			jmp L

			E:
	}

	cout << endl;
	cout << "Отсортированный массив:" << endl;
	for (auto el : array2)
		cout << el << ' ';
	cout << endl;

	////////////////////////////////////////////////////////////////////////////////

	unsigned short int array3[100];
	unsigned int minarr[100] = { 0 };
	unsigned short int count, min;

	for (int i = 0; i < 100; i++)
		array3[i] = rand() % 20;

	cout << endl;
	cout << "Часть C" << endl;
	cout << endl;

	cout << "Сгенерированный массив:" << endl;
	for (auto el : array3)
		cout << el << ' ';
	cout << endl;

	_asm
	{
		mov ax, array3[0]
		mov esi, 1

		Y:
		cmp ax, array3[esi * 2]
			jl CC

			cmp ax, array3[esi * 2]
			jne N
			inc count
			jmp H
			N :

			mov count, 1
			mov ax, array3[esi * 2]
			mov min, ax
			jmp H
			CC :
			
			H:

		inc esi
			cmp esi, 100
			jne Y	
	}
	cout << endl;
	cout << "Минимальное значение в массиве: " << min << endl;
	cout << "Количество минимальных значений: " << count << endl;
	cout << endl;
	_asm
	{
		mov dx, min
		mov esi, 0
		mov edi, 0

		M:
		cmp dx, array3[esi * 2]
			jne B
			mov minarr[edi * 4], esi
			inc edi

			B:
		inc esi
			cmp esi, 100
			jne M
	}
	cout << endl;
	cout << "Индексы минимальных элементов:" << endl;
	for (int i = 0; i < count; i++)
		cout << minarr[i] << ' ';
	cout << endl;

	system("pause");
	return 0;
}