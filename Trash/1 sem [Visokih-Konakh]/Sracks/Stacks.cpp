#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <cstring>

using namespace std;

#define MAX_LEN 256
char stack[MAX_LEN];    
int top = 0;             

void push(char* stakk, int& toppoz, char info)
{
	stakk[toppoz++] = info;
}

char pop(char* stakk, int& toppoz)
{
	return stakk[--toppoz];
}

void PostfixNotation(const char* input, char* output)
{
	char sim;
	int pozout = 0;      
	int pozin = 0;       

	do
	{
		sim = input[pozin];  

		switch (sim)
		{
		case '+':
		case '-':
		{
			while (top != 0)
			{
				char op = stack[top - 1];
				if (op != '(')
				{
					output[pozout++] = op;
					pop(stack, top);
				}
				else
					break;
			}
			push(stack, top, sim);
			break;
		}
		case '*':
		case '/':
		{
			while (top != 0)
			{
				char op = stack[top - 1];
				if ((op == '^') || (op == '*') || (op == '/'))
				{
					output[pozout++] = op; 
					pop(stack, top);         
				}
				else
					break;
			}
			push(stack, top, sim);
			break;
		}
		case '(': push(stack, top, sim); break;
		case ')':
		{
			while (top != 0)
			{
				char op = pop(stack, top); 
				if (op == '(')                 
					break;                      
				else
					output[pozout++] = op; 
			}
			break;
		}
		case '^': push(stack, top, sim); break;
		default:    
		{
			output[pozout] = sim;
			pozout++;
			break;
		}
		}

		pozin++; 

	} while (input[pozin] != 0);  

	while (top != 0)
		output[pozout++] = pop(stack, top);

	output[pozout] = 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char str_infix[MAX_LEN];
	char str_postfix[MAX_LEN];

	cout << "Введите математическое выражение состоящее из операторов ()+-*/^ , односимвольных буквенных операндов, а также цифр" << endl;

	scanf("%s", str_infix);

	cout << "Математическое выражение в постфиксной форме:" << endl;
	PostfixNotation(str_infix, str_postfix);
	cout << "====================" << endl;
	cout << str_postfix << endl;
	cout << "====================" << endl;
	system("pause");
	return 0;
}