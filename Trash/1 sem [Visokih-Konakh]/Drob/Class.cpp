#include "Header.h"

std::ostream& operator<<(std::ostream& S, const DROB& link)
{
	std::string drob;

	if (link.R != 0)
		drob = drob + '\n' + '\t' + "   " + std::to_string(link.a) + '\n' + '\t' + std::to_string(link.R) + " ———" + '\n' + '\t' + "   " + std::to_string(link.b) + '\n';
	else
		drob = drob + '\n' + '\t' + "   " + std::to_string(link.a) + '\n' + '\t'  + "  ———" + '\n' + '\t' + "   " + std::to_string(link.b) + '\n';
	S << drob;
	return S;
}

void DROB::SETR(int RR)
{
	if (RR < 0 && a < 0)
	{
		RR = abs(RR);
		a = abs(a);
	}

	if (RR > 0 && a < 0)
	{
		RR *= -1;
		a = abs(a);
	}

	R += RR;
}
void DROB::SETa(int aa)
{
	for (int i = 2; i <= abs(aa); i++)
		if ((aa % i == 0) && (b % i == 0))
		{
			aa /= i;
			b /= i;
			i--;
		}

	if (abs(aa) > b)
	{
		int ost;
		ost = aa % b;
		R += aa / b;
		if (ost == 0)
			aa = 1;
		else
		aa = abs(ost);
	}
	a = aa;
}
void DROB::SETb(int bb)
{
	if (bb == 0)
		throw std::exception("ERROR! Division by zero!");

	for (int i = 2; i <= abs(bb); i++)
		if ((bb % i == 0) && (a % i == 0))
		{
			bb /= i;
			a /= i;
			i--;
		}

	if (bb < 0)
	{
		bb = abs(bb);
		a *= -1;
	}
	b = bb;
}

DROB DROB::operator-() const
{
	if (R != 0)
		return DROB(-R, a, b);
	else
		return DROB(R, -a, b);
}
const DROB& DROB::operator=(const int& dd) 
{
	R = dd;
	a = 1;
	b = 1;
	return *this;
}

DROB DROB::operator+(const DROB& link) const
{
	return DROB(R + link.R, a * link.b + link.a * b, b * link.b);
}
DROB DROB::operator+(const int& dd) const
{
	return DROB(R, a + dd * b, b);
}
DROB operator+(const int& dd, const DROB& link)
{
	return DROB(link.R, link.a + dd * link.b, link.b);
}

DROB DROB::operator-(const DROB& link) const
{
	return DROB(R - link.R, a * link.b - link.a * b, b * link.b);
}
DROB DROB::operator-(const int& dd) const
{
	return DROB(R, a - dd * b, b);
}
DROB operator-(const int& dd, const DROB& link)
{
	return DROB(link.R, link.a + dd * link.b, link.b);
}

DROB DROB::operator*(const DROB& link) const
{
	return DROB(0, (b * R + a) * (link.b * link.R + link.a), b * link.b);
}
DROB DROB::operator*(const int& dd) const
{
	return DROB(0,dd*(b*R+a),b);
}
DROB operator*(const int& dd, const DROB& link)
{
	return DROB(0, dd * (link.b * link.R + link.a),link.b);
}

DROB DROB::operator/(const DROB& link) const
{
	if (link.a == 0)
		throw std::exception("ERROR! Division by zero!");
	return DROB(0, (b * R + a) * link.b, b * (link.b * link.R + link.a));
}
DROB DROB::operator/(const int& dd) const
{
	if (dd == 0)
		throw std::exception("ERROR! Division by zero!");
	return DROB(0, b * R + a, b * dd);
}
DROB operator/(const int& dd, const DROB& link)
{
	if (link.a == 0)
		throw std::exception("ERROR! Division by zero!");
	return DROB(0, link.b * dd, link.b * link.R + link.a);
}

const DROB& DROB::operator+=(const DROB& link)
{
	R = R + link.R;
	a = a * link.b + link.a * b;
	b = b * link.b;
	SETa(a);
	return *this;
}
const DROB& DROB::operator+=(const int& dd)
{
	a = a + dd * b;
	SETa(a);
	return *this;
}

const DROB& DROB::operator-=(const DROB& link)
{
	R = R - link.R;
	a = a * link.b - link.a * b;
	b = b * link.b;
	SETa(a);
	return *this;
}
const DROB& DROB::operator-=(const int& dd)
{
	a = a - dd * b;
	SETa(a);
	return *this;
}

const DROB& DROB::operator*=(const DROB& link)
{
	R = 0;
	a = (b * R + a) * (link.b * link.R + link.a);
	b = b * link.b;
	SETa(a);
	return *this;
}
const DROB& DROB::operator*=(const int& dd)
{
	R = 0;
	a = dd * (b * R + a);
	SETa(a);
	return *this;
}

const DROB& DROB::operator/=(const DROB& link)
{
	R = 0;
	a = (b * R + a) * link.b;
	b = b * (link.b * link.R + link.a);
	SETa(a);
	return *this;
}
const DROB& DROB::operator/=(const int& dd)
{
	R = 0;
	a = b * R + a;
	b = b * dd;
	SETa(a);
	return *this;
}

bool DROB::operator==(const DROB& link) const
{
	return ((R == link.R) && (a == link.a) && (b == link.b));
}
bool DROB::operator!=(const DROB& link) const
{
	return (!(this->operator==(link)));
}
bool DROB::operator==(const int& dd) const
{
	return ((R == dd) && (a == 1) && (b == 1));
}
bool DROB::operator!=(const int& dd) const
{
	return (!(this->operator==(dd)));
}
bool operator==(const int& dd, const DROB& link)
{
	return ((link.R == dd) && (link.a == 1) && (link.b == 1));
}
bool operator!=(const int& dd, const DROB& link)
{
	return (!(link.operator==(dd)));
}

bool DROB::operator>(const DROB& link) const
{
	return (((b * R + a) * link.b) > ((link.b * link.R + link.a) * b));
}
bool DROB::operator>=(const DROB& link) const
{
	return (((b * R + a) * link.b) >= ((link.b * link.R + link.a) * b));
}
bool DROB::operator>(const int& dd) const
{
	return ((b * R + a) > (dd*b));
}
bool operator>(const int& dd, const DROB& link)
{
	return ((link.b * link.R + link.a) > (dd * link.b));
}
bool DROB::operator>=(const int& dd) const
{
	return ((b * R + a) >= (dd * b));
}
bool operator>=(const int& dd, const DROB& link)
{
	return ((link.b * link.R + link.a) >= (dd * link.b));
}


bool DROB::operator<(const DROB& link) const
{
	return (((b * R + a) * link.b) < ((link.b * link.R + link.a) * b));
}
bool DROB::operator<=(const DROB& link) const
{
	return (((b * R + a) * link.b) <= ((link.b * link.R + link.a) * b));
}
bool DROB::operator<(const int& dd) const
{
	return ((b * R + a) < (dd * b));
}
bool operator<(const int& dd, const DROB& link)
{
	return ((link.b * link.R + link.a) < (dd * link.b));
}
bool DROB::operator<=(const int& dd) const
{
	return ((b * R + a) <= (dd * b));
}
bool operator<=(const int& dd, const DROB& link)
{
	return ((link.b * link.R + link.a) <= (dd * link.b));
}

DROB& DROB::operator++()
{
	R++;
	return *this;
}
DROB DROB::operator++(int)
{
	DROB link(*this);
	R++;
	return link;
}

DROB& DROB::operator--()
{
	R--;
	return *this;
}
DROB DROB::operator--(int)
{
	DROB link(*this);
	R--;
	return link;
}