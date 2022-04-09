#include "Student.h"

Person::Person():ID(++nextID)
{
	name = new char[7];
	strcpy(name, "Noname");
}
Person::Person(const char* str):ID(++nextID)
{
	if (str == nullptr)
		throw exception("Error! Null pointer!");

	name = new char[strlen(str) + 1];
	strcpy(name, str);
}
Person::Person(const Person& P):ID(P.ID)
{
		name = new char[strlen(P.name) + 1];
		strcpy(name, P.name);
}
Person::~Person()
{
	delete[] name;
}

void Person::Print(ostream& out) const
{
	out << name << '\t' << ID << '\n';
}

void Person::Getname(char* P) const
{
	if (P == nullptr)
		throw exception("Error! Null pointer!");
	strcpy(P, name);
}
void Person::SetName(const char* str)
{
	if (str == nullptr)
		throw exception("Error! Null pointer!");

	delete[] name;
	name = new char[strlen(str) + 1];
	strcpy(name, str);
}

const Person& Person::operator=(const Person& P)
{
	if (this != &P)
	{
		delete[] name;
		name = new char[strlen(P.name) + 1];
		strcpy(name, P.name);
	}

	return *this;
}
ostream& operator<<(ostream& out, const Person& P)
{

	P.Print(out);
	return out;
}

Student::Student()
{
	course = 0;
	group = 0;
}
Student::Student(const char* str, const int c, const int g)
{
	SetName(str);
	course = c;
	group = g;
}
Student::Student(const Student& S)
{
	SetName(S.name);
	course = S.course;
	group = S.group;
}

void Student::Print(ostream& out) const
{
	out << name << '\t' << ID << '\t' << course << '\t' << group << '\n';
}
const Student& Student::operator=(const Student& S)
{
	if (this != &S)
	{
		SetName(S.name);
		course = S.course;
		group = S.group;
	}

	return *this;
}

Teacher::Teacher()
{
	depart = new char[9];
	strcpy(depart, "Nodepart");
}
Teacher::Teacher(const char* name, const char* str)
{
	if (str == nullptr)
		throw exception("Error! Null pointer!");

	SetName(name);

	depart = new char[strlen(str) + 1];
	strcpy(depart, str);

}
Teacher::Teacher(const Teacher& T)
{
	SetName(T.name);
	
	depart = new char[strlen(T.depart) + 1];
	strcpy(depart, T.depart);
}
Teacher::~Teacher()
{
	delete[] depart;
}

void Teacher::Print(ostream& out) const
{
	out << name << '\t' << ID << '\t' << depart << '\n';
}

void Teacher::GetDepart(char* P) const
{
	if (P == nullptr)
		throw exception("Error! Null pointer!");
	strcpy(P, depart);
}
void Teacher::SetDepart(const char* str)
{
	if (str == nullptr)
		throw exception("Error! Null pointer!");

	delete[] depart;
	depart = new char[strlen(str) + 1];
	strcpy(depart, str);
}

const Teacher& Teacher::operator=(const Teacher& P)
{
	if (this != &P)
	{
		SetName(P.name);
		delete[] depart;
		depart = new char[strlen(P.depart) + 1];
		strcpy(depart, P.depart);
	}

	return *this;
}

int Person::nextID = 0;
