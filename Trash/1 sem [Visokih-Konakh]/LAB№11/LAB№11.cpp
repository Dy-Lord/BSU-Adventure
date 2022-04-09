/*
lolol frgr erdf lolol fs 3432
lolololol lolololol rg jisf gre jf 3 fsrg ef 3
weew reer weew reer
12 21 we ew
31
er 12345 54321 y er
olret terlo
*/

#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
#include<stdio.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream input("input.txt", ios::in);
	ofstream output("output.txt", ios::out);
	
	if (!input)
	{
		output << "Ошибка---входной файл не найден!";
		output.close();
		return 0;
	}

	string str, inputstr;
	string sub = " ,.;:";
	string temp1, temp2;
	int poz1 = 0, poz2 = 0;
	int subpoz1 = 0, subpoz2 = 0;
	int len1, len2, count = 0;

	if (input.eof())
	{
		output << "Ошибка---входной файл пустой!";
		input.close();
		output.close();
		return 0;
	}

	ofstream temple("temple.txt", ios::out);

	while (getline(input, str))
	{
		if (str == "") { count++; continue; }

		str += ' ';

		count++;
		while ((poz1 = str.find_first_not_of(sub, poz1)) != string::npos)
		{
			subpoz1 = str.find_first_of(sub, poz1);
			len1 = subpoz1 - poz1;
			temp1 = str.substr(poz1, len1);
			int temppoz = subpoz1;
			while ((poz2 = str.find_first_not_of(sub, subpoz1)) != string::npos)
			{
				subpoz2 = str.find_first_of(sub, poz2);
				len2 = subpoz2 - poz2;
				temp2= str.substr(poz2, len2);
				if (len1 != len2) { subpoz1 = subpoz2; continue; }
				else
				{
					bool stop = 0;
					for (int i = 0; i < len1; i++)
						if (temp1[i] != temp2[len1 - 1 - i]) { stop = 1; break; }
		
					if (stop) subpoz1 = subpoz2;
					else
					{
						output << count << "->" << temp1 << ' ' << temp2 << endl;
						str.erase(poz2, len2);
						str.erase(poz1, len1);
						temppoz = 0;
						break;
					}
				}
			}
			poz1 = temppoz;
		}
		temple << str << endl;
		poz1 = 0;
	}

	temple.close();
	input.close();
	output.close();

	ifstream templel("temple.txt", ios::in);
	ofstream unput("input.txt", ios::out | ios::trunc);
	string copy;

	while (getline(templel, str))
	{
		unput << str << endl;;
	}

	templel.close();
	unput.close();
	remove("temple.txt");
	return 0;
}