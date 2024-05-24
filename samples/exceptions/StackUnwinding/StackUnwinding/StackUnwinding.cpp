// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

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

class Logger
{
public:
	Logger(std::string name)
		: m_name{ std::move(name) }
	{
		std::cout << "Logger " << m_name << " was created\n";
	}
	Logger(const Logger& other)
		: m_name{ other.m_name }
	{
		std::cout << "Logger " << m_name << " was copied\n";
	}
	Logger& operator=(const Logger&) = delete; // No assignment
	~Logger()
	{
		std::cout << "Logger " << m_name << " was destroyed\n";
	}

private:
	std::string m_name;
};

#if 0
void Bar()
{
	Logger logger{ "Bar" };
	abort(); // Аварийное завершение работы программы
}

void Foo()
{
	Logger logger{ "Foo" };
	Bar();
}

void Example1()
{
	Logger logger{ "main" };
	Foo();
}
#else
void Bar()
{
	Logger logger{ "Bar" };
	throw std::runtime_error("Error in Bar");
	std::cout << "Exit from bar";
}

void Foo()
{
	Logger logger{ "Foo" };
	Bar();
}

void Example1()
{
	try
	{
		Logger logger{ "main" };
		Foo();
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught " << e.what() << std::endl;
	}
}
#endif

void MayThrow()
{
}

void MayThrowAsWell() noexcept(false)
{
}

void DoesNotThrow() noexcept
{
}

void DoesNotThrowAsWell() noexcept(true)
{
}

void Example2()
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
}

int main()
{
	Example1();
	return 0;
}
