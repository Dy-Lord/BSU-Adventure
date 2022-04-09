#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<deque>
#include<list>
#include<string>
#include<Windows.h>

using namespace std;

struct STUD
{
	string Name;
	string Group;
	vector <int> Ocenki;

	STUD() {};
	STUD(string name, string group, vector<int> ocenki)
	{
		Name = name;
		Group = group;
		Ocenki = ocenki;
	}

	friend std::ostream& operator << (std::ostream& os, const STUD& ob)
	{
		os << "Name" << '\t' << ob.Name << '\t' << "Group" << '\t' << ob.Group << '\t' << "Ocenki: " << '\t';
		for (int i=0;i<ob.Ocenki.size();i++)
		{
			os << ob.Ocenki[i] << ' ';
		}
		os << "\n";
		return os;
	}
};

double SrBall(STUD s1, STUD s2)
{
	double Ball1=0, Ball2=0;
	int count=0;

	for (int i = 0; i < s1.Ocenki.size(); i++)
	{
		Ball1+=s1.Ocenki[i];
		count++;
	}

	if (count != 0)
		Ball1 /= count;
	count = 0;

	for (int i = 0; i < s2.Ocenki.size(); i++)
	{
		Ball2 += s2.Ocenki[i];
		count++;
	}

	if (count != 0)
		Ball2 /= count;

	return Ball1 > Ball2;
}

bool zadl(STUD one)
{
	for (int i = 0; i < one.Ocenki.size(); i++)
		if (one.Ocenki[i] < 4)
			return true;
	return false;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	fstream inputA("input.txt");
	fstream inputB("Data.txt");
	
	if (!inputA)
	{
		cout << "Ошибка файла" << endl;
		return 0;
	}

	deque<vector<int>> matrix;
	vector <int> row;
	
	int val;
	char c;
	while ((c = inputA.peek()) != EOF)
	{
		if (c == ' ')
		{
			inputA.ignore();
			continue;
		}
		else
		{
			if (c == '\n')
			{
				matrix.push_back(row);
				row.clear();
				inputA.ignore();
				continue;
			}
			else
			{
				inputA >> val;
				row.push_back(val);
				continue;
			}
		}
	}

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
			cout << matrix[i][j] << '\t';
		cout << endl;
	}
	cout << endl;

	int Max = matrix[0][0];
	int MaxCount=1;

	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix[i].size(); j++)
			if (matrix[i][j] >= Max)
			{
				if (matrix[i][j] == Max)
					MaxCount++;
				else
				{
					Max = matrix[i][j];
					MaxCount = 1;
				}
			}

	cout << "Максимальный эелемнт матрицы: " << Max << endl << "Количество максимальных элементов: " << MaxCount << endl;

	vector <int>::iterator it3;
	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] == Max)
			{
				it3 = matrix[i].begin() + j;
				matrix[i].erase(it3);
			}
		}

	cout << endl;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
			cout << matrix[i][j] << '\t';
		cout << endl;
	}
	cout << endl;
	
	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix[i].size(); j++)
			if (matrix[i][j] < 0)
			{
				matrix[i][j] = abs(matrix[i][j]);
			}

	cout << endl;
	cout << "Положительная матрица:" << endl;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
			cout << matrix[i][j] << '\t';
		cout << endl;
	}
	cout << endl;
	/////////////////////////////////////////////////////////////////////////////////B
	list<STUD>::iterator findol;
	list<STUD>::iterator temp;
	int poz1 = 0, subpoz1 = 0, len1, count = 0;
	string str, temp1;
	string sub = " ";
	string NAME, GROUP;
	vector<int> OCENKI;

	list <STUD> one;
	
	while (getline(inputB, str))
	{
		str += ' ';

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
					GROUP = temp1;
				else
					if (count > 2)
						if ((atoi(temp1.c_str()) >= 0) && (atoi(temp1.c_str()) <= 10))
						OCENKI.push_back(atoi(temp1.c_str()));

			poz1 = subpoz1;
		}

			STUD two(NAME, GROUP, OCENKI);
			one.push_back(two);
			
		OCENKI.clear();
		count = 0;
		poz1 = 0;
	}

	for (auto el : one)
		cout << el;
	cout << endl;

	list<STUD> FAM(one), GROU(one), SRB(one);

	FAM.sort([](STUD s1, STUD s2) {return s1.Name[0] < s2.Name[0]; });
	GROU.sort([](STUD s1, STUD s2) {return atoi(s1.Group.c_str()) < atoi(s2.Group.c_str()); });
	SRB.sort([](STUD s1, STUD s2) {return SrBall(s1, s2); });

	cout << "Контейнер отсортированный по фамилиям: " << endl;
	for (auto el : FAM)
		cout << el;
	cout << endl;

	cout << "Контейнер отсортированный по группам: " << endl;
	for (auto el : GROU)
		cout << el;
	cout << endl;

	cout << "Контейнер отсортированный по среднему баллу: " << endl;
	for (auto el : SRB)
		cout << el;
	cout << endl;

	bool aim = false;

	string alfa;
	cout << "Введите первую букву фамилии студента: " << endl;
	cin >> alfa;

	findol = FAM.begin();
	for (findol; findol != FAM.end();)
	{
		if ((findol = find_if(findol, FAM.end(), [=](STUD s) {return (tolower(s.Name[0]) == tolower(alfa[0])); })) != FAM.end())
		{
			cout << *findol;
			aim = true;
			findol++;
		}
		else
			break;
	}
	cout << endl;

	if (!aim)
		cout << "Данных не найдено!" << endl;
	aim = false;

	string gr;
	cout << "Введите номер группы студента: " << endl;
	cin >>gr;

	findol = GROU.begin();
	for (findol; findol != GROU.end();)
	{
		if ((findol = find_if(findol, GROU.end(), [=](STUD s) {return s.Group == gr; })) != GROU.end())
		{
			cout << *findol;
			aim = true;
			findol++;
		}
		else
			break;
	}
	cout << endl;

	if (!aim)
		cout << "Данных не найдено!" << endl;
	aim = false;

	int ct;
	cout << "Введите количество студентов с наибольшим средним баллом: " << endl;
	cin >> ct;

	for (auto el : SRB)
		if (ct > 0)
		{
			cout << el;
			aim = true;
			ct--;
		}
	cout << endl;

	if (!aim)
		cout << "Данных не найдено!" << endl;
	aim = false;

	cout << "Студенты задолжники: " << endl;

	findol = SRB.begin();

	for (findol; findol != SRB.end();)
	{
		if ((findol = find_if(findol, SRB.end(), zadl)) != SRB.end())
		{
			cout << *findol;
			aim = true;
			temp = findol;
			findol++;
			SRB.erase(temp);
		}
		else
			break;
	}
	cout << endl;

	if (!aim)
		cout << "Студентов задолжников не найдено!" << endl;
	aim = false;

	cout << "Студенты незадолжники: " << endl;
	for (auto el : SRB)
		cout << el;
	cout << endl;

	system("pause");
	return 0;
}