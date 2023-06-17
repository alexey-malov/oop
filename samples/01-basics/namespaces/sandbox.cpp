#include <iostream>

struct Foo {
	Foo() { std::cout << "Default ctor\n"; }
	Foo(const Foo&) { std::cout << "Copy ctor\n"; }
	Foo(Foo&&) { std::cout << "Move ctor\n"; }
	Foo& operator=(const Foo&) { std::cout << "Copy assign\n"; return *this; }
	Foo& operator=(Foo&&) { std::cout << "Move assign\n"; return *this; }
	~Foo() { std::cout << "Dtor\n"; }
};

void ByVal(Foo foo) {}
Foo Create() { return {}; }
Foo Create2() {
	Foo foo;
	return foo;
}
Foo Create3(bool returnA){
	Foo a, b;
	return returnA ? a : b;
}

class Rational
{
public:
	Rational(int numerator = 0, int denominator = 1);

	Rational operator+(const Rational rhs) const;

private:
	int m_numerator = 0, m_denominator = 1;
};

Rational operator+(const Rational lhs, const Rational rhs);

struct Record
{
	std::string name;
	unsigned int floor;
	double weight;

	auto operator<=>(const Record&) const = default;
};
// records can now be compared with ==, !=, <, <=, >, and >=

int main() {
	{
		Foo foo;
		ByVal(foo);
		ByVal(Foo{});
		ByVal(std::move(foo));
	}
	Create();
	Create2();
	Create3(true);
	auto a = Create2();
	std::cout << "--\n";
}
