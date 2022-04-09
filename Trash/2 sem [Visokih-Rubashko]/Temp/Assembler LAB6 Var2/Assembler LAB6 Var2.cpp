#include<iostream>
#include<ctime>
using namespace std;
extern "C" void __stdcall matrixswtitch1(unsigned int*, int, int);
extern "C" void __cdecl matrixswtitch2(unsigned int*, int, int);
extern "C" void __fastcall matrixswtitch3(unsigned int*, int, int);
int main()
{
	setlocale(LC_ALL, "ru");
	const int N = 5;
	unsigned int array[N][N];
	int per = 3;
	srand(time(NULL));
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			array[i][j] = rand() % 10;
	cout << "Matrica" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << array[i][j] << "  ";
		cout << endl;
	}

	cout << "Vvedite nomer stolbca(srtroki)(indeksacia nachinaetsia s 0):" << endl;
	cin >> per;
	if (per >= N)
	{
		cout << "Indeks stolbca(srtroki) previshaet razmer matrici N!" << endl;
		return 0;
	}
	cout << "1)STDCALL" << endl << "2)CDECL" << endl << "3)FASTCALL" << endl;
	int sw;
	cin >> sw;

	if (sw == 1)
		matrixswtitch1(*array, N, per);
	else
		if (sw == 2)
			matrixswtitch2(*array, N, per);
		else
			matrixswtitch3(*array, N, per);

	cout << "Preobrazovanaia matrica:" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << array[i][j] << "  ";
		cout << endl;
	}

	return 0;
}