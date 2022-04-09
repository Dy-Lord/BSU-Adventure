#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<exception>
#include<string>

struct ROOT
{
	int Info;
	
	ROOT* left;
	ROOT* right;
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
	ROOT* del(ROOT* P, int finder, std::ostream&);

	friend void DATAOUT(ROOT*, std::ostream&);

public:
	DEREVO();
	DEREVO(const DEREVO&);
	~DEREVO();

	void ADDINFO(int, std::ostream&);
	void DELINFO(int, std::ostream&);
	void FINDINFO(int, std::ostream&);

	void IMPORT(std::istream& in, std::ostream& out);

	void PRAMOBHOD(void (*function)(ROOT*, std::ostream&), std::ostream&) const;
	void PRAMOBHOD(void (*function)(ROOT* info)) const;
	void RINGOBHOD(void (*function)(ROOT* info)) const;


	const DEREVO& operator = (const DEREVO&);;
};