// Operators.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

void ArithmeticOperatorsTest()
{
	/*
	Вася купил 10 килограммов яблок, а бананов - на 5 килограммов больше, чем яблок.
	Груш он купил столько же, сколько яблок и бананов вместе.
	
	Во сколько раз больше масса всех фруктов, чем яблок?
	*/
	double apples = 10;
	double bananas = apples + 5;
	double pears = apples + bananas;
	double totalFruit = apples + bananas + pears;
	double ratio = totalFruit / apples;
	std::cout << "Total fruit to aplles ratio is " << ratio << "\n";
}

void ComparisonOperatorsTest()
{
	/*
	Пользователь вводит 3 числа: a, b и c
	Найти вывести максимальное из этих чисел
	*/
	std::cout << "Enter 3 integer numbers: ";

	int a, b, c;
	std::cin >> a >> b >> c;

	int maximum = a;
	if (b > maximum)
		maximum = b;
	if (c > maximum)
		maximum = c;

	std::cout << "Maximum is " << maximum << "\n";
}

void LeapYear()
{
	// Определить, является ли високосным введённый пользователем год
	std::cout << "Enter year: ";

	int year;
	std::cin >> year;

	bool isLeap = (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
	if (isLeap)
		std::cout << year << " is a leap year\n";
	else
		std::cout << year << " is not a leap year\n";
}

int main()
{
	/*
	Пользователь вводит натуральное число.
	Вывести количество единиц в десятичной записи этого числа
	*/
	std::cout << "Enter a natural number: ";
	int number;
	std::cin >> number;

	int n = number;
	int ones = 0;
	do
	{
		int units = n % 10;
		if (units == 1)
		{
			++ones;
		}
		n /= 10;
	} while (n != 0);
	std::cout << "Decimal notation of " << number << " contains " << ones << " 1s\n";
}

