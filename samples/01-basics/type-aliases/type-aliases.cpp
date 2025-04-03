#include <array>
#include <cmath>
#include <iostream>
#include <numbers>
#include <vector>

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
		std::cout << std::endl;
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
		std::cout << std::endl;
	}
}

// Теперь Real можно использовать для обозначения чисел с плавающей запятой
typedef float Real;
struct Vec3
{
	Real x = 0;
	Real y = 0;
	Real z = 0;
};

// Возвращает скалярное произведение 3D векторов
auto DotProduct(const Vec3& a, const Vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

auto GetLength(const Vec3& a) // Возвращает длину вектора
{
	return std::hypot(a.x, a.y, a.z);
}

auto GetAngle(const Vec3& a, const Vec3& b) // Возвращает угол в радианах между векторами
{
	return std::acos(DotProduct(a, b) / (GetLength(a) * GetLength(b)));
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

	std::cout << GetAngle({ 1, 0, 0 }, { 1, 1, 0 }) * 180 / std::numbers::pi << std::endl;
}
