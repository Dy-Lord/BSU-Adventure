#include <iostream>
#include "Spiski.h"
#include <Windows.h>
#include<fstream>
#include<string>
#include<ctime>

using namespace std;

struct STO
{
	string GOSNUM;
	string MARK;
	string DATA;
	string COUNT;

	STO() {};
	STO(string gosnum, string mark, string data, string count)
	{
		GOSNUM = gosnum;
		MARK = mark;
		DATA = data;
		COUNT = count;
	}

	friend std::ostream& operator << (std::ostream& os, const STO& ob)
	{
		os << "GOSNUM" << '\t' << ob.GOSNUM << '\t' << "MARK" << '\t' 
			<< ob.MARK << '\t' << "DATA" << '\t' << ob.DATA << '\t'
			<< "COUNT" << '\t' << ob.COUNT << '\n';
		return os;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int w;
	int task;

	ifstream input("input1.txt", ios::in);
	
	try
	{
		while (true)
		{

			cout << "Выберите часть задания:" << endl 
				<< "(1) --- Манипуляции над списком <char*>"
				<< endl << "(2) --- Тесты" << endl << "(3) --- ВЫХОД" 
				<< endl;
			cin >> task;
			system("cls");

			switch (task)
			{
			case 1:
			{
				Spisok<char*> test;
				while (true)
				{
					cout << "(1)---Добавить элемент в начало списка" <<
						endl << "(2)---Добавить элемент в конец списка" <<
						endl << endl << "(3)---Удалить элемент из начала списка" <<
						endl << "(4)---Удалить элемент из конца списка" << endl <<
						endl << "(5)---Поиск первого элемента списка по заданному значению" <<
						endl << "(6)---Вывести элементы списка с начала" <<
						endl << "(7)---Вывести элементы списка с конца" <<
						endl << endl << "(8)---ВЫХОД" << endl;
					cin >> w;
					system("cls");
					switch (w)
					{
					case 1:
					{
						cout << "Введите элемент списка:" << endl;
						char* info = new char[200];
						scanf("%s", info);
						cout << endl;
						test.ADDINFOstart(info,cout);
						delete[] info;
						break;
					}
					case 2: 
					{
						cout << "Введите элемент списка:" << endl;
						char* info = new char[200];
						scanf("%s", info);
						cout << endl;
						test.ADDINFOfinal(info,cout);
						delete[] info;
						break;
					}
					case 3:
					{
						test.DELINFOstart(cout);
						break;
					}
					case 4: 
					{
						test.DELINFOfinal(cout);
						break;
					}
					case 5:
					{
						cout << "Введите элемент списка для поиска:" << endl;
						char* finder = new char[200];
						scanf("%s", finder);
						cout << endl;
						test.FINDDATA(finder,cout);
						delete[] finder;
						break;
					}
					case 6:
					{
						test.SHOWwithSTART(cout);
						break;
					}
					case 7:
					{
						test.SHOWwithFINAL(cout);
						break;
					}
					case 8: return 0; break;
					default:
						cout << "ОШИБКА---некорректный пункт меню!" << endl;
						cout << endl;
						break;
					}
				}
				break;
			}
			case 2:
			{
				if (!input)
					throw std::exception("Wrong way!!!");

		int poz1 = 0, subpoz1 = 0, len1, count = 0;
		std::string str, temp1;
		std::string sub = " ";
		std::string GOSNUM, MARK, DATA, COUNT;

		int kol = 0;
		int size;
		while (getline(input, str))
		{
			kol++;
		}
		size = kol;
		kol = 0;


		if (size == 0)
			throw std::exception("Wrong count of information!!!");

		STO arr[1000];

		input.close();
		input.open("input1.txt", ios::in);

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
					GOSNUM = temp1;
				else
					if (count == 2)
						MARK = temp1;
					else
						if (count == 3)
							DATA = temp1;
						else
							if (count == 4)
								COUNT = temp1;

				poz1 = subpoz1;
			}

			if (count != 4)
				throw std::exception("Wrong count of information!!!");

			if (kol != size)
			{
				arr[kol] = STO(GOSNUM, MARK, DATA, COUNT);
				kol++;
			}

			count = 0;
			poz1 = 0;
		}

		Spisok<STO> one(arr, size);
		one.SHOWwithSTART(cout);

		srand(time(NULL));
		int arrint[10];
		for (int i = 0; i < 10; i++)
			arrint[i] = rand() % 100 - 100;

		Spisok<int> two(arrint, 10);
		two.SHOWwithSTART(cout);
		cout << endl;
		two.SHOWwithFINAL(cout);

		char arrchar[10];
		for (int i = 0; i < 10; i++)
			arrchar[i] = rand() % 100 - 100;
				break;
			}
			case 3:
			{
				system("pause");
				return 0;
				break;
			}
			default:
				cout << "ОШИБКА---некорректный пункт меню!" << endl;
				cout << endl;
				break;
			}
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

	input.close();
	std::system("pause");
	return 0;
}