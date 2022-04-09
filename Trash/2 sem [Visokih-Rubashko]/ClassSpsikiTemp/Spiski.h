#pragma once
#include <iostream>
#include <exception>
#include<cstring>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

template <typename DATA>
class Spisok
{
private:
	struct ListItem
	{
		DATA Info;

		ListItem* Next;
		ListItem* Prev;
	};

	ListItem* CORE;
	ListItem* TAIL;
	
	int ListCount = 0;

	void CLONE(const Spisok&);
	void ERASE();

public:
	Spisok();
	Spisok(DATA* arr, int size);
	Spisok(const Spisok& ob);
	~Spisok();

	void FINDDATA(DATA info, std::ostream& out);

	void ADDINFOstart (DATA info, std::ostream& out);
	void ADDINFOfinal(DATA info, std::ostream& out);

	void DELINFOstart(std::ostream& out);
	void DELINFOfinal(std::ostream& out);

	void SHOWwithSTART(std::ostream& out);
	void SHOWwithFINAL(std::ostream& out);
	
	const Spisok& operator = (const Spisok& ob);
};

template <typename DATA>
inline void Spisok<DATA>::CLONE(const Spisok& e)
{
	if (e.CORE == NULL)
		throw std::exception("NULL LIST!!!");

	ListItem* OLD = e.CORE;
	ListItem* NEW = new ListItem;
	ListItem* PREV = new ListItem;

	CORE = NEW;
	TAIL = NEW;
	NEW->Prev = NULL;
	PREV = NEW;
	ListCount = e.ListCount;

	while (true)
	{
		NEW->Info = OLD->Info;

		if (OLD->Next == NULL)
		{
			NEW->Next = NULL;
			TAIL = NEW;
			break;
		}
		else
		{
			OLD = OLD->Next;
			NEW->Next = new ListItem;
			NEW = NEW->Next;
			NEW->Prev = PREV;
			PREV = NEW;
		}

	}
}
template <>
inline void Spisok<char*>::CLONE(const Spisok& e)
{
	if (e.CORE == NULL)
		throw std::exception("NULL LIST!!!");

	ListItem* OLD = e.CORE;
	ListItem* NEW = new ListItem;
	ListItem* PREV = new ListItem;

	CORE = NEW;
	TAIL = NEW;
	NEW->Prev = NULL;
	PREV = NEW;
	ListCount = e.ListCount;

	while (true)
	{
		NEW->Info = new char[strlen(OLD->Info) + 1];
		std::strcpy((char*)NEW->Info, OLD->Info);

		if (OLD->Next == NULL)
		{
			NEW->Next = NULL;
			TAIL = NEW;
			break;
		}
		else
		{
			OLD = OLD->Next;
			NEW->Next = new ListItem;
			NEW = NEW->Next;
			NEW->Prev = PREV;
			PREV = NEW;
		}

	}
}

template <typename DATA>
inline void Spisok<DATA>::ERASE()
{
	ListItem* lst = CORE;

	while (lst != NULL)
	{
		ListItem* DEL = lst;
		lst = lst->Next;
		delete DEL;
	}

	CORE = NULL;
	TAIL = NULL;
}
template <>
inline void Spisok<char*>::ERASE()
{
	ListItem* lst = CORE;

	while (lst != NULL)
	{
		ListItem* DEL = lst;
		lst = lst->Next;
		delete[] DEL->Info;
		delete DEL;
	}

	CORE = NULL;
	TAIL = NULL;
}

template <typename DATA>
inline Spisok<DATA>::Spisok()
{
	CORE = NULL;
	TAIL = NULL;
}

