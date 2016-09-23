#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool IsNotEmpty(string const& str)
{
	return !str.empty();
}

void TestThatAllStringsInVectorAreNonEmpty()
{
	vector<string> strings = {"One", "Two", "Three"};

	if (all_of(strings.begin(), strings.end(), IsNotEmpty))
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