#include <iostream>
#include <string>
#include <boost/algorithm/searching/knuth_morris_pratt.hpp>
#include <boost/algorithm/searching/boyer_moore.hpp>
#include <boost/algorithm/searching/boyer_moore_horspool.hpp>
#include <boost/format.hpp>

using namespace std;
using namespace boost;
using namespace boost::algorithm;

// See http://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
void TestKnuthMorrisPratt(const string & text, const string & pattern)
{
	cout << format("Searching for occurrences of '%1%' in '%2%' using Knuth-Morris-Pratt algorithm") % pattern % text << endl;

	auto searchForPattern = make_knuth_morris_pratt(pattern);

	auto pos = text.cbegin();
	while ((pos = searchForPattern(pos, text.cend())) != text.cend())
	{
		cout << "The pattern '" << pattern << "' has been found at position " << (pos - text.cbegin()) << endl;
		pos += pattern.length();
	}

	cout << endl;
}

// http://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string_search_algorithm
void TestBoyerMoore(const string & text, const string & pattern)
{
	cout << format("Searching for occurrences of '%1%' in '%2%' using Boyer-Moore algorithm") % pattern % text << endl;

	auto searchForPattern = make_boyer_moore(pattern);

	auto pos = text.cbegin();
	while ((pos = searchForPattern(pos, text.cend())) != text.cend())
	{
		cout << "The pattern '" << pattern << "' has been found at position " << (pos - text.cbegin()) << endl;
		pos += pattern.length();
	}

	cout << endl;
}

// http://en.wikipedia.org/wiki/Boyer%E2%80%93Moore%E2%80%93Horspool_algorithm
void TestBoyerMooreHorspool(const string & text, const string & pattern)
{
	cout << format("Searching for occurrences of '%1%' in '%2%' using Boyer-Moore-Horspool algorithm") % pattern % text << endl;

	auto searchForPattern = make_boyer_moore_horspool(pattern);

	auto pos = text.cbegin();
	while ((pos = searchForPattern(pos, text.cend())) != text.cend())
	{
		cout << "The pattern '" << pattern << "' has been found at position " << (pos - text.cbegin()) << endl;
		pos += pattern.length();
	}

	cout << endl;
}

void main()
{
	const string text = "Hello, this is a text.";
	const string pattern = "is";

	TestKnuthMorrisPratt(text, pattern);
	TestBoyerMoore(text, pattern);
	TestBoyerMooreHorspool(text, pattern);
}