template<typename DATA>
inline Spisok<DATA>::Spisok(DATA* arr, int size)
{
	CORE = NULL;
	TAIL = NULL;
	for (int i = 0; i < size; i++)
	{
		ListItem* NEW = new ListItem;
		if (CORE != NULL)
		{
			NEW->Next = CORE;
			CORE->Prev = NEW;
			CORE = NEW;
			CORE->Prev = NULL;
		}
		else
		{
			CORE = NEW;
			TAIL = NEW;
			CORE->Prev = NULL;
			CORE->Next = NULL;
		}
		ListCount++;

		NEW->Info = arr[i];
	}
}
template <>
inline Spisok<char*>::Spisok(char** arr, int size)
{
	CORE = NULL;
	TAIL = NULL;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == nullptr)
			throw std::exception("œ”—“¿ﬂ —“–Œ ¿!");

		ListItem* NEW = new ListItem;
		if (CORE != NULL)
		{
			NEW->Next = CORE;
			CORE->Prev = NEW;
			CORE = NEW;
			CORE->Prev = NULL;
		}
		else
		{
			CORE = NEW;
			TAIL = NEW;
			CORE->Prev = NULL;
			CORE->Next = NULL;
		}
		ListCount++;

		NEW->Info = new char[strlen(arr[i]) + 1];
		std::strcpy((char*)NEW->Info, arr[i]);
	}
}


template <typename DATA>
inline Spisok<DATA>::Spisok(const Spisok& e)
{
	CLONE(e);
}
template <typename DATA>
inline Spisok<DATA>::~Spisok()
{
	ERASE();
}

template <typename DATA>
inline void Spisok<DATA>::FINDDATA(DATA info, std::ostream& out)
{
	ListItem* lst = CORE;
	int count = 0;
	bool find = false;

	while (lst != NULL)
	{
		if (lst->Info == info)
		{
			out << "ÕÓÏÂ ˝ÂÎÂÏÂÌÚ‡ Ó˜ÂÂ‰Ë: " << count << "\n";
			find = true;
		}
		count++;
		lst = lst->Next;
	}

	if (!find)
		out << "›À≈Ã≈Õ“ Õ≈ Õ¿…ƒ≈Õ!" << std::endl;
}
template <>
inline void Spisok<char*>::FINDDATA(char* info, std::ostream& out)
{
	if (info == nullptr)
		throw std::exception("œ”—“¿ﬂ —“–Œ ¿!");


	ListItem* lst = CORE;
	int count = 0;
	bool find = false;

	while (lst != NULL)
	{
		if (strcmp(lst->Info, info) == 0)
		{
			out << "ÕÓÏÂ ˝ÂÎÂÏÂÌÚ‡ Ó˜ÂÂ‰Ë: " << count << "\n";
			find = true;
		}
		count++;
		lst = lst->Next;
	}

	if (!find)
		out << "›À≈Ã≈Õ“ Õ≈ Õ¿…ƒ≈Õ!" << std::endl;
}

template <typename DATA>
inline void Spisok<DATA>::ADDINFOstart(DATA info, std::ostream& out)
{
	ListItem* NEW = new ListItem;
	if (CORE != NULL)
	{
		NEW->Next = CORE;
		CORE->Prev = NEW;
		CORE = NEW;
		CORE->Prev = NULL;
	}
	else
	{
		CORE = NEW;
		TAIL = NEW;
		CORE->Prev = NULL;
		CORE->Next = NULL;
	}
	ListCount++;

	NEW->Info = info;

	out << "›À≈Ã≈Õ“ ƒŒ¡¿¬À≈Õ!" << '\n';
}
template<>
inline void Spisok<char*>::ADDINFOstart(char* info, std::ostream& out)
{
	if (info == nullptr)
		throw std::exception("œ”—“¿ﬂ —“–Œ ¿!");

	ListItem* NEW = new ListItem;
	if (CORE != NULL)
	{
		NEW->Next = CORE;
		CORE->Prev = NEW;
		CORE = NEW;
		CORE->Prev = NULL;
	}
	else
	{
		CORE = NEW;
		TAIL = NEW;
		CORE->Prev = NULL;
		CORE->Next = NULL;
	}
	ListCount++;
	
	NEW->Info = new char[strlen(info) + 1];
	std::strcpy((char*)NEW->Info, info);

	out << "›À≈Ã≈Õ“ ƒŒ¡¿¬À≈Õ!" << '\n';
}

