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

int main()
{
	Point point1 {10, 20, none};
	Point point2 { 10, 20, Color::Red };
	PrintPoint(cout, point1) << endl; 
	PrintPoint(cout, point2) << endl;
}
