
/*
----------------
1111
????? ????????????? ???????????? ?????????? ??? = 1
?????????? ?????????? ???????????? ????? = 4
????? ? ????????? ??????(-???) = 0
----------------
123345
????? ????????????? ???????????? ?????????? ??? = 3
?????????? ?????????? ???????????? ????? = 2
????? ? ????????? ??????(-???) = 1245
----------------
1223345
????? ????????????? ???????????? ?????????? ??? = 2
?????????? ?????????? ???????????? ????? = 2
????????! ??????? ?????? ?????, ????????????? ???????????? ?????????? ??? = 3
?????????? ?????????? ???????????? ????? = 2
????? ? ????????? ??????(-???) = 145
------------------
12345
????? ????????????? ???????????? ?????????? ??? = 1
?????????? ?????????? ???????????? ????? = 1
????????! ??????? ?????? ?????, ????????????? ???????????? ?????????? ??? = 2
?????????? ?????????? ???????????? ????? = 1
????????! ??????? ?????? ?????, ????????????? ???????????? ?????????? ??? = 3
?????????? ?????????? ???????????? ????? = 1
????????! ??????? ?????? ?????, ????????????? ???????????? ?????????? ??? = 4
?????????? ?????????? ???????????? ????? = 1
????????! ??????? ?????? ?????, ????????????? ???????????? ?????????? ??? = 5
?????????? ?????????? ???????????? ????? = 1
????? ? ????????? ??????(-???) = 0
---------------------------
122334455
????? ????????????? ???????????? ?????????? ??? = 2
?????????? ?????????? ???????????? ????? = 2
????????! ??????? ?????? ?????, ????????????? ???????????? ?????????? ??? = 3
?????????? ?????????? ???????????? ????? = 2
????????! ??????? ?????? ?????, ????????????? ???????????? ?????????? ??? = 4
?????????? ?????????? ???????????? ????? = 2
????????! ??????? ?????? ?????, ????????????? ???????????? ?????????? ??? = 5
?????????? ?????????? ???????????? ????? = 2
????? ? ????????? ??????(-???) = 1
*/

#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, ".1251");
	int a, i,c=0, MAX=0, t ,MaxC=0,n=0,MACC=0,g=0;
	cin >> t;
	do
	{
		for (i = 0; i < 10; i++)
		{
			a = t;
			while (a > 0)
			{
				if (a % 10 == i)
					c++;
				a /= 10;
			}
			if (c > MaxC)
			{
				MaxC = c;
				MAX = i;
			}
			c = 0;
		}
		if (g > 0)
		{
			if (MaxC == MACC)
				cout << "????????! ??????? ?????? ?????, ????????????? ???????????? ?????????? ??? = " << MAX << endl;
			else
			{
				cout << "????? ? ????????? ??????(-???) = " << t << endl;
				system("pause");
				return 0;
			}
		}
		a = 0;
		while (t > 0)
		{
			if ((t % 10) != MAX)
			{
				a = (t % 10) * pow(10, n) + a;
				n++;
			}
			t /= 10;
		}
		n = 0;
		if(g==0)
		cout << "????? ????????????? ???????????? ?????????? ??? = " << MAX << endl;
		cout << "?????????? ?????????? ???????????? ????? = " << MaxC << endl;
		MACC = MaxC;
		MaxC = 0;
		MAX = 0;
		t = a;
		i = 0;
		g++;
	} while (true);
	
}
