// numbers.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <numbers>

double CalculateCircleArea(double radius)
{
	return std::numbers::pi * radius * radius;
}

int main()
{
	std::cout << CalculateCircleArea(10) << std::endl;
}
