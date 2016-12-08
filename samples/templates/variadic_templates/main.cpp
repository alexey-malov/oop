#include <iostream>


template <typename Arg1, typename ...Args>
void Print(Arg1 && arg1, Args &&...args)
{
	std::cout << arg1 << " ";
	Print(std::forward<Args>(args)...);
}

void Print()
{
}


template <typename T, typename ...Args>
const T & Max(const T & arg1, const Args & ...args)
{
	const auto & maxArgs = Max(args...);
	return arg1 > maxArgs ? arg1 : maxArgs;
}

template <typename T>
const T & Max(const T & arg1)
{
	return arg1;
}

using namespace std;


int main()
{
	Print("hi", 1, 2, "hello");
	cout << endl;
	cout << Max(1, 2, 3, -3) << endl;

	return 0;
}
