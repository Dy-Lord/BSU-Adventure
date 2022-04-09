#pragma once
#include<iostream>
#include<string>
#include <ostream>

class PRAM
{
private:

	double X1, X2, Y1, Y2;

public:

	PRAM()
	{
		X1 = 0;                                               
		X2 = 0;                                                   
		Y1 = 0;                                                     
		Y2 = 0;
	}

	PRAM(double x1, double y1, double x2, double y2)
	{
		X1 = x1;                                                        // X1 - οπΰβΰÿ βεπυνÿÿ               A———————————————B
		X2 = x2;                                                        // Y1 - οπΰβΰÿ βεπυνÿÿ               |               |
		Y1 = y1;                                                        // X2 - νθζνÿÿ λεβΰÿ                 |               |
		Y2 = y2;                                                        // Y2 - νθζνÿÿ λεβΰÿ                 |               |
	}                                                                   //                                   D———————————————C

	PRAM(const PRAM& cp)
	{
		X1 = cp.GetX1();
		X2 = cp.GetX2();
		Y1 = cp.GetY1();
		Y2 = cp.GetY2();
	}

	double GetX1() const
	{
		return X1;
	}
	double GetY1() const
	{
		return Y1;
	}
	double GetX2() const
	{
		return X2;
	}
	double GetY2() const
	{
		return Y2;
	}

	void SetX1(double x1)
	{
		X1 = x1;
	}
	void SetY1(double y1)
	{
		Y1 = y1;
	}
	void SetX2(double x2)
	{
		X2 = x2;
	}
	void SetY2(double y2)
	{
		Y2 = y2;
	}


	std::string to_String() const;
	std::string View() const;
	void print() const;

	void POX(const double&);
	void POY(const double&);
	double SSS() const;
	void BUILD(PRAM, PRAM);
	friend std::ostream& operator <<(std::ostream&, const PRAM&);
};

