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
		output << "Ошибка---входной файл не найден!";
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
		output << "Ошибка---входной файл пустой!";
		input.close();
		output.close();
		return 0;
	}

	getline(input, sub);

	if (sub == "")
	{
		output << "Ошибка---Не определены разделители между словами!";
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
		output << "Ошибка---входной файл не найден!";
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
		output << "Ошибка---входной файл пустой!";
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
СТРОКИ ТИПА string
Средства стандартной библиотеки для работы со строками типа string становятся
доступными при подключении заголовочного файла <string>. Рассмотрим основные
аспекты работы со строками типа string.
Строку string можно инициализировать нуль–строкой, другой строкой string,
подстрокой строки string или последовательностью символов. Однако её нельзя
инициализировать символом или числом. Например, string s0; // пустая
строка
string s1 = "Hello, wolrd!";// инициализация строковой константой
char s[] ="Hello, wolrd!"; // нуль–строка
string s11(s); // так можно преобразовывть нуль–строки в string
string s12 = s; // так тоже можно преобразовывть нуль–строки в string
string s2 = s1; // копия s1, можно записать и так: string s2(s1);
string s3(s2, 0, 5); // 5 символов из s2, начиная с первого, то есть "Hello"
string s4(7, 'q'); // 7 символов 'q', то есть "qqqqqqq"
Нельзя объявить строку длиной n. В случае такой необходимости можно объявить
строку, в которую поместить n копий указанного символа (строка s4).
Длина строки определяется функцией length(), например, s4.length() вернёт
значение 7. Отметим, что вычисление длины строки не основывается на понятии
«завершающего нуля», обрывающего нуль–строку. Реализация string хранит длину
строки, не полагаясь на завершающий символ '\0'. Символы в строке нумеруются,
начиная с 0, так что строка – это последовательность символов с номерами от 0 до
length()–1.
Над строками можно выполнять простейшие операции:
присваивание: =
конкатенация: + , += ,
сравнение: = = , < , > , >= , <=,
индексирование: [] ,
ввод–вывод: >>, << .
Эти операции позволяют использовать объекты string в нормальных выражениях.
В выражениях можно смешивать строки string и нуль–строки. Следует заметить, что при
присваиваниях и конкатенациях результирующая строка string будет увеличиваться по
мере надобности в соответствии с размером новой строки. Строке string также можно
присвоить один символ или добавить один символ.
Далее приводятся функции – члены класса string. Используются следующие
обозначения: pos означает позицию, а n – количество символов в строке – объекте класса
string, для которой вызывается функция; pos1 означает позицию, а n1 – количество
символов в строке, которая передаётся функции как параметр; npos означает «все
элементы строки».
Присваивание строк и частей строк
string& assign(const string& s); //например, s4.assign(s1);
string& assign(const string& s, size_t pos1, size_t n1); //s4.assign(s1, 7, 5);
string& assign(const char* p);//например, s4.assign(s);
string& assign(const char* p, size_t n1);//например, s4.assign(s, 5);
string& assign(size_t n1, char c);//например, s4.assign(5, 'q');
Добавление строк и частей строк
string& append(const string& s);
string& append(const string& s, size_t pos1, size_t n1);
string& append(const char* p);
string& append(const char* p, size_t n1);
string& append(size_t n1, char c);
Вставка строк и частей строк
string& insert(size_t pos, const string& s);
string& insert(size_t pos, const string& s, size_t pos1, size_t n1);
string& insert(size_t pos, const char* p);
string& insert(size_t pos, const char* p, size_t n1);
string& insert(size_t pos, size_t n1, char c);
Замена в строках
string& replace(size_t pos, size_t n, const string& s);
string& replace(size_t pos, size_t n, const string& s, size_t pos1, size_t n1);
string& replace(size_t pos, size_t n, const char* p);
string& replace(size_t pos, size_t n, const char* p, size_t n1);
string& replace(size_t pos, size_t n, size_t n1, char c);
Удаление подстроки
string& erase(size_t pos = 0, size_t n = npos);
Поиск подстрок
//Функции возвращают номер позции в строке, если поиск завершился успешно, и //–1 в
противном случае.
//Поиск первого вхождения подстроки в строку
size_t find(const string& s, size_t pos = 0) const;
size_t find(const char* p, size_t pos = 0) const;
size_t find(const char* p, size_t pos, size_t n1) const;
size_t find(const char c, size_t pos = 0) const;
//Поиск последнего вхождения подстроки в строку
size_t rfind(const string& s, size_t pos = npos) const;
size_t rfind(const char* p, size_t pos = npos) const;
size_t rfind(const char* p, size_t pos, size_t n1) const;
size_t rfind(const char c, size_t pos = npos) const;
//Поиск первого вхождения любого символа подстроки в строку
size_t find_first_of(const string& s, size_t pos = 0) const;
size_t find_first_of(const char* p, size_t pos = 0) const;
size_t find_first_of(const char* p, size_t pos, size_t n1) const;
size_t find_first_of(const char c, size_t pos = 0) const;
//Поиск последнего вхождения любого символа подстроки в строку
size_t find_last_of(const string& s, size_t pos = npos) const;
size_t find_last_of(const char* p, size_t pos = npos) const;
size_t find_last_of(const char* p, size_t pos, size_t n1) const;
size_t find_last_of(const char c, size_t pos = npos) const;
//Поиск в строке первого символа, которого нет подстроке
size_t find_first_not_of(const string& s, size_t pos = 0) const;
size_t find_first_not_of(const char* p, size_t pos = 0) const;
size_t find_first_not_of(const char* p, size_t pos, size_t n1) const;
size_t find_first_not_of(const char c, size_t pos = 0) const;
//Поиск в строке последнего символа, которого нет подстроке
size_t find_last_not_of(const string& s, size_t pos = npos) const;
size_t find_last_not_of(const char* p, size_t pos = npos) const;
size_t find_last_not_of(const char* p, size_t pos, size_t n1) const;
size_t find_last_not_of(const char c, size_t pos = npos) const;
Сравнение строк
// Функции возвращают значения –1, 0, 1, если строка – объект, для которой //вызывается
функция, соответственно меньше, равна или больше строки, которая //передаётся
функции как параметр.
int compare(const string& s)const;
int compare(size_t pos, size_t n, const string& s)const;
int compare(size_t pos, size_t n, const string& s, size_t pos1, size_t n1,)const;
int compare(const char* p)const;
int compare(size_t pos, size_t n, const char* p, size_t n1 = npos)const;
Функция getline()
istream& getline(istream&, string& s);
istream& getline(istream&, string& s, char term);
Преобразование в нуль–строку
const char* c_str() const;
Перевод из типа string в тип char * достаточно сложен. Класс string имеет в своем
составе метод c_str, который возвращает указатель на нуль-терминированную строку,
однако дополнительная память при этом не выделяется, метод имеет прототип
const char *c_str() const;
т.е. он возвращает указатель на константу.
Для полноценной работы с такой строкой необходимо записать следующий код:
string s1;
// получим указатель на строку константу
const char *sc1 = s1.c_str();
char *sc2=new char[strlen(sc1)+1];
strcpy(sc2, sc1);
// и далее работаем со строкой sc2
Еще один вариант реализации этого механизма:
char *sc2= new char[s1.length()+1];
strcpy(sc2, s1.c_str()));
С другой стороны, запись
char *sc2 = sc1;
приведет к ошибке компиляции из-за неверного преобразования типов.
Пример 1. С клавиатуры вводится строка. Строка разделена на слова символами–
разделителями: пробел, запятая, точка с запятой и двоеточие. Разработать программу,
которая будет переставлять в строке первое слово мак. длины и посл. словом мин. длины.
#include <iostream>
#include <string>
using namespace std;
int main()
{
string str, s2; //объявляем строку, в которую будем читать с клавиатуры
string d = " ,;:"; //строка с символами-разделителями
string s; //для слова
unsigned pos1 = 0, pos2, imax, imin;
cout << "Input your string" << endl;
getline(cin, str);
s2 = str; //копия строки str
string smax = "";
string smin = str;
str = str + d; //завершаем строку символами–разделителями
//Пока в исходной строке есть символы, отличные от символов–разделителей,
//выполняем цикл:
while ((pos1 = str.find_first_not_of(d, pos1)) != string::npos)
{
//Выполним в строке str, начиная с позиции pos1, поиск первого разделителя.
pos2 = str.find_first_of(d, pos1);
//Копируем в строку s символы строки str, начиная с позиции pos1, в количестве
//pos2 – pos1.
s = str.substr(pos1, pos2 - pos1);//или так: s.assign(str, pos1, pos2– pos1);
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
//обмен словами
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
Пример 2. С клавиатуры вводится строка. Строка разделена на слова символами–
разделителями: пробел, запятая, точка с запятой и двоеточие. Разработать программу,
которая будет искать в заданной строке слова, представляющие собой корректные записи
числовых десятичных констант языка C++.
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring> //библиотека для работы с нуль–строками
//Тип string определён в пространстве имён std стандартной библиотеки C++.
//Объявляем все имена пространства std глобальными.
using namespace std;
void main()
{
string str; //объявляем строку, в которую будем читать с клавиатуры
string d = " ,;:"; //строка с символами-разделителями
7
char w[100]; //в нуль–строку w будем заносить выделенное слово, чтобы
//затем использовать функцию strtod() библиотеки <cstring> для преобразования
//слова в число
string s; //в строку s будем заносить слово, выделенное из строки str
unsigned pos1 = 0, pos2;
char *p; //указатель на строку
cout << "Input your string" << endl;
getline(cin, str);
str = str + d; //завершаем строку символами–разделителями

//Пока в исходной строке есть символы, отличные от символов–разделителей,

//выполняем цикл:
while ( (pos1 = str.find_first_not_of(d, pos1) ) != string::npos)
{
//Выполним в строке str, начиная с позиции pos1, поиск первого разделителя.
pos2 = str.find_first_of(d, pos1);
//Копируем в строку s символы строки str, начиная с позиции pos1, в количестве
//pos2 – pos1.
s = str.substr(pos1, pos2 - pos1);//или так: s.assign(str, pos1, pos2– pos1);
//Преобразуем строку s из типа string в нуль–строку, которую копируем в w.
strcpy(w, s.c_str());
//Следующие две строки комментариев демонстрируют ещё одну возможность
//выделения слова из строки str и преоразования его к типу char*.
//str.copy(w, pos2 – pos1, pos1); копируем символы строки str в w
//w[pos2– pos1] = '\0'; завершаем строку w символом '\0'
//Преобразуем строку w в число без сохранения результата преобразования.
strtod(w, &p);
//Функция strtod() вернёт в указателе p позицию первого непреобразованного
//символа в строке w. Если все символы строки w преобразованы в число, то
//p[0]=='\0', т.е. strlen(p) == 0. Если длина строки p равна 1, то символ p[0] может
//быть суффиксом в записи числовой десятичной константы. Далее проверяем это.
if ((strlen(p) == 0) || (strlen(p) == 1 && (p[0] == 'l' || p[0] == 'L' ||
p[0] == 'u' || p[0] == 'U' || p[0] == 'f' || p[0] == 'F')))
cout << w << endl;
pos1 = pos2;
}
}


Прототипы функций обработки нуль–терминированных строк:
size_t strlen(const char *s);// возвращает длину строки s без учёта завершающего
//символа ‘\0’
char* strcpy(char *s1, const char *s2);// копирует s2 в s1, включая завершающий
//символ ‘\0’
char* strncpy(char *s1, const char *s2, size_t n);// копирует не более n символов
//из s2 в s1
int strcmp(const char *s1, const char *s2);//сравнивает строки s1 и s2 и возвра–
//щает значение 0, -1, 1, если s1 соответственно равна, меньше или больше, чем s2
int strncmp(const char *s1, const char *s2, size_t n);//сравнивает не более n
//символов строки s1 со строкой s2 и возвращает одно из значений 0, -1 или 1
char* strcat(char *s1, const char *s2);// добавляет строку s2 к строке s1, причём
//первый символ строки s2 записывается поверх завершающего нуля строки s1
char* strncat(char *s1, const char s2*, size_t n);// добавляет не более n символов
//строки s2 в строку s1
char* strtok(char *s1, const char *s2);// Последовательность вызовов этой
//функции разбивает строку s1 на лексемы, разделённые символами,
//содержащимися в строке s2. Первый вызов содержит в качестве первого
//параметра s1, а последующие вызовы для продолжения обработки той же
//строки содержат в качестве первого параметра 0. При каждом вызове
//возвращается указатель на текущее слово. Если при вызове функции слов
//больше нет, возвращается 0. Следует подчеркнуть, что функция strtok() изменяет
//первый параметр – строку s1.
//Рассмотрим пример использования функции strtok():
char *s1=new char [100];
strcpy(s1, "white*^green^~~ black~^*red ");//s1– строка, из которой надо выделить слова
char *s2="~*^", *w; //s2 – строка с разделителями между словами
w = strtok(s1, s2);//выделяем из строки s1 первое слово и его адрес заносим в w
while(w != NULL) // пока в строке s1 есть слова, выделяем их и выводим на экран
 {
cout << w << endl;
w = strtok(NULL, s2);
 }
 Прототипы функций для поиска в нуль–терминированных строках:
char* strchr(const char *s, int c);// определяет позицию первого вхождения
//символа c в строку s; если c найден, возвращается указатель на c в s; в
//противном случае возаращается указатель 0
size_t strcspn(const char *s1, const char *s2);// определяет и возвращает длину
//начальной части строки s1, состоящей из символов, не содержащихся в s2
size_t strspn(const char *s1, const char *s2);// определяет и возвращает длину
//начальной части строки s1, состоящей только из символов, содержащихся в s2
char* strpbrk(const char *s1, const char *s2);// определяет позицию первого
//вхожденияв в s1 любого из символов строки s2
char* strstr(const char *s1, const char *s2);// определяет позицию первого
//вхождения в строку s1 подстроки s2
Прототипы функций преобразования нуль–терминированных строк:
//Функции преобразования строк объявлены в библиотеке <stdlib.h>.
//Функции atoi(), atol(), atof() преобразуют символьную строку s в число в
//соответствии с типом возвращаемого значения. Символы пробела в начале
//строки пропускаются. Если указан знак, то он учитывается. Если встречается
//недопустимый символ, то преобразование прекращается и возвращаемым
//значением является число, полученное преобразованием символов с начала
//строки до первого недопустимого символа. Если недопустимым является первый
//символ строки, то возвращается число 0.
int atoi(const char *s); // ascii to int
long atol(const char *s); // ascii to long
double atof(const char *s);// ascii to float
//Функции strtol(), strtoul() преобразуют символьную строку s в целое число,
//используя систему счисления с основанием basis. Преобразование прекращается,
//если всречается символ, который не может быть распознан как составная часть
//числа в заданной системе счисления. Указатель на этот символ записывается в
//параметр endptr.
long strtol(const char *s, char **endptr, int basis);
unsigned long strtoul(const char *s, char **endptr, int basis);
//Функция strtod() преобразует символьную строку s в число типа double.
//Указатель endptr отмечает символ, на котором была прекращена обработка.
double strtod(const char *s, char **endptr);
//Функции itoa(), ltoa(), ultoa() преобразуют целое число value в нуль–
//терминированную символьную строку s, используя систему счисления с
//основание basis.
char* itoa(int value, char *s, int basis); //int to ascii
char* ltoa(long value, char *s, int basis); //long to ascii
char* ultoa(unsigned long value, char *s, int basis);//unsigned long to ascii
//Функция gcvt() преобразует value – число с плавающей точкой типа double в
//нуль–терминированную символьную строку s. Параметр digits задаёт количество
//значащих цифр числа value, которые будут помещены в строку s.
char* gcvt(double value, int digits, char *s);
Прототипы функций классификации символов:
//Функции классификации ASCII–символов объявлены в библиотеке <ctype.h>.
//int isalpha(int c); // буква: ‘a’..’z’ и ’A’..’Z’
//int isupper(int c); // буква в верхнем регистре: ‘A’..’Z’
//int islower(int c); // буква в нижнем регистре: ‘a’..’z’
//int isdigit(int c); // ‘0’..’9’
//int isxdigit(int c); // ‘0’..’9’ или буква
//int isspace(int c); // символы–разделители
//int iscntrl(int c); // управляющие символы (ASCII 0..31 и 127)
//int ispunct(int c); // пунктуация: ни один символ из вышеупомянутых
//int isalnum(int c); // isalpha() или isdigit()
//int isprint(int c); // то, что можно напечатать
//int isgraph(int c); // isalpha() или isdigit() или ispunct()
//int toupper(int c); // эквивалент в верхнем регистре
//int tolower(int c); // эквивалент в нижнем регистре
*/


//Совершенные натуральные
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
		cout << "Ошибка---входной файл не найден!" << endl;
		output << "Ошибка---входной файл не найден!";
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
		output << "Ошибка---входной файл пустой!";
		input.close();
		output.close();
		return 0;
	}

	getline(input, sub);

	if (sub == "")
	{
		output << "Ошибка---Не определены разделители между словами!";
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
		output << "Во входном файле нет натуральных чисел!";
	}

	input.close();
	output.close();
	return 0;
}

