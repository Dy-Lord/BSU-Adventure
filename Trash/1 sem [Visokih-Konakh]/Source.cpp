#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE 

#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
#include<stdio.h>

using namespace std;

int prost(const string& str)
{
	char* end_ptr;
	int dd;

	char* s2 = new char[str.length() + 1];
	strcpy(s2, str.c_str());

	dd = strtol(s2, &end_ptr, 10);

	if (dd < 1)
		return false;

	if ((dd != 0) && (*end_ptr == 0))
	{
		for (int i = 2; i <= dd / 2; i++)
			if (dd % i == 0)
				return false;
	}
	else
		return false;
	return dd;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream input("input.txt", ios::in);
	ofstream output("output.txt", ios::out);

	if (!input)
	{
		output << "������---������� ���� �� ������!";
		output.close();
		return 0;
	}

	string str;
	string sub;
	string temp1;
	int poz1 = 0;
	int subpoz1 = 0;
	int len1, count = 0;

	string MAXSTR, MINSTR;
	int num;
	int MAX, MIN;
	int MAXLEN, MINLEN;
	int MAXPOZ, MINPOZ;

	bool aim = 1;

	if (input.eof())
	{
		output << "������---������� ���� ������!";
		input.close();
		output.close();
		return 0;
	}

	getline(input, sub);

	if (sub == "")
	{
		output << "������---�� ���������� ����������� ����� �������!";
		input.close();
		output.close();
		return 0;
	}


	while (getline(input, str))
	{
		if (str == "") continue;

		str += ' ';

		while ((poz1 = str.find_first_not_of(sub, poz1)) != string::npos)
		{
			subpoz1 = str.find_first_of(sub, poz1);
			len1 = subpoz1 - poz1;
			temp1 = str.substr(poz1, len1);

			if (prost(temp1))
			{
				count++;
				num = prost(temp1);
				if (aim)
				{
					MAXSTR = temp1;
					MINSTR = temp1;
					MAX = prost(temp1);
					MIN = prost(temp1);
					MAXLEN = temp1.length();
					MINLEN = temp1.length();
					MAXPOZ = poz1;
					MINPOZ = poz1;
					aim = 0;
				}
				else
					if (num > MAX)
					{
						MAXSTR = temp1;
						MAX = num;
						MAXLEN = temp1.length();
						MAXPOZ = poz1;
					}
					else
						if (num < MIN)
						{
							MINSTR = temp1;
							MIN = num;
							MINLEN = temp1.length();
							MINPOZ = poz1;
						}
			}
			poz1 = subpoz1;
		}

		if (count < 2)
			str.insert(0, "*");
		else
		{
			if (MAXPOZ > MINPOZ)
			{

				str.erase(MAXPOZ, MAXLEN);
				str.insert(MAXPOZ, MINSTR);

				str.erase(MINPOZ, MINLEN);
				str.insert(MINPOZ, MAXSTR);
			}
			else
			{
				str.erase(MINPOZ, MINLEN);
				str.insert(MINPOZ, MAXSTR);

				str.erase(MAXPOZ, MAXLEN);
				str.insert(MAXPOZ, MINSTR);
			}
		}

		output << str << endl;
		count = 0;
		poz1 = 0;
	}

	input.close();
	output.close();
	return 0;
}

///////////////////////////////////////////////////////////////////

/*
lolol frgr erdf lolol fs 3432
lolololol lolololol rg jisf gre jf 3 fsrg ef 3
weew reer weew reer
12 21 we ew
31
er 12345 54321 y er
olret terlo
*/

