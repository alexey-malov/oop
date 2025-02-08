// type-aliases.cpp : Defines the entry point for the application.
//

#include "type-aliases.h"
#include <array>
#include <vector>

using namespace std;

// Так в языке C объявляли синонимы типов
void TypeAliasInCStyle()
{
	// Теперь uint можно использовать наравне с unsigned int
	typedef unsigned int uint;
	uint value = 42;
}

// Теперь можно использовать имя типа Matrix3x3d для объявления матриц 3*3
using Matrix3x3d = std::array<std::array<double, 3>, 3>;

void PrintMatrix(const Matrix3x3d& m)
{
	for (auto& row : m) // Пробегаем по строкам матрицы
	{
		for (double item : row) // Пробегаем по элементам строки
		{
			std::cout << item << " ";
		}
		std::cout << endl;
	}
}

template <typename T, unsigned Rows, unsigned Columns>
using MatrixT = std::array<std::array<T, Columns>, Rows>;

template <typename T, unsigned Rows, unsigned Columns>
void PrintMatrix(const MatrixT<T, Rows, Columns>& m)
{
	for (auto& row : m) // Пробегаем по строкам матрицы
	{
		for (auto& item : row) // Пробегаем по элементам строки
		{
			std::cout << item << " ";
		}
		std::cout << endl;
	}
}
int main()
{
	Matrix3x3d m{ {
		{ { 1.0, 0.0, 0.0 } },
		{ { 0.0, 1.0, 0.0 } },
		{ { 0.0, 0.0, 1.0 } },
	} };
	PrintMatrix(m);

	// Матрица целых чисел размером 3*2
	using Matrix3x2i = MatrixT<int, 3, 2>;
	Matrix3x2i m1{ {
		{ { 1, 2 } },
		{ { 3, 4 } },
		{ { 5, 6 } },
	} };
	PrintMatrix(m1);
}
