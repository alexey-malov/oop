// function.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace v1
{
bool FindStringInStream(std::istream& haystack, const std::string& needle)
{
	std::string line;
	bool found = false;
	for (int lineIndex = 1; std::getline(haystack, line); ++lineIndex)
	{
		auto pos = line.find(needle);
		if (pos != std::string::npos)
		{
			found = true;
			std::cout << lineIndex << std::endl;
		}
	}
	return found;
}
} // namespace v1

namespace v2
{
// Функция, принимающая параметры int, line, foundPos
using FindStringCallback = std::function<void(int lineIndex, const std::string& line, size_t foundPos)>;
bool FindStringInStream(std::istream& haystack, const std::string& needle,
	const FindStringCallback& callback = FindStringCallback())
{
	std::string line;
	bool found = false;
	for (int lineIndex = 1; std::getline(haystack, line); ++lineIndex)
	{
		auto pos = line.find(needle);
		if (pos != std::string::npos)
		{
			found = true;
			if (callback)
			{
				callback(lineIndex, line, pos);
			}
		}
	}
	return found;
}
} // namespace v2

void PrintLine(int lineIndex, [[maybe_unused]] const std::string& line, [[maybe_unused]] size_t foundPos)
{
	std::cout << lineIndex << std::endl;
}

class Printer
{
public:
	void Print(int lineIndex, [[maybe_unused]] const std::string& line, [[maybe_unused]] size_t foundPos)
	{
		std::cout << ++m_index << ". " << lineIndex << std::endl;
	}

private:
	int m_index = 0;
};

int main()
{
#if 0
	return v1::FindStringInStream(std::cin, "needle") ? 0 : 1;
	return v2::FindStringInStream(std::cin, "needle", PrintLine) ? 0 : 1;
	
	return v2::FindStringInStream(std::cin, "needle",
		[](int lineIndex, const std::string& line, size_t foundPos) {
			std::cout << lineIndex << std::endl;
		});
	std::vector<int> lines;
	v2::FindStringInStream(std::cin, "needle",
		[&lines](int lineIndex, const std::string& line, size_t foundPos) {
			lines.push_back(lineIndex);
		});
	// Можно использовать lines
#endif

	Printer printer;
	v2::FindStringInStream(std::cin, "needle", std::bind_front(&Printer::Print, printer));
}
