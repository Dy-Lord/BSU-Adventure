#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include<cstdio>
#include<cstring>
#include<exception>

using namespace std;

int num = 0;

struct DEREVO
{
	char* Info;
	int id;
	DEREVO* core;
	DEREVO* left;
	DEREVO* right;
};

DEREVO* one = NULL;
DEREVO* PREP = NULL;

DEREVO* first(char* infor);//Инициализация первого элемента дерева
void add(DEREVO* P, char* infor); //Добавление элемента в дерево


void PRAM(DEREVO* P);  //Прямой обход дерева
void OBRAT(DEREVO* P); //Обратный обход дерева
void UROVN(DEREVO* P); //Обход дерева по уровням

void find(DEREVO* First, char* finder);//Поиск первого элемента дерева по заданному значению

DEREVO* del(DEREVO* First, char* finder); //Удаление  элемента из дерева по заданному значению
DEREVO* finddel(DEREVO* First, char* finder);

void obxodleft(DEREVO* P);
void obxodright(DEREVO* P);

void obxodleftobr(DEREVO* P);
void obxodrightobr(DEREVO* P);


void Levels(DEREVO* P, int lev);

DEREVO* first(char* infor)
{
	DEREVO* one;

	one = new DEREVO;

	char* inf = new char[strlen(infor) + 1];
	strcpy(inf, infor);
	
	one->Info = inf;

	one->right = NULL;
	one->left = NULL;
	one->id = ++num;
	one->core = one;
	return(one);
}

