#include <iostream>
#include <boost/algorithm/cxx11/all_of.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace boost::algorithm;

bool IsNotEmpty(string const& str)
{
	return !str.empty();
}

void TestThatAllStringsInVectorAreNonEmpty()
{
	vector<string> strings = { "One", "Two", "Three" };

	if (all_of(strings, IsNotEmpty))
	{
		cout << "All of the strings are non-empty" << endl;
	}
	else
	{
		cout << "Some of the strings are empty" << endl;
	}
}

void main()
{
	TestThatAllStringsInVectorAreNonEmpty();
}