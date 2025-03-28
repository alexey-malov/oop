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

	virtual void Update(double timeDelta) {}

private:
	Point m_position;
};

struct Vector
{
	double dx = 0, dy = 0;
};

Point MovePoint(Point p, Vector speed, double timeDelta)
{
	p.x += speed.dx * timeDelta;
	p.y += speed.dy * timeDelta;
	return p;
}

class Rocket : public GameObject
{
public:
	void SetSpeed(Vector speed) { m_speed = speed; }
	void Update(double timeDelta) override
	{
		SetPosition(MovePoint(GetPosition(), m_speed, timeDelta));
	}

private:
	Vector m_speed;
};

constexpr double GravityConstant = 9.8;

class Ball : public GameObject
{
public:
	void SetSpeed(Vector speed) { m_speed = speed; }
	void Update(double timeDelta) override
	{
		m_speed.dy -= timeDelta * GravityConstant;
		SetPosition(MovePoint(GetPosition(), m_speed, timeDelta));
	}

private:
	Vector m_speed;
};

void UpdateGameObject(GameObject& gameObj)
{
	gameObj.Update(10);
}

int main()
{
	Rocket r;
	Ball b;
	b.SetSpeed({ .dx = 10, .dy = 20 });
	r.SetSpeed({ .dx = 10, .dy = 20 });
	UpdateGameObject(r);
	UpdateGameObject(b);
}
