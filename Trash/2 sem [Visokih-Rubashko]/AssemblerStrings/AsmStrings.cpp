#include <iostream>
#include<ctime>
#include<Windows.h>

using namespace std;

#define SIZE 100

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	char str[SIZE + 1];
	int count = 0;

	cout << "Введите слова разделённые пробелами:" << endl << endl;

	cin.getline(str, SIZE);
	cout << endl;

	int len = strlen(str);

	_asm
	{
		xor ebx, ebx

		cld

		mov ecx, len
		mov al, ' '
		lea edi, str

		B:

		repe scasb
			and cx, cx
			jz E
			inc count
			repne scasb
			and cx, cx
			jnz B

			E:
	}

	if (count != 0)
		cout << "Количество слов в строке:" << '\t' << count << endl;
	else
		cout << "В строке нет слов!" << endl;

	system("pause");
	return 0;
}