#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
#include<stdio.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream input("input.txt", ios::in);
	ofstream output("output.txt", ios::out);

	if (!input)
	{
		output << "������---������� ���� �� ������!";
		output.close();
		return 0;
	}

	string str, inputstr;
	string sub = " ,.;:";
	string temp1, temp2;
	int poz1 = 0, poz2 = 0;
	int subpoz1 = 0, subpoz2 = 0;
	int len1, len2, count = 0;

	if (input.eof())
	{
		output << "������---������� ���� ������!";
		input.close();
		output.close();
		return 0;
	}

	ofstream temple("temple.txt", ios::out);

	while (getline(input, str))
	{
		if (str == "") { count++; continue; }

		str += ' ';

		count++;
		while ((poz1 = str.find_first_not_of(sub, poz1)) != string::npos)
		{
			subpoz1 = str.find_first_of(sub, poz1);
			len1 = subpoz1 - poz1;
			temp1 = str.substr(poz1, len1);
			int temppoz = subpoz1;
			while ((poz2 = str.find_first_not_of(sub, subpoz1)) != string::npos)
			{
				subpoz2 = str.find_first_of(sub, poz2);
				len2 = subpoz2 - poz2;
				temp2 = str.substr(poz2, len2);
				if (len1 != len2) { subpoz1 = subpoz2; continue; }
				else
				{
					bool stop = 0;
					for (int i = 0; i < len1; i++)
						if (temp1[i] != temp2[len1 - 1 - i]) { stop = 1; break; }

					if (stop) subpoz1 = subpoz2;
					else
					{
						output << count << "->" << temp1 << ' ' << temp2 << endl;
						str.erase(poz2, len2);
						str.erase(poz1, len1);
						temppoz = 0;
						break;
					}
				}
			}
			poz1 = temppoz;
		}
		temple << str << endl;
		poz1 = 0;
	}

	temple.close();
	input.close();
	output.close();

	ifstream templel("temple.txt", ios::in);
	ofstream unput("input.txt", ios::out | ios::trunc);
	string copy;

	while (getline(templel, str))
	{
		unput << str << endl;;
	}

	templel.close();
	unput.close();
	remove("temple.txt");
	return 0;
}

