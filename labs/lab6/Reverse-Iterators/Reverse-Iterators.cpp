// Reverse-Iterators.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

int main()
{
	auto s = "Hello world!"s;

	copy(s.begin(), s.end(), ostream_iterator<char>(cout, "|"));
	cout << "\n";
	copy(s.rbegin(), s.rend(), ostream_iterator<char>(cout, "|"));
	cout << "\n";
	copy(make_reverse_iterator(s.end()),
		make_reverse_iterator(s.begin()),
		ostream_iterator<char>(cout, "|"));
	cout << "\n";

	return 0;
}
