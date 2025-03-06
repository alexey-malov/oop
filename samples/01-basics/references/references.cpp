// references.cpp : Defines the entry point for the application.
//

#include <array>
#include <cassert>
#include <iostream>
#include <string>

int main()
{
	std::string name = "Ivan"; // Это переменная типа std::string

	std::string& refName = name; // Ссылка на переменную name;
	refName += " Ivanov"; // Изменяем переменную name, используя ссылку

	std::cout << name << "\n"; // Ivan Ivanov

	int numbers[] = { 10, 20, 30, 40 };
	for (int i = 0; i < std::size(numbers); ++i)
	{
		int& currentNumber = numbers[i]; // Ссылка на текущий элемент массива
		currentNumber += 1;
	}

	for (int& number : numbers) // Перебираем элементы по ссылке
	{
		number += 2;
	}

	for (int number : numbers)
	{
		std::cout << number << " ";
	} // 13, 23, 33, 43

	return 0;
}
