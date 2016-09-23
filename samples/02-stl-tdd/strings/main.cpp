#include <string>
#include <iostream>

using namespace std;

bool HasSubstring(const string& haystack, const string& needle)
{
	auto pos = haystack.find(needle, 0);
	return pos != string::npos;
}

void main()
{
	string s("Hello, world");
	cout << "Length: " << s.length() << endl;
	cout << "Size: " << s.size() << endl;
	cout << "Capacity: " << s.capacity() << endl;
	cout <<  HasSubstring(s, "mama") << endl;

	s.replace(7, 5, "PS");

	cout << s << endl;
}