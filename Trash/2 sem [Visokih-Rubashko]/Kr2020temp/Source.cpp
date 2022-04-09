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

class BOOK
{
public:
	string InvenNumber;
	string Name;
	deque <string> Autors;

	BOOK() {};
	BOOK(string number, string name, deque<string> autors)
	{
		InvenNumber = number;
		Name = name;
		Autors = autors;
	}

	friend std::ostream& operator << (std::ostream& os, const BOOK& ob)
	{
		os << "Invetar Number" << '\t' << ob.InvenNumber << '\t' << "Name" << '\t' << ob.Name << '\t' << "Autors:" << '\t';
		bool aim = false;
		for (auto el : ob.Autors)
		{
			os << el << "<->";
			aim = true;
		}

		if (aim)
			os << "\n";
		else
			os << "None Autors" << "\n";

		return os;
	}
};

string CheckReg(string str)
{
	string s = str;
	transform(s.begin(), s.end(), s.begin(), tolower);
	return s;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector <BOOK> BOOKS;

	fstream input("input.txt");
	if (!input)
	{
		cout << "Ошибка файла" << endl;
		system("pause");
		return 0;
	}

	int poz1 = 0, subpoz1 = 0, len1, count = 0;
	string str, temp1;
	string sub = ";";
	string NUMBER, NAME;
	deque <string> AUTORS;

	while (getline(input, str))
	{
		str += ';';

		while ((poz1 = str.find_first_not_of(sub, poz1)) != std::string::npos)
		{
			subpoz1 = str.find_first_of(sub, poz1);
			len1 = subpoz1 - poz1;
			temp1 = str.substr(poz1, len1);
			count++;

			if (count == 1)
				NUMBER = temp1;
			else
				if (count == 2)
					NAME = temp1;
				else
					if (count >= 3)
						AUTORS.push_back(temp1);

			poz1 = subpoz1;
		}

		if (count < 2)
		{
			cout << "Wrong count of information!" << endl;
			return 0;
		}

		BOOK two(NUMBER, NAME, AUTORS);
		BOOKS.push_back(two);

		AUTORS.clear();
		count = 0;
		poz1 = 0;
	}
	input.close();

	////////////////////////////////////////////////////////////////////////////////////

	sort(BOOKS.begin(), BOOKS.end(), [](BOOK s1, BOOK s2) {
		if (CheckReg(s1.Name) == CheckReg(s2.Name))
			return s1.InvenNumber < s2.InvenNumber;
		else
			return s1.Name < s2.Name;
		});


	cout << "Результаты части №1: " << endl << endl;
	bool aim = false;
	for (auto el : BOOKS)
	{
		cout << el << '\n';
		aim = true;
	}

	if (!aim)
		cout << "None Data" << endl;
	aim = false;
	//////////////////////////////////////////////////////////////////////////////////////

	map<string, set<string>, less<string>> Names;
	map<string, set<string>, less<string>>::iterator NameIt;
	
	for (auto el : BOOKS)
		for (auto ul : el.Autors)
		{
			if ((NameIt = Names.find(CheckReg(ul))) == Names.end())
			{
				set<string> MF;
				MF.emplace(el.InvenNumber);
				Names.emplace(make_pair(CheckReg(ul), MF));
			}
			else
			{
				NameIt->second.emplace(el.InvenNumber);
			}
		}

	cout << "Результаты части №2: " << endl << endl;

	cout << "Имена водителей маршрутов: " << endl;
	for (auto el : Names)
	{
		cout << el.first << endl;
		aim = true;
	}

	if (!aim)
		cout << "None Data" << endl;
	aim = false;
	cout << endl;
	////////////////////////////////////////////////////////////////

	cout << "Введите имя водителя: " << endl << endl;
	string Vod;
	cin >> Vod;
	cout << endl;
	if ((NameIt = Names.find(CheckReg(Vod))) != Names.end())
	{
		cout << "Маршруты, на которых не работает данный водитель: " << endl;
		for (auto el : BOOKS)
		{
			if (NameIt->second.find(el.InvenNumber) == NameIt->second.end())
			{
				cout << el << endl;
				aim = true;
			}
		}
	}
	else
		cout << "Водитель не найден!" << endl;
	
	if (!aim)
		cout << "Соответствующих маршрутов не найдено!" << endl;
	aim = false;
	cout << endl;
	//////////////////////////////////////////////////////////////////////////

	cout << "Водители, которые работают на всех маршрутах: " << endl;

	bool yep = false;

	for (auto el : Names)
		if (BOOKS.size() == el.second.size())
		{
			cout << el.first << endl;
			aim = true;
		}

	
	if (!aim)
		cout << "Соответствующих водителей не найдено!" << endl;		
	aim = false;
	cout << endl;
	//////////////////////////////////////////////////////////////////////////
	cout << "Результаты части №3: " << endl << endl;

	cout << "Введите название маршрута:" << endl;
	string Marsh;

	cin >> Marsh;
	cout << endl;

	int COUNT = 0;

	COUNT = count_if(BOOKS.begin(), BOOKS.end(), [=](BOOK s) {return CheckReg(s.Name) == CheckReg(Marsh); });
		

		if (COUNT != 0)
			cout << "Количество маршрутов по заданному названию: " << COUNT << endl;
		else
			cout << "Соответствующих маршрутов не найдено!" << endl;

		cout << endl;
     /////////////////////////////////////////////////////////////////////////////
	cout << "Введите водителя для удаления его данных:" << endl;
	cout << endl;

	cin >> Vod;

	vector <BOOK>::iterator findhol;
	
	for (findhol = BOOKS.begin(); findhol != BOOKS.end(); findhol++)
	{
		if (find_if(findhol->Autors.begin(), findhol->Autors.end(), [=](string s) {return CheckReg(s) == CheckReg(Vod); }) != findhol->Autors.end())
		{
			findhol->Autors.erase(find_if(findhol->Autors.begin(), findhol->Autors.end(), [=](string s) {return CheckReg(s) == CheckReg(Vod); }));
			aim = true;
		}	
	}

	if (aim)
		cout << "Удаление успешно!" << endl;
	else
		cout << "Водитель не найден!" << "\n";
	cout << endl;

	for (auto el : BOOKS)
		cout << el << endl;

	system("pause");
	return 0;
}