#include <boost/optional.hpp>
#include <iostream>
#include <string>

using boost::optional;
using boost::none;
using namespace std;

enum class Color
{
	Red, Yellow, Green, Black, White
};

// Точка, у которой может быть или не быть задан цвет
struct Point
{
	int x;
	int y;
	optional<Color> color;
};

string ColorToString(Color color)
{
	switch (color)
	{
	case Color::Red: return "red";
	case Color::Yellow: return "yellow";
	case Color::Green: return "green";
	case Color::Black: return "black";
	case Color::White: return "white";
	default:
		assert(!"unknown color. please update code");
		return "";
	}
}

std::ostream & PrintPoint(ostream & strm, const Point& point)
{
	strm << "{" << point.x << ", " << point.y << ", ";
	strm << (point.color ? ColorToString(point.color.get()) : "undefined color") << "}";
	return strm;
}

struct Vector2d
{
	double x;
	double y;
};

struct LineSegment
{
	Vector2d start;
	Vector2d end;
};

optional<Vector2d> IntersectLineSegements(const LineSegment &l1, const LineSegment &l2)
{
	optional<Vector2d> intersectionPoint; // по умолчанию optional хранит занчение "не инициализировано"
	if (true)
	{
		intersectionPoint = Vector2d { 3.5, 2.8 };
	}
	// TODO: вычислить точку пересечения отрезков прямых или вернуть none, если такой точки нет
	return intersectionPoint; // пересечения нет
}


int main()
{
	Point point1 {10, 20, none};
	Point point2 { 10, 20, Color::Red };
	PrintPoint(cout, point1) << endl; 
	PrintPoint(cout, point2) << endl;
}
