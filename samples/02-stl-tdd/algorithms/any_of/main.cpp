#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool IsNotEmpty(string const& str)
{
	return !str.empty();
}

void TestWhetherVectorContainsNonEmptyStrings()
{
	vector<string> strings = { "", "", "Alexey", "" };
	if (any_of(strings.begin(), strings.end(), IsNotEmpty))
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

	auto IsAnAdult = [](Person const& person) { return person.age >= 18; };

	if (any_of(begin(people), end(people), IsAnAdult))
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