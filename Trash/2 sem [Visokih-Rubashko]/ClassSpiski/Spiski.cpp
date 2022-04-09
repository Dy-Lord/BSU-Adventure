#include "Spiski.h"

void Spisok::CLONE(const Spisok& e)
{
	if(e.CORE==NULL)
		throw std::exception("NULL LIST!!!");

	ListItem* OLD = e.CORE;
	ListItem* NEW = new ListItem;
	
	CORE = NEW;
	ListCount = e.ListCount;

	while (true)
	{
		NEW->FIO = OLD->FIO;
		NEW->DATA = OLD->DATA;
		NEW->NUMBER = OLD->NUMBER;
		NEW->TIME = OLD->TIME;

		if (OLD->Next == NULL)
		{
			NEW->Next = NULL;
			//TAIL = NEW;
			break;
		}
		else
		{
			OLD = OLD->Next;
			NEW->Next = new ListItem;
			NEW = NEW->Next;
		}

	}
}
void Spisok::ERASE()
{
	ListItem* lst = CORE;

	while (lst != NULL)
	{
		ListItem* DEL = lst;
		lst = lst->Next;
		delete DEL;
	}
	
	CORE = NULL;
}

Spisok::Spisok()
{
	CORE = NULL;
}
Spisok::Spisok(const Spisok& e)
{
	CLONE(e);
}
Spisok::~Spisok()
{
	ERASE();
}

void Spisok::FINDNUM(std::string info)
{
	ListItem* lst = CORE;
	bool find = false;

	while (lst != NULL)
	{
		if (lst->NUMBER == info)
		{
			std::cout << lst->FIO << "\t" << lst->NUMBER << "\t" << lst->DATA << "\t" << lst->TIME << "\n";
			find = true;
		}
		lst = lst->Next;
	}

	if (!find)
		std::cout << "ÍÎÌÅÐ ÍÅ ÍÀÉÄÅÍ!" << std::endl;
}
void Spisok::FINDDATA(std::string info)
{
	ListItem* lst = CORE;
	bool find = false;

	while (lst != NULL)
	{
		if (lst->DATA == info)
		{
			std::cout << lst->FIO << "\t" << lst->NUMBER << "\t" << lst->DATA << "\t" << lst->TIME << "\n";
			find = true;
		}
		lst = lst->Next;
	}

	if (!find)
		std::cout << "ÄÀÒÀ ÍÅ ÍÀÉÄÅÍÀ!" << std::endl;
}
void Spisok::ADDINFO(std::string fio, std::string num, std::string data, std::string time)
{
	ListItem* NEW = new ListItem;
	NEW->Next = CORE;
	CORE = NEW;
	ListCount++;

	NEW->FIO = fio;
	NEW->DATA = data;
	NEW->NUMBER = num;
	NEW->TIME = time;

}

void Spisok::IMPORT(std::istream& out)
{
	if (!out)
		throw std::exception("Wrong way!!!");

	int poz1 = 0, subpoz1 = 0, len1, count = 0;
	std::string str, temp1;
	std::string sub = " ";
	std::string fio, num, data, time;

	while (getline(out, str))
	{
		str += ' ';

		while ((poz1 = str.find_first_not_of(sub, poz1)) != std::string::npos)
		{
			subpoz1 = str.find_first_of(sub, poz1);
			len1 = subpoz1 - poz1;
			temp1 = str.substr(poz1, len1);
			count++;

			if (count <= 3)
				fio += temp1 + " ";
			else
				if (count == 4)
					num = temp1;
				else
					if (count == 5)
						data = temp1;
					else
						if (count == 6)
							time = temp1;

			poz1 = subpoz1;
		}

		if (count != 6)
			throw std::exception("Wrong count of information!!!");

		ADDINFO(fio, num, data, time);
		fio.clear();
		count = 0;
		poz1 = 0;
	}
}
void Spisok::SORTINGNUM()
{
	if (CORE == NULL)
		throw std::exception("NULL LIST!!!");

	ListItem* temp = CORE;
	ListItem* save, *prevsave;
	ListItem** arr = new ListItem*[ListCount];

	for (int i = 0; i < ListCount; i++)
	{
		arr[i] = temp;
		temp = temp->Next;
	}

	double fakt = 1.6473309;
	int len = ListCount / fakt;
	int stop = 0;
	if (ListCount == 1)
		return;

	while (true)
	{
		for (int i = 0; (i < ListCount) && (i + len < ListCount); i++)
			if (arr[i]->NUMBER > arr[i + len]->NUMBER)
			{
				if (arr[i] == CORE)
				{
					if (len != 1)
					{
						save = arr[i]->Next;

						arr[i]->Next = arr[i + len]->Next;
						arr[i + len - 1]->Next = arr[i];

						arr[i + len]->Next = save;
						CORE = arr[i + len];
						std::swap(arr[i], arr[i + len]);
					}
					else
					{
						arr[i]->Next = arr[i + len]->Next;
						arr[i + len]->Next = arr[i];
						CORE= arr[i + len];
						std::swap(arr[i], arr[i + len]);
					}
				}
				else
				{
					if (len != 1)
					{
						save = arr[i]->Next;
						prevsave = arr[i - 1];

						arr[i]->Next = arr[i + len]->Next;
						arr[i + len - 1]->Next = arr[i];

						arr[i + len]->Next = save;
						prevsave->Next = arr[i + len];
						std::swap(arr[i], arr[i + len]);
					}
					else
					{
						prevsave = arr[i - 1];
						arr[i]->Next = arr[i + len]->Next;
						arr[i + len]->Next = arr[i];
						prevsave->Next = arr[i + len];
						std::swap(arr[i], arr[i + len]);
					}
				}
			}

		if (len != 1)
			len /= fakt;

		else
		{
			len = 0;
			stop = 1;
		}

		if (stop)
			break;
	}
	delete[] arr;
}
void Spisok::SORTINGDATA()
{
	if (CORE == NULL)
		throw std::exception("NULL LIST!!!");

	ListItem* temp = CORE;
	ListItem* save, * prevsave;
	ListItem** arr = new ListItem * [ListCount];

	for (int i = 0; i < ListCount; i++)
	{
		arr[i] = temp;
		temp = temp->Next;
	}

	double fakt = 1.6473309;
	int len = ListCount / fakt;
	int stop = 0;
	if (ListCount == 1)
		return;

	while (true)
	{
		for (int i = 0; (i < ListCount) && (i + len < ListCount); i++)
			if (arr[i]->DATA > arr[i + len]->DATA)
			{
				if (arr[i] == CORE)
				{
					if (len != 1)
					{
						save = arr[i]->Next;

						arr[i]->Next = arr[i + len]->Next;
						arr[i + len - 1]->Next = arr[i];

						arr[i + len]->Next = save;
						CORE = arr[i + len];
						std::swap(arr[i], arr[i + len]);
					}
					else
					{
						arr[i]->Next = arr[i + len]->Next;
						arr[i + len]->Next = arr[i];
						CORE = arr[i + len];
						std::swap(arr[i], arr[i + len]);
					}
				}
				else
				{
					if (len != 1)
					{
						save = arr[i]->Next;
						prevsave = arr[i - 1];

						arr[i]->Next = arr[i + len]->Next;
						arr[i + len - 1]->Next = arr[i];

						arr[i + len]->Next = save;
						prevsave->Next = arr[i + len];
						std::swap(arr[i], arr[i + len]);
					}
					else
					{
						prevsave = arr[i - 1];
						arr[i]->Next = arr[i + len]->Next;
						arr[i + len]->Next = arr[i];
						prevsave->Next = arr[i + len];
						std::swap(arr[i], arr[i + len]);
					}
				}
			}

		if (len != 1)
			len /= fakt;

		else
		{
			len = 0;
			stop = 1;
		}

		if (stop)
			break;
	}
	delete[] arr;
}


