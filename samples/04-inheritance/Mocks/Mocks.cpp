#include <cassert>
#include <iostream>
#include <sstream>

class ICanvas
{
public:
	virtual void DrawElliplse(double l, double t, double w, double h) = 0;
	virtual void DrawLine(double x0, double y0, double x1, double y1) = 0;
};

class Shape
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;
};

class Circle : public Shape
{
public:
	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawElliplse(m_x - m_r, m_y - m_r, m_r * 2, m_r * 2);
	}

private:
	double m_x = 0;
	double m_y = 0;
	double m_r = 42;
};

class Rectangle : public Shape
{
public:
	void Draw(ICanvas& canvas) const override
	{
		const auto right = m_left + m_width;
		canvas.DrawLine(m_left, m_top, right, m_top); // top side
		const auto bottom = m_top + m_height;
		canvas.DrawLine(m_left, bottom, right, bottom); // bottom side
		canvas.DrawLine(m_left, m_top, m_left, bottom); // left side
		canvas.DrawLine(right, m_top, right, bottom); // right side
	}

private:
	double m_left = 0;
	double m_top = 0;
	double m_width = 10;
	double m_height = 5;
};

class Canvas : public ICanvas
{
public:
	void DrawElliplse(double l, double t, double w, double h) override
	{
		//
	}

	void DrawLine(double x0, double y0, double x1, double y1) override
	{
	}
};

struct MockCanvas : ICanvas
{
	std::ostream& os;

	MockCanvas(std::ostream& os)
		: os(os)
	{
	}

	void DrawElliplse(double l, double t, double w, double h)
	{
		os << "ellipse " << l << " " << t << " " << w << " " << h << "\n";
	}

	void DrawLine(double x0, double y0, double x1, double y1) override
	{
		os << "line " << x0 << " " << y0 << " " << x1 << " " << y1 << "\n";
	}
};

int main()
{
	{
		Circle c;
		std::ostringstream ss;
		MockCanvas canvas{ ss };

		c.Draw(canvas);
		assert(ss.str() == "ellipse -42 -42 84 84\n");
	}

	{
		Rectangle r;
		std::ostringstream ss;
		MockCanvas canvas{ ss };

		// Рисую прямоугольник на mock-холсте
		r.Draw(canvas);

		// Снимаю с холста данные о вызовах функций рисования
		// и сравниваю с ожидаемым от прямоугольника результатом
		assert(ss.str() == "line 0 0 10 0\n"
						   "line 0 5 10 5\n"
						   "line 0 0 0 5\n"
						   "line 10 0 10 5\n");
	}
}
