// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

struct Base
{
	int x = 1;
	Base() = default;
	Base(const Base& other)
		: x(other.x)
	{
		std::cout << "Copying Base from " << &other << " to " << this << "\n";
	}
	virtual void WhoAmI() const { std::cout << "Base " << this << "\n"; }
	virtual ~Base()
	{
		if (std::uncaught_exception())
		{
			std::cout << "Deleting " << this << " during stack unwinding\n";
		}
		else
		{
			std::cout << "Deleting " << this << " during normal execution\n";
		}
	}
};

struct Derived : Base
{
	int y = 2;
	Derived() = default;
	Derived(const Derived& other)
		: Base(other)
		, y(other.y)
	{
		std::cout << "Copying Derived from " << &other << " to " << this << "\n";
	}
	void WhoAmI() const override { std::cout << "Derived " << this << "\n"; }
};

int main()
{
	try
	{
		{
			Derived d0;
		}
		Derived d;
		d.x = 555;
		std::cout << "Throwing " << &d << "\n";
		throw d;
	}
	catch (Base& b)
	{
		b.WhoAmI();
	}
	return 0;
}
