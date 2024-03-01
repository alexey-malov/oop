// reinterpret_cast.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdint>
#include <string>

void ChangeString(std::uintptr_t p)
{
	std::string* pstr = reinterpret_cast<std::string*>(p);
	(*pstr) = "Goodbye";
}

int main()
{
	std::string name = "Hello";
	// Так нельзя
	// ChangeString(&name);
	
	// Так можно
	ChangeString(reinterpret_cast<uint64_t>(&name));

	std::cout << name << std::endl; // Выведет Goodbye
}
