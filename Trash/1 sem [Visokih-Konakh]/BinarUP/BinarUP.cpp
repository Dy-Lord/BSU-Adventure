#pragma warning(disable : 4996)
#include<cstdio>
#include<cstring>
#include<windows.h>
#include<algorithm>

using namespace std;

char Base[] = "Phonebase.txt";
char Comm[] = "Com.txt";

void show();
void add();

void searchnum();
void searchdate();

struct Info
{
	char FIO[120];
	unsigned number;
	char date[11];
	unsigned time;
	unsigned id;
};

struct Commun
{
	char comdate[11];
	unsigned comnumber;
	unsigned comid;
};

void SORTSHELL(Commun*& arr, int SIZE);

int main() 
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int n;
	while (true)
	{
		printf("%s\n", "(1)---Добавить новый счёт");

		printf("%s\n", "(2)---Просмотреть счета");

		printf("%s\n", "(3)---Поиск по номеру телефона");

		printf("%s\n", "(4)---Поиск по дате разговора");

		printf("%s\n", "(5)---Выход");

		printf("%s\n", "Введите номер пункта меню");

		scanf("%d", &n);

		switch (n)
		{
		case 1:
			add();
			break;
		case 2:
			show();
			break;
		case 3:
			searchnum();
			break;
		case 4:
			searchdate();
			break;
		case 5:
			return 0;
		default:
			printf("%s\n", "Некорректный пунк меню");
		}
	}
}

void print_zap(const Info& zap)
{
	printf("%s\t%u\t%s\t%u\n", zap.FIO, zap.number, zap.date, zap.time);
}

void show()
{
	FILE* in = fopen(Base, "r");
	if (!in)
	{
		printf("%s\n", "Ошибка открытия файла!");
		return;
	}

	Info zap;

	if (!fread(&zap, sizeof(Info), 1, in))
	{
		printf("Файл пуст!\n");
		return;
	}

	
	do
	{ 
		print_zap(zap);
		
		fread(&zap, sizeof(Info), 1, in);
	} while (!feof(in));
	
	fclose(in);
}

int counts()
{
	int count = 0;
	FILE* in = fopen(Base, "r");
	if (!in)
	{
		printf("%s\n", "Ошибка открытия файла!");
		return 0;
	}

	Info zap;

	if (!fread(&zap, sizeof(Info), 1, in))
		return count;

	do
	{
		count++;
		fread(&zap, sizeof(Info), 1, in);
	} while (!feof(in));

	fclose(in);
	return count;
}

void add()
{
	FILE* in = fopen(Base, "r+");
	FILE* xxx = fopen(Comm, "r+");

	Info zap;

	int poz=0;
	if (!in)
	{
		printf("%s\n", "Ошибка открытия файла!");
		return;
	}
	if (!xxx)
	{
		printf("%s\n", "Ошибка открытия файла!");
		return;
	}

	poz = counts();

	fclose(in);
	in = fopen(Base, "a");
		Commun* ad = new Commun[poz + 1];

		if (poz)
		{
			for (int i = 0; i < poz; i++)
				fread(&ad[i], sizeof(Commun), 1, xxx);
		}
	
	
		{
			printf("%s\n", "Введите данные");

			printf("%s\n", "ФИО абонента");
			scanf("%s", &zap.FIO);

			printf("%s\n", "Телефонный номер абонента");
			scanf("%u", &zap.number);

			ad[poz].comnumber = zap.number;

			printf("%s\n", "Дата телефонного разговора в формате (dd.mm.yyyy)");
			scanf("%s", &zap.date);

			strcpy(ad[poz].comdate, zap.date);

			printf("%s\n", "Время телефонного разговора в минутах");
			scanf("%u", &zap.time);

			zap.id = poz;
			ad[poz].comid = poz;
		} //ввод данных


		SORTSHELL(ad, poz + 1);
		fclose(xxx);

		xxx = fopen(Comm, "w");

		fwrite(&zap, sizeof(Info), 1, in);

		for (int i = 0; i < poz + 1; i++)
			fwrite(&ad[i], sizeof(Commun), 1, xxx);

	fclose(xxx);
	fclose(in);
}

void searchnum()
{
	FILE* in = fopen(Base, "r+");
	FILE* xxx = fopen(Comm, "r+");

	Info zap;

	int poz = 0, pu = 0;
	if (!in)
	{
		printf("%s\n", "Ошибка открытия файла!");
		return;
	}
	if (!xxx)
	{
		printf("%s\n", "Ошибка открытия файла!");
		return;
	}

	poz = counts();

	
	Commun* ad = new Commun[poz];

	if (poz)
	{
		for (int i = 0; i < poz; i++)
			fread(&ad[i], sizeof(Commun), 1, xxx);
	}

	unsigned numm;
	printf("%s\n", "Введите номер телефона");
	scanf("%u", &numm);

	for (int i = 0; i < poz; i++)
		if (numm == ad[i].comnumber)
		{
			pu++;
			fseek(in, sizeof(Info) * (ad[i].comid), SEEK_SET);
			fread(&zap, sizeof(Info), 1, in);
			printf("%s\t%u\t%s\t%u\t%u\n", zap.FIO, zap.number, zap.date, zap.time,zap.id);
		}

	if(!pu)
		printf("%s\n", "Совпадений не найдено!");

	fclose(xxx);
	fclose(in);
}

void searchdate()
{
	FILE* in = fopen(Base, "r+");
	FILE* xxx = fopen(Comm, "r+");

	Info zap;

	int poz = 0, pu = 0;
	if (!in)
	{
		printf("%s\n", "Ошибка открытия файла!");
		return;
	}
	if (!xxx)
	{
		printf("%s\n", "Ошибка открытия файла!");
		return;
	}

	poz = counts();


	Commun* ad = new Commun[poz];

	if (poz)
	{
		for (int i = 0; i < poz; i++)
			fread(&ad[i], sizeof(Commun), 1, xxx);
	}

	char date[11];
	printf("%s\n", "Введите дату телефонного разговора в формате (dd.mm.yyyy)");
	scanf("%s", &date);

	for (int i = 0; i < poz; i++)
		if (!strcmp(date, ad[i].comdate))
		{
			pu++;
			fseek(in, sizeof(Info) * (ad[i].comid), SEEK_SET);
			fread(&zap, sizeof(Info), 1, in);
			printf("%s\t%u\t%s\t%u\t%u\n", zap.FIO, zap.number, zap.date, zap.time, zap.id);
		}

	if (!pu)
		printf("%s\n", "Совпадений не найдено!");

	fclose(xxx);
	fclose(in);
}

void SORTSHELL(Commun *& arr, int SIZE)
{
	double fakt = 1.6473309;
	int len = SIZE / fakt;
	int stop = 0;
	if (SIZE == 1)
		return;

	while (true)
	{
		for (int i = 0; (i < SIZE) && (i + len < SIZE); i++)
			if (arr[i].comnumber > arr[i + len].comnumber)
				swap(arr[i], arr[i + len]);

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