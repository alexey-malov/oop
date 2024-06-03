#include <iostream>
#include <math.h>
#include <memory>
#include <numbers>
#include <sstream>
#include <string>
#include <vector>

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual std::string ToString() const = 0;
	virtual ~IShape() = default;
};

class Shape : public IShape
{
public:
	// Подклассы не могут переопределить этот финальный метод
	std::string ToString() const final
	{
		std::ostringstream s;
		s << GetType() << " ";
		AppendCustomProperties(s); // выводим специфичные для фигуры свойства
		s << " area: " << GetArea(); // выводим общие для всех фигур свойства
		return s.str();
	}

private:
	// Наследники не могут вызвать приватные виртуальные методы, но смогут их переопределить
	virtual std::string GetType() const = 0;
	virtual void AppendCustomProperties(std::ostream&) const {}
};

class Circle final : public Shape
{
public:
	explicit Circle(double radius)
		: m_radius{ radius }
	{
	}
	double GetArea() const override
	{
		return std::numbers::pi * m_radius * m_radius;
	}

private:
	std::string GetType() const override
	{
		return "Circle";
	}

	void AppendCustomProperties(std::ostream& s) const override
	{
		s << "radius: " << m_radius;
	}

	double m_radius;
};

class Square final : public Shape
{
public:
	explicit Square(double size)
		: m_size(size)
	{
	}
	double GetArea() const override
	{
		return m_size * m_size;
	}

private:
	std::string GetType() const override
	{
		return "Square";
	}

	void AppendCustomProperties(std::ostream& s) const override
	{
		s << "size: " << m_size;
	}

	double m_size;
};

void ProcessShapes(const std::vector<std::unique_ptr<Shape>>& shapes)
{
	double totalArea = 0;
	for (const auto& sh : shapes)
	{
		std::cout << sh->ToString() << std::endl;
		totalArea += sh->GetArea();
	}
	std::cout << "Total area:" << totalArea << std::endl;
}

int main()
{
	std::vector<std::unique_ptr<Shape>> shapes;

	shapes.push_back(std::make_unique<Circle>(10));
	shapes.push_back(std::make_unique<Square>(5));

	ProcessShapes(shapes);
}