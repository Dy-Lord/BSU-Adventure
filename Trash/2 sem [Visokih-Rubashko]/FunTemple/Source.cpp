#include<iostream>
#include<Windows.h>
#include<ctime>

using namespace std;

template <typename Type>

void swither(Type (*arr), int size, int trig)
{
	if (trig == 0)
		return;

	if (trig < 0)
		trig += size;

	for (int i = 0; i < trig; i++)
	{
		Type nexttemp;
		Type prevtemp = arr[size - 1];
		for (int g = 0; g < size; g++)
		{
			nexttemp = arr[g];
			arr[g] = prevtemp;
			prevtemp = nexttemp;
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int size;
	
	cout << "¬ведите размерность массива:" << endl;
	cin >> size;

	int* INTarr = new int[size];
	char* CHARarr = new char[size];
	double* DOUBLEarr = new double[size];

	srand(time(NULL));

	for (int i = 0; i < size; i++)
	{
		INTarr[i] = rand() % 101;
		DOUBLEarr[i] = (rand() % 101) + (static_cast <double> (rand()) / static_cast <double> (RAND_MAX));
		CHARarr[i] = rand() % (101) + 100;
	}

	for (int i = 0; i < size; i++)
	{
		cout << INTarr[i] << " ";
	}
	cout << endl << endl;

	for (int i = 0; i < size; i++)
	{
		cout << DOUBLEarr[i] << " ";
	}
	cout << endl << endl;

	for (int i = 0; i < size; i++)
	{
		cout << CHARarr[i] << " ";
	}
	cout << endl << endl;

	cout << "Bведите размерность сдвига:" << endl;
	int trig;
	cin >> trig;

	swither(INTarr, size, trig);
	swither(DOUBLEarr, size, trig);
	swither(CHARarr, size, trig);

	for (int i = 0; i < size; i++)
	{
		cout << INTarr[i] << " ";
	}
	cout << endl << endl;

	for (int i = 0; i < size; i++)
	{
		cout << DOUBLEarr[i] << " ";
	}
	cout << endl << endl;

	for (int i = 0; i < size; i++)
	{
		cout << CHARarr[i] << " ";
	}
	cout << endl << endl;

	delete[] INTarr;
	delete[] CHARarr;
	delete[] DOUBLEarr;
	system("pause");
	return 0;
}