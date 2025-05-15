#include <chrono>
#include <iostream>
#include <memory>
#include <numbers>
#include <variant>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
using Seconds = std::chrono::duration<double>;

template <class... Ts>
struct overloaded : Ts...
{
	using Ts::operator()...;
};

// explicit deduction guide (не требуется, начиная с C++20)
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

struct Timings
{
	Clock::time_point startTime = Clock::now();
	Clock::time_point fillTime = startTime;
	Clock::time_point calcTime = startTime;
	Clock::time_point endTime = startTime;
};

struct Durations
{
	Durations(const Timings& t)
		: fillDuration(t.fillTime - t.startTime)
		, calcDuration(t.calcTime - t.fillTime)
		, destroyDuration(t.endTime - t.calcTime)
	{
	}

	Clock::duration fillDuration;
	Clock::duration calcDuration;
	Clock::duration destroyDuration;

	Durations& operator+=(const Durations& rhs)
	{
		fillDuration += rhs.fillDuration;
		calcDuration += rhs.calcDuration;
		destroyDuration += rhs.destroyDuration;
		return *this;
	}

	void Normalize(int count)
	{
		fillDuration /= count;
		calcDuration /= count;
		destroyDuration /= count;
	}
};

void PrintDurations(const Durations& d)
{
	std::cout << "Fill time: " << Seconds(d.fillDuration) << "\n";
	std::cout << "Calc time: " << Seconds(d.calcDuration) << "\n";
	std::cout << "Destroy time: " << Seconds(d.destroyDuration) << "\n";
}

namespace inheritance
{

class Shape
{
public:
	virtual ~Shape() = default;
	virtual double GetArea() const = 0;
};

class Rectangle : public Shape
{
public:
	Rectangle(double w, double h)
		: m_width(w)
		, m_height(h)
	{
	}

	double GetArea() const override { return m_width * m_height; }

private:
	double m_width, m_height;
};

class Circle : public Shape
{
public:
	explicit Circle(double r)
		: m_radius(r)
	{
	}

	double GetArea() const override { return m_radius * m_radius * std::numbers::pi; }

private:
	double m_radius;
};

Timings Benchmark()
{
	constexpr int NumShapes = 50'000'000;

	Timings timings;
	Clock::time_point fillEnd;
	Clock::time_point areaEnd;
	Clock::time_point destroyEnd;

	{
		std::vector<std::unique_ptr<Shape>> shapes;
		shapes.reserve(NumShapes);

		for (int i = 0; i < NumShapes; i += 2)
		{
			shapes.push_back(std::make_unique<Circle>(10));
			shapes.push_back(std::make_unique<Rectangle>(10, 20));
		}

		timings.fillTime = Clock::now();

		double area = 0;
		for (auto& sh : shapes)
		{
			area += sh->GetArea();
		}

		timings.calcTime = Clock::now();
	}
	timings.endTime = Clock::now();
	return timings;
}

} // namespace inheritance

namespace var
{
class Circle
{
public:
	explicit Circle(double r)
		: m_radius(r)
	{
	}

	double GetRadius() const { return m_radius; }

private:
	double m_radius;
};

class Rectangle
{
public:
	Rectangle(double w, double h)
		: m_width(w)
		, m_height(h)
	{
	}

	double GetWidth() const { return m_width; }
	double GetHeight() const { return m_height; }

private:
	double m_width, m_height;
};

using Shape = std::variant<Circle, Rectangle>;

double GetArea(const Shape& shape)
{
	return std::visit(
		overloaded{
			[](const Circle& c) { auto r = c.GetRadius(); return std::numbers::pi * r * r; },
			[](const Rectangle& r) { return r.GetWidth() * r.GetHeight(); },
		},
		shape);
}

Timings Benchmark()
{
	constexpr int NumShapes = 50'000'000;

	Timings timings;
	Clock::time_point fillEnd;
	Clock::time_point areaEnd;
	Clock::time_point destroyEnd;

	{
		std::vector<Shape> shapes;
		shapes.reserve(NumShapes);

		for (int i = 0; i < NumShapes; i += 2)
		{
			shapes.emplace_back(Circle(10));
			shapes.emplace_back(Rectangle(10, 20));
		}

		timings.fillTime = Clock::now();

		double area = 0;
		for (const auto& sh : shapes)
		{
			area += GetArea(sh);
		}

		timings.calcTime = Clock::now();
	}
	timings.endTime = Clock::now();
	return timings;
}

} // namespace var

namespace var1
{
class Circle
{
public:
	explicit Circle(double r)
		: m_radius(r)
	{
	}

	double GetRadius() const { return m_radius; }

private:
	double m_radius;
};

class Rectangle
{
public:
	Rectangle(double w, double h)
		: m_width(w)
		, m_height(h)
	{
	}

	double GetWidth() const { return m_width; }
	double GetHeight() const { return m_height; }

private:
	double m_width, m_height;
};

class Triangle
{
};
class Ellipse
{
};
class Square
{
};
class Polygon
{
};

using Shape = std::variant<Circle, Rectangle, Triangle, Ellipse, Square, Polygon>;

double GetArea(const Shape& shape)
{
	return std::visit(
		overloaded{
			[](const Circle& c) { auto r = c.GetRadius(); return std::numbers::pi * r * r; },
			[](const Rectangle& r) { return r.GetWidth() * r.GetHeight(); },
			[](const Ellipse&) { return 0.0; },
			[](const Triangle&) { return 0.0; },
			[](const Square&) { return 0.0; },
			[](const Polygon&) { return 0.0; },
		},
		shape);
}

Timings Benchmark()
{
	constexpr int NumShapes = 50'000'000;

	Timings timings;
	Clock::time_point fillEnd;
	Clock::time_point areaEnd;
	Clock::time_point destroyEnd;

	{
		std::vector<Shape> shapes;
		shapes.reserve(NumShapes);

		for (int i = 0; i < NumShapes; i += 2)
		{
			shapes.emplace_back(Circle(10));
			shapes.emplace_back(Rectangle(10, 20));
		}

		timings.fillTime = Clock::now();

		double area = 0;
		for (const auto& sh : shapes)
		{
			area += GetArea(sh);
		}

		timings.calcTime = Clock::now();
	}
	timings.endTime = Clock::now();
	return timings;
}

} // namespace var1

int main()
{
	std::cout << "Inheritance:\n";
	Durations d1 = inheritance::Benchmark();
	PrintDurations(d1);
	std::cout << "---\n";
	std::cout << "Variant (2 types):\n";
	Durations d2 = var::Benchmark();
	PrintDurations(d2);
	std::cout << "---\n";
	std::cout << "Variant (6 types):\n";
	Durations d3 = var1::Benchmark();
	PrintDurations(d3);
}
