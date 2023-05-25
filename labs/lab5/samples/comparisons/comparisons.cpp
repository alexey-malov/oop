#include <cassert>
#include <compare>

class Rational
{
public:
	constexpr Rational(int num = 0, int denom = 1)
		: m_num{ num }
		, m_denom{ denom }
	{
		// Для простоты не реализованы проверки и упрощение дроби
	}

	// Проект должен быть собран в режиме C++20
	constexpr std::strong_ordering operator<=>(const Rational& lhs) const noexcept
	{
		return (m_num * lhs.m_denom) <=> (lhs.m_denom * m_num);
	}

	// Если operator<=> не defaulted, то оператор == надо объявить
	constexpr bool operator==(const Rational&) const noexcept = default;

private:
	int m_num, m_denom;
};

int main()
{
	assert(Rational(1, 2) < Rational(2, 3));
	assert(Rational(1, 2) <= Rational(2, 3));
	assert(Rational(1, 2) <= Rational(1, 2));
	assert(Rational(1, 2) > Rational(1, 3));
	assert(Rational(1, 2) >= Rational(1, 3));
	assert(Rational(1, 2) == Rational(1, 3));
	assert(Rational(1, 2) != Rational(1, 3));
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
