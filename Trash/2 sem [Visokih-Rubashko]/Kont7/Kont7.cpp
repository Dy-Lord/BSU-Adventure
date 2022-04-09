#include<iostream>
#include<fstream>
#include<algorithm>
#include<list>
#include<map>
#include<string>
#include<Windows.h>

using namespace std;

void VIEW(map < string, list<pair<string, string>>> one)
{
	bool aim = false;

	for (auto el : one)
	{
		cout << "���������: " << el.first << '\n';

		cout << "�����-------------------������" << endl << endl;
		for (auto ls : el.second)
		{
			cout << ls.second << "-------------------" << ls.first << '\n';
			aim = true;
		}
		if (aim)
			cout << endl;
		else
			cout << "�������� ��������� �� ��������� --- � ���������� ��������� ���������� � �������������!" << endl;
		aim = false;
	}
	cout << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	fstream inputA("input.txt");

	if (!inputA)
	{
		cout << "������ �����" << endl;
		return 0;
	}

	map < string, list<pair<string, string>>> one;

	int poz1 = 0, subpoz1 = 0, len1, count = 0;
	string str, temp1;
	string sub = "##";
	string NAME;
	list<pair<string, string>> two;
	pair<string, string> data;

	while (getline(inputA, str))
	{
		str += '##';

		while ((poz1 = str.find_first_not_of(sub, poz1)) != std::string::npos)
		{
			subpoz1 = str.find_first_of(sub, poz1);
			len1 = subpoz1 - poz1;
			temp1 = str.substr(poz1, len1);
			count++;

			if (count == 1)
				NAME = temp1;
			else
			{
				data.first = temp1;
				poz1 = subpoz1;
				if ((poz1 = str.find_first_not_of(sub, poz1)) != std::string::npos)
				{
					subpoz1 = str.find_first_of(sub, poz1);
					len1 = subpoz1 - poz1;
					temp1 = str.substr(poz1, len1);
					count++;

					data.second = temp1;
				}
				else
				{
					cout << "Wrong count of information!" << endl;
					system("pause");
					return 0;
				}

				two.push_back(data);
			}
			
			poz1 = subpoz1;
		}

		if (count==0)
		{
			cout << "Wrong count of information!" << endl;
			system("pause");
			return 0;
		}

		map < string, list<pair<string, string>>>::iterator aim;
		
		if ((aim = one.find(NAME)) == one.end())
			one.emplace(NAME, two);
		else
			(*aim).second.splice((*aim).second.end(), two);

		two.clear();
		count = 0;
		poz1 = 0;
	}
	inputA.close();


	int w;
	while (true)
	{
		cout << "(1)---������� ������" << endl <<
			"(2)---����� ������� �� ����������" << endl <<	
			"(3)---������� ���������� ����������� , � ������� ���� ������, ������������� � ��������� ������" << endl << 
			"(4)---������� �������� ���� �����, ������ ������� ���� � �����������" << endl << 
			"(5)---�������  �������� ���� �����, ������ ������� ���� � ������ ����������" << endl << 
			"(6)---������� ��� ���������� ���������� ��� ���������� ��������� ������ ������������" << endl <<  
			"(7)---�����" << endl;
		cin >> w;
		system("cls");
		switch (w)
		{
		case 1:
		{
			VIEW(one);
			break;
		}
		case 2:
		{
			cout << "������� ���������:" << endl;
			string kinot;
			cin >> kinot;



			map < string, list<pair<string, string>>>::iterator aim;
			if ((aim = one.find(kinot)) != one.end())
			{
				(*aim).second.sort([](pair<string, string> s1, pair<string, string> s2) {
					if (s1.first != s2.first)
						return s1.first > s2.first;
					else
						return s1.second > s2.second;
					});

				for (auto el : (*aim).second)
					cout << el.second << "-------------------" << el.first << '\n';
			}
			else
				cout << "���������� �� �������!" << endl;

			break;
		}
		case 3:
		{
			cout << "������� ������:" << endl;
			string country;

			cin >> country;
			int COUNT = 0;
			for (auto el : one)
				if (count_if(el.second.begin(), el.second.end(), [=](pair<string, string> s) {return s.first == country; }) != 0)
					COUNT++;

			if (COUNT != 0)
				cout << "���������� ����������� , � ������� ���� ������, ������������� � ��������� ������: " << COUNT << endl;
			else
				cout << "��������������� ����������� �� �������!" << endl;
			break;
		}
		case 4:
		{
			cout << "H������� ���� �����, ������ ������� ���� � �����������:" << endl;
			
			map<string, string,greater<string>> lol;

			for (auto el : one)
				for (auto ul : el.second)
					lol.emplace(ul);

			for (auto el : lol)
				cout << el.first << endl;

			break;
		}
		case 5:
		{
			cout << "H������� ���� �����, ������ ������� ���� � ������ ����������:" << endl;

			map<string, string, greater<string>> lol;

			for (auto el : one)
				for (auto ul : el.second)
				{
					bool aim = true;
					for (auto el : one)
						if (find_if(el.second.begin(), el.second.end(), [=](pair<string, string> s) {return s.first == ul.first; }) == el.second.end())
							aim = false;

					if (aim)
						lol.emplace(ul);
				}

			if (lol.empty())
				cout << "��������������� ����������� �� �������!" << endl;
			else
				for (auto el : lol)
					cout << el.first << endl;

			break;
		}
		case 6:
		{
			cout << "������� �������� ����������:" << endl;
			string kinot;
			cin >> kinot;

			cout << "������� ������ ��� �������� � �������:" << endl;
			string country;
			cin >> country;

			map < string, list<pair<string, string>>>::iterator it;

			if ((it = find_if(one.begin(), one.end(), [=](pair<string, list<pair<string, string>>> s) {return s.first == kinot; })) == one.end())
			{
				cout << "��������� �� ������!" << endl;
				break;
			}

			bool aim = false;
			for (auto ut = it->second.begin(); ut != it->second.end();)
			{
				if ((*ut).first == country)
				{
					it->second.erase(ut);
					ut = it->second.begin();
					aim = true;
				}
				else
					ut++;
		    }
			if (!aim)
				cout << "������ ������������ ������� �� �������!" << endl;
			else
				VIEW(one);

			break;
		}
		case 7: return 0; break;
		default:
			cout << "������---������������ ����� ����!" << endl;
			cout << endl;
			break;
		}
	}
	system("pause");
	return 0;
}