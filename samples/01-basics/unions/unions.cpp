#include <iostream>

enum class NumericType
{
	INTEGER,
	REAL,
};

struct Numeric
{
	NumericType type;

	union
	{
		int	intValue;
		double realValue;
	}value;
};

void PrintNumeric(const Numeric & n)
{
	if (n.type == NumericType::INTEGER)
		std::cout << n.value.intValue << std::endl;
	else
		std::cout << n.value.realValue << std::endl;
}

void main()
{
	Numeric a, b;

	a.type = NumericType::INTEGER;	a.value.intValue = 5;
	b.type = NumericType::REAL;		b.value.realValue = 3.8;

	PrintNumeric(a);
	PrintNumeric(b);
}
