#include <cassert>
#include <compare>
#include <unordered_map>
#include <string>
#include <iostream>

namespace bad
{
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
	constexpr auto operator<=>(const Rational& lhs) const noexcept = default;

private:
	int m_num, m_denom;
};
} // namespace bad

namespace good
{
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
		return (m_num * lhs.m_denom) <=> (lhs.m_num * m_denom);
	}

	// Если operator<=> не defaulted, то оператор == надо объявить
	constexpr bool operator==(const Rational&) const noexcept = default;

private:
	int m_num, m_denom;
};
} // namespace good

class TV
{
public:
	bool IsTurnedOn() const noexcept
	{
		return m_isTurnedOn;
	}

private:
	bool m_isTurnedOn;
};

class MyString
{
public:
	MyString(MyString&& other) noexcept
		: m_chars(other.m_chars)
		, m_size(other.m_size)
		, m_capacity(other.m_capacity)
	{
		other.m_chars = nullptr;
		other.m_size = m_capacity = 0;
	}

private:
	char* m_chars;
	size_t m_size;
	size_t m_capacity;
};

namespace sample1
{
class Dictionary
{
public:
	Dictionary(Dictionary&& other)
		: m_translations(std::move(other.m_translations))
	{
	}

private:
	std::unordered_map<std::string, std::string> m_translations;
};
} // namespace sample1

class Dictionary
{
public:
	Dictionary(Dictionary&& other) noexcept(false)
		: m_translations(std::move(other.m_translations))
	{
	}

private:
	std::unordered_map<std::string, std::string> m_translations;
};

int main()
{
	using namespace std::literals;
	static_assert(!noexcept("hello"s + "world"s));
	std::cout << noexcept("hello"s + "world"s) << std::endl;
	return 0;


	{
		using bad::Rational;
		assert(Rational(1, 2) == Rational(1, 2));
		assert(!(Rational(1, 2) == Rational(1, 3)));
		assert(Rational(1, 2) != Rational(1, 3));
		assert(!(Rational(1, 2) != Rational(1, 2)));
		assert(Rational(1, 2) < Rational(2, 3));
		assert(Rational(1, 2) <= Rational(2, 3));
		assert(Rational(1, 2) <= Rational(1, 2));
		assert(Rational(1, 2) > Rational(1, 3));
		assert(Rational(1, 2) >= Rational(1, 3));
	}
	{
		using good::Rational;
		assert(Rational(1, 2) < Rational(2, 3));
		assert(Rational(1, 2) <= Rational(2, 3));
		assert(Rational(1, 2) <= Rational(1, 2));
		assert(Rational(1, 2) > Rational(1, 3));
		assert(Rational(1, 2) >= Rational(1, 3));
		assert(Rational(1, 2) == Rational(1, 2));
		assert(!(Rational(1, 2) == Rational(1, 3)));
		assert(Rational(1, 2) != Rational(1, 3));
		assert(!(Rational(1, 2) != Rational(1, 2)));
	}
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
