// variant_with_overloaded.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <variant>

using VariableType = std::variant<int, double, std::string>;

// Структура, наследующая переданный набор базовых классов
template <typename... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};
// Это т.н. deduction guide, который помогает компилятору вывести тип.
// Начиная с C++20, его можно не писать в этой конкретной ситуации.
template <typename... Ts>
overloaded(Ts...)->overloaded<Ts...>;

int main()
{
	auto printer = overloaded{ 
		[](int i) { std::cout << "int " << i << std::endl; },
		[](double d) { std::cout << "double " << d << std::endl; },
		[](const std::string& s) { std::cout << "string " << s << std::endl; },
	};

	VariableType varType = 42;
	std::visit(printer, varType); // int 42
	varType = 3.14;
	std::visit(printer, varType); // double 3.14
	varType = "Hello";
	std::visit(printer, varType); // string Hello
}

