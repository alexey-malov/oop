#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <iostream>

enum class MakeOfCar
{
	Toyota,
	Mitsubishi,
	Ford,
	Volkswagen,
};

enum class Color
{
	Red,
	Green,
	Blue,
	Black,
};

class Car
{
public:
	void Drive(double distanceKm);
	void Repaint(Color color);
	void Refuel(double fuel);

private:
	MakeOfCar m_make = MakeOfCar::Toyota;
	int m_yearOfManufacture = 2019;
	Color m_color = Color::Black;
	double m_fuel;
};

class Point
{
public:
	double x, y;
};

class Triangle
{
public:
	double GetArea() const;
	double GetPerimeter() const;
	Point GetCenter() const;

	void Move(double dx, double dy);
	void Scale(double sx, double sy);
	void Rotate(Point center, double angle);

private:
	Point p0, p1, p2;
};

using namespace std;

class IntStack
{
public:
	void Push(int value);
	int Pop();
	bool IsEmpty() const;

private:
	struct Node
	{
		int data;
		unique_ptr<Node> next;
	};
	unique_ptr<Node> m_top;
};

class Shape
{
public:
	virtual ~Shape() = default;
	Color GetColor() const { return m_color; }
	void SetColor(Color c) { m_color = c; }
	virtual double GetArea() const = 0;

private:
	Color m_color = Color::Red;
};

class Circle : public Shape
{
public:
	double GetArea() const override { return M_PI * m_radius * m_radius; }
	double GetRadius() const { return m_radius; }
	void SetRadius(double r) { m_radius = r; }

private:
	double m_radius = 1.0;
};

class Date
{
public:
	void Next();
	void Print() const;

private:
	int year, month, day;
};

// Реализация методов класса
void Date::Print() const
{
	std::cout << day << "/" << month << "/" << year << "\n";
}

void Date::Next()
{
	// ...
}


int main()
{
	return 0;
}
