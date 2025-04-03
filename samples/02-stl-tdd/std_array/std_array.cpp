#include <array>
#include <iostream>

int main()
{
	try
	{
		std::array<int, 6> fibNumbers{ 1, 1, 2, 3, 5, 8 };
		int itemIndex;
		if (std::cin >> itemIndex)
		{
			// Метод at() выбросит исключение если индекс выходит
			// за пределы массива
			std::cout << fibNumbers.at(itemIndex) << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
