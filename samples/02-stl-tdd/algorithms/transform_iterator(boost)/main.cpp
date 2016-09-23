#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <functional>

using namespace std;
using namespace boost;

string IntToStringWithinSquareBraces(int value)
{
	return "[" + to_string(value) + "]";
}

// A function object that converts ints to strings in a some way
using Fn = function < string(int) > ;

// Source iterator type
using SrcIt = vector<int>::const_iterator;

// Iterator that transforms values provided by SrcIt by applying Fn to them
using It = transform_iterator < Fn, SrcIt > ;


void IntsToStrings()
{
	cout << "Constructing vector<string> from vector<int> using transform_iterator" << endl;

	vector<int> ints = { 1, 2, -3, 42, 13 };

	// Construct a vector of strings by transforming values retrieved
	vector<string> strings(It(ints.begin(), IntToStringWithinSquareBraces), It(ints.end(), IntToStringWithinSquareBraces));

	cout << "vector<string> items:" << endl;

	copy(strings, ostream_iterator<string>(cout, ", "));
	cout << endl;
}

void CopyIntsToStdoutWithTransformation()
{
	cout << "Copying decorated ints to stdout using transform_iterator" << endl;

	vector<int> ints = { 1, 2, -3, 42, 13 };

	cout << "Decorated items:" << endl;

	copy(It(ints.begin(), IntToStringWithinSquareBraces),	// start
		It(ints.end(), IntToStringWithinSquareBraces),		// end
		ostream_iterator<string>(cout, ", "));					// where
	cout << endl;
}

void main()
{
	IntsToStrings();
	cout << endl;
	CopyIntsToStdoutWithTransformation();
}