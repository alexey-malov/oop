// Booleans.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

int main()
{
	int n;
	std::cout << "Enter a number:";
	std::cin >> n;

	bool isEven = false;
	if (n % 2 == 0)
	{
		isEven = true;
	}
	if (isEven)
	{
		std::cout << n << " is an even number\n";
	}
	else
	{
		std::cout << n << " is an odd number\n";
	}
	return 0;
}
