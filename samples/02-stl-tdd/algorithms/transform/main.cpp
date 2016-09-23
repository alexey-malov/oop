#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

void IntsToStrings()
{
	vector<int> ints = {1, 2, -3, 42, 13};

	vector<string> strings;
	strings.reserve(ints.size());

	transform(ints.begin(), ints.end(), back_inserter(strings), [](int number){
		return "{" + to_string(number) + "}";
	});

	copy(strings.begin(), strings.end(), ostream_iterator<string>(cout, ", "));
	cout << endl;
}

void main()
{
	IntsToStrings();
}
