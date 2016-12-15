#include <vector>
#include <iostream>
#include <string>
#include <iterator>
#include <functional>
#include <utility>

using namespace std;

/*
int AccumulateVector(vector<int> const& v)
{
	int sum = 0;
	for (auto & val : v)
	{
		sum += val;
	}
	return sum;
}

string AccumulateVector(vector<string> const& v)
{
	string sum;
	for (auto & val : v)
	{
		sum += val;
	}
	return sum;
}*/

template <typename T>
T AccumulateVector(vector<T> const& v)
{
	T sum {};
	for (auto & val : v)
	{
		sum += val;
	}
	return sum;
}

template <typename T>
T FindProduct(vector<T> const& v)
{
	T sum = 1;
	for (auto & val : v)
	{
		sum *= val;
	}
	return sum;
}

template <typename T, typename Op>
T Reduce(vector<T> const& v, Op && op, T init)
{
	for (auto & val : v)
	{
		init = op(init, val);
	}
	return init;
}

int main()
{
	vector<int> v = { 10, 20, 5 };

	int r = AccumulateVector(v);// r = 35
	cout << r << endl;

	vector<string> vs = { "A", "B", "C" };
	string rs = AccumulateVector(vs);// rs = "ABC"
	cout << rs << endl;

	r = FindProduct(v);// r = 1000
	cout << r << endl;

	r = Reduce(v, std::multiplies<int>(), 1);
	cout << r << endl;

	rs = Reduce(vs, plus<string>(), string());
	cout << rs << endl;

	auto SelectMin = [](const auto & l, const auto & r){
		return l < r ? l : r;
	};

	rs = Reduce(vs, SelectMin, vs.front());
	cout << rs << endl;
}
