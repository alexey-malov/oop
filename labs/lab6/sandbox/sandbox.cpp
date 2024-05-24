// sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class Base
{
public:
	Base(std::string const& message)
		: m_message(message)
	{
	}
	std::string GetMessage() const
	{
		return m_message;
	}
	virtual void PrintInfo() const
	{
		std::cout << "Base exception: "
				  << m_message << "\n";
	}
	virtual ~Base() = default;

private:
	std::string m_message;
};

class Derived : public Base
{
public:
	Derived(std::string const& message)
		: Base(message)
	{
	}
	void PrintInfo() const override
	{
		std::cout << "Derived exception: "
				  << GetMessage() << "\n";
	}
};

void PrintInfo(Base base)
{
	base.PrintInfo();
}

int main(int argc, char* argv[])
{
	Derived d{ "SomeInfo" };
	PrintInfo(d);

	try
	{
		Derived error("SomeInfo");
		error.PrintInfo();
		throw error;
	}
	// Выброшенное исключение типа CDerived
	// превратится в CBase
	catch (Base e)
	{
		e.PrintInfo();
	}

	return 0;
}


#if 0
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

#endif