void add(DEREVO* P, char* infor)
{
	do
	{

		if (strcmp(P->Info, infor) == 0)
			throw exception("Error. Structure Element Already Exists");
		else
			if (strcmp(P->Info, infor) == -1)
			{
				if (P->left == NULL)
				{
					P->left = new DEREVO;
					P = P->left;

					char* inf = new char[strlen(infor) + 1];
					strcpy(inf, infor);

					P->Info = inf;
					P->id = ++num;
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
				if (strcmp(P->Info, infor) == 1)
				{
					if (P->right == NULL)
					{
						P->right = new DEREVO;
						P = P->right;

						char* inf = new char[strlen(infor) + 1];
						strcpy(inf, infor);

						P->Info = inf;
						P->id = ++num;
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

void PRAM(DEREVO* P)
{
	if(P==NULL)
		throw exception("Error. The tree is empty!");
	cout << P->Info << '\t' << P->id << endl;
	obxodright(P);
	obxodleft(P); 
	
}

void OBRAT(DEREVO* P)
{
	if (P == NULL)
		throw exception("Error. The tree is empty!");
	
	obxodrightobr(P);
	obxodleftobr(P);
	
	cout << P->Info << '\t' << P->id << endl;
}

void UROVN(DEREVO* P)
{
	if (P == NULL)
		throw exception("Error. The tree is empty!");

	for (int i = 0; i <= num; i++)
	{
		Levels(P, i);
		cout << endl;
	}
}

void Levels(DEREVO *P, int level)
{
    if (P == nullptr) 
        return;
     else 
	{
        Levels(P->right, level - 1);  
		if (level == 0)
			cout << P->Info << '\t' << P->id << endl;
        Levels(P->left, level - 1);  
    }
}

void find(DEREVO* P, char* finder)
{
	if (P == NULL)
		throw exception("Error. The tree is empty!");

	do
	{
		if (strcmp(P->Info, finder) == 0)
		{
			cout << "Элемент найден!" << endl;
			cout << P->Info << '\t' << P->id << endl;
			break;
		}
		else
			if (strcmp(P->Info, finder) == -1)
			{
				if (P->left == NULL)
				{
					cout << "Совпадений не найдено!" << endl;
					break;
				}
				else
				{
					P = P->left;
					continue;
				}
			}
			else
				if (strcmp(P->Info, finder) == 1)
				{
					if (P->right == NULL)
					{
						cout << "Совпадений не найдено!" << endl;
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

DEREVO* finddel(DEREVO* P, char* finder)
{
	if (P == NULL)
		throw exception("Error. The tree is empty!");

	do
	{
		if (strcmp(P->Info, finder) == 0)
		{
			return P;
			break;
		}
		else
			if (strcmp(P->Info, finder) == -1)
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
				if (strcmp(P->Info, finder) == 1)
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

DEREVO* del(DEREVO* First, char* finder)
{
	DEREVO* temp;
	temp = finddel(First, finder);


	if (temp == NULL)
	{
		cout << "Совпадений не найдено!" << endl;
		return First;
	}
	else
		if (PREP == NULL)
		{
			if (temp->right == NULL && temp->left == NULL)
			{
				delete[] temp->Info;
				delete temp;;
				cout << "Удаление успешно!" << endl;
				return NULL;
			}

			DEREVO* templeft = NULL;
			DEREVO* tempdel = NULL;

			templeft = temp->left;
			tempdel = temp->left;

			while (tempdel->right != NULL)
				tempdel = tempdel->right;

			char* inf = new char[strlen(tempdel->Info) + 1];
			strcpy(inf, tempdel->Info);

			
			First = del(First, tempdel->Info);

			temp->Info = inf;
			cout << "Удаление успешно!" << endl;
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
			delete[] temp->Info;
			delete temp;
			cout << "Удаление успешно!" << endl;
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
				delete[] temp->Info;
				delete temp;
				cout << "Удаление успешно!" << endl;
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
					delete[] temp->Info;
					delete temp;
					cout << "Удаление успешно!" << endl;
					return First;
				}
				else
				{
					DEREVO* templeft = NULL;
					DEREVO* tempdel = NULL;

					templeft = temp->left;
					tempdel = temp->left;

					while (tempdel->right != NULL)
						tempdel = tempdel->right;

					temp->Info = tempdel->Info;
					First = del(First, tempdel->Info);
					cout << "Удаление успешно!" << endl;
					return First;
				}
	}
}

void obxodleft(DEREVO* P)
{
	if (P->left != NULL)
	{
		P = P->left;
		cout << P->Info << '\t' << P->id << endl;
		obxodleft(P);
		obxodright(P);
	}
}
void obxodright(DEREVO* P)
{
	if (P->right != NULL)
	{
		P = P->right;
		cout << P->Info << '\t' << P->id << endl;
		obxodright(P);
		obxodleft(P);
	}
}

void obxodrightobr(DEREVO* P)
{
	if (P->right != NULL)
	{
		P = P->right;
		obxodrightobr(P);
		//cout << P->Info << '\t' << P->id << endl;
		obxodleftobr(P);
		cout << P->Info << '\t' << P->id << endl;
	}
}
void obxodleftobr(DEREVO* P)
{
	if (P->left != NULL)
	{
		P = P->left;
		obxodrightobr(P);
		//cout << P->Info << '\t' << P->id << endl;
		obxodleftobr(P);
		cout << P->Info << '\t' << P->id << endl;
	}
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool aim = 1;
	int w;
	try
	{

		while (true)
		{
			cout << "(1)---Добавить элемент в дерево" << endl << "(2)---Прямой обход дерева" << endl << "(3)---Обратный обход дерева" << endl << "(4)---Обход дерева по уровням" << endl << "(5)---Удалить элемент из дерева" << endl << "(6)---Поиск  элемента дерева по заданному значению" << endl << "(7)---ВЫХОД" << endl;
			cin >> w;
			system("cls");

			switch (w)
			{
			case 1:
			{
				cout << "Введите элемент списка:" << endl;
				char* info = new char[200];
				scanf("%s", info);
				if (one == NULL)
				{
					one = first(info);
					aim = 0;
				}
				else
					add(one, info);
				break;
			}
			case 2: PRAM(one); cout << endl; break;
			case 3: OBRAT(one); cout << endl; break;
			case 4: UROVN(one); cout << endl; break;
			case 5:
			{
				cout << "Введите элемент списка для удаления:" << endl;
				char* finder = new char[200];
				scanf("%s", finder);
				cout << endl;
				one = del(one, finder);
				cout << endl;
				delete[] finder;
				break;
			}
			case 6:
			{
				cout << "Введите элемент для поиска:" << endl;
				char* finder = new char[200];
				scanf("%s", finder);
				cout << endl;
				find(one, finder);
				cout << endl;
				delete[] finder;
				break;
			}
			case 7: return 0; break;
			default:
			{
				cout << "ОШИБКА---некорректный пункт меню!" << endl;
				cout << endl;
				break;
			}
			}
		}
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		system("pause");
		return 0;
	}
	system("pause");
	return 0;
}