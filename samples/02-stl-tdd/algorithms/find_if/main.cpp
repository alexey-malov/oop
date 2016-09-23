#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

bool IsEven(int value)
{
	return (value % 2) == 0;
}

void FindFirstEvenValueInArray()
{
	int numbers[] = { 1, 3, 9, 10, 17, 12, 21 };

	auto it = find_if(cbegin(numbers), cend(numbers), IsEven);

	if (it != cend(numbers))
	{
		cout << "First even number in array is " << *it << endl;
	}
}

void FindLastNegativeNumberInVector()
{
	vector<int> numbers = {1, 2, 3, 0, -4, -1, 20};

	auto isNegative = bind2nd(less<int>(), 0);

	auto it = find_if(numbers.crbegin(), numbers.crend(), isNegative);

	if (it != numbers.crend())
	{
		cout << "Last negative number in vector is " << *it << endl;
	}
}

void main()
{
	FindFirstEvenValueInArray();
	FindLastNegativeNumberInVector();
}
