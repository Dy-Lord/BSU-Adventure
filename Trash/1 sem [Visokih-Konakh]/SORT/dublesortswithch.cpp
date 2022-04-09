#include<iostream>
#include<windows.h>
#include<ctime>
#include<chrono>
#include<algorithm>
#include"Header1.h"

using namespace std;

extern unsigned long long swotch, sravn;

void dublesortswithch(int*& arr, int SIZE)
{
	int i = 0;
	int MAX = SIZE - 1;
	int MIN = i;
	bool stop=1;

	if (SIZE == 1)
		return;

	if (SIZE == 2)
	{
		sravn++;
		if (arr[0] > arr[1])
		{
			swap(arr[0], arr[1]);
			swotch++;
		}
			return;
	}

	while (stop)
	{

		for (int j=i; j < SIZE; j++)
		{
			sravn += 2;
			if (arr[j] <= arr[MIN])
				MIN = j;
			if (arr[SIZE - 1 - j] >= arr[MAX])
				MAX = SIZE - 1 - j;
		}

		sravn++;
		if (arr[MIN] != arr[MAX])
		{
			sravn += 2;
			if (i != MIN)
			{
				swotch++;
				swap(arr[i], arr[MIN]);
				if (MAX == i)
					MAX = MIN;
			}
			if ((SIZE -1 - i) != MAX)
			{
				swotch++;
				swap(arr[SIZE - 1 - i], arr[MAX]);
			}
		}
		i++;
		MIN = i;
		MAX = SIZE -1 - i;
		if (i == (SIZE - 1 - i))
			stop = 0;
		if ((i + 1) == (SIZE - 1 - i))
			stop = 0;
	}

	if (i + 1 == SIZE - 1 - i)
	{
		sravn++;
			if (arr[i] > arr[i + 1])
			{
				swotch++;
				swap(arr[i], arr[i + 1]);
			}
	}

}