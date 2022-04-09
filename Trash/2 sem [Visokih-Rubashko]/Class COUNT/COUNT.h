#pragma once
#include <iostream>
#include <exception>

class COUNT
{
	int varea;
	unsigned char elem[8192];

public:
	COUNT();
	COUNT(const COUNT& ob);
	~COUNT();

	void ADDelem(unsigned int el);
	bool ELinclude(unsigned int el);
	void Print();

	friend std::ostream& operator <<(std::ostream& out, const COUNT& ob);
	const COUNT& operator = (const COUNT& ob);

	bool operator == (const COUNT& ob) const;
	bool operator > (const COUNT& ob) const;
	bool operator < (const COUNT& ob) const;

	COUNT operator & (const COUNT& ob) const;
	COUNT operator | (const COUNT& ob) const;

	COUNT operator - (const COUNT& ob) const;
};