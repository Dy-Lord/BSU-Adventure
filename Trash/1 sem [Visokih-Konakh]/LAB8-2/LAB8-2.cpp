#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE 
#pragma warning(disable : 4996)
#include<iostream>
#include<string.h>
#include<windows.h>

bool gog(int x)
{
	if (x % 2 == 0)
		return 1;
}

using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const int size = 300;
	char str[size], cstr[size];
	char abc[53] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
	char glasabs[13] = "euoaiyEUOAIY";
	int temp = 0, countabc = 0, countsrav = 0, glas = 0, sogl = 0, counttoken = 0;

	cout << "Введите строку" << endl;
	cin.getline(str, size);

	strcpy(cstr, str);

	char* one = strtok(cstr, " ");

	if (one == 0)
	{
		cout << "Строка пустая!" << endl;
		system("pause");
		return 0;
	}

	strcpy(cstr, str);

	int len = strlen(str);

	char* token = strtok(str, " ");
	char* temptoken = token;

	while (token != NULL)
	{
		
		int lenlen = strlen(token);
		int tlen = lenlen;
		for (temptoken; tlen; temptoken++,tlen--)
			for (int i = 0; i < 53; i++)
				if (*temptoken == abc[i])
					counttoken++;
				
		
		if (counttoken == lenlen)
		{
			countabc++;
			temptoken = token;
			tlen = lenlen;
			for (temptoken; tlen; temptoken++,tlen--)
				for (int i = 0; i < 13; i++)
					if (*temptoken == glasabs[i])
						glas++;

				if (gog(lenlen) && (lenlen - glas == lenlen / 2))
					countsrav++;
		}
		token = strtok(NULL, " ");
		temptoken = token;
		sogl = 0;
		glas = 0;
		counttoken = 0;
	}

	if (countabc == 0)
	{

		cout << "В строке нет латинских слов!" << endl;
		system("pause");
		return 0;
	}
	cout << "Количество слов содержащие только символы латинского алфавита = " << countabc <<endl;
	if (countsrav == 0)
		cout << "Из них нет слов с равным числом гласных и согласных букв " << endl;
	else
	cout << "Из них количество слов с равным числом гласных и согласных букв = " << countsrav << endl;
	system("pause");
	return 0;
}