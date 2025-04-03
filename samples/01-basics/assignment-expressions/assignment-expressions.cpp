#include <iostream>

int ReadInt()
{
	int n;
	std::cin >> n;
	return std::cin && n >= 0 ? n : -1;
}

int main()
{
	// Считываем до первого отрицательного числа
	for (int n; (n = ReadInt()) >= 0;)
	{
		std::cout << n << std::endl;
	}
}
