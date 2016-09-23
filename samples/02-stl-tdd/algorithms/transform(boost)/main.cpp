#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm/copy.hpp>

using namespace std;
using namespace boost;

string IntToStringWithinCurlyBraces(int value)
{
	return "{" + to_string(value) + "}";
}

void IntsToStrings()
{
	vector<int> ints = { 1, 2, -3, 42, 13 };

	vector<string> strings;
	strings.reserve(ints.size());

	transform(ints, back_inserter(strings), IntToStringWithinCurlyBraces);

	copy(strings, ostream_iterator<string>(cout, ", "));
	cout << endl;
}

void main()
{
	IntsToStrings();
}
