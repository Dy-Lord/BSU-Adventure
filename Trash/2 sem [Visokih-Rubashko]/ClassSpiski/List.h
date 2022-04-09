#pragma once
#include <iostream>
#include <string>

struct ListItem
{
	std::string FIO;
	std::string DATA;

	std::string NUMBER;
	std::string TIME;

	ListItem* Next;
};