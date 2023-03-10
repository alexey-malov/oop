// namespaces.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

namespace
{
int Add1(int x, int y)
{
	return x + y;
}
} // namespace

int Add2(int x, int y)
{
	return x + y;
}

int Example1(int x, int y)
{
	return Add1(x, y);
}

int Example2(int x, int y)
{
	return Add2(x, y);
}

int main()
{
	DoSomeInternalTask();
}
