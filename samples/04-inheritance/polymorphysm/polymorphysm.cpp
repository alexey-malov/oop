// polymorphysm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

class ISerializable
{
public:
	virtual void Serialize(ostream & strm)const = 0;
	virtual ~ISerializable(){}
};

class CCat : public ISerializable
{
public:
	void Serialize(ostream & strm)const override
	{
		strm << "cat" << endl;
	}
};

class CShape : public ISerializable
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
private:
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


	return 0;
}

