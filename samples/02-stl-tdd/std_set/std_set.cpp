#include <iostream>
#include <set>
#include <string>

int main()
{
	std::set<std::string> maleNames{ "Ivan", "Peter", "Vasily" };
	maleNames.insert("Alexey");

	if (std::string name; std::getline(std::cin, name))
	{
		if (maleNames.contains(name))
		{
			std::cout << name << " is a male name\n";
		}
	}

	for (const auto& name : maleNames)
	{
		std::cout << name << " "; // Alexey, IVan, Peter, Vasily
	}
}
