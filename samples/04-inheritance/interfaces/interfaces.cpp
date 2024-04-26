// interfaces.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using Color = std::uint32_t;

struct Point
{
	double x, y;
};

// Интерфейс Graphics предоставляет методы для рисования графических примитивов
class Graphics
{
public:
	virtual ~Graphics() = default;
	virtual void MoveTo(Point p) = 0;
	virtual void LineTo(Point p) = 0;
	virtual void DrawEllipse(Point leftTop, Point rightBottom) = 0;
	virtual void SetColor(Color color) = 0;
	// Прочие методы рисования графических примитивов
};

// Объекты, которые можно нарисовать с помощью Graphics
class Drawable
{
public:
	virtual ~Drawable() = default;
	virtual void Draw(Graphics& g) const = 0;
};

class Shape : public Drawable {
public:
	explicit Shape(Color color);
	Color GetColor() const;
	void SetColor(Color color);
private:
	Color m_color;
};

class Circle : public Shape {
public:
	Circle(Color color, Point center, double radius)
		: Shape(color) , m_center{center} , m_radius{radius}{
	}

	void Draw(Graphics& g) const override {
		g.SetColor(GetColor());
		g.DrawEllipse(
			{ m_center.x - m_radius, m_center.y - m_radius },
			{ m_center.x + m_radius, m_center.y + m_radius }
		);
	}
private:
	Point m_center;
	double m_radius;
};

int main()
{
    std::cout << "Hello World!\n";
}
