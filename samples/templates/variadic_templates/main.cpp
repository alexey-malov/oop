// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>

void Print0()
{
}

template <typename T1>
void Print1(const T1& v1)
{
	cout << v1 << ",";
	Print0();
}

template <typename T1, typename T2>
void Print2(const T1& v1, const T2 & v2)
{
	cout << v1 << ",";
	Print1(v2);
}

template <typename T1, typename T2, typename T3>
void Print3(const T1& v1, const T2 & v2, const T3 & v3)
{
	cout << v1 << ",";
	Print2(v2, v3);
}

template <typename T1, typename T2, typename T3, typename T4>
void Print4(const T1& v1, const T2 & v2, const T3 & v3, const T4 & v4)
{
	cout << v1 << ",";
	Print3(v2, v3, v4);
}




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
