
class Rational
{
public:
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
		if (denominator != 0) // Знаменатель не может быть равен нулю.
		{
			m_denominator = denominator;
		}
	}

private:
	int m_numerator = 0; // Числитель.
	int m_denominator = 1; // Знаменатель.
};

Rational CreateRational(int numerator, int denominator)
{
	Rational r;
	r.SetNumerator(numerator);
	r.SetDenominator(denominator);
	return r;
}

int main()
{
	Rational four; // Сразу после создания four хранит значение 0/1, или 0
	four.SetNumerator(4); // Превращаем дробь в 4/1, или число 4

	// Создаём дробь 2/3 в три шага:
	Rational twoTrird; // 1. Объявляем переменную
	twoTrird.SetNumerator(2); // 2. Задаём числитель
	twoTrird.SetDenominator(3); // 3. Задаём знаменатель
}
