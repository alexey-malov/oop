
#include "pch.h"

using namespace std;

// clang-format off
enum class Color { Red, Yellow, Green, Black, White };
// clang-format on

struct Point
{
	double x, y;
};

struct Triangle
{
	Point vertex1, vertex2, vertex3;
	optional<Color> outlineColor;
	optional<Color> fillColor;
};

// clang-format off
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
// clang-format on

// Так в C++ переопределяется операция << для типов ostream и Point
std::ostream& operator<<(ostream& strm, Point point)
{
	return strm << "{" << point.x << ", " << point.y << "}";
}

ostream& operator<<(ostream& strm, const Triangle& t)
{
	strm << "{p1: " << t.vertex1 << ", p2: " << t.vertex2
		 << ", p3: " << t.vertex3;
	strm << ", outlineColor: "
		 << (t.outlineColor ? ColorToString(*t.outlineColor) : "none"s);
	strm << ", fillColor: "
		 << (t.fillColor ? ColorToString(*t.fillColor) : "none"s);
	return strm << "}";
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

optional<Vector2d> IntersectLineSegements(const LineSegment& l1, const LineSegment& l2)
{
	optional<Vector2d> intersectionPoint; // по умолчанию optional хранит аначение "не инициализировано"
	if (true)
	{
		intersectionPoint = Vector2d{ 3.5, 2.8 };
	}
	// TODO: вычислить точку пересечения отрезков прямых или вернуть none, если такой точки нет
	return intersectionPoint; // пересечения нет
}

int main()
{
	Triangle t{ { 0, 0 }, { 0, 1 }, { 1, 0 }, Color::Red, nullopt };
	cout << t << endl;
}
