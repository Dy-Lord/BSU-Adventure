#pragma once
#include <iostream>
#include <exception>
#include <string>
#include <algorithm>
#include"List.h"

class Spisok
{
private:
	ListItem* CORE;

	int ListCount = 0;

	void CLONE(const Spisok&);
	void ERASE();

public:
	Spisok();
	Spisok(const Spisok&);
	~Spisok();

	void FINDNUM(std::string num);
	void FINDDATA(std::string data);
	void ADDINFO(std::string fio, std::string num, std::string data, std::string time);
	void IMPORT(std::istream&);
	void SORTINGNUM();
	void SORTINGDATA();

	const Spisok& operator = (const Spisok&);

	friend std::ostream& operator <<(std::ostream&, const Spisok&);

	Spisok operator - (const std::string) const;
	Spisok operator + (const std::string) const;

	bool operator == (const Spisok&) const;
};