#include<iostream>
#include<windows.h>
#include<ctime>
#include<chrono>
#include<algorithm>
#include"Header1.h"

using namespace std;

extern unsigned long long swotch, sravn;

void sortrust(int*& arr, int SIZE)
{
	double fakt = 1.2473309;
	int len = SIZE / fakt;
	int stop = 0;

	if (SIZE == 1)
		return;

	while (true)
	{
		for (int i = 0; (i < SIZE) && (i + len < SIZE); i++)
		{
			sravn++;
			if (arr[i] > arr[i + len])
			{
				swotch++;
				swap(arr[i], arr[i + len]);
			}
		}

		if (len != 1)
			len /= fakt;

		else
		{
			len = 0;
			stop = 1;
		}

		if (stop)
			break;
	}

}