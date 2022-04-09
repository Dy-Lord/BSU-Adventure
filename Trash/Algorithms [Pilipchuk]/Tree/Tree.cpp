#define _CRT_SECURE_NO_WARNINGS 
#include <algorithm>
#include<iostream>
#include<exception>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

struct ROOT
{
	int Info;
	int Height;

	ROOT* left;
	ROOT* right;
	ROOT* prep;
};

class DEREVO
{
private:

	ROOT* CORE;
	ROOT* PREP;

	bool firstDEL = true;

	void CLONE(const DEREVO&);
	void ERASE();

	void ADDOBHOD(ROOT* NEW) const;
	void leftadd(ROOT* NEW, ROOT* OLD) const;
	void rightadd(ROOT* NEW, ROOT* OLD) const;

	void obxodleftobr(ROOT* E, void (*function)(ROOT* info)) const;
	void obxodrightobr(ROOT* E, void (*function)(ROOT* info)) const;

	void obxodleft(ROOT* E, void (*function)(ROOT* info)) const;
	void obxodright(ROOT* E, void (*function)(ROOT* info)) const;

	void obxodleft(ROOT* E, void (*function)(ROOT* info, std::ostream&), std::ostream&) const;
	void obxodright(ROOT* E, void (*function)(ROOT* info, std::ostream&), std::ostream&) const;

	ROOT* finddel(ROOT* P, int finder);
	ROOT* del(ROOT* P, int finder);

	friend void DATAOUT(ROOT*, std::ostream&);

public:
	DEREVO();
	DEREVO(const DEREVO&);
	~DEREVO();

	void ADDINFO(int);
	void DELINFO(int);
	void FINDINFO(int, std::ostream&);

	void IMPORT(std::istream& in);

	void PRAMOBHOD(void (*function)(ROOT*, std::ostream&), std::ostream&) const;
	void PRAMOBHOD(void (*function)(ROOT* info)) const;
	void RINGOBHOD(void (*function)(ROOT* info)) const;
	void tempOBHOD(void (*function)(ROOT* info)) const;

	int getCOREinfo() {
		return CORE->Info;
	}

	ROOT* getCORE() {
		return CORE;
	}

	const DEREVO& operator = (const DEREVO&);;
};

void DEREVO::CLONE(const DEREVO& link)
{
	if (link.CORE == NULL)
		throw std::exception("NULL TREE!!!");

	ROOT* NEW = new ROOT;

	CORE = NEW;
	NEW->Info = link.CORE->Info;

	NEW->left = NULL;
	NEW->right = NULL;

	link.ADDOBHOD(NEW);
}
void DEREVO::ERASE()
{
	if (CORE == NULL)
		return;
	ROOT* DEL = CORE;
	while (true)
	{

		if (DEL->left != NULL)
		{
			PREP = DEL;
			DEL = DEL->left;
			continue;
		}

		if (DEL->right != NULL)
		{
			PREP = DEL;
			DEL = DEL->right;
			continue;
		}

		if (DEL->left == NULL && DEL->right == NULL)
		{
			if (PREP == NULL)
			{
				delete DEL;
				CORE = NULL;
				break;
			}

			if (PREP->left == DEL)
				PREP->left = NULL;
			else
				PREP->right = NULL;
			PREP = NULL;
			delete DEL;
			break;
		}
	}
	ERASE();
}

void DEREVO::ADDOBHOD(ROOT* NEW) const
{
	ROOT* OLD = CORE;

	if (CORE->left != NULL)
		leftadd(NEW, OLD);

	if (CORE->right != NULL)
		rightadd(NEW, OLD);
}
void DEREVO::leftadd(ROOT* NEW, ROOT* OLD) const
{
	ROOT* DNEW = NEW;
	ROOT* DOLD = OLD->left;

	DNEW->left = new ROOT;
	DNEW = DNEW->left;

	DNEW->Info = DOLD->Info;

	if (DOLD->left != NULL)
		leftadd(DNEW, DOLD);
	else
		DNEW->left = NULL;

	if (DOLD->right != NULL)
		rightadd(DNEW, DOLD);
	else
		DNEW->right = NULL;
}
void DEREVO::rightadd(ROOT* NEW, ROOT* OLD) const
{
	ROOT* DNEW = NEW;
	ROOT* DOLD = OLD->right;

	DNEW->right = new ROOT;
	DNEW = DNEW->right;

	DNEW->Info = DOLD->Info;

	if (DOLD->left != NULL)
		leftadd(DNEW, DOLD);
	else
		DNEW->left = NULL;

	if (DOLD->right != NULL)
		rightadd(DNEW, DOLD);
	else
		DNEW->right = NULL;
}

void DEREVO::obxodleftobr(ROOT* P, void(*function)(ROOT* info)) const
{
	if (P->left != NULL)
	{
		P = P->left;
		obxodrightobr(P, function);
		obxodleftobr(P, function);
		function(P);
	}
	/*else
		if (P->right == NULL)
			function(P);*/
}
void DEREVO::obxodrightobr(ROOT* P, void(*function)(ROOT* info)) const
{
	if (P->right != NULL)
	{
		P = P->right;
		obxodrightobr(P, function);
		obxodleftobr(P, function);
		function(P);
	}
	/*else
		if (P->left == NULL)
		function(P);*/
}

void DEREVO::obxodleft(ROOT* P, void(*function)(ROOT* info)) const
{
	if (P->left != NULL)
	{
		P = P->left;
		function(P);
		obxodright(P, function);
		//function(P);
		obxodleft(P, function);
	}
}
void DEREVO::obxodright(ROOT* P, void(*function)(ROOT* info)) const
{
	if (P->right != NULL)
	{
		P = P->right;
		function(P);
		obxodright(P, function);
		//function(P);
		obxodleft(P, function);
	}
}

void DEREVO::obxodleft(ROOT* P, void(*function)(ROOT* info, std::ostream&), std::ostream& out) const
{
	if (P->left != NULL)
	{
		P = P->left;

		obxodright(P, function, out);
		function(P, out);
		obxodleft(P, function, out);
	}
}
void DEREVO::obxodright(ROOT* P, void(*function)(ROOT* info, std::ostream&), std::ostream& out) const
{
	if (P->right != NULL)
	{
		P = P->right;

		obxodright(P, function, out);
		function(P, out);
		obxodleft(P, function, out);
	}
}


ROOT* DEREVO::finddel(ROOT* P, int finder)
{
	do
	{
		if (P->Info == finder)
		{
			return P;
			break;
		}
		else
			if (P->Info < finder)
			{
				if (P->left == NULL)
				{
					return NULL;
					break;
				}
				else
				{
					PREP = P;
					P = P->left;
					continue;
				}
			}
			else
				if (P->Info > finder)
				{
					if (P->right == NULL)
					{
						return NULL;
						break;
					}
					else
					{
						PREP = P;
						P = P->right;
						continue;
					}
				}

	} while (true);
}
ROOT* DEREVO::del(ROOT* First, int finder)
{
	ROOT* temp;
	temp = finddel(First, finder);


	if (temp == NULL)
		return First;
	else
		if (PREP == NULL)
		{
			if (temp->right == NULL && temp->left == NULL)
			{
				delete temp;
				return NULL;
			}
			else
				if (temp->right != NULL && temp->left == NULL) {
					First = temp->right;
					delete temp;
					return First;
				}
				else
					if (temp->right == NULL && temp->left != NULL) {
						First = temp->left;
						delete temp;
						return First;
					}

			ROOT* tempdel = NULL;

			if (temp->left != NULL)
			{
				tempdel = temp->left;
				while (tempdel->right != NULL)
					tempdel = tempdel->right;
			}
			else
				if (temp->right != NULL)
				{
					tempdel = temp->right;
					while (tempdel->left != NULL)
						tempdel = tempdel->left;
				}

			int inf = tempdel->Info;

			firstDEL = false;
			First = del(First, tempdel->Info);

			temp->Info = inf;
			return First;
		}
		else
		{
			if (temp->right == NULL && temp->left == NULL)
			{
				if (PREP->left == temp)
					PREP->left = NULL;
				else
					if (PREP->right == temp)
						PREP->right = NULL;
				delete temp;
				return First;
			}
			else
				if (temp->right == NULL && temp->left != NULL)
				{
					if (PREP->right == temp)
						PREP->right = temp->left;
					else
						if (PREP->left == temp)
							PREP->left = temp->left;
					delete temp;
					return First;
				}
				else
					if (temp->right != NULL && temp->left == NULL)
					{
						if (PREP->right == temp)
							PREP->right = temp->right;
						else
							if (PREP->left == temp)
								PREP->left = temp->right;
						delete temp;
						return First;
					}
					else
					{
						ROOT* tempdel = NULL;

						tempdel = temp->left;

						while (tempdel->right != NULL)
							tempdel = tempdel->right;

						int newNum = tempdel->Info;


						firstDEL = false;
						First = del(First, tempdel->Info);
						temp->Info = newNum;
						return First;
					}
		}
}

DEREVO::DEREVO()
{
	CORE = NULL;
	PREP = NULL;
}
DEREVO::DEREVO(const DEREVO& link)
{
	CLONE(link);
}
DEREVO::~DEREVO()
{
	ERASE();
}

