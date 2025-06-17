#include <fstream>
#include <iostream>
#include <string>

class Vector2D
{
public:
	Vector2D(double x0, double y0);
	Vector2D() = default;

    bool operator!=(const Vector2D& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
 
	double x = 0;
	double y = 0;
};

bool operator==(const Vector2D& lhs, const Vector2D& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

// В C++ 20 != можно не реализовывать, если у класса уже реализована операция ==
bool operator!=(const Vector2D& lhs, const Vector2D& rhs)
{
    return !(lhs == rhs);
}
