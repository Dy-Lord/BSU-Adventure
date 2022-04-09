#pragma once
#include <iostream>
#include <string>
#include <exception>

class DROB
{
private:
	                                         //     a
	int a, b;                               //   R ———
	int R;                                  //      b

public:

	DROB()
	{
		R = 0;
		a = 1;
		b = 1;
	}
	DROB(int RR, int aa, int bb)
	{
		if (bb == 0)
			throw std::exception("ERROR! Division by zero!");

		if (bb < 0)
		{
			bb = abs(bb);
			aa *= -1;
		}

		if (RR < 0 && aa < 0)
		{
			RR = abs(RR);
			aa = abs(aa);
		}

		if (RR > 0 && aa < 0)
		{
			RR *= -1;
			aa = abs(aa);
		}

		R = RR;
		a = aa;
		b = bb;

		SETa(aa);
	}
	DROB(const DROB& cp)
	{
		R = cp.GETR();
		a = cp.GETa();
		b = cp.GETb();
	}

	int GETR() const
	{
		return R;
	}
	int GETa() const
	{
		return a;
	}
	int GETb() const
	{
		return b;
	}

	void SETR(int);
	void SETa(int);
	void SETb(int);

	friend std::ostream& operator <<(std::ostream&, const DROB&);
	
	DROB operator - () const;   
	const DROB& operator = (const int&);

	DROB operator + (const DROB&) const;
	DROB operator + (const int&) const;
	friend DROB operator + (const int&, const DROB&);
	
	DROB operator - (const DROB&) const;
	DROB operator - (const int&) const;
	friend DROB operator - (const int&, const DROB&);
	
	DROB operator * (const DROB&) const;
	DROB operator * (const int&) const;
	friend DROB operator * (const int&, const DROB&);

	DROB operator / (const DROB&) const;
	DROB operator / (const int&) const;
	friend DROB operator / (const int&, const DROB&);

	const DROB& operator +=(const DROB&);
	const DROB& operator +=(const int&);

	const DROB& operator -=(const DROB&);
	const DROB& operator -=(const int&);

	const DROB& operator *=(const DROB&);
	const DROB& operator *=(const int&);

	const DROB& operator /=(const DROB&);
	const DROB& operator /=(const int&);

	bool operator == (const DROB&) const;
	bool operator != (const DROB&) const;
	bool operator == (const int&) const;
	bool operator != (const int&) const;
	friend bool operator == (const int&, const DROB&);
	friend bool operator != (const int&, const DROB&);

	bool operator > (const DROB&) const;
	bool operator >= (const DROB&) const;
	bool operator > (const int&) const;
	friend bool operator > (const int&, const DROB&);
	bool operator >= (const int&) const;
	friend bool operator >= (const int&, const DROB&);

	bool operator < (const DROB&) const;
	bool operator <= (const DROB&) const;
	bool operator < (const int&) const;
	friend bool operator < (const int&, const DROB&);
	bool operator <= (const int&) const;
	friend bool operator <= (const int&, const DROB&);

	DROB& operator ++ ();
	DROB operator ++ (int);

	DROB& operator -- ();
	DROB operator -- (int);
};