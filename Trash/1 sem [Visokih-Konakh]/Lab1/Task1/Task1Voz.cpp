#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, ".1251");
	double x,y,z;
	cout << "¬ведите три действительных числа " << endl;
	cin >> x;
	cin >> y;
	cin >> z;
	cout << "S = " << (1 + pow(sin(x + y), 2)) / abs(x - (2 * y / (1 + x * x * y * y))) * pow(x, (abs(y))) + pow(cos(atan(1 / z)), 2) << endl;
	system("pause");
	return 0;
}