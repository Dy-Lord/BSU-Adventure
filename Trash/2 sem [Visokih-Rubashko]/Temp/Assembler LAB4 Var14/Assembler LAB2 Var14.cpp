#include<iostream>
#include<ctime>
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	cout << "Prostie trexznachnie chisla:" << endl;
	unsigned int arrray[1000];
	int len = 0;

	_asm
	{
		mov ebx, 100
		mov ecx, 2
		mov edi, 0

		_while:

		mov eax, ebx
			cdq
			idiv ecx
			mov esi, eax

		_prost:
		mov eax, ebx
			cdq
			idiv ecx
			cmp edx, 0
			je _cont

			inc ecx
			cmp ecx, esi
			jne _prost
		
			mov arrray[edi*4], ebx
			inc edi
			
			_cont:

		mov ecx, 2
		inc ebx
			cmp ebx, 1000
			jne _while

			mov len, edi
	}

	for (int i = 0; i < len; i++)
		cout << arrray[i] << "  ";

	cout << endl << endl;
	cout << "Sortirovka puzirkom:" << endl;

	short arrray2[50];
	srand(time(NULL));

	for (int i = 0; i < 50; i++)
		arrray2[i] = rand() % 100-50;
	cout << "Sgenerirovanii massiv:" << endl;
	for (int i = 0; i < 50; i++)
		cout << arrray2[i] << "  ";
	cout << endl;

	_asm
	{
	mov esi, 1
	
	_whone:
	mov edi, 0
_whtwo:
		mov eax, 50
		sub eax, esi

		cmp edi, eax
		je _cot

		mov cx, arrray2[edi * 2]
		cmp cx, arrray2[edi * 2 + 2]
		jle _no

		mov dx, arrray2[edi * 2 + 2]
		mov arrray2[edi * 2 + 2], cx
		mov arrray2[edi * 2], dx

		_no:
	inc edi
		cmp edi, eax
		jne _whtwo

		_cot:
		inc esi
		cmp esi, 50
		jne _whone
	}
	cout << endl;
	cout << "Otsortirovannii massiv:" << endl;
	for (int i = 0; i < 50; i++)
		cout << arrray2[i] << "  ";
	
	return 0;
}