/////////////////////////////////////////////////////
/*
������ ���� string
�������� ����������� ���������� ��� ������ �� �������� ���� string ����������
���������� ��� ����������� ������������� ����� <string>. ���������� ��������
������� ������ �� �������� ���� string.
������ string ����� ���������������� ������������, ������ ������� string,
���������� ������ string ��� ������������������� ��������. ������ � ������
���������������� �������� ��� ������. ��������, string s0; // ������
������
string s1 = "Hello, wolrd!";// ������������� ��������� ����������
char s[] ="Hello, wolrd!"; // �����������
string s11(s); // ��� ����� �������������� ����������� � string
string s12 = s; // ��� ���� ����� �������������� ����������� � string
string s2 = s1; // ����� s1, ����� �������� � ���: string s2(s1);
string s3(s2, 0, 5); // 5 �������� �� s2, ������� � �������, �� ���� "Hello"
string s4(7, 'q'); // 7 �������� 'q', �� ���� "qqqqqqq"
������ �������� ������ ������ n. � ������ ����� ������������� ����� ��������
������, � ������� ��������� n ����� ���������� ������� (������ s4).
����� ������ ������������ �������� length(), ��������, s4.length() �����
�������� 7. �������, ��� ���������� ����� ������ �� ������������ �� �������
������������� �����, ����������� �����������. ���������� string ������ �����
������, �� ��������� �� ����������� ������ '\0'. ������� � ������ ����������,
������� � 0, ��� ��� ������ � ��� ������������������ �������� � �������� �� 0 ��
length()�1.
��� �������� ����� ��������� ���������� ��������:
������������: =
������������: + , += ,
���������: = = , < , > , >= , <=,
��������������: [] ,
���������: >>, << .
��� �������� ��������� ������������ ������� string � ���������� ����������.
� ���������� ����� ��������� ������ string � �����������. ������� ��������, ��� ���
������������� � ������������� �������������� ������ string ����� ������������� ��
���� ���������� � ������������ � �������� ����� ������. ������ string ����� �����
��������� ���� ������ ��� �������� ���� ������.
����� ���������� ������� � ����� ������ string. ������������ ���������
�����������: pos �������� �������, � n � ���������� �������� � ������ � ������� ������
string, ��� ������� ���������� �������; pos1 �������� �������, � n1 � ����������
�������� � ������, ������� ��������� ������� ��� ��������; npos �������� ����
�������� ������.
������������ ����� � ������ �����
string& assign(const string& s); //��������, s4.assign(s1);
string& assign(const string& s, size_t pos1, size_t n1); //s4.assign(s1, 7, 5);
string& assign(const char* p);//��������, s4.assign(s);
string& assign(const char* p, size_t n1);//��������, s4.assign(s, 5);
string& assign(size_t n1, char c);//��������, s4.assign(5, 'q');
���������� ����� � ������ �����
string& append(const string& s);
string& append(const string& s, size_t pos1, size_t n1);
string& append(const char* p);
string& append(const char* p, size_t n1);
string& append(size_t n1, char c);
������� ����� � ������ �����
string& insert(size_t pos, const string& s);
string& insert(size_t pos, const string& s, size_t pos1, size_t n1);
string& insert(size_t pos, const char* p);
string& insert(size_t pos, const char* p, size_t n1);
string& insert(size_t pos, size_t n1, char c);
������ � �������
string& replace(size_t pos, size_t n, const string& s);
string& replace(size_t pos, size_t n, const string& s, size_t pos1, size_t n1);
string& replace(size_t pos, size_t n, const char* p);
string& replace(size_t pos, size_t n, const char* p, size_t n1);
string& replace(size_t pos, size_t n, size_t n1, char c);
�������� ���������
string& erase(size_t pos = 0, size_t n = npos);
����� ��������
//������� ���������� ����� ������ � ������, ���� ����� ���������� �������, � //�1 �
��������� ������.
//����� ������� ��������� ��������� � ������
size_t find(const string& s, size_t pos = 0) const;
size_t find(const char* p, size_t pos = 0) const;
size_t find(const char* p, size_t pos, size_t n1) const;
size_t find(const char c, size_t pos = 0) const;
//����� ���������� ��������� ��������� � ������
size_t rfind(const string& s, size_t pos = npos) const;
size_t rfind(const char* p, size_t pos = npos) const;
size_t rfind(const char* p, size_t pos, size_t n1) const;
size_t rfind(const char c, size_t pos = npos) const;
//����� ������� ��������� ������ ������� ��������� � ������
size_t find_first_of(const string& s, size_t pos = 0) const;
size_t find_first_of(const char* p, size_t pos = 0) const;
size_t find_first_of(const char* p, size_t pos, size_t n1) const;
size_t find_first_of(const char c, size_t pos = 0) const;
//����� ���������� ��������� ������ ������� ��������� � ������
size_t find_last_of(const string& s, size_t pos = npos) const;
size_t find_last_of(const char* p, size_t pos = npos) const;
size_t find_last_of(const char* p, size_t pos, size_t n1) const;
size_t find_last_of(const char c, size_t pos = npos) const;
//����� � ������ ������� �������, �������� ��� ���������
size_t find_first_not_of(const string& s, size_t pos = 0) const;
size_t find_first_not_of(const char* p, size_t pos = 0) const;
size_t find_first_not_of(const char* p, size_t pos, size_t n1) const;
size_t find_first_not_of(const char c, size_t pos = 0) const;
//����� � ������ ���������� �������, �������� ��� ���������
size_t find_last_not_of(const string& s, size_t pos = npos) const;
size_t find_last_not_of(const char* p, size_t pos = npos) const;
size_t find_last_not_of(const char* p, size_t pos, size_t n1) const;
size_t find_last_not_of(const char c, size_t pos = npos) const;
��������� �����
// ������� ���������� �������� �1, 0, 1, ���� ������ � ������, ��� ������� //����������
�������, �������������� ������, ����� ��� ������ ������, ������� //���������
������� ��� ��������.
int compare(const string& s)const;
int compare(size_t pos, size_t n, const string& s)const;
int compare(size_t pos, size_t n, const string& s, size_t pos1, size_t n1,)const;
int compare(const char* p)const;
int compare(size_t pos, size_t n, const char* p, size_t n1 = npos)const;
������� getline()
istream& getline(istream&, string& s);
istream& getline(istream&, string& s, char term);
�������������� � �����������
const char* c_str() const;
������� �� ���� string � ��� char * ���������� ������. ����� string ����� � �����
������� ����� c_str, ������� ���������� ��������� �� ����-��������������� ������,
������ �������������� ������ ��� ���� �� ����������, ����� ����� ��������
const char *c_str() const;
�.�. �� ���������� ��������� �� ���������.
��� ����������� ������ � ����� ������� ���������� �������� ��������� ���:
string s1;
// ������� ��������� �� ������ ���������
const char *sc1 = s1.c_str();
char *sc2=new char[strlen(sc1)+1];
strcpy(sc2, sc1);
// � ����� �������� �� ������� sc2
��� ���� ������� ���������� ����� ���������:
char *sc2= new char[s1.length()+1];
strcpy(sc2, s1.c_str()));
� ������ �������, ������
char *sc2 = sc1;
�������� � ������ ���������� ��-�� ��������� �������������� �����.
������ 1. � ���������� �������� ������. ������ ��������� �� ����� ���������
�������������: ������, �������, ����� � ������� � ���������. ����������� ���������,
������� ����� ������������ � ������ ������ ����� ���. ����� � ����. ������ ���. �����.
#include <iostream>
#include <string>
using namespace std;
int main()
{
string str, s2; //��������� ������, � ������� ����� ������ � ����������
string d = " ,;:"; //������ � ���������-�������������
string s; //��� �����
unsigned pos1 = 0, pos2, imax, imin;
cout << "Input your string" << endl;
getline(cin, str);
s2 = str; //����� ������ str
string smax = "";
string smin = str;
str = str + d; //��������� ������ ����������������������
//���� � �������� ������ ���� �������, �������� �� ��������������������,
//��������� ����:
while ((pos1 = str.find_first_not_of(d, pos1)) != string::npos)
{
//�������� � ������ str, ������� � ������� pos1, ����� ������� �����������.
pos2 = str.find_first_of(d, pos1);
//�������� � ������ s ������� ������ str, ������� � ������� pos1, � ����������
//pos2 � pos1.
s = str.substr(pos1, pos2 - pos1);//��� ���: s.assign(str, pos1, pos2� pos1);
if( s.length() > smax.length() )
{
smax = s; imax = pos1;
}
if (s.length() <= smin.length())
{
smin = s; imin = pos1;
6
}
pos1 = pos2;
}
//����� �������
str = s2;
int lmax = smax.length();
int lmin = smin.length();
if (imax > imin)
{
str.replace(imax, lmax, smin);
str.replace(imin, lmin, smax);
}
else
if (imax < imin)
{
str.replace(imin, lmin, smax);
str.replace(imax, lmax, smin);
}
cout << str << endl;
return 0;
}
������ 2. � ���������� �������� ������. ������ ��������� �� ����� ���������
�������������: ������, �������, ����� � ������� � ���������. ����������� ���������,
������� ����� ������ � �������� ������ �����, �������������� ����� ���������� ������
�������� ���������� �������� ����� C++.
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring> //���������� ��� ������ � �������������
//��� string �������� � ������������ ��� std ����������� ���������� C++.
//��������� ��� ����� ������������ std �����������.
using namespace std;
void main()
{
string str; //��������� ������, � ������� ����� ������ � ����������
string d = " ,;:"; //������ � ���������-�������������
7
char w[100]; //� ����������� w ����� �������� ���������� �����, �����
//����� ������������ ������� strtod() ���������� <cstring> ��� ��������������
//����� � �����
string s; //� ������ s ����� �������� �����, ���������� �� ������ str
unsigned pos1 = 0, pos2;
char *p; //��������� �� ������
cout << "Input your string" << endl;
getline(cin, str);
str = str + d; //��������� ������ ����������������������

//���� � �������� ������ ���� �������, �������� �� ��������������������,

//��������� ����:
while ( (pos1 = str.find_first_not_of(d, pos1) ) != string::npos)
{
//�������� � ������ str, ������� � ������� pos1, ����� ������� �����������.
pos2 = str.find_first_of(d, pos1);
//�������� � ������ s ������� ������ str, ������� � ������� pos1, � ����������
//pos2 � pos1.
s = str.substr(pos1, pos2 - pos1);//��� ���: s.assign(str, pos1, pos2� pos1);
//����������� ������ s �� ���� string � �����������, ������� �������� � w.
strcpy(w, s.c_str());
//��������� ��� ������ ������������ ������������� ��� ���� �����������
//��������� ����� �� ������ str � ������������� ��� � ���� char*.
//str.copy(w, pos2 � pos1, pos1); �������� ������� ������ str � w
//w[pos2� pos1] = '\0'; ��������� ������ w �������� '\0'
//����������� ������ w � ����� ��� ���������� ���������� ��������������.
strtod(w, &p);
//������� strtod() ����� � ��������� p ������� ������� ������������������
//������� � ������ w. ���� ��� ������� ������ w ������������� � �����, ��
//p[0]=='\0', �.�. strlen(p) == 0. ���� ����� ������ p ����� 1, �� ������ p[0] �����
//���� ��������� � ������ �������� ���������� ���������. ����� ��������� ���.
if ((strlen(p) == 0) || (strlen(p) == 1 && (p[0] == 'l' || p[0] == 'L' ||
p[0] == 'u' || p[0] == 'U' || p[0] == 'f' || p[0] == 'F')))
cout << w << endl;
pos1 = pos2;
}
}


��������� ������� ��������� �������������������� �����:
size_t strlen(const char *s);// ���������� ����� ������ s ��� ����� ������������
//������� �\0�
char* strcpy(char *s1, const char *s2);// �������� s2 � s1, ������� �����������
//������ �\0�
char* strncpy(char *s1, const char *s2, size_t n);// �������� �� ����� n ��������
//�� s2 � s1
int strcmp(const char *s1, const char *s2);//���������� ������ s1 � s2 � �������
//���� �������� 0, -1, 1, ���� s1 �������������� �����, ������ ��� ������, ��� s2
int strncmp(const char *s1, const char *s2, size_t n);//���������� �� ����� n
//�������� ������ s1 �� ������� s2 � ���������� ���� �� �������� 0, -1 ��� 1
char* strcat(char *s1, const char *s2);// ��������� ������ s2 � ������ s1, ������
//������ ������ ������ s2 ������������ ������ ������������ ���� ������ s1
char* strncat(char *s1, const char s2*, size_t n);// ��������� �� ����� n ��������
//������ s2 � ������ s1
char* strtok(char *s1, const char *s2);// ������������������ ������� ����
//������� ��������� ������ s1 �� �������, ���������� ���������,
//������������� � ������ s2. ������ ����� �������� � �������� �������
//��������� s1, � ����������� ������ ��� ����������� ��������� ��� ��
//������ �������� � �������� ������� ��������� 0. ��� ������ ������
//������������ ��������� �� ������� �����. ���� ��� ������ ������� ����
//������ ���, ������������ 0. ������� �����������, ��� ������� strtok() ��������
//������ �������� � ������ s1.
//���������� ������ ������������� ������� strtok():
char *s1=new char [100];
strcpy(s1, "white*^green^~~ black~^*red ");//s1� ������, �� ������� ���� �������� �����
char *s2="~*^", *w; //s2 � ������ � ������������� ����� �������
w = strtok(s1, s2);//�������� �� ������ s1 ������ ����� � ��� ����� ������� � w
while(w != NULL) // ���� � ������ s1 ���� �����, �������� �� � ������� �� �����
 {
cout << w << endl;
w = strtok(NULL, s2);
 }
 ��������� ������� ��� ������ � �������������������� �������:
char* strchr(const char *s, int c);// ���������� ������� ������� ���������
//������� c � ������ s; ���� c ������, ������������ ��������� �� c � s; �
//��������� ������ ������������ ��������� 0
size_t strcspn(const char *s1, const char *s2);// ���������� � ���������� �����
//��������� ����� ������ s1, ��������� �� ��������, �� ������������ � s2
size_t strspn(const char *s1, const char *s2);// ���������� � ���������� �����
//��������� ����� ������ s1, ��������� ������ �� ��������, ������������ � s2
char* strpbrk(const char *s1, const char *s2);// ���������� ������� �������
//���������� � s1 ������ �� �������� ������ s2
char* strstr(const char *s1, const char *s2);// ���������� ������� �������
//��������� � ������ s1 ��������� s2
��������� ������� �������������� �������������������� �����:
//������� �������������� ����� ��������� � ���������� <stdlib.h>.
//������� atoi(), atol(), atof() ����������� ���������� ������ s � ����� �
//������������ � ����� ������������� ��������. ������� ������� � ������
//������ ������������. ���� ������ ����, �� �� �����������. ���� �����������
//������������ ������, �� �������������� ������������ � ������������
//��������� �������� �����, ���������� ��������������� �������� � ������
//������ �� ������� ������������� �������. ���� ������������ �������� ������
//������ ������, �� ������������ ����� 0.
int atoi(const char *s); // ascii to int
long atol(const char *s); // ascii to long
double atof(const char *s);// ascii to float
//������� strtol(), strtoul() ����������� ���������� ������ s � ����� �����,
//��������� ������� ��������� � ���������� basis. �������������� ������������,
//���� ���������� ������, ������� �� ����� ���� ��������� ��� ��������� �����
//����� � �������� ������� ���������. ��������� �� ���� ������ ������������ �
//�������� endptr.
long strtol(const char *s, char **endptr, int basis);
unsigned long strtoul(const char *s, char **endptr, int basis);
//������� strtod() ����������� ���������� ������ s � ����� ���� double.
//��������� endptr �������� ������, �� ������� ���� ���������� ���������.
double strtod(const char *s, char **endptr);
//������� itoa(), ltoa(), ultoa() ����������� ����� ����� value � �����
//��������������� ���������� ������ s, ��������� ������� ��������� �
//��������� basis.
char* itoa(int value, char *s, int basis); //int to ascii
char* ltoa(long value, char *s, int basis); //long to ascii
char* ultoa(unsigned long value, char *s, int basis);//unsigned long to ascii
//������� gcvt() ����������� value � ����� � ��������� ������ ���� double �
//�������������������� ���������� ������ s. �������� digits ����� ����������
//�������� ���� ����� value, ������� ����� �������� � ������ s.
char* gcvt(double value, int digits, char *s);
��������� ������� ������������� ��������:
//������� ������������� ASCII��������� ��������� � ���������� <ctype.h>.
//int isalpha(int c); // �����: �a�..�z� � �A�..�Z�
//int isupper(int c); // ����� � ������� ��������: �A�..�Z�
//int islower(int c); // ����� � ������ ��������: �a�..�z�
//int isdigit(int c); // �0�..�9�
//int isxdigit(int c); // �0�..�9� ��� �����
//int isspace(int c); // �������������������
//int iscntrl(int c); // ����������� ������� (ASCII 0..31 � 127)
//int ispunct(int c); // ����������: �� ���� ������ �� ��������������
//int isalnum(int c); // isalpha() ��� isdigit()
//int isprint(int c); // ��, ��� ����� ����������
//int isgraph(int c); // isalpha() ��� isdigit() ��� ispunct()
//int toupper(int c); // ���������� � ������� ��������
//int tolower(int c); // ���������� � ������ ��������
*/


