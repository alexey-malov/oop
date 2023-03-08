#include <algorithm>
#include <iostream>

// Неизменяемый потенциально тяжёлый аргумент следует принимать
// по константной ссылке, чтобы не копировать его
bool IsStringInLowerCase(const std::string& s)
{
	for (char ch : s)
		if (ch != std::tolower(static_cast<unsigned char>(ch)))
			return false;
	return true;
}

// Параметр n – входной. Он легковесный, поэтому его лучше принимать по значению
bool IsEven(int n)
{
	return n % 2 == 0;
}

/*
Ожидается, что функция изменит значение переданного ей параметра.
Поэтому она принимает s по ссылке
*/
void TrimBlanks(std::string& s)
{
	if (auto start = s.find_first_not_of(' '); start != s.npos)
	{
		s = s.substr(start, s.find_last_not_of(' ') - start + 1);
	}
}

struct Point
{
	int x, y;
};

// Входной параметр типа Point – легковесный.
// Он может быть эффективно передан по значению.
void PrintPoint(Point p)
{
	std::cout << p.x << ", " << p.y << "\n";
}

// Вызываемый код ожидает, что функция изменит строку s,
// переданную снаружи.Поэтому параметр s принимается по ссылке
void ToLower(std::string& s)
{
	for (char& ch : s)
		ch = std::tolower(static_cast<unsigned char>(ch));
}

int main()
{
}
