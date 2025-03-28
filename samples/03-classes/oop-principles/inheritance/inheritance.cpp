#include <iostream>
#include <vector>

struct Point
{
	double x = 0, y = 0;
};

class GameObject
{
public:
	Point GetPosition() const { return m_position; }
	void SetPosition(Point pos) { m_position = pos; }

private:
	Point m_position;
};

struct Vector
{
	double dx = 0, dy = 0;
};

class Rocket : public GameObject
{
public:
	void SetSpeed(Vector speed) { m_speed = speed; }
	void Update(double timeDelta)
	{
		auto pos = GetPosition();
		pos.x += m_speed.dx * timeDelta;
		pos.y += m_speed.dy * timeDelta;
		SetPosition(pos);
	}

private:
	Vector m_speed;
};

int main()
{
	Rocket r;
	r.SetSpeed({.dx = 10, .dy = 20});
	r.Update(1);
	auto pos = r.GetPosition();
	std::cout << pos.x << ", " << pos.y << "\n";
}
