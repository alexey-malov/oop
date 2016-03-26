// class_internals_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

class CShape
{
public:
	virtual void Hello()const{ cout << "Hello from CShape" << endl; }
	virtual void Draw(int color)const { cout << "Drawing Shape with color: " << color << endl; }
};

class CRectangle : public CShape
{
public:
	CRectangle(int w, int h) :m_width(w), m_height(h){}
	void Hello()const override { cout << "Hello from CRectangle " << m_width << "x" << m_height << endl; }
	void Draw(int color)const override { cout << "Drawing Rectangle with color: " << color << endl; }
private:
	int m_width, m_height;
};

class CCircle : public CShape
{
public:
	CCircle(int radius) :m_radius(radius){}
	void Hello()const override { cout << "Hello from CCircle of radius " << m_radius << endl; }
	void Draw(int color)const override { cout << "Drawing Circle with color: " << color << endl; }
private:
	int m_radius;
};

void PrintGreetingFromShape(const CShape & shape)
{
	shape.Hello();
	shape.Draw(42);
}

void BackToThePast();

int _tmain(int argc, _TCHAR* argv[])
{
	{
		CCircle circle(42);
		CRectangle rect(13, 28);
		CShape shape;
		PrintGreetingFromShape(shape);
		PrintGreetingFromShape(rect);
		PrintGreetingFromShape(circle);
	}

	cout << "Welcome to world of C language" << endl;

	BackToThePast();
	return 0;
}

struct Shape;

// PFNSHAPEHELLO - указатель на функцию void(const Shape * const self)
// аналог метода класса CShape::Hello
typedef void(*PFNSHAPEHELLO)(const Shape * const self);
// Аналог метода Draw(int color)
typedef void(*PFNSHAPEDRAW)(const Shape * const self, int color);

// Таблица виртуальных функций класса Shape
struct ShapeVtbl
{
	// Виртуальная функция Hello
	PFNSHAPEHELLO hello;
	// Виртуальная функция Draw
	PFNSHAPEDRAW draw; 
};

struct Shape
{
	const ShapeVtbl * pvtbl;
};

void ShapeHello(const Shape * const self)
{
	printf("Hello from Shape\n");
}

void ShapeDraw(const Shape * const self, int color)
{
	printf("Drawing Shape with color %d\n", color);
}

struct Rectangle
{
	Shape shape;
	int width;
	int height;
};
void RectangleHello(const Rectangle * const self)
{
	printf("Hello from Rectangle %dx%d\n", self->width, self->height);
}
void RectangleDraw(const Rectangle * const self, int color)
{
	printf("Drawing Rectangle with color %d\n", color);
}


struct Circle
{
	Shape shape;
	int radius;
};
void CircleHello(const Circle * const self)
{
	printf("Hello from Circle %d\n", self->radius);
}
void CircleDraw(const Circle * const self, int color)
{
	printf("Drawing Circle with color %d\n", color);
}


void ShapeHelloVirtual(const Shape * const self)
{
	self->pvtbl->hello(self);
}
void ShapeDrawVirtual(const Shape * const self, int color)
{
	self->pvtbl->draw(self, color);
}

const ShapeVtbl g_shapeVtbl = 
{
	&ShapeHello,
	&ShapeDraw
};
const ShapeVtbl g_circleVtbl = 
{
	(PFNSHAPEHELLO)&CircleHello,
	(PFNSHAPEDRAW)&CircleDraw
};
const ShapeVtbl g_rectangleVtbl = 
{
	(PFNSHAPEHELLO)&RectangleHello,
	(PFNSHAPEDRAW)&RectangleDraw
};

void PrintGreetingFromOldSchoolShape(const Shape* shape)
{
	ShapeHelloVirtual(shape);
	ShapeDrawVirtual(shape, 42);
}

void ConstructShape(Shape *shape)
{
	shape->pvtbl = &g_shapeVtbl;
}

void ConstructRectangle(Rectangle *rect, int w, int h)
{
	rect->shape.pvtbl = &g_rectangleVtbl;
	rect->width = w;
	rect->height = h;
}

void ConstructCircle(Circle * circle, int radius)
{
	circle->shape.pvtbl = &g_circleVtbl;
	circle->radius = radius;
}

void BackToThePast()
{
	Shape shape;
	ConstructShape(&shape);

	Rectangle rect;
	ConstructRectangle(&rect, 22, 33);

	Circle circle;
	ConstructCircle(&circle, 66);

	ShapeHello(&shape);
	RectangleHello(&rect);
	CircleHello(&circle);

	PrintGreetingFromOldSchoolShape(&shape);
	PrintGreetingFromOldSchoolShape(&rect.shape);
	PrintGreetingFromOldSchoolShape(&circle.shape);


}