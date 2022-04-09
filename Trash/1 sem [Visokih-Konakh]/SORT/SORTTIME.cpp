#include<iostream>
#include <ctime>
#include<chrono>
#include <fstream>
#include<windows.h>
#include <algorithm>
#include"Header1.h"
#include<stdlib.h> 
#include<stdio.h>
#include <fstream>
#include <string>
#pragma warning(disable:4996)

using namespace std;
using namespace std::chrono;

extern unsigned long long swotch, sravn;

void SORTTIME(int SIZE)
{
	int* arr = new int[SIZE + 1];
	char* s = new char[SIZE + 1];

	setlocale(LC_ALL, "ru");
	ofstream output;
	output.open("C:\\Users\\User01\\Desktop\\Labs\\LabsOne\\SORT\\output.txt");

	ifstream input;
	input.open("C:\\Users\\User01\\Desktop\\Labs\\LabsOne\\SORT\\input.txt");


	string str, slovo;
	int i = 0, pos = 0, nach = 0, kon = 0;
	if (input.is_open())
	{
		getline(input, str);
		while ((nach = str.find_first_not_of(" ", nach)) != -1)
		{
			kon = str.find_first_of(" ", nach);
			slovo = str.substr(nach, kon - nach);
			strcpy(s, slovo.c_str());
			arr[i] = atoi(s);
			strcpy(s, "");
			i++;
			nach = kon;
		}
	}
	else
	{
		cout << "ÎØÈÁÊÀ---Íå óäàëîñü îòêðûòü ôàéë!" << endl;
		return;
	}

	int* temparr = new int[SIZE + 1];
	for (int i = 0; i < SIZE; i++)
		temparr[i] = arr[i];

	auto start = system_clock::now();
	dublesortswithch(arr, SIZE);
	auto end = system_clock::now();

	output << "ÄÂÓÑÒÐÎÍÍßß ÑÎÐÒÈÐÎÂÊÀ ÂÛÁÎÐÎÌ" << '\n';
	for (int i = 0; i < SIZE; i++)
		output << arr[i] << " ";
	output << '\n';

	auto elapsed_seconds = duration_cast<seconds>(end - start).count();
	auto elapsed_milliseconds = duration_cast<milliseconds>(end - start).count();

	time_t end_time = system_clock::to_time_t(end);
	cout << "Àëãîðèòì ÄÂÓÑÒÐÎÐÎÍÍÅÉ ÑÎÐÒÈÐÎÂÊÈ ÂÛÁÎÐÎÌ çàâåðø¸í  " << ctime(&end_time)
		<< "Âðåìÿ âû÷èñëåíèÿ â ñåêóíäàõ: " << elapsed_seconds << "s\n"
		<< "Âðåìÿ âû÷èñëåíèÿ â ìèëëèñåêóíäàõ: " << elapsed_milliseconds << "ms\n";

	cout << "Êîëè÷åñòâî îáìåíîâ --- " << swotch << endl;
	cout << "Êîëè÷åñòâî ñðàâíåíèé --- " << sravn << endl;

	cout << endl;

	swotch = 0;
	sravn = 0;

	for (int i = 0; i < SIZE; i++)
		arr[i] = temparr[i];
	
	start = system_clock::now();
	SORTSHELL(arr, SIZE);
	end = system_clock::now();

	output << "ÑÎÐÒÈÐÎÂÊÀ ØÅËËÀ" << '\n';
	for (int i = 0; i < SIZE; i++)
		output << arr[i] << " ";
	output << '\n';

    elapsed_seconds = duration_cast<seconds>(end - start).count();
	elapsed_milliseconds = duration_cast<milliseconds>(end - start).count();

	end_time = system_clock::to_time_t(end);
	cout << "Àëãîðèòì ÑÎÐÒÈÐÎÂÊÈ ØÅËËÀ çàâåðø¸í  " << ctime(&end_time)
		<< "Âðåìÿ âû÷èñëåíèÿ â ñåêóíäàõ: " << elapsed_seconds << "s\n"
		<< "Âðåìÿ âû÷èñëåíèÿ â ìèëëèñåêóíäàõ: " << elapsed_milliseconds << "ms\n";
	cout << "Êîëè÷åñòâî îáìåíîâ --- " << swotch << endl;
	cout << "Êîëè÷åñòâî ñðàâíåíèé --- " << sravn << endl;
	cout << endl;
	swotch = 0;
	sravn = 0;

	for (int i = 0; i < SIZE; i++)
		arr[i] = temparr[i];

	start = system_clock::now();
	sortrust(arr, SIZE);
	end = system_clock::now();

	output << "ÑÎÐÒÈÐÎÂÊÀ ÐÀÑ×¨ÑÊÎÉ" << '\n';
	for (int i = 0; i < SIZE; i++)
		output << arr[i] << " ";
	output << '\n';

	elapsed_seconds = duration_cast<seconds>(end - start).count();
	elapsed_milliseconds = duration_cast<milliseconds>(end - start).count();
	end_time = system_clock::to_time_t(end);
	cout << "Àëãîðèòì ÑÎÐÒÈÐÎÂÊÈ ÐÀÑ×¨ÑÊÎÉ çàâåðø¸í  " << ctime(&end_time)
		<< "Âðåìÿ âû÷èñëåíèÿ â ñåêóíäàõ: " << elapsed_seconds << "s\n"
		<< "Âðåìÿ âû÷èñëåíèÿ â ìèëëèñåêóíäàõ: " << elapsed_milliseconds << "ms\n";
	cout << "Êîëè÷åñòâî îáìåíîâ --- " << swotch << endl;
	cout << "Êîëè÷åñòâî ñðàâíåíèé --- " << sravn << endl;
	output.close();
	input.close();
	delete[] temparr;
	delete[] s;
	delete[] arr;

}