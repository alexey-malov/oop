#include <iostream>
#include <optional>

void IsOdd1()
{
	int number;
	if (std::cin >> number) // Удалось ли прочитать number из консоли?
	{
		if (number % 2 == 0)
			std::cout << "Number is even";
		else
			std::cout << "Number is odd";
	}
	// Можно ли здесь использовать переменную number?
}

void IsOdd2()
{
	if (int number; std::cin >> number)
	{ // Видимость переменной `number` ограничена блоком if
		if (number % 2 == 0)
			std::cout << "Number is even";
		else
			std::cout << "Number is odd";
	}
	else
	{
		// Переменная number видна и здесь,
		// но тут number не инициализирована и использовать её нельзя
		number = 42;
	}
	// Здесь number не видна
}

void VarDeclaration()
{
	int x;
	int y;
	std::cin >> x >> y;
	if (int sum = x + y)
	{ // сюда попадём, если sum — не 0
		std::cout << sum << std::endl;
	}
	else
	{
		// Переменная sum равна нулю
	}
}

void PrintMark(int score)
{
	if (score >= 90)
		std::cout << "Excellent\n";
	else if (score >= 75)
		std::cout << "Good\n";
	else if (score >= 60)
		std::cout << "Satisfactory\n";
	else
		std::cout << "Unsatisfactory\n";
}

int main()
{
	int score;
	std::cin >> score;
	PrintMark(score);
}
