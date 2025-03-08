#include <iostream>
#include <utility>
#include <vector>

void Invalidation()
{
	std::vector<int> numbers;
	numbers.push_back(42);
	numbers.push_back(10);
	numbers.push_back(100);
	
	int& first = numbers.front();
	int& middle = numbers[numbers.size() / 2];
	int& last = numbers.back();

	auto b = numbers.begin();
	auto e = numbers.end();
	auto m = numbers.begin() + std::distance(b, e) / 2;

	numbers.push_back(12345);
	// Ссылки first, middle, last больше использовать нельзя
	// Итераторы b, e, m также нельзя использовать
}

int main()
{
	std::vector<int> numbers;
	for (int number; std::cin >> number;)
	{
		numbers.push_back(number);
	}

	std::cout << numbers.size() << " numbers entered\n";

	for (size_t i = 0; i < numbers.size() / 2; ++i)
	{
		std::swap(numbers[i], numbers[numbers.size() - i - 1]);
	}

	for (int number : numbers)
	{
		std::cout << number;
	}
}
