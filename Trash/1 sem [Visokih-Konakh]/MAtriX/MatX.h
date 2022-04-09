#pragma once
#include <iostream>
#include <exception>

class MatX
{
private:
	int STR, COL;
	int** arr; 
	void CLONE(const MatX&);
	void ERASE(); 
public:
	MatX(); 
	MatX(int, int, int);
	MatX(const MatX&);
	~MatX();
	void SETcol(int);
	void SETstr(int);
	void SETval(int);

	int GETcol() const;
	int GETstr() const;

	const MatX& operator = (const MatX&);

	MatX operator + (const MatX&) const;
	MatX operator + (const int&) const;
	friend MatX operator + (const int&, const MatX&);

	const MatX& operator +=(const MatX&);
	const MatX& operator +=(const int&);

	MatX operator * (const MatX&) const;
	MatX operator * (const int&) const;
	friend MatX operator * (const int&, const MatX&);

	const MatX& operator *=(const MatX&);
	const MatX& operator *=(const int&);

	bool operator == (const MatX&) const;
	bool operator != (const MatX&) const;

	friend std::ostream& operator <<(std::ostream&, const MatX&);
	friend std::istream& operator >>(std::istream&, const MatX&);

};