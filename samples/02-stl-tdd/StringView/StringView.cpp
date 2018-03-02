// StringView.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

void StringViewCreation()
{
	const char arr[] = { 'H', 'e', 'l', 'l', 'o' };
	string_view v(arr, 5);
	assert(v.length() == 5);
	assert(v.data() == &arr[0]); // view uses arr's data

	string s("Hello");
	string_view sv = s;
	assert(sv.data() == s.data());
	assert(sv.length() == s.length());

	sv = string_view(s.data(), 4);
	assert(sv.length() == 4);
}

void StringViewExample()
{
	auto url = "http://en.cppreference.com/w/cpp/string/basic_string_view"s;

	string_view scheme(&url[0], 4);
	assert(scheme == "http");

	string_view domain(&url[7], 19);
	assert(domain == "en.cppreference.com");
}

int main()
{
	StringViewCreation();
	StringViewExample();
	return 0;
}

