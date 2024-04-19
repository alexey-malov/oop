// inheritance_and_destructors.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

struct Computer {
	Computer() { std::cout << "Computer::Computer" << std::endl; }
	~Computer() { std::cout << "Computer::~Computer" << std::endl; }
};

class Person {
public:
	Person(std::string name) : m_name(std::move(name)) {
		std::cout << "Person::Person(" << m_name << ")" << std::endl;
	}
	~Person() {
		std::cout << "Person::~Person" << std::endl;
	}
private:
	std::string m_name;
};

class Programmer : public Person {
public:
	Programmer(std::string name) : Person{ std::move(name) } {
		std::cout << "Programmer::Programmer" << std::endl;
	}
	~Programmer() { std::cout << "Programmer::~Programmer" << std::endl; }

private:
	Computer m_computer;
};

int main()
{
	Programmer programmer{ "John Carmack" };
}
