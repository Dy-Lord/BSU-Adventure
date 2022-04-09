#include "Driver.h"

CEmployee::CEmployee(const char* str, Sex aPol) throw(char*) :ID(++ID_Repository),Pol(aPol)
{
	if (str == nullptr)
		throw std::exception("Error! Null pointer!");

	name = new char[strlen(str) + 1];
	strcpy(name, str);
}
CEmployee::CEmployee(const CEmployee& Ob) :ID(Ob.ID), Pol(Ob.Pol)
{
	name = new char[strlen(Ob.name) + 1];
	strcpy(name, Ob.name);
}
CEmployee::~CEmployee()
{
	delete[] name;
}

const char* CEmployee::GetName() const
{
	return name;
}
void CEmployee::SetName(const char* str) throw(char*)
{
	if (str == nullptr)
		throw std::exception("Error! Null pointer!");

	delete[] name;
	name = new char[strlen(str) + 1];
	strcpy(name, str);
}

void CEmployee::InStream(std::ostream& out) const
{
	if (Pol == 0)
		out << "Имя" << '\t' << name << "Пол" << '\t' << 'M' << '\t' << "Номер лицензии" << '\t' << ID << '\n';
	else
		out << "Имя" << '\t' << name << "Пол" << '\t' << 'Ж' << '\t' << "Номер лицензии" << '\t' << ID << '\n';
}
const CEmployee& CEmployee::operator=(const CEmployee& S)
{
	if (this != &S)
	{
		SetName(S.name);
	}

	return *this;
}
std::ostream& operator<<(std::ostream& out, const CEmployee& P)
{
	P.InStream(out);
	return out;
}

CDriver::CDriver(const char* name, Sex aPol, const char* str) throw(char*) :CEmployee(name, aPol)
{
	if (str == nullptr)
		throw std::exception("Error! Null pointer!");

	LicenceType = new char[strlen(str) + 1];
	strcpy(LicenceType, str);
}
CDriver::CDriver(const CDriver& T):CEmployee(T.name, T.Pol)
{
	LicenceType = new char[strlen(T.LicenceType) + 1];
	strcpy(LicenceType, T.LicenceType);
}
CDriver::~CDriver()
{
	delete[] LicenceType;
}

const char* CDriver::GetLicenceType() const
{
	return LicenceType;
}
void CDriver::SetLicenceType(const char* str) throw(char*)
{
	if (str == nullptr)
		throw std::exception("Error! Null pointer!");

	delete[] LicenceType;
	LicenceType = new char[strlen(str) + 1];
	strcpy(LicenceType, str);
}

void CDriver::InStream(std::ostream& out) const
{
	if (Pol == 0)
		out << "Имя" << '\t' << name << '\t' << "Пол" << '\t' << 'M' << '\t' << "Тип лицензии" << '\t' << LicenceType << '\t' << "Номер лицензии" << '\t' << ID << '\n';
	else
		out << "Имя" << '\t' << name << '\t' << "Пол" << '\t' << 'Ж' << '\t' << "Тип лицензии" << '\t' << LicenceType << '\t' << "Номер лицензии" << '\t' << ID << '\n';
}
const CDriver& CDriver::operator=(const CDriver& S)
{
	if (this != &S)
	{
		SetName(S.name);
		SetLicenceType(S.LicenceType);
	}

	return *this;
}

CTempDriver::CTempDriver(const char* aName, Sex aPol, const char* aLicenceType, int str) :CDriver(aName, aPol, aLicenceType), ContractEnd(str) {}
CTempDriver::CTempDriver(const CTempDriver& Ob) : CDriver(Ob.name, Ob.Pol, Ob.LicenceType), ContractEnd(Ob.ContractEnd) {}
CTempDriver::~CTempDriver() {}

CTempDriver& CTempDriver::operator=(const CTempDriver& S)
{
	if (this != &S)
	{
		SetName(S.name);
		SetLicenceType(S.LicenceType);
	}

	return *this;
}

void CTempDriver::InStream(std::ostream& out) const
{
	if (Pol == 0)
		out << "Имя" << '\t' << name << '\t' << "Пол" << '\t' << 'M' << '\t' << "Тип лицензии" << '\t' << LicenceType << '\t' << "Номер лицензии" << '\t' << ID << '\t' << "Срок контракта (мес)" << '\t' << ContractEnd << '\n';
	else
		out << "Имя" << '\t' << name << '\t' << "Пол" << '\t' << 'Ж' << '\t' << "Тип лицензии" << '\t' << LicenceType << '\t' << "Номер лицензии" << '\t' << ID << '\t' << "Срок контракта (мес)" << '\t' << ContractEnd << '\n';
}

int CEmployee::ID_Repository = 0;
