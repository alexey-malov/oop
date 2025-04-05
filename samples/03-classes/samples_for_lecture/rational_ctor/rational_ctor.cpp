#include <cassert>
#include <iostream>

class Rational
{
public:
	// Это конструктор, который инициализирует дробь нужными
	// значениями числителя и знаменателя.
	Rational(int numerator, int denominator)
	{
		assert(denominator != 0);
		m_numerator = numerator;
		m_denominator = denominator;
	}

	int GetNumerator() const
	{
		return m_numerator;
	}

	int GetDenominator() const
	{
		return m_denominator;
	}

	void SetNumerator(int numerator)
	{
		m_numerator = numerator;
	}

	void SetDenominator(int denominator)
	{
		if (denominator != 0)
		{
			m_denominator = denominator;
		}
	}

private:
	int m_numerator;
	int m_denominator;
};

int main()
{
	// Конструктор можно вызвать, создав объект.
	// Параметры можно передать в фигурных скобках.
	Rational half{ 1, 2 };

	// После работы конструктора Rational поля
	// получили переданные в параметрах значения.
	assert(half.GetNumerator() == 1 && half.GetDenominator() == 2);

	// Вызвать конструктор явно нельзя.
	// Единственный способ — создать новый объект.
	half.Rational(10, 15); // <-- Ошибка!
}