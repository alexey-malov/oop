#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>

using namespace std;

class IShape
{
public:
	virtual double GetArea()const = 0;
	virtual string ToString()const = 0;
};

class CShape : public IShape
{
public:
	string ToString() const final
	{
		ostringstream s;
		s << GetType() << " ";
		AppendCustomProperties(s); // выводим специфичные для фигуры свойства
		s << " area: " << GetArea(); // выводим общие для всех фигур свойства
		return s.str();
	}
protected:
	virtual string GetType()const = 0;
	virtual void AppendCustomProperties(ostream & s)const
	{
		(void)&s;
	}
};

class CCircle final : public CShape
{
public:
	double GetArea()const override
	{
		return M_PI * m_radius * m_radius;
	}

protected:
	string GetType() const override
	{
		return "Circle";
	}

	void AppendCustomProperties(ostream & s) const override
	{
		s << "radius: " << m_radius;
	}
private:
	double m_radius = 42;
};

class CSquare final: public CShape
{
public:
	double GetArea()const
	{
		return m_size * m_size;
	}
protected:
	string GetType() const override
	{
		return "Square";
	}

	void AppendCustomProperties(ostream & s) const override
	{
		s << "size: " << m_size;
	}

private:
	double m_size = 10;
};

int main()
{
	return 0;
}