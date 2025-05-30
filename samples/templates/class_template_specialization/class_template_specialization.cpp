#include <iostream>

// Первичный шаблон
template <typename T>
struct IsIntegral
{
	// Тип не является целочисленным
	static inline const bool value = false;
};
// Вспомогательная константа для проверки целочисленных типов
template <typename T>
inline constexpr bool IsIntegralV = IsIntegral<T>::value;

// Базовый класс для IsIntegral-специализаций для целочисленных типов
struct IsIntegralTrue
{
	static inline const bool value = true;
};
template <>
struct IsIntegral<unsigned> : IsIntegralTrue
{
};
template <>
struct IsIntegral<int> : IsIntegralTrue
{
};

template <typename T>
void Print(T value)
{
	if constexpr (IsIntegralV<T>)
	{
		std::cout << std::hex << "0x";
	}
	std::cout << value;
	if constexpr (IsIntegralV<T>)
	{
		std::cout << std::dec;
	}
	std::cout << "\n";
}

int main()
{
	static_assert(IsIntegralV<float> == false);
	static_assert(IsIntegralV<int> == true);
	static_assert(IsIntegralV<unsigned> == true);
	Print(100);
	Print(10.5);
}
