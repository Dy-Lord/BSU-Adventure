#include<iostream>
#include<ctime>
#include<limits.h>
using namespace std;
int SPM(int x)
{
	int D=2,S=0,DD;
	while (x > 1)
	{
		while ((x % D) == 0)
		{
			if (D > 10)
			{
				DD = D;
				while (DD)
				{
					S += DD % 10;
					DD /= 10;
				}
			}
			else
				S += D;
			x /= D;
		}
		D++;
	}
	return S;
}

 bool simple(int x)
{
	int n = x / 2;
	for (int i = 2; i <= n; i++)
		if (x % i == 0)
			return false;
	return true;
}

 int SMIT(int a)
 {
	int t = a;
	int s = 0;
	 while (t)
	 {
		 s += t % 10;
		 t /= 10;
	 }
	 if ((SPM(a) == s) && (simple(a) == false))
		 return a;
	 else return 0;
 }
int main()
	{
	setlocale(LC_ALL, ".1251");
	int a, b, s=0, t,count=0;
	cout << "Введите промежуток [a,b] для чисел Смитта, где a и b натуральные числа" << endl;
	cin >> a >> b;
	if (a <= 0 || b <= 0 || b < a)
	{
		cout << "Ошибка---введите корректный промежуток!" << endl;
		system("pause");
		return 0;
	}
	cout << "Числа Смитта: " << endl;
	unsigned t1 = time(0);
	for(a;a<=b;a++)
	{
		if (SMIT(a))
		{
			cout << SMIT(a) << endl;
			count++;
		}
		/*
		t = a;
		s = 0;
		while (t)
		{
			s += t % 10;
				t /= 10;
		}
		if ((SPM(a) == s)&&(simple(a)==false))
		{
			cout << a << endl;
			count++;
		}
		*/
	}
	unsigned t2 = time(0);
	if(count==0)
		cout << "Чисел Смитта нет на указанном промежутке! " << endl;
	else
	cout << "Найдено " << count << " чисел Смитта на данном промежутке!" << endl;
	cout << "Время работы = " << t2 - t1 << "мс" << endl;
	system("pause");
	return 0;
	}
