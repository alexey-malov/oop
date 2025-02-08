// global-vars.cpp : Defines the entry point for the application.
//

#include <iostream>

// Глобальные переменные по умолчанию инициализируются нулями
int globalVar;
int anotherGlobalVar = 42; // Можно проинициализировать заданным значением

void PrintGlobalVar()
{
	std::cout << globalVar << std::endl;
}

int main()
{
	PrintGlobalVar(); // Выведет 0
	globalVar = 13;
	PrintGlobalVar(); // Выведет 13
	std::cout << anotherGlobalVar << std::endl; // Выведет 42
}
