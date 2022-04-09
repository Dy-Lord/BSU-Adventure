#include "DEREVO.h"

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

		if(DEL->right!=NULL)
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
}

void DEREVO::obxodleft(ROOT* P, void(*function)(ROOT* info)) const
{
	if (P->left != NULL)
	{
		P = P->left;

		obxodright(P, function);
		function(P);
		obxodleft(P, function);
	}
}
void DEREVO::obxodright(ROOT* P, void(*function)(ROOT* info)) const
{
	if (P->right != NULL)
	{
		P = P->right;

		obxodright(P, function);
		function(P);
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
	if (P == NULL)
		throw std::exception("Error. The tree is empty!");

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
ROOT* DEREVO::del(ROOT* First, int finder, std::ostream& out)
{
	if (!out)
		throw std::exception("Wrong way!!!");

	ROOT* temp;
	temp = finddel(First, finder);


	if (temp == NULL)
	{
		out << finder << '\t' << "Not deleted!" << std::endl;
		return First;
	}
	else
		if (PREP == NULL)
		{
			if (temp->right == NULL && temp->left == NULL)
			{
				delete temp;
				if(firstDEL)
				out << finder << '\t' << "Deleted!" << std::endl;
				return NULL;
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
			First = del(First, tempdel->Info, out);

			temp->Info = inf;
			out << finder << '\t' << "Deleted!" << std::endl;
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
				if (firstDEL)
				out << finder << '\t' << "Deleted!" << std::endl;
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
					if (firstDEL)
					out << finder << '\t' << "Deleted!" << std::endl;
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
						if (firstDEL)
						out << finder << '\t' << "Deleted!" << std::endl;
						return First;
					}
					else
					{
						ROOT* tempdel = NULL;
						tempdel = temp->left;

						while (tempdel->right != NULL)
							tempdel = tempdel->right;

						temp->Info = tempdel->Info;

						firstDEL = false;
						First = del(First, tempdel->Info, out);
						out << finder << '\t' << "Deleted!" << std::endl;
						return First;
					}
		}
}

void DATAOUT(ROOT* info, std::ostream& out) 
{
	out << info->Info << std::endl;
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

void DEREVO::ADDINFO(int infor, std::ostream& out)
{
	if (!out)
		throw std::exception("Wrong way!!!");

	if (CORE == NULL)
	{
		CORE = new ROOT;
		CORE->Info = infor;
		CORE->left = NULL;
		CORE->right = NULL;
		out << infor << '\t' << "Inserted" << std::endl;
		return;
	}

	ROOT* P = CORE;
	do
	{

		if (P->Info == infor)
		{
			out << infor << '\t' << "Not inserted" << std::endl;
			return;
		}
		else
			if (P->Info < infor)
			{
				if (P->left == NULL)
				{
					P->left = new ROOT;
					P = P->left;

					P->Info = infor;
					P->right = NULL;
					P->left = NULL;
					out << infor << '\t' << "Inserted" << std::endl;
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
						P = P->right;

						P->Info = infor;
						P->right = NULL;
						P->left = NULL;
						out << infor << '\t' << "Inserted" << std::endl;
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
void DEREVO::DELINFO(int finder, std::ostream& out)
{
	if (!out)
		throw std::exception("Wrong way!!!");

	CORE = del(CORE, finder, out);
	firstDEL = true;
	PREP = NULL;
}
void DEREVO::FINDINFO(int finder, std::ostream& out)
{
	if (!out)
		throw std::exception("Wrong way!!!");

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

void DEREVO::IMPORT(std::istream& in, std::ostream& out)
{
	if (!out)
		throw std::exception("Wrong way!!!");

	if (!in)
		throw std::exception("Wrong way!!!");

	if(in.peek()==EOF)
		throw std::exception("Input file is void!!!");

	int poz1 = 0, subpoz1 = 0, len1;
	std::string str, temp1,temp2;
	std::string sub = " ";
	bool one = true;

	while (getline(in, str))
	{
		if (str == "") continue;

		str += ' ';

		while ((poz1 = str.find_first_not_of(sub, poz1)) != std::string::npos)
		{
			subpoz1 = str.find_first_of(sub, poz1);
			len1 = subpoz1 - poz1;

			if (one)
			{
				temp1 = str.substr(poz1, len1);
				one = false;
			}
			else
			{
				temp2 = str.substr(poz1, len1);
				one = true;
			}

			if (temp1 == "L")
				break;
			poz1 = subpoz1;
		}

		if (temp1 != "L")
		{
			char* end_ptr;
			int dd;

			char* s2 = new char[temp2.length() + 1];
			strcpy(s2, temp2.c_str());

			dd = strtol(s2, &end_ptr, 10);

			if (*end_ptr != 0)
			{
				delete[] s2;
				throw std::exception("Wrong information!!!");
			}


			if (temp1 == "I")
				ADDINFO(dd, out);
			else
				if (temp1 == "D")
					DELINFO(dd, out);
				else
					if (temp1 == "F")
						FINDINFO(dd, out);
					else
						throw std::exception("Wrong information!!!");
		}
		else
			if (temp1 == "L")
			{
				out << "List of elements" << std::endl;
				PRAMOBHOD(DATAOUT, out);
			}
			else
				throw std::exception("Wrong information!!!");
		temp1.clear();
		temp2.clear();
		poz1 = 0;
	}
}

void DEREVO::PRAMOBHOD(void(*function)(ROOT*, std::ostream&), std::ostream& out) const
{
	if (CORE == NULL)
		throw std::exception("Error. The tree is empty!");

	obxodright(CORE, function, out);
	function(CORE, out);
	obxodleft(CORE, function, out);
}
void DEREVO::PRAMOBHOD(void(*function)(ROOT* info)) const
{
	if (CORE == NULL)
		throw std::exception("Error. The tree is empty!");

	obxodright(CORE, function);
	function(CORE);
	obxodleft(CORE, function);
}
void DEREVO::RINGOBHOD(void(*function)(ROOT* info)) const
{
	if (CORE == NULL)
		throw std::exception("Error. The tree is empty!");

	obxodrightobr(CORE, function);
	obxodleftobr(CORE, function);
	function(CORE);
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

