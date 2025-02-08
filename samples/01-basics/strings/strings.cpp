#include <iostream>
#include <string>

int main()
{
	std::string name = "Ivan";
	std::string surname = "Ivanov";

	std::string fullName = name + " " + surname;

	std::cout << fullName << std::endl;
}