//����������� �����������
#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
#include<stdio.h>

using namespace std;

int nut(const string& str)
{
	char* end_ptr;
	int dd;

	char* s2 = new char[str.length() + 1];
	strcpy(s2, str.c_str());

	dd = strtol(s2, &end_ptr, 10);

	if (*end_ptr != 0)
	{
		delete[] s2;
		return false;
	}

	if (dd < 1)
	{
		delete[] s2;
		return false;
	}

	delete[] s2;
	return dd;
}


int sov(const string& str)
{
	char* end_ptr;
	int dd;
	int S = 0;

	char* s2 = new char[str.length() + 1];
	strcpy(s2, str.c_str());

	dd = strtol(s2, &end_ptr, 10);

	if (dd <= 1)
		return false;

	if (*end_ptr == 0)
	{
		for (int i = 1; i <= dd / 2; i++)
			if (dd % i == 0)
				S += i;
	}
	else
		return false;

	if (dd == S)
		return dd;
	else
		return false;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream input("input.txt", ios::in);
	ofstream output("output.txt", ios::out);

	if (!input)
	{
		cout << "������---������� ���� �� ������!" << endl;
		output << "������---������� ���� �� ������!";
		output.close();
		return 0;
	}

	string str;
	string sub;
	string temp1;
	int poz1 = 0;
	int subpoz1 = 0;
	int len1, count = 0;

	string MAXSTR, MINSTR;
	int num;
	int MAX, MIN;
	int MAXLEN, MINLEN;
	int MAXPOZ, MINPOZ;

	bool aim = 0;

	if (input.eof())
	{
		output << "������---������� ���� ������!";
		input.close();
		output.close();
		return 0;
	}

	getline(input, sub);

	if (sub == "")
	{
		output << "������---�� ���������� ����������� ����� �������!";
		input.close();
		output.close();
		return 0;
	}


	for (int i = 0; i < 2; i++)
	{

		while (getline(input, str))
		{
			if (str == "") continue;

			str += ' ';

			while ((poz1 = str.find_first_not_of(sub, poz1)) != string::npos)
			{
				subpoz1 = str.find_first_of(sub, poz1);
				len1 = subpoz1 - poz1;
				temp1 = str.substr(poz1, len1);

				if (i == 0)
				{
					if (nut(temp1))
					{
						count++;
						if (aim)
							output << ',';
						output << temp1;
						aim = true;
					}
				}

				if (i == 1)
				{
					if (nut(temp1))
						if (sov(temp1))
							output << temp1 << "->" << "SOVERSHENNOE" << endl;
						else
							output << temp1 << "->" << "NENESOVERSHENNOE" << endl;
				}
				poz1 = subpoz1;
			}
			poz1 = 0;
		}
		input.close();
		input.open("input.txt", ios::in);
		output << endl;
	}

	if (count == 0)
	{
		output.close();
		output.open("output.txt", ios::out);
		output << "�� ������� ����� ��� ����������� �����!";
	}

	input.close();
	output.close();
	return 0;
}

