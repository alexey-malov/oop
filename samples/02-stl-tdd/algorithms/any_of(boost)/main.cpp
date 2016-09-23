#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/cxx11/any_of.hpp>

using namespace std;
using namespace boost::algorithm;

bool IsNotEmpty(string const& str)
{
	return !str.empty();
}

void TestWhetherVectorContainsNonEmptyStrings()
{
	vector<string> strings = { "", "", "Alexey", "" };
	if (any_of(strings, IsNotEmpty))
	{
		cout << "strings vector contains at least one non-empty string" << endl;
	}
	else
	{
		cout << "strings vector contains empty strings only" << endl;
	}
}

struct Person
{
	string name;
	int age;
};

void TestWhetherThereIsAtLeastOneAdult()
{
	Person people[] = {
			{ "Ivan", 4 },
			{ "Sergey", 16 },
			{ "Stepan Anatolievich", 65 },
			{ "Maria Semenovna", 36 },
			{ "Egor", 13 }
	};

	if (any_of(people, [](Person const& person){
		return person.age >= 18;
	}))
	{
		cout << "At least one person is an adult" << endl;
	}
	else
	{
		cout << "There are no adults" << endl;
	}
}

void main()
{
	TestWhetherVectorContainsNonEmptyStrings();
	TestWhetherThereIsAtLeastOneAdult();
}