template<typename DATA>
inline void Spisok<DATA>::ADDINFOfinal(DATA info, std::ostream& out)
{
	ListItem* NEW = new ListItem;
	if (TAIL != NULL)
	{
		NEW->Next = NULL;
		NEW->Prev = TAIL;
		TAIL->Next = NEW;
		TAIL = NEW;
	}
	else
	{
		TAIL = NEW;
		CORE = NEW;
		CORE->Prev = NULL;
		CORE->Next = NULL;
	}
	ListCount++;

	NEW->Info = info;

	out << "›À≈Ã≈Õ“ ƒŒ¡¿¬À≈Õ!" << '\n';
}
template<>
inline void Spisok<char*>::ADDINFOfinal(char* info, std::ostream& out)
{
	if (info == nullptr)
		throw std::exception("œ”—“¿ﬂ —“–Œ ¿!");

	ListItem* NEW = new ListItem;
	if (TAIL != NULL)
	{
		NEW->Next = NULL;
		NEW->Prev = TAIL;
		TAIL->Next = NEW;
		TAIL = NEW;
	}
	else
	{
		TAIL = NEW;
		CORE = NEW;
		CORE->Prev = NULL;
		CORE->Next = NULL;
	}
	ListCount++;

	NEW->Info = new char[strlen(info) + 1];
	std::strcpy((char*)NEW->Info, info);

	out << "›À≈Ã≈Õ“ ƒŒ¡¿¬À≈Õ!" << '\n';
}

template<typename DATA>
inline void Spisok<DATA>::DELINFOstart(std::ostream& out)
{
	if (CORE == NULL)
		throw std::exception("—œ»—Œ  œ”—“!");

	ListItem* lst = CORE;
	if (CORE == TAIL)
	{
		CORE = NULL;
		TAIL = NULL;
		delete lst;
	}
	else
	{
		CORE = lst->Next;
		CORE->Prev = NULL;
		delete lst;
	}

	out << "”ƒ¿À≈Õ»≈ ”—œ≈ÿÕŒ!" << std::endl;
}
template<>
inline void Spisok<char*>::DELINFOstart(std::ostream& out)
{
	if (CORE == NULL)
		throw std::exception("—œ»—Œ  œ”—“!");

	ListItem* lst = CORE;
	if (CORE == TAIL)
	{
		CORE = NULL;
		TAIL = NULL;
		delete[] lst->Info;
		delete lst;
	}
	else
	{
		CORE = lst->Next;
		CORE->Prev = NULL;
		delete[] lst->Info;
		delete lst;
	}
	out << "”ƒ¿À≈Õ»≈ ”—œ≈ÿÕŒ!" << std::endl;
}

template<typename DATA>
inline void Spisok<DATA>::DELINFOfinal(std::ostream& out)
{
	if (TAIL == NULL)
		throw std::exception("—œ»—Œ  œ”—“!");

	ListItem* lst = TAIL;
	if (CORE == TAIL)
	{
		CORE = NULL;
		TAIL = NULL;
		delete lst;
	}
	else
	{
		TAIL = lst->Prev;
		TAIL->Next = NULL;
		delete lst;
	}
	out << "”ƒ¿À≈Õ»≈ ”—œ≈ÿÕŒ!" << std::endl;
}
template<>
inline void Spisok<char*>::DELINFOfinal(std::ostream& out)
{
	if (TAIL == NULL)
		throw std::exception("—œ»—Œ  œ”—“!");

	ListItem* lst = TAIL;
	if (CORE == TAIL)
	{
		CORE = NULL;
		TAIL = NULL;
		delete[] lst->Info;
		delete lst;
	}
	else
	{
		TAIL = lst->Prev;
		TAIL->Next = NULL;
		delete[] lst->Info;
		delete lst;
	}
	out << "”ƒ¿À≈Õ»≈ ”—œ≈ÿÕŒ!" << std::endl;
}

template<typename DATA>
inline void Spisok<DATA>::SHOWwithSTART(std::ostream& out)
{
	if (CORE == NULL)
		throw std::exception("—œ»—Œ  œ”—“!!!");

	ListItem* lst = CORE;

	while (lst != NULL)
	{
		out << lst->Info << "\n";
		lst = lst->Next;
	}

}
template<typename DATA>
inline void Spisok<DATA>::SHOWwithFINAL(std::ostream& out)
{
	if (TAIL == NULL)
		throw std::exception("—œ»—Œ  œ”—“!!!");

	ListItem* lst = TAIL;

	while (lst != NULL)
	{
		out << lst->Info << "\n";
		lst = lst->Prev;
	}

}

template <typename DATA>
inline const Spisok<DATA>& Spisok<DATA>::operator=(const Spisok& e)
{
	if (this != &e)
		CLONE(e);
	return *this;
}

