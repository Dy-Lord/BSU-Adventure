#include "COUNT.h"

COUNT::COUNT()
{
	varea = 8191;
	for (int i = 8191; i >= 0; i--)
		for (int g = 0; g < 8; g++)
			elem[i] &= ~(1 << g);
}
COUNT::COUNT(const COUNT& ob)
{
	varea = ob.varea;
	for (int i = 8191; i >= 0; i--)
		for (int g = 0; g < 8; g++)
			if (bool((1 << g) & ob.elem[i]))
				elem[i] |= (1 << g);
			else
				elem[i] &= ~(1 << g);
}
COUNT::~COUNT()
{
}

void COUNT::ADDelem(unsigned int el)
{
	if(el > 65535)
		throw std::exception("Wrong element!");

	double temp = el;
	
	int poz = 8191 - floor(temp / 8);
	int bitpoz = el % 8;

	if (varea > poz)
		varea = poz;

	elem[poz] |= (1 << bitpoz);
}
bool COUNT::ELinclude(unsigned int det)
{
	if (det > 65535)
		return false;

	double temp = det;

	int poz = 8191 - floor(temp / 8);

	int bitpoz = det % 8;

	if (varea > poz)
		return false;

	if (bool((1 << bitpoz) & elem[poz]))
		return true;
	else
		return false;
}
void COUNT::Print()
{
	bool aim = true;
	for (int i = 8191; i >= varea; i--)
		for (int g = 0; g < 8; g++)
			if (bool((1 << g) & elem[i]))
			{
				aim = false;
				int el = 65528 - i * 8 + g;
				std::cout << el << " ";
			}

	if (aim)
		std::cout << "Множество пустое!" << std::endl;
	else
		std::cout << std::endl;
}

const COUNT& COUNT::operator=(const COUNT& ob)
{
	if (&ob != this)
	{
		varea = ob.varea;
		for (int i = 8191; i >= varea; i--)
			for (int g = 0; g < 8; g++)
				if (bool((1 << g) & ob.elem[i]))
					elem[i] |= (1 << g);
				else
					elem[i] &= ~(1 << g);
	}

	return *this;
}
std::ostream& operator<<(std::ostream& out, const COUNT& ob)
{
	bool aim = true;
	for (int i = 8191; i >= ob.varea; i--)
		for (int g = 0; g < 8; g++)
			if (bool((1 << g) & ob.elem[i]))
			{
				aim = false;
				int el = 65528 - i * 8 + g;
				out << el << " ";
			}

	if (aim)
		out << "Множество пустое!" << '\n';
	else
		out << '\n';

	return out;
}

bool COUNT::operator==(const COUNT& ob) const
{
	if (varea != ob.varea)
		return false;

	for (int i = 8191; i >= varea; i--)
		for (int g = 0; g < 8; g++)
			if (bool((1 << g) & ob.elem[i]) != bool((1 << g) & elem[i]))
				return false;

	return true;
}
bool COUNT::operator>(const COUNT& ob) const
{
	if (varea < ob.varea)
		return false;

	for (int i = 8191; i >= ob.varea; i--)
		for (int g = 0; g < 8; g++)
			if (bool((1 << g) & elem[i]))
				if (!(bool((1 << g) & ob.elem[i])))
					return false;

	return true;
}
bool COUNT::operator<(const COUNT& ob) const
{
	if (varea > ob.varea)
		return false;

	for (int i = 8191; i >= varea; i--)
		for (int g = 0; g < 8; g++)
			if (bool((1 << g) & ob.elem[i]))
				if (!(bool((1 << g) & elem[i])))
					return false;

	return true;
}

COUNT COUNT::operator&(const COUNT& ob) const
{
	COUNT NEW;
	unsigned int MAX=0;

	if (varea < ob.varea)
		NEW.varea = varea;
	else
		NEW.varea = ob.varea;
	
	for (int i = 8191; i >= NEW.varea; i--)
		for (int g = 0; g < 8; g++)
			if (bool((1 << g) & elem[i]))
				if (bool((1 << g) & ob.elem[i]))
				{
					NEW.elem[i] |= (1 << g);
					if (i > MAX)
						MAX = i;
				}

	NEW.varea = 8191 - floor(MAX / 8);

	return NEW;
}
COUNT COUNT::operator|(const COUNT& ob) const
{
	COUNT NEW;

	if (varea < ob.varea)
		NEW.varea = varea;
	else
		NEW.varea = ob.varea;

	for (int i = 8191; i >= NEW.varea; i--)
		for (int g = 0; g < 8; g++)
			if (bool((1 << g) & elem[i]) || bool((1 << g) & ob.elem[i]))
				NEW.elem[i] |= (1 << g);



	return NEW;
}

COUNT COUNT::operator-(const COUNT& ob) const
{
	COUNT NEW;
	unsigned int MAX = 8191;

	if (varea < ob.varea)
		NEW.varea = varea;
	else
		NEW.varea = ob.varea;

	for (int i = 8191; i >= NEW.varea; i--)
		for (int g = 0; g < 8; g++)
			if (bool((1 << g) & elem[i]))
				if (!(bool((1 << g) & ob.elem[i])))
				{
					NEW.elem[i] |= (1 << g);
					if (i < MAX)
						MAX = i;
				}

	NEW.varea = MAX;

	return NEW;
}

