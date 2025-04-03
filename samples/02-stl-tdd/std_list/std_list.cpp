#include <iostream>
#include <list>

int main()
{
	std::list<int> numbers;
	numbers.push_back(1); // [1]
	numbers.push_front(2); // [2, 1]

	auto b = numbers.begin(); // [ b>2, 1]
	++b; //[2, b>1]
	numbers.insert(b, 42); // [2, 42, b>1]
	auto c = numbers.insert(b, 100); // [2, 42, c>100, b>1]

	numbers.erase(b); // [2, 42, c>100], b невалиден

	for (auto number : numbers)
	{
		std::cout << number << " ";
	}
}
