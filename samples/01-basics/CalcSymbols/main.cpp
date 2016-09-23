#include <iostream>

int main() /* подсчет цифр, символов-разделителей и прочих символов */
{
	int numSpaces = 0;
	int numDigits[10] = {};
	int numOther = 0;
	char ch;
	while (std::cin.get(ch))
	{
		switch (ch)
		{
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			++numDigits[ch - '0'];
			break;
		case ' ':  case '\n': case '\t':
			++numSpaces;
			break;
		default:
			++numOther;
		}
	}

	std::cout << "Digits:";
	for (int n : numDigits)
	{
		std::cout << " " << n;
	}
	std::cout << ", whitespaces: " << numSpaces << ", other: " << numOther << std::endl;
	return 0;
}
