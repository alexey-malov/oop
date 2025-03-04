#include <iostream>

// Объявление функции.
int Add(int x, int y);

int Double(int x)
{
	// Чтобы вызвать функцию, она должна быть объявлена до своего вызова
	return Add(x, x);
}

// Определение функции
int Add(int x, int y)
{
	return x + y;
}

// Функция, которая не имеет возвращаемого значения
void Print(int x)
{
	std::cout << x << std::endl;
}

int main()
{
	Print(Double(7)); // Выведет 14
}
