#include <iostream>

template <typename T>
T Maximum(T a, T b)
{
	std::cout << "Generic version called\n";
	return (a > b) ? a : b;
}

// Специализация шаблона для const char*
template <>
const char* Maximum<const char*>(const char* a, const char* b)
{
	std::cout << "Specialized version for const char* called\n";
	return (std::strcmp(a, b) > 0) ? a : b;
}




int main()
{
	std::cout << Maximum(1, 2) << "\n";
	std::cout << Maximum("hello", "world") << "\n";
}
