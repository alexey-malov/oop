// class_internals.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

class CPoint
{
public:
	/*
	CPoint()
		: m_x(0)
		, m_y(0)
	{
	}
	*/

	/*
	CPoint()
		:CPoint(0, 0)
	{
	}
	*/
	CPoint() = default;

	CPoint(int x, int y)
		: m_x(x)
		, m_y(y)
	{
	}

	void Draw()const
	{
		cout << m_x << ", " << m_y << endl;
	}

	void MoveBy(int dx, int dy)
	{
		m_x += dx;
		m_y += dy;
	}
private:
	int m_x = 0;
	int m_y = 0;
};

struct Point
{
	int x;
	int y;
};

void PointInit(Point * p, int x, int y)
{
	p->x = x;
	p->y = y;
}

void PointDraw(const Point *p)
{
	printf("%d, %d\n", p->x, p->y);
}

class CStudent
{
public:
	CStudent() = default;

	CStudent(const string& name, const string& surname)
		: m_name(name)
		, m_surname(surname)
	{
		cout << "Student " << m_name << " " << m_surname << " was born" << endl;
	}

	string GetName()const
	{
		return m_name;
	}

	~CStudent()
	{
		cout << "Student " << m_name << " " << m_surname << " has died" << endl;
	}
private:
	string m_name;
	string m_surname;
};

class Campus
{
public:
	Campus()
		: ivan(make_shared<CStudent>("Ivan", "Petrov"))
		, sergey(make_shared<CStudent>("Sergey", "Vasiliev"))
	{
	}
	shared_ptr<CStudent> GetSergey()const
	{
		return sergey;
	}
	~Campus()
	{
		cout << "The campus has been destroyed" << endl;
	}
private:
	shared_ptr<CStudent> ivan;
	shared_ptr<CStudent> sergey;
};

int _tmain(int argc, _TCHAR* argv[])
{
	{
		cout << "sizeof Point:" << sizeof(Point) << endl;
		Point p1;
		PointInit(&p1, 0, 0);
		Point p2;
		PointInit(&p2, 7, 8);
		PointDraw(&p1);
		PointDraw(&p2);
	}

	cout << "====" << endl;
	{
		cout << "sizeof CPoint:" << sizeof(CPoint) << endl;
		CPoint p0;
		p0.Draw();
		CPoint p1(0, 0);
		CPoint p2(7, 8);
		cout << &p1 << endl;
		p1.Draw();
		cout << &p2 << endl;
		p2.Draw();
		auto p = new CPoint(1, 2);
		p->Draw();
		delete p; p = nullptr;
	}

	{
		CStudent s1;
		cout << "'" << s1.GetName() << "'" << endl;
	}
	cout << "====" << endl;
	{
		auto s = std::make_shared<CStudent>();

		cout << "----" << endl;
		std::shared_ptr<CStudent> s1(new CStudent());
		auto s1copy = s1;
		s1 = nullptr;
		cout << "----" << endl;
	}
	cout << "====" << endl;
	{
		weak_ptr<CStudent> weakSergey;
		shared_ptr<CStudent> oneMoreSergey;
		{
			shared_ptr<CStudent> sergey;
			{
				Campus c;
				sergey = c.GetSergey();
			}
			cout << "Sergey is still alive" << endl;
			weakSergey = sergey;
			oneMoreSergey = weakSergey.lock();
		}
		assert(weakSergey.lock());
		cout << "Sergey must die" << endl;
		oneMoreSergey.reset();
		cout << "Sergey should be dead here" << endl;
		assert(!weakSergey.lock());
	}
	return 0;
}

