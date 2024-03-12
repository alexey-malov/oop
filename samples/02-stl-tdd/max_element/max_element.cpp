// max_element.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string GetLongestString(const std::vector<std::string>& strings)
{
	auto it = std::ranges::max_element(strings, std::less<>{}, &std::string::length);
	return it != strings.cend() ? *it : std::string{};
}

int main()
{
	std::cout << GetLongestString({ { "one", "two", "three", "four", "five" } }) << std::endl;
}
