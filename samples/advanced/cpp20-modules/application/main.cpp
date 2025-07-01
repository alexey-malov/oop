#include <iostream>
import person;

int main()
{

	Person person{ "John Doe", 30 };

	auto gender = person.GetGender();
	std::cout << gender << std::endl;
}
