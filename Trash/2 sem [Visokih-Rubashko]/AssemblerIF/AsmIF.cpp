#include<iostream>
#include<Windows.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "F2(х, у) = \n(x^2 + y^2), если x < 0 и y < 0, \n(-2x + y), если x < 0 и y >= 0, \n(x - 2y), если x >= 0 и у < 0, \n(2x + 2y), если x >= 0 и у >= 0\n";

	int x, y, result;
	cout << "X= ";
	cin >> x;
	cout << endl;

	cout << "Y= ";
	cin >> y;
	cout << endl;

	if (x < 0)
	{
		if (y < 0)
			result = x * x + y * y;
		else
			result = -2 * x + y;
	}
	else
		if (y < 0)
			result = x - 2 * y;
		else
			result = 2 * x + 2 * y;

	cout << "C++ result = " << result << endl;

	_asm
	{
		mov eax, x
		mov ebx, y

		cmp x, 0
		jl S	
			imul ebx, 2
			cmp y, 0
			jl W
			     imul eax, 2			     
			     jmp R
			
				 W : 		         
		            neg ebx
				    jmp R
		
		
				S: 
		          cmp ebx, 0
			      jl P
			          imul eax, -2			         
			          jmp R

			P : 
			   imul eax
			   imul ebx, ebx			  

				   R: 
			   add eax, ebx
			   mov result, eax
				  
	}

	cout << "Assembler result = " << result << endl;

	system("pause");
	return 0;
}