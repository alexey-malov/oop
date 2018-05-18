#include "Bad.h"

// Программа не будет компилироваться, пока из Bad.h не убрать using namespace std; 
// наша функция copy будет конфликтовать с алгоритмом std::copy 
void copy(int* from, int* to, int* foo)
{
	if (foo != nullptr)
	{
		to = from;
	}
}

int main()
{
	int x = 5;
	int y = 6;
	copy(&x, &y, nullptr);
	std::cout << "y:" << y;
	return 0;
}
