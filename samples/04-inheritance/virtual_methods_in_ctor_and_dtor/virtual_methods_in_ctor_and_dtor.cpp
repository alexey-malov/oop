// virtual_methods_in_ctor_and_dtor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class Base
{
public:
	Base()
	{
		std::cout << "Base::Base" << std::endl;
		PrintInfo();
	}
	~Base()
	{
		std::cout << "Base::~Base" << std::endl;
		PrintInfo();
	}
	virtual void PrintInfo() const
	{
		std::cout << "Base::PrintInfo" << std::endl;
	}
};

class Derived : public Base
{
public:
	Derived()
	{
		std::cout << "Derived::Derived" << std::endl;
		PrintInfo();
	}
	~Derived()
	{
		std::cout << "Derived::~Derived" << std::endl;
		PrintInfo();
	}
	void PrintInfo() const override
	{
		std::cout << "Derived::PrintInfo" << std::endl;
	}
};

int main()
{
	Derived d;
	std::cout << "----" << std::endl;
	d.PrintInfo();
	std::cout << "----" << std::endl;
}