const Spisok& Spisok::operator=(const Spisok& e)
{
	if (this != &e)
		CLONE(e);
	return *this;
}

Spisok Spisok::operator-(const std::string info) const
{
	Spisok NEW;
	NEW.CLONE(*this);

	ListItem* lst = NEW.CORE;
	ListItem* PREV = NULL;

	bool find = false;
	bool first = true;

	while (lst != NULL)
	{
		if (lst->FIO == info || lst->DATA == info || lst->NUMBER == info || lst->TIME == info)
			if (PREV == NULL)
			{
				find = true;
				NEW.CORE = lst->Next;
				delete lst;
				NEW.ListCount--;
				lst = NEW.CORE;
				continue;
			}
			else
			{
				find = true;
				PREV->Next = lst->Next;
				delete lst;
				NEW.ListCount--;
				lst = NEW.CORE;
				PREV = NULL;
				first = true;
				continue;
			}

		if (first)
		{
			PREV = NEW.CORE;
			first = false;
		}
		else
			PREV = lst;

		lst = lst->Next;
	}
	
	if (find)
		std::cout << "ÓÄÀËÅÍÈÅ ÓÑÏÅØÍÎ!" << std::endl;
	else
		std::cout << "ÈÍÔÎÐÌÀÖÈÈ ÍÅ ÍÀÉÄÅÍÎ!" << std::endl;
	return NEW;
}
Spisok Spisok::operator+(const std::string info) const
{
	Spisok NEW;
	NEW.CLONE(*this);

	int poz1 = 0, subpoz1 = 0, len1, count = 0;
	std::string str = info, temp1;
	std::string sub = " ";
	std::string fio, num, data, time;
	str += ' ';


	while ((poz1 = str.find_first_not_of(sub, poz1)) != std::string::npos)
	{
		subpoz1 = str.find_first_of(sub, poz1);
		len1 = subpoz1 - poz1;
		temp1 = str.substr(poz1, len1);
		count++;

		if (count <= 3)
			fio += temp1+" ";
		else
			if (count == 4)
				num = temp1;
			else
				if (count == 5)
					data = temp1;
				else
					if (count == 6)
						time = temp1;
			
		poz1 = subpoz1;
	}

	if (count != 6)
		throw std::exception("Wrong count of information!!!");

	NEW.ADDINFO(fio, num, data, time);
	NEW.ListCount++;

	return NEW;
}

bool Spisok::operator==(const Spisok& link) const
{
	ListItem* one = CORE;
	ListItem* two = link.CORE;

	while (one != NULL && two != NULL)
	{
		if (one->FIO == two->FIO && one->DATA == two->DATA && one->NUMBER == two->NUMBER && one->TIME == two->TIME)
		{
			one = one->Next;
			two = two->Next;
		}
		else
			return false;
	}

	if (one == NULL && two == NULL)
		return true;
	else
		return false;
}

std::ostream& operator<<(std::ostream& out, const Spisok& e)
{
	if (e.CORE == NULL)
		throw std::exception("NULL LIST!!!");

	ListItem* lst = e.CORE;

	while (lst != NULL)
	{
		out << lst->FIO << "\t" << lst->NUMBER << "\t" << lst->DATA << "\t" << lst->TIME << "\n";
		lst = lst->Next;
	}

	return out;
}

