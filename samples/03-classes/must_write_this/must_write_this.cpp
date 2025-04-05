#include <iostream>

struct Vector
{
	double x = 0, y = 0;

	// Оператор += возвращает ссылку на текущий объект,
	// чтобы можно было использовать цепочку вызовов:
	// Vector v1, v2, v3;
	// v1 += v2 += v3;
	Vector& operator+=(Vector const& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}
};

template <typename T>
class Base
{
public:
	void SetValue(T v)
	{
		m_value = v;
	}

protected:
	T m_value = {};
};

template <typename T>
class Derived : public Base<T>
{
public:
	void PrintValue()
	{
		// Без this-> будет ошибка компиляции
		std::cout << this->m_value << std::endl;
	}
};

int main()
{
	Derived<int> derived;
	derived.PrintValue();
}
