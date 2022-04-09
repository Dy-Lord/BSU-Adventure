#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE 
#pragma warning(disable : 4996)
#include<iostream>
#include<string>
#include<windows.h>
using namespace std;


int maxdifnum(string &str)
{
	char prep[] = " ,.)('&!?#;№:*@$^-=+][}{<>~`/";
	int poz = 0,pozx=0;
	int size = strlen(prep);
	str += prep;
	int len = str.length();
	int aim = 1, w = 0, aim2=1;
	string num1, num2,strcopy,temp;
	int doublestr[1000];
	int MAXPOZ = 0, MAXLEN = 0;
	int k = 0, copy = 1;
	int NUMMAX1, NUMMAX2;
	strcopy = str;
	int a, j = -1, stop = 0;

	while (k != len-1)
	{


		if (aim2)
		{
			for (int i = 0; i < size; i++)
			{
				a = -1;
				do {
					a = strcopy.find(prep[i], a + 1);
					if (a != -1)
						strcopy[a] = ' ';
				} while (a != -1);

			}
		}

		if (aim2)
		{
			if (strcopy[0] != ' ')
				poz = 0;
			else
				for (k = poz; k < len; k++)
				{
					j = strcopy.find(' ', k);
					if ((j != -1) && (strcopy[j + 1] != ' '))
					{
						poz = j + 1;
						aim = 1;
						break;
					}
				}
		}
		
	if(!aim2)
		for (k=poz; k < len; k++)
		{
			j = strcopy.find(' ', k);
			if ((j != -1) && (strcopy[j + 1] != ' '))
			{
				poz = j+1;
				aim = 1;
				break;
			}
		}
		
		if (aim2)
			if (j == len-1)
				return 0;
			
		if(!aim2)
				if (j == len-1)
					break;

				//aim2 = 0;
		pozx = strcopy.find(' ', poz + 1);
		
		
		if (aim2)
		{
			num1 = str.substr(poz, pozx - poz);

			temp = num1;

			NUMMAX1 = num1.length();
			for (int l = 0; l <= temp.length(); l++)
				for (int g = l + 1; g <= temp.length();)
				{
					if (temp[l] == temp[g])
					{
						NUMMAX1--;
						temp.erase(g, 1);
					}
					else
						g++;
				}

			temp.clear();

			MAXLEN = num1.length();
			MAXPOZ = poz;
			doublestr[w] = poz;
			w++;
			doublestr[w] = num1.length();
		}

		if (aim2)
		{
			for (int k = pozx; k < len; k++)
			{
				j = strcopy.find(' ', k);
				if ((j != -1) && (strcopy[j + 1] != ' '))
				{
					poz = j + 1;
					break;
				}
			}

			if (j == len - 1)
				break;

			pozx = strcopy.find(' ', poz + 1);
		}

		num2 = str.substr(poz, pozx - poz);

		temp = num2;

		NUMMAX2 = num2.length();
		for (int l = 0; l <= temp.length(); l++)
			for (int g = l + 1; g <= temp.length();)
			{
				if (temp[l] == temp[g])
				{
					NUMMAX2--;
					temp.erase(g, 1);
				}
				else
					g++;
			}

		temp.clear();
		
		if (NUMMAX1 == NUMMAX2)
		{
			w++;
			doublestr[w] = poz;
			w++;
			doublestr[w] = num2.length();
			copy++;
		}

		if (NUMMAX2 > NUMMAX1)
		{
			num1.clear();
			num1 = num2;
			NUMMAX1 = NUMMAX2;
			MAXLEN = num2.length();
			MAXPOZ = poz;
			copy = 1;
			////
			w = 0;
			memset(doublestr, 0, 100 * sizeof(int));
			doublestr[w] = poz;
			w++;
			doublestr[w] = num2.length();
		}


		poz = pozx;
		aim2 = 0;
		//k = poz;
	}

	str.erase(len - size, size);

	if (copy == 1)
		str.erase(MAXPOZ, MAXLEN);
	else
		for (int o = w; o >= 0; o -= 2)
			str.erase(doublestr[o-1], doublestr[o]);

	return 1;
}

int main()
{

	string str,f;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Введите строку" << endl;
	getline(cin, str);

	
	if (maxdifnum(str))
	{
		cout << "Отредактированная строка:" << endl;
		cout << str << endl;
	}
	else
		cout << "ОШИБКА---Строка пустая или содержит только символы разделители!";
	
	cout << endl;

	system("pause");
	return 0;
}
