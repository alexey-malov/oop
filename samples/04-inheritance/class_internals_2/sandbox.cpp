#include "stdafx.h"
#include <vector>
#include <memory>

using namespace std;

class Shape
{
public:
	virtual ~Shape() = default;
};

class Circle : public Shape
{
};
class Rectangle : public Shape
{
};

int main()
{
	vector<unique_ptr<Shape>> shapes;
	shapes.emplace_back(make_unique<Circle>(10.0, Color::RED));
	shapes.emplace_back(make_unique<Rectangle>(10.0, 20.0, Color::BLUE));
	// Деструкторы unique_ptr корректно удалят фигуры через указатель на класс Shape
}