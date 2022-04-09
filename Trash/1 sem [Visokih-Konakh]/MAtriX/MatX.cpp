#include "MatX.h"

void MatX::CLONE(const MatX& c)
{
	STR = c.STR;
	COL = c.COL;

	arr = new int* [c.STR];

	for (int i = 0; i < c.STR; i++)
		arr[i] = new int[c.COL];

	for (int i = 0; i < c.STR; i++)
		for (int j = 0; j < c.COL; j++)
			arr[i][j] = c.arr[i][j];
}

void MatX::ERASE()
{
	for (int i = 0; i < STR; i++)
		delete[] arr[i];
	delete[] arr;
}

MatX::MatX() : COL(1), STR(1)
{
	arr = new int*;
	*arr = new int;
	**arr = 0;
}

MatX::MatX(int s, int c, int v)
{
	if (c <= 0 || s <= 0)
		throw std::exception("ERROR! Incorrect value of columns or rows in the matrix!");

	COL = c;
	STR = s;

	arr = new int* [s];

	for (int i = 0; i < s; i++)
		arr[i] = new int[c];

	for (int i = 0; i < s; i++)
		for (int j = 0; j < c; j++)
			arr[i][j] = v;
}

MatX::MatX(const MatX& c)
{
	CLONE(c);
}

MatX::~MatX()
{
	ERASE();
}

void MatX::SETcol(int c)
{
	if (c <= 0)
		throw std::exception("ERROR! Incorrect value of columns in the matrix!");

	COL = c;

	ERASE();

	MatX(STR, COL, 0);
}

void MatX::SETstr(int s)
{
	if (s <= 0)
		throw std::exception("ERROR! Incorrect value of columns in the matrix!");

	STR = s;

	ERASE();

	MatX(STR, COL, 0);
}

void MatX::SETval(int v)
{
	ERASE();
	MatX(STR, COL, v);
}

int MatX::GETcol() const
{
	return COL;
}

int MatX::GETstr() const
{
	return STR;
}

const MatX& MatX::operator=(const MatX& link)
{
	if (this != &link)
	{
		ERASE();
		CLONE(link);
	}
	return *this;
}

MatX MatX::operator+(const MatX& link) const
{
	if (COL != link.COL || STR != link.STR)
		throw std::exception("ERROR! Mismatch of columns or rows of matrices!");

	MatX SUM(STR, COL, 0);

	for (int i = 0; i < STR; i++)
		for (int j = 0; j < COL; j++)
			SUM.arr[i][j] = arr[i][j] + link.arr[i][j];

	return SUM;
}

MatX MatX::operator+(const int& dd) const
{
	MatX SUM(STR, COL, 0);

	for (int i = 0; i < STR; i++)
		for (int j = 0; j < COL; j++)
			SUM.arr[i][j] = arr[i][j] + dd;

	return SUM;
}

const MatX& MatX::operator+=(const MatX& link)
{
	*this = *this + link;
	return *this;
}

const MatX& MatX::operator+=(const int& dd)
{
	*this = *this + dd;
	return *this;
}

MatX MatX::operator*(const MatX& link) const
{
	if (COL!=link.STR)
		throw std::exception("ERROR! Matrices are not compatible!");

	MatX P(STR, link.COL, 0);

	for (int i = 0; i < STR; i++)
		for (int j = 0; j < link.COL; j++)
			for (int k = 0; k < COL; k++)
				P.arr[i][j] = P.arr[i][j] + arr[i][k] * link.arr[k][i];

	return P;
}

MatX MatX::operator*(const int& dd) const
{
	MatX P(STR, COL, 0);

	for (int i = 0; i < STR; i++)
		for (int j = 0; j < COL; j++)
			P.arr[i][j] = arr[i][j] * dd;

	return P;
}

const MatX& MatX::operator*=(const MatX& link)
{
	*this = *this * link;
	return *this;
}

const MatX& MatX::operator*=(const int& dd)
{
	*this = *this * dd;
	return *this;
}

bool MatX::operator==(const MatX& link) const
{
	if (COL != link.COL || STR != link.STR)
		return false;

	for (int i = 0; i < link.STR; i++)
		for (int j = 0; j < link.COL; j++)
			if (arr[i][j] != link.arr[i][j])
				return false;

	return true;

}

bool MatX::operator!=(const MatX& link) const
{
	return (!(this->operator==(link)));
}

MatX operator+(const int& dd, const MatX& link)
{
	MatX SUM(link.STR, link.COL, 0);

	for (int i = 0; i < link.STR; i++)
		for (int j = 0; j < link.COL; j++)
			SUM.arr[i][j] = link.arr[i][j] + dd;

	return SUM;
}

MatX operator*(const int& dd, const MatX& link)
{
	MatX P(link.STR, link.COL, 0);

	for (int i = 0; i < link.STR; i++)
		for (int j = 0; j < link.COL; j++)
			P.arr[i][j] = link.arr[i][j] * dd;

	return P;
}

std::ostream& operator<<(std::ostream& S, const MatX& link)
{
	for (int i = 0; i < link.STR; i++)
	{
		for (int j = 0; j < link.COL; j++)
			S << "  " << link.arr[i][j];
		S << '\n';
	}

	return S;
}

std::istream& operator>>(std::istream& in, const MatX& link)
{
	for (int i = 0; i < link.STR; i++)
		for (int j = 0; j < link.COL; j++)
			in >> link.arr[i][j];

	return in;
}
