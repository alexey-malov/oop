#include <iostream>

enum TrafficLight
{
	Red,
	Green,
	Blue,
};

int main()
{
	TrafficLight tl = Blue;
	std::cout << tl << std::endl; // Выведет 2
}