void DEREVO::ADDINFO(int infor)
{
	if (CORE == NULL)
	{
		CORE = new ROOT;
		CORE->Info = infor;
		CORE->left = NULL;
		CORE->right = NULL;
		CORE->prep = NULL;
		return;
	}

	ROOT* P = CORE;
	do
	{

		if (P->Info == infor)
			return;
		else
			if (P->Info < infor)
			{
				if (P->left == NULL)
				{
					P->left = new ROOT;
					ROOT* prepRoot = P;
					P = P->left;

					P->Info = infor;
					P->prep = prepRoot;
					P->right = NULL;
					P->left = NULL;
					break;
				}
				else
				{
					P = P->left;
					continue;
				}
			}
			else
				if (P->Info > infor)
				{
					if (P->right == NULL)
					{
						P->right = new ROOT;
						ROOT* prepRoot = P;
						P = P->right;

						P->Info = infor;
						P->prep = prepRoot;
						P->right = NULL;
						P->left = NULL;
						break;
					}
					else
					{
						P = P->right;
						continue;
					}
				}

	} while (true);
}
void DEREVO::DELINFO(int finder)
{
	CORE = del(CORE, finder);
	firstDEL = true;
	PREP = NULL;
}
void DEREVO::FINDINFO(int finder, std::ostream& out)
{
	if (CORE == NULL)
	{
		out << "Error. The tree is empty!" << std::endl;
		return;
	}

	int count = 0;

	ROOT* P = CORE;

	do
	{

		if (P->Info == finder)
		{
			count++;
			out << P->Info << '\t' << "found after " << count << " comprasion(s)" << std::endl;
			break;
		}
		else
		{
			if (P->Info < finder)
			{
				if (P->left == NULL)
				{
					count++;
					out << finder << '\t' << "Not found after " << count << " comprasion(s)" << std::endl;
					break;
				}
				else
				{
					P = P->left;
					count++;
					continue;
				}
			}
			else
			{
				if (P->Info > finder)
				{
					if (P->right == NULL)
					{
						count++;
						out << finder << '\t' << "Not found after " << count << " comprasion(s)" << std::endl;
						break;
					}
					else
					{
						P = P->right;
						count++;
						continue;
					}
				}
			}
		}
	} while (true);
}

void DEREVO::IMPORT(std::istream& in)
{
	int dd;
	while (in >> dd) {
		ADDINFO(dd);
	}
}

void DEREVO::PRAMOBHOD(void(*function)(ROOT*, std::ostream&), std::ostream& out) const
{
	obxodleft(CORE, function, out);
	function(CORE, out);
	obxodright(CORE, function, out);
}
void DEREVO::PRAMOBHOD(void(*function)(ROOT* info)) const
{
	function(CORE);
	obxodright(CORE, function);
	obxodleft(CORE, function);

}
void DEREVO::RINGOBHOD(void(*function)(ROOT* info)) const
{
	obxodrightobr(CORE, function);
	obxodleftobr(CORE, function);
	function(CORE);
	/*if (CORE->left == NULL || CORE->right == NULL)
		function(CORE);*/
}

void DEREVO::tempOBHOD(void(*function)(ROOT* info)) const
{
	obxodright(CORE, function);
	obxodleft(CORE, function);
}

const DEREVO& DEREVO::operator=(const DEREVO& e)
{
	if (this != &e)
	{
		ERASE();
		CLONE(e);
	}
	return *this;
}

ifstream input("input.txt", ios::in);
ofstream output("output.txt", ios::out);
DEREVO Tree;

vector<ROOT*> maxRoots;

int pathLenght(ROOT* list) {
	if (list->right != NULL && list->left != NULL)
		if (list->right->Height +1 == list->Height)
			return list->Height + list->left->Height + 1;
		else
			return list->Height + list->right->Height + 1;

	return list->Height;
}

void findMaxRoots(ROOT* list) {
	if (pathLenght(list) > pathLenght(*maxRoots.begin())) {
		maxRoots.clear();
		maxRoots.push_back(list);
	}
	else if (pathLenght(list) == pathLenght(*maxRoots.begin()))
		maxRoots.push_back(list);
}


void TreeWork(ROOT* list)
{
	ROOT* maxRoot = list;
	int maxLenght = pathLenght(list);
	maxRoots.push_back(list);

	Tree.tempOBHOD(findMaxRoots);
}

void heightSet(ROOT* list) {
	if (list->right == NULL && list->left == NULL)
		list->Height = 0;
	else if (list->right == NULL && list->left != NULL)
		list->Height = list->left->Height + 1;
	else if (list->right != NULL && list->left == NULL)
		list->Height = list->right->Height + 1;
	else if (list->right->Height > list->left->Height)
		list->Height = list->right->Height + 1;
	else
		list->Height = list->left->Height + 1;
}

void DATAOUT(ROOT* info)
{
	output << info->Info << std::endl;
}

int main()
{

	try
	{
		Tree.IMPORT(input);
		Tree.RINGOBHOD(heightSet);
		TreeWork(Tree.getCORE());
		sort(maxRoots.begin(), maxRoots.end(), [](ROOT* a, ROOT* b) {return (*a).Info < (*b).Info; });

		Tree.DELINFO((*maxRoots.begin())->Info);
		Tree.PRAMOBHOD(DATAOUT);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

	input.close();
	output.close();
	return 0;
}