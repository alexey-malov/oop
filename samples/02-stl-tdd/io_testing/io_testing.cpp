/*
* Пример показывает, как можно тестировать ввод-вывод в тестах
* Идея - вместо чтения из cin и вывода в cout функции принимают ссылки на потоки ввода и вывода
*/
#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <sstream>

std::string ToLower(std::string s)
{
	std::ranges::transform(s, s.begin(),
		[](unsigned char ch) { return std::tolower(ch); });
	return s;
}

struct IO
{
	std::istream& input;
	std::ostream& output;
};

void EchoLowecased(IO io)
{
	std::string s;
	while (std::getline(io.input, s))
	{
		io.output << ToLower(s) << std::endl;
	}
}

void Test()
{
	// Тесты используют строковые потоки
	std::istringstream input;
	std::ostringstream output;

	input.str("");
	EchoLowecased({ input, output });
	assert(output.str() == "");

	// сбрасываем флаги eof и fail, которые установились при чтении до конца строки
	input.clear();
	input.str("HeLlo 125");
	EchoLowecased({ input, output });
	assert(output.str() == "hello 125\n");

	output.str(""); // Очистили вывод от предыдущего теста
	input.clear();
	input.str("HeLlo\nWorld");
	EchoLowecased({ input, output });
	assert(output.str() == "hello\nworld\n");
}

int main()
{
	Test();

	// В самой программе передаём std::cin и std:cout
	EchoLowecased({ std::cin, std::cout });
}
