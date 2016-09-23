#include <iostream>
#include <vector>
#include <functional>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/phoenix.hpp>

using namespace std;
using namespace boost::range;
using namespace boost::adaptors;
using namespace boost::phoenix::placeholders;

void FindFirstEvenValueInArray()
{
	int numbers[] = { 1, 3, 9, 10, 17, 12, 21 };

	auto it = find_if(numbers, arg1 % 2 == 0);

	if (it != end(numbers))
	{
		cout << "First even number in array is " << *it << endl;
	}
}

void FindLastNegativeNumberInVector()
{
	vector<int> numbers = { 1, 2, 3, 0, -4, -1, 20 };

	auto reversedNumbers = numbers | reversed;
	auto it = find_if(reversedNumbers, arg1 < 0);

	if (it != reversedNumbers.end())
	{
		cout << "Last negative number in vector is " << *it << endl;
	}
}

void main()
{
	FindFirstEvenValueInArray();
	FindLastNegativeNumberInVector();
}
