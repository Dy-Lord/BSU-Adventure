#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>

enum Sex { male, female };

class CEmployee
{
protected:

	const int ID;
	const Sex Pol;

	char* name;
	static int ID_Repository;

public:

	CEmployee(const char* aName, Sex aPol) throw(char*);
	CEmployee(const CEmployee& Ob);
    virtual ~CEmployee();

	int GetID()const { return ID; }
	Sex GetPol()const { return Pol; }
	const char* GetName()const;

	virtual const char* GetPosition()const = 0;
	void SetName(const char* aName)throw(char*);
	virtual void InStream(std::ostream& out) const;

	friend std::ostream& operator << (std::ostream& os, const CEmployee&);
	const CEmployee& operator = (const CEmployee& e);
};

class CDriver : public CEmployee
{
protected:

	char* LicenceType;

public:

	CDriver(const char* aName, Sex aPol, const char* aLicenceType)throw(char*);
	CDriver(const CDriver& Ob);
	virtual ~CDriver();


	const char* GetLicenceType()const;
	virtual const char* GetPosition() const { return "DRIVER"; }

	void SetLicenceType(const char* aLicenceType)throw(char*);

	virtual void InStream(std::ostream& out)const;
	const CDriver& operator = (const CDriver& d);
};

class CTempDriver : public CDriver
{
protected:

	const int ContractEnd;

public:
	CTempDriver(const char* aName, Sex aPol, const char* aLicenceType, int aContractEnd);
	CTempDriver(const CTempDriver& Ob);
	virtual ~CTempDriver();

	virtual const char* GetPosition() const { return "TEMPORARY_DRIVER"; }
	int GetContractEnd()const { return ContractEnd; }
	CTempDriver& operator = (const CTempDriver& Ob);
	void InStream(std::ostream& out)const;
};