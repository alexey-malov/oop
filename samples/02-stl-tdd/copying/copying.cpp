#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
#include <cassert>
#include <iterator>

int main()
{
	std::vector<int> numbers{ 1, 2, 3 };
	std::copy(numbers.cbegin(), numbers.cend(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << "\n";
	std::copy(numbers.crbegin(), numbers.crend(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << "\n";

	std::deque<int> numbersQueue(numbers.size());
	
	std::copy(numbers.begin(), numbers.end(), numbersQueue.begin());
	std::copy(numbersQueue.begin(), numbersQueue.end(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << "\n";

	std::copy(numbers.begin(), numbers.end(), std::front_inserter(numbersQueue));
	std::copy(numbersQueue.begin(), numbersQueue.end(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << "\n";
}
