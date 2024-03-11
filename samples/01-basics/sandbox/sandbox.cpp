#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
	std::istringstream in{ "Hello 42" };
	std::string hello;
	int n;
	in >> hello >> n;
	assert(hello == "Hello" && n == 42);
	
	std::ostringstream out;
	out << "Hi " << 123;
	assert(out.str() == "Hi 123");
}
