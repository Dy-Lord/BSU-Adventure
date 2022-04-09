#include"Header.h"

std::string PRAM::to_String() const
{
	std::string coord = "((";
	coord = coord + std::to_string(X1);
	coord = coord + ',';
	coord = coord + std::to_string(Y1);
	coord = coord + "); (";
	coord = coord + std::to_string(X2);
	coord = coord + ',';
	coord = coord + std::to_string(Y2);
	coord = coord + "))";

	return coord;
}

std::string PRAM::View() const
{
	std::string output;
	output = output + ' ' + '\n' + '\t' + "A———————————————B" + '\n' + '\t' + "|               |" + '\n' + '\t' + "|               |" + '\n' + '\t' + "|               |" + '\n' + '\t' + "D———————————————C" + '\n';
	output = output + '\n';
	output = output + '\t' + "A(" + std::to_string(X2) + ',' + std::to_string(Y1) + ')' + '\n';
	output = output + '\t' + "B(" + std::to_string(X1) + ',' + std::to_string(Y1) + ')' + '\n';
	output = output + '\t' + "C(" + std::to_string(X1) + ',' + std::to_string(Y2) + ')' + '\n';
	output = output + '\t' + "D(" + std::to_string(X2) + ',' + std::to_string(Y2) + ')' + '\n';
	return output;
}


void PRAM::print() const
{
	std::cout << to_String();
}

void PRAM::POX(const double& p) 
{
	Y1 = Y1 + p;
	Y2 = Y2 + p;
}

void PRAM::POY(const double& p) 
{
	X1 = X1 + p;
	X2 = X2 + p;
}

double PRAM::SSS() const
{
	return fabs((X1 - X2) * (Y1 - Y2));
}

void PRAM::BUILD(PRAM one, PRAM two) 
{
	if (one.Y2 >= two.Y2)
		Y2 = two.Y2;
	else
		Y2 = one.Y2;

	if (one.Y1 >= two.Y1)
		Y1 = one.Y1;
	else
		Y1 = two.Y1;

	if (one.X2 >= two.X2)
		X2 = two.X2;
	else
		X2 = one.X2;

	if (one.X1 >= two.X1)
		X1 = one.X1;
	else
		X1 = two.X1;
}

std::ostream& operator<<(std::ostream& S, const PRAM& p)
{
	S << p.View();
	return S;
}