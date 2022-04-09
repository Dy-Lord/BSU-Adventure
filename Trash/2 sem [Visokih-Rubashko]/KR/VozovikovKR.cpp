#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<deque>
#include<map>
#include<set>
#include<string>
#include<Windows.h>

using namespace std;


void VIEW(const map<string, deque<pair<string, string>>>& ob)
{
	bool aim = false;
	for (auto el : ob)
	{
		cout << "Имя пациента: " << '\t' << el.first << '\n';
		cout << "Врач --- Дата приёма" << '\n';
		for (auto ul : el.second)
		{
			cout << ul.first << '\t' << ul.second << '\n';
			aim = true;
		}
		cout << "\n";
	}

	if (aim)
		cout << "\n";
	else
		cout << "Приёмы у врачей отсутствуют" << "\n";
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	map<string, deque<pair<string, string>>> BLOCK;
	map<string, deque<pair<string, string>>>::iterator BIT;
	deque <pair<string, string>> DTVR;

	fstream input("DATA.txt");
	if (!input)
	{
		cout << "Ошибка файла" << endl;
		system("pause");
		return 0;
	}

	bool aim = false;
	int poz1 = 0, subpoz1 = 0, len1, count = 0;
	string str, temp1;
	string sub = "*";
	string NAME,VRNAME,DATA;
	
	while (getline(input, str))
	{
		str += '*';

		while ((poz1 = str.find_first_not_of(sub, poz1)) != std::string::npos)
		{
			subpoz1 = str.find_first_of(sub, poz1);
			len1 = subpoz1 - poz1;
			temp1 = str.substr(poz1, len1);
			count++;

			if (count == 1)
				NAME = temp1;
			else
				if (count == 2)
					VRNAME = temp1;
				else
					if (count == 3)
						DATA = temp1;

			poz1 = subpoz1;
		}

		if (count < 3)
		{
			cout << "Wrong count of information!" << endl;
			return 0;
		}
		
		if ((BIT = BLOCK.find(NAME)) == BLOCK.end())
		{
			DTVR.push_back(make_pair(VRNAME, DATA));
			BLOCK.emplace(NAME, DTVR);
		}
		else
		{
			BIT->second.push_back(make_pair(VRNAME, DATA));
		}

		DTVR.clear();
		count = 0;
		poz1 = 0;
	}
	input.close();

	////////////////////////////////////////////////////////////////////////////////////

	VIEW(BLOCK);

	set<string> Names;
	int COUNTMIN = BLOCK.begin()->second.size();
	Names.emplace(BLOCK.begin()->first);

	for (auto el : BLOCK)
		if (el.second.size() < COUNTMIN)
		{
			COUNTMIN = el.second.size();
			Names.clear();
			Names.emplace(el.first);
		}
		else
			if (el.second.size() == COUNTMIN)
				Names.emplace(el.first);

	cout << "Пациенты, у которых меньше всего приёмов" << endl;
	for (auto el : Names)
	{
		cout << el << '\t';
		aim = true;
	}

	if (!aim)
		cout << "Соответствующих пациентов не найдено!" << endl;
	aim = false;
	cout << endl;
	////////////////////////////////////////////////////////////////////////////////////

	map<string, set<string>, less<string>> Vnames;
	map<string, set<string>, less<string>>::iterator VIT;

	for (auto el : BLOCK)
		for (auto ul : el.second)
			if ((VIT = Vnames.find(ul.first)) == Vnames.end())
			{
				set<string> MF;
				MF.emplace(el.first);
				Vnames.emplace(ul.first, MF);
			}
			else
				VIT->second.emplace(el.first);
	
	cout << endl;
	cout << endl;
	cout << "Введите ФИО пациента" << endl;
	cout << (NAME = "Петров Д.Ф.") << endl;

	cout << "Врачи, которых посещал указанный пациент: " << endl;
	for (auto el : Vnames)
		for(auto ul:el.second)
			if (ul == NAME)
			{
				cout << el.first << '\t';
				aim = true;
			}

	if (!aim)
		cout << "Соответствующих врачей не найдено!" << endl;
	aim = false;
	cout << endl;
	////////////////////////////////////////////////////////////////////////////////////

	cout << endl;
	cout << endl;
	cout << "Фамилии всех врачей: " << endl;

	for (auto el : Vnames)
	{
		cout << el.first << '\t';
		aim = true;
	}

	if (!aim)
		cout << "Соответствующих врачей не найдено!" << endl;
	aim = false;
	cout << endl;

	////////////////////////////////////////////////////////////////////////////////////

	cout << endl;
	cout << endl;

	cout << "Фамилии всех врачей, которых посетил каждый пациент : " << endl;

	for (auto el : Vnames)
		if (BLOCK.size() == el.second.size())
		{
			cout << el.first << endl;
			aim = true;
		}


	if (!aim)
		cout << "Соответствующих врачей не найдено!" << endl;
	aim = false;
	cout << endl;

	////////////////////////////////////////////////////////////////////////////////////

	cout << endl;
	cout << endl;

	cout << "Введите пациента: " << endl;
	cout << endl;
	cout << (NAME = "Петров Д.Ф.") << endl;
	

	cout << "Введите врача для удаления его данных из записи пациента: " << endl;
	cout << endl;
	cout << (VRNAME = "Авдеев А.А.") << endl;

	for (BIT = BLOCK.begin(); BIT != BLOCK.end();BIT++)
	{
		if (BIT->first == NAME)
			if (find_if(BIT->second.begin(), BIT->second.end(), [=](pair<string, string> s) {return VRNAME == s.first; }) != BIT->second.end())
			{
				BIT->second.erase(find_if(BIT->second.begin(), BIT->second.end(), [=](pair<string, string> s) {return VRNAME == s.first; }));
				BIT = BLOCK.begin();
				aim = true;
			}
	}

	if (aim)
		cout << "Удаление успешно!" << endl;
	else
		cout << "Данные не найдены!" << "\n";
	cout << endl;

	VIEW(BLOCK);

	system("pause");
	return 0;
}