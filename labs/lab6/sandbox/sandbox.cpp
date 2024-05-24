// sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class Rational
{
public:
	Rational(int numerator = 0)
		: m_numerator{ numerator }
	{
	}
	Rational(int numerator, int denominator)
		: m_numerator{ numerator }
		, m_denominator{ denominator }
	{
		if (m_denominator == 0)
		{
			throw std::invalid_argument("Denominator must be nonzero");
		}
		/*...*/
	}

	int GetNumerator() const { return m_numerator; }
	int GetDenominator() const { return m_denominator; }

#if 0
	bool IsValid() const { return m_denominator != 0; }
#endif

private:
	int m_numerator = 0;
	int m_denominator = 1;
};

Rational operator/(Rational lhs, Rational rhs)
{
	if (rhs.GetDenominator() == 0)
	{
		throw std::invalid_argument("Division by zero");
	}
	return { lhs.GetNumerator() * rhs.GetDenominator(), rhs.GetNumerator() * lhs.GetDenominator() };
}


#if 0
int main()
{
	Rational a, b;
	try
	{
		Rational c = a/ b;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
#endif


#if 0
int main()
{
	try
	{
		/* Код, который может выбросить исключение */
	}
	catch (Тип перехватываемого исключения)
	{
		/* Код, обрабатывающий исключение */
	}
	catch (Тип перехватываемого исключения)
	{
		/* Код, обрабатывающий исключение */
	}
	catch (...)
	{
		/* Код, обрабатывающий все прочие исключения */
	}
}
#endif

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
