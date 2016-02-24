#include "stdafx.h"
#include "VectorProcessor.h"
#include <algorithm>
#include <numeric>
#include <functional>
#include <boost/range/algorithm/transform.hpp>
#pragma warning (push, 3)
#include <boost/phoenix.hpp>
#pragma warning (pop)

using namespace std;
using namespace std::placeholders;
using namespace boost::phoenix::placeholders;
using namespace boost::phoenix;
using boost::transform;

void ProcessVector(std::vector<double> & numbers)
{
	auto IsPositive = [](double number){return number > 0; };

	size_t numberOfPositives = 0;

	// функция, суммирующая только положительные числа с подсчетом их количества
	auto addIfPositive = [&numberOfPositives](double acc, double current) {
		if (current > 0.0)
		{
			++numberOfPositives;
			return acc + current;
		}
		return acc;
	};

	auto sumOfPositives = accumulate(numbers.begin(), numbers.end(), 0.0, addIfPositive);

	double avg = (numberOfPositives > 0) ? sumOfPositives / numberOfPositives : 0.0;

	// TODO: Используй силу алгоритма std::transform, Люк, вместо этого цикла
	boost::transform(numbers, numbers.begin(), arg1 + avg);
	/*
	auto addAvg = bind(plus<double>(), _1, avg);
	transform(numbers, numbers.begin(), addAvg);
	*/
	/*transform(numbers, numbers.begin(), bind(plus<double>(), _1, avg));*/

	/*transform(numbers.begin(), numbers.end(), numbers.begin(), bind(plus<double>(), _1, avg));*/
	/*
	transform(numbers.begin(), numbers.end(), numbers.begin(), [&avg](double current){
		return current + avg;
	});
	*/
	/*
	for (auto &number : numbers)
	{
		number += avg;
	}*/
}