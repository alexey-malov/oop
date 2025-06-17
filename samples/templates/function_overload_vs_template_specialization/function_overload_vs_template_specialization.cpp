#include <cstring>
#include <iostream>
#include <string>

namespace by_val
{

template <typename T>
T Max(T a, T b)
{
	return (a > b) ? a : b;
}

template <>
const char* Max<const char*>(const char* a, const char* b)
{
	return (std::strcmp(a, b) > 0) ? a : b;
}

} // namespace by_val

namespace by_const_ref
{
template <typename T>
T Max(const T& a, const T& b)
{
	return (a > b) ? a : b;
}

template <>
const char* Max<const char*>(const char* const& a, const char* const& b)
{
	return (std::strcmp(a, b) > 0) ? a : b;
}
} // namespace by_const_ref

namespace use_overload
{

template <typename T>
T Max(const T& a, const T& b)
{
	return (a > b) ? a : b;
}

// Обратите внимание, что в перегрузке мы не обязаны принимать указатель по ссылке
const char* Max(const char* a, const char* b)
{
	return (std::strcmp(a, b) > 0) ? a : b;
}

} // namespace use_overload

int main()
{
	{
		using namespace by_val;
		std::cout << "Max of 3 and 4 is: " << Max(3, 4) << std::endl;
		// Будет вызвана специализация Max<const char*>
		std::cout << "Max of 'hello' and 'world' is: "
				  << Max("hello", "world") << std::endl;

		std::string str1 = "apple";
		std::string str2 = "banana";
		// Ok, но str1 и str2 будут скопированы в Max
		std::cout << "Max of '" << str1 << "' and '" << str2 << "' is: "
				  << Max(str1, str2) << std::endl;
	}

	// Ок, будем принимать аргументы по константной ссылке
	{
		using namespace by_const_ref;
		std::cout << "Max of 3 and 4 is: " << Max(3, 4) << std::endl;

		std::string str1 = "apple";
		std::string str2 = "banana";
		// Будет вызван первичный шаблон Max(const T&, const T&)
		std::cout << "Max of '" << str1 << "' and '" << str2 << "' is: "
				  << Max(str1, str2) << std::endl;

#if 0
		// Так не скомпилируется, так как "apple" и "banana" — массивы символов разной длины
		std::cout << "Max of 'apple' and 'banana' is: " << Max("apple", "banana") << std::endl;
#endif

#if 0
		// Так не скомпилируется, так как "hello" и "world" — массивы, а массивы нельзя возвращать из функции
		
		// std::cout << "Max of 'hello' and 'world' is: "
		//           << Max("hello", "world") << std::endl;
#endif

		// Так скомпилируется, но код усложнён из-за приведения типов
		std::cout << "Max of 'hello' and 'world' is: "
				  << Max(static_cast<const char*>("hello"), static_cast<const char*>("world")) << std::endl;

		// Указываем явно, какую именно специализацию хотим использовать
		std::cout << "Max of 'hello' and 'world' is: "
				  << Max<const char*>("apple", "banana") << std::endl;
	}

	{
		using namespace use_overload;
		// Будет вызвана перегрузка Max(const T&, const T&)
		std::cout << "Max of 3 and 4 is: " << Max(3, 4) << std::endl;

		// Будет вызвана перегрузка Max(const char*, const char*),
		// так как если подходит перегрузка, то шаблон не используется
		std::cout << "Max of 'hello' and 'world' is: " << Max("apple", "banana") << std::endl;

		std::string str1 = "apple";
		std::string str2 = "banana";
		// Будет вызвана перегрузка Max(const T&, const T&)
		std::cout << "Max of '" << str1 << "' and '" << str2 << "' is: " << Max(str1, str2) << std::endl;
		std::cout << "Max of 0 and 0 is: " << Max(0, 0) << std::endl;
	}
}
