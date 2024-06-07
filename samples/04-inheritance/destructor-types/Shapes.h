#pragma once
#include <cstdint>

class Shape
{
public:
	// Публичный виртуальный деструктор позволит безопасно
	// удалять наследников, используя указатель на класс Shape.
	virtual ~Shape() = default;

	void SetColor(uint32_t color) { m_color = color; }
	uint32_t GetColor() const { return m_color; }

protected:
	Shape(uint32_t color)
		: m_color{ color }
	{
	}

private:
	uint32_t m_color = 0;
};

class Circle : public Shape
{
public:
	Circle(double radius, uint32_t color)
		: Shape{ color }
		, m_radius{ radius }
	{
	}

	// Так как деструктор родителя виртуальный,
	// он остаётся виртуальным и в Circle
private:
	double m_radius;
};

class Rectangle : public Shape
{
public:
	Rectangle(double width, double height, uint32_t color)
		: Shape{ color }
		, m_width{ width }
		, m_height{ height }
	{
	}

private:
	double m_width;
	double m_height;
};
