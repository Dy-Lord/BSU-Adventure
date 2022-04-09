#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<deque>
#include<map>
#include<string>
#include<Windows.h>

using namespace std;

struct BOOK
{
	string InvenNumber;
	string Name;
	string Year;
	deque <string> Autors;

	BOOK() {};
	BOOK(string number, string name, string year, deque<string> autors)
	{
		InvenNumber = number;
		Name = name;
		Year = year;
		Autors = autors;
	}

	friend std::ostream& operator << (std::ostream& os, const BOOK& ob)
	{
		os << "Invetar Number" << '\t' << ob.InvenNumber << '\t' << "Name" << '\t' << ob.Name << '\t' << "Year" << '\t' << ob.Year << '\t' << "Autors:" << '\t';
		bool aim = false;
		for(auto el: ob.Autors)
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

typedef multimap <string, BOOK> AutorBook;
typedef pair <AutorBook::iterator, AutorBook::iterator> inters;

typedef multimap <int, BOOK, greater<int>> AutorsBooks;
typedef pair <AutorsBooks::iterator, AutorsBooks::iterator> coutinters;


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
	string sub = " ";
	string NUMBER, NAME, YEAR;
	deque <string> AUTORS;

	while (getline(input, str))
	{
		str += ' ';

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
					if (count == 3)
						YEAR = temp1;
					else
						if (count > 3)
							AUTORS.push_back(temp1);

			poz1 = subpoz1;
		}

		if (count < 3)
		{
			cout << "Wrong count of information!" << endl;
			return 0;
		}

		BOOK two(NUMBER, NAME, YEAR, AUTORS);
		BOOKS.push_back(two);

		AUTORS.clear();
		count = 0;
		poz1 = 0;
	}
	input.close();
	bool aim = false;
	for (auto el: BOOKS)
	{
		cout << el << '\n';
		aim = true;
	}

	if (!aim)
	{
		cout << "None Data" << endl;
		return 0;
	}

	cout << "Сортировка по названию:" << endl;

	sort(BOOKS.begin(), BOOKS.end(), [](BOOK s1, BOOK s2) {return s1.Name < s2.Name; });
		for (auto el : BOOKS)
			cout << el;
		cout << endl;

	/*cout << "Сортировка по году издания:" << endl;

	sort(BOOKS.begin(), BOOKS.end(), [](BOOK s1, BOOK s2) {return s1.Year < s2.Year; });
	for (auto el : BOOKS)
		cout << el << '\n';

	cout << "Сортировка по количеству авторов:" << endl;

	sort(BOOKS.begin(), BOOKS.end(), [](BOOK s1, BOOK s2) {return s1.Autors.size() < s2.Autors.size(); });
	for (auto el : BOOKS)
		cout << el << '\n';*/


		/////////////////////////////////////////////////////////////////////////
		cout << "Введите автора:" << endl;
		string tempautor;
		cin >> tempautor;

		AutorBook GOG;
		AutorBook::iterator ITER;
		inters temppair;

		for (auto el : BOOKS)
			for (auto au : el.Autors)
				GOG.emplace(au, el);

		temppair = GOG.equal_range(tempautor);

		aim = false;
		for (ITER = temppair.first; ITER != temppair.second; ITER++)
		{
			cout << (*ITER).second;
			aim = true;
		}

		if (aim)
			cout << "Поиск успешен!" << endl;
		else
			cout << "Авторов не найдено!" << "\n";
		cout << endl;
		//////////////////////////////////////////////////////////////////////////
		cout << "Книги с максимальным количеством авторов:" << endl;
		cout << endl;

		AutorsBooks KOK;
		AutorsBooks::iterator findol;
		coutinters tempIT;

		for (auto el : BOOKS)
			KOK.insert(pair<int, BOOK>(el.Autors.size(), el));

		findol = KOK.begin();
		int MAX = (*findol).first;

		for_each(KOK.begin(), KOK.end(), [&MAX](pair<int, BOOK> s) {if (s.first > MAX)MAX = s.first; });
	
		tempIT = KOK.equal_range(MAX);

		for (findol =tempIT.first; findol != tempIT.second; findol++)
		{
			cout << (*findol).second;
			aim = true;
		}

		cout << endl;
		//////////////////////////////////////////////////////////////////////////
		cout << "Введите год издания:" << endl;
		cout << endl;

		string tempyear;
		cin >> tempyear;

		vector <BOOK>::iterator findhol;
		aim = false;
		for (findhol = BOOKS.begin(); findhol != BOOKS.end();)
		{
			if ((findhol = find_if(findhol, BOOKS.end(), [=](BOOK s) {return s.Year == tempyear; })) != BOOKS.end())
			{
				BOOKS.erase(findhol);
				findhol = BOOKS.begin();
				aim = true;
			}
			else
				break;
		}

		if (aim)
			cout << "Удаление успешно!" << endl;
		else
			cout << "Год не найден!" << "\n";
		cout << endl;

		for (auto el : BOOKS)
			cout << el;

	system("pause");
	return 0;
}