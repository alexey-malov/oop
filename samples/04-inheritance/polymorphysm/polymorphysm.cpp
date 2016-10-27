// polymorphysm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>

using namespace std;

class ISerializable
{
public:
	virtual void Serialize(ostream & strm)const = 0;
	virtual ~ISerializable(){}
};

class ICanvas
{
public:
	virtual void DrawCircle(double x, double y, double radius, const string & color) = 0;
	virtual void DrawLine(double x0, double y0, double x1, double y1, const string& color) = 0;

	virtual ~ICanvas() = default;
};

class IDrawable
{
public:
	virtual void Draw(ICanvas & canvas) const = 0;

	virtual ~IDrawable() = default;
};

class CCat : public ISerializable
{
public:
	void Serialize(ostream & strm)const override
	{
		strm << "cat" << endl;
	}
};

class CShape 
	: public ISerializable
	, public IDrawable
{
public:
	virtual double GetArea()const = 0;
};

class CCircle : public CShape
{
public:
	void Serialize(ostream & strm)const override
	{
		strm << "circle:" << m_radius << endl;
	}
	double GetArea()const override
	{
		return M_PI * m_radius * m_radius;
	}
	void Draw(ICanvas & canvas) const override
	{
		canvas.DrawCircle(m_centerX, m_centerY, m_radius, "red");
	}

private:
	int m_centerX = 100;
	int m_centerY = 100;
	int m_radius = 42;
};

void DoSomethingWithShape(CShape & shape)
{
	shape.Serialize(cout);
	ostringstream strm;
	shape.Serialize(strm);

	cout << "Shape area is " << shape.GetArea() << endl;
}

void Serialize(vector<const ISerializable*> const & someSerializableObjects, ostream & strm)
{
	for (auto obj : someSerializableObjects)
	{
		obj->Serialize(strm);
	}
}

class CLoggingCanvas : public ICanvas
{
public:

	void DrawCircle(double x, double y, double radius, const string & color) override
	{
		cout << "DrawCircle: " << x << ", " << y << ", " << radius << ", " << color << endl;
	}

	void DrawLine(double x0, double y0, double x1, double y1, const string& color) override
	{
		cout << "DrawLine: (" << x0 << ", " << y0 << ") - (" 
			<< x1 << ", " << y1 << "), " << color << endl;
	}
};

void DrawPicture(
	vector<const IDrawable*> const & drawables,
	ICanvas & canvas
	)
{
	for (auto drawable : drawables)
	{
		drawable->Draw(canvas);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	CCircle circle;
	CCat cat;
	DoSomethingWithShape(circle);

	cout << "----" << endl;

	vector<const ISerializable*> objects = { &cat, &circle };
	Serialize(objects, cout);
	ostringstream strm;
	Serialize(objects, strm);
	cout << "!!!" << strm.str() << "!!!" << endl;

	cout << "----" << endl;

	vector<const IDrawable *> picture = { &circle, };
	CLoggingCanvas canvas;
	DrawPicture(picture, canvas);

	return 0;
}

