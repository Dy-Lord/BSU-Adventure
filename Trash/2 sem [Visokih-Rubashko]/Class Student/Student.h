#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>
using namespace std;

class Person 
{
protected:

	char* name;
	const int ID;
    static int nextID;

public:
	Person();
	Person(const char*);
	Person(const Person&);

    virtual ~Person();
	virtual void Print(ostream&) const;

	void Getname(char*) const;
	void SetName(const char*);
	int GetID() const { return ID; }

	const Person& operator = (const Person&);
	friend ostream& operator <<(ostream&, const Person&);
};

class Student : public Person
{
protected:

	int course;
	int group;

public:

	Student();
	Student(const char* fio, const int course, const int group);
	Student(const Student&);

	virtual ~Student() {};
	virtual void Print(ostream&) const;

	virtual int GetCourse() const { return course; }
	virtual int GetGroup() const { return group; }

	void SetCourse(const int c) { course = c; }
	void SetGroup(const int g) { group = g; }

	const Student& operator = (const Student&);
};

class Teacher : public Person
{
private:

	char* depart;

public:

	Teacher();
	Teacher(const char* name, const char* depart);
	Teacher(const Teacher&);

	virtual ~Teacher();
	virtual void Print(ostream&) const;

	virtual void GetDepart(char*) const;
	void SetDepart(const char*);

	const Teacher& operator = (const Teacher&);
};
