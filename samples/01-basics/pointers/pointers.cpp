#include <iostream>

// возвращаем адрес найденного символа в строке или nullptr в случае отсутствия
const char* FindChar(const char str[], char ch) {
	const char* p = str;

	while (*p != '\0') {
		if (*p == ch)
			return p;
		++p;
	}

	return nullptr;
}

int main()
{
	const char str[] = "Hello, world!\n";

	const char* pw = FindChar(str, 'w');
	if (pw)
		std::cout << pw << std::endl;
}
