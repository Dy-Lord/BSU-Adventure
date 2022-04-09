#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include"Driver.h"
#include<typeinfo>

using namespace std;

void licsearch(CEmployee** arrp, int len, char* str)
{
	bool aim = false;
	for (int i = 0; i < len; i++)
	{
		if (typeid(*arrp[i]) == typeid(CDriver))
		{
			CDriver* S = dynamic_cast<CDriver*>(arrp[i]);
			if (strcmp(S->GetLicenceType(), str) == 0)
			{
				cout << *arrp[i] << endl;
				aim = true;
			}
		}

	}

	if (aim == false)
		cout << "Данных не найдено!" << endl;
}

void contractsearch(CEmployee** arrp, int len, int end)
{
	bool aim = false;

	for (int i = 0; i < len; i++)
	{
		if (typeid(*arrp[i]) == typeid(CTempDriver))
		{
			CTempDriver* S = dynamic_cast<CTempDriver*>(arrp[i]);
			
			if (S->GetContractEnd() >= end)
			{
				cout << *arrp[i] << endl;
				aim = true;
			}
		}

	}

	if (aim == false)
		cout << "Данных не найдено!" << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	CDriver one("Vasa", male, "AX"), two("Kola", male, "AX"), three("ANNA", female, "UX");
	CTempDriver four("Vlad", male, "UX", 12), five("Igor", male, "LX", 2), six("Yana", female, "LXX", 5);

	CEmployee* arrp[5];
	arrp[0] = &one;
	arrp[1] = &two;
	arrp[2] = &three;
	arrp[3] = &four;
	arrp[4] = &five;
	arrp[5] = &six;

	for (int i = 0; i < 6; i++)
		cout << *arrp[i] << endl;

	int Cdrcount = 0;
	int CTdrcount = 0;

	for (int i = 0; i < 6; i++)
	{
		if (typeid(*arrp[i]) == typeid(CDriver))
			Cdrcount++;
		else
			if (typeid(*arrp[i]) == typeid(CTempDriver))
				CTdrcount++;
	}

	cout << "Количество объектов CDriver: " << Cdrcount;
	cout << endl;
	cout << "Количество объектов CTempDriver: " << CTdrcount;

	cout << endl;
	cout << "Введите тип лицензи водителя:" << endl;
	char* num = new char[200];
	scanf("%s", num);

	licsearch(arrp, 6, num);
	delete[] num;
	cout << endl;

	cout << "Введите срок контракта водителя:" << endl;
	int end;
	cin >> end;
	contractsearch(arrp, 6, end);

	system("pause"); 
	return 0;
}