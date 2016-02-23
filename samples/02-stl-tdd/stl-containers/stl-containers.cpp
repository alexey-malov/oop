// stl-containers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>

#define BOOST_RESULT_OF_USE_DECLTYPE 1
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using boost::adaptors::filtered;
using boost::adaptors::reversed;
using boost::adaptors::transformed;
using boost::to_upper_copy;
using boost::make_iterator_range;

string ToUpper(const string& s)
{
	return to_upper_copy(s);
}

void main()
{
	list<string> names = { "Ivan", "Alexander", "Sergey", "Vladimir", "Anatoly", "Alexey", };
	{
		for (list<string>::const_iterator it = names.begin(); it != names.end(); ++it)
		{
			cout << *it << ", ";
		}
		cout << endl;

		for (auto it = names.begin(); it != names.end(); ++it)
		{
			cout << *it << ", ";
		}
		cout << endl;

		for (const auto & name : names)
		{
			cout << name << ", ";
		}
		cout << endl;

		copy(names.begin(), names.end(), ostream_iterator<string>(cout, ", "));
		cout << endl;

		boost::copy(names, ostream_iterator<string>(cout, ", "));
		cout << endl;
	}

	auto startsWithA = [](const string& name){
		return name.substr(0, 1) == "A";
	};


	cout << "Print only names starting with 'A':\n";
	{
		for (const auto & name : names)
		{
			if (name.substr(0, 1) == "A")
			{
				cout << name << ", ";
			}
		}
		cout << endl;

		boost::copy(names | filtered(startsWithA), ostream_iterator<string>(cout, ", "));
		cout << endl;
	}

	cout << "Print only names starting with 'A' in reversed order:\n";
	{
		for (auto it = names.crbegin(); it != names.crend(); ++it)
		{
			if (it->substr(0, 1) == "A")
			{
				cout << *it << ", ";
			}
		}
		cout << endl;

		boost::copy(names | filtered(startsWithA) | reversed, 
			ostream_iterator<string>(cout, ", "));
		cout << endl;
	}

	cout << "Print only names starting with 'A' in reversed order using upper letters:\n";
	{
		for (auto it = names.crbegin(); it != names.crend(); ++it)
		{
			if (it->substr(0, 1) == "A")
			{
				cout << to_upper_copy(*it) << ", ";
			}
		}
		cout << endl;	

		boost::copy(names 
			| filtered(startsWithA) 
			| reversed 
			| transformed(ToUpper),
			ostream_iterator<string>(cout, ", "));
		cout << endl;
	}

	{
		auto sortedNames(names);
		sortedNames.sort();
		boost::copy(sortedNames, ostream_iterator<string>(cout, ", "));
		cout << endl;

		sortedNames.sort(std::greater<string>());
		boost::copy(sortedNames, ostream_iterator<string>(cout, ", "));
		cout << endl;
	}

	{
		vector<string> namesVector = {"Peter", "Ivan", "John"};

		sort(namesVector.begin(), namesVector.end());
		list<string> namesList(namesVector.begin(), namesVector.end());
		copy(namesVector.begin(), namesVector.end(), front_inserter(namesList));
		boost::copy(namesList, ostream_iterator<string>(cout, ", "));
		cout << endl;
	}

	{
		istringstream strm("10 20 30 42");
		copy(istream_iterator<int>(strm), istream_iterator<int>(), ostream_iterator<int>(cout, ", "));
		cout << endl;
		strm.clear(ios_base::eofbit);
		strm >> noskipws;
		strm.seekg(0, istringstream::beg);
		copy(istream_iterator<char>(strm), istream_iterator<char>(), ostream_iterator<char>(cout, ", "));
		cout << endl;

		strm.clear(ios_base::eofbit);
		strm.seekg(0, istringstream::beg);
		char ch;
		while (strm >> ch)
		{
			cout << "'" << ch << "', ";
		}
		cout << endl;

		strm.clear(ios_base::eofbit);
		strm.seekg(0, istringstream::beg);
		copy(make_iterator_range(istream_iterator<char>(strm), istream_iterator<char>())
			| transformed([](char ch){ return string("'") + ch + "'"; }),
			ostream_iterator<string>(cout, ", "));
		cout << endl;
	}
}

