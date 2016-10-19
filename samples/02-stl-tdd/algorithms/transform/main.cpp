#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <functional>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/algorithm/transform.hpp>

using namespace std;
using namespace std::placeholders;
using boost::transform;
using boost::adaptors::filtered;


void IntsToStrings()
{
	vector<int> ints = {1, 2, -3, 42, 13};

	vector<int> result;

	transform(ints | filtered([](int x) {
		return x > 0;
	}), back_inserter(result), [](auto x) {
		return x + 5; 
	});

}

void main()
{
	IntsToStrings();
}
