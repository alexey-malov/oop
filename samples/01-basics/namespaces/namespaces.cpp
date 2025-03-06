// namespaces.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

namespace graphics
{
namespace shapes
{

struct Point
{
	int x = 0;
	int y = 0;
};

void Print(Point p)
{
	std::cout << p.x << ", " << p.y << "\n";
}

} // namespace shapes

void Draw(shapes::Point p)
{
	// ...
}

} // namespace graphics

namespace game::units
{
struct Monster
{
};
} // namespace game::units

void Test()
{
	using namespace game::units;
	Monster m;
}


void Draw(graphics::shapes::Point p)
{
	// ...
}

int main()
{
	graphics::shapes::Point p{ 10, 20 };
	Print(p); // Print будет найдена благодаря ADL
	/*graphics::*/Draw(p); // Надо указать namespace, т.к. ADL не найдёт Draw

	using graphics::shapes::Point;
	Point p2; // Теперь можно не указывать полное имя для Point
}
