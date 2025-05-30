#include <iostream>
#include <numbers>
#include <string>

// Базовый шаблон с CRTP (Curiously Recurring Template Pattern)
template <typename Derived>
class Shape
{
public:
	explicit Shape(const std::string& color)
		: m_color(color)
	{
	}

	void Draw() const
	{
		// Делегируем рисование производному классу
		static_cast<const Derived*>(this)->DrawImpl();
	}

	double GetArea() const
	{
		// Делегируем вычисление площади производному классу
		return static_cast<const Derived*>(this)->GetAreaImpl();
	}

	const std::string& GetColor() const
	{
		return m_color;
	}

private:
	std::string m_color;
};

// Класс Circle
class Circle : public Shape<Circle>
{
	// Нужно, чтобы Shape мог использовать приватные методы Circle
	friend class Shape<Circle>;

public:
	Circle(double radius, const std::string& color)
		: Shape(color)
		, m_radius(radius)
	{
	}

private:
	void DrawImpl() const
	{
		std::cout << "Drawing a " << GetColor()
				  << " circle with radius " << m_radius << '\n';
	}

	double GetAreaImpl() const
	{
		return std::numbers::pi * m_radius * m_radius;
	}

	double m_radius;
};

// Класс Square
class Square : public Shape<Square>
{
	// Нужно, чтобы Shape мог использовать приватные методы Square5
	friend class Shape<Square>;

public:
	Square(double side, const std::string& color)
		: Shape(color)
		, m_side(side)
	{
	}

private:
	void DrawImpl() const
	{
		std::cout << "Drawing a " << GetColor()
				  << " square with side " << m_side << '\n';
	}

	double GetAreaImpl() const
	{
		return m_side * m_side;
	}

	double m_side;
};

int main()
{
	Circle circle(5.0, "red");
	Square square(4.0, "blue");

	circle.Draw();
	std::cout << "Area: " << circle.GetArea() << "\n\n";

	square.Draw();
	std::cout << "Area: " << square.GetArea() << '\n';

	return 0;
}
