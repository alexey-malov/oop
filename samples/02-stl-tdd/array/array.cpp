// array.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <array>
#include <iostream>
#include <optional>

using Matrix3x3 = std::array<std::array<double, 3>, 3>;

void PrintMatrix(const Matrix3x3& mat)
{
	for (const auto& row : mat)
	{
		for (const auto& item : row)
		{
			std::cout << item << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	Matrix3x3 m{};
	m[0][0] = m[1][1] = m[2][2] = 1.0;
	PrintMatrix(m);
}
