#include <cassert>
#include <iostream>
#include <string>

using namespace std;

bool HasSubstring(const string& haystack, const string& needle)
{
	auto pos = haystack.find(needle, 0);
	return pos != string::npos;
}

void Test1()
{
	string s("Hello, world");
	cout << "Length: " << s.length() << endl;
	cout << "Size: " << s.size() << endl;
	cout << "Capacity: " << s.capacity() << endl;
	cout << HasSubstring(s, "mama") << endl;

	s.replace(7, 5, "PS");

	cout << s << endl;
}

void StringConstruction()
{
	string emptyString;
	string hello = "Hello";
	auto goodbye = "Goodbye"s;

	const char chars[] = { 'O', 'n', 'e' };
	// Создание строки из массива символов заданной длины
	string one(chars, std::size(chars)); // One

	string aaaa(4, 'a'); // aaaa
}

void SizeAndCapacity()
{
	auto text = "This is a very long string"s;
	assert(text.length() == 26);
	assert(text.size() == text.length());
	assert(text.capacity() >= text.length());

	auto oldCapacity = text.capacity();
	text.erase(19, 7); // erase " string"
	assert(text == "This is a very long"s);
	assert(text.capacity() == oldCapacity);
	assert(text.length() == 19);

	assert(!text.empty());
	text.clear();
	assert(text.length() == 0);
	assert(text.empty());
	assert(text.capacity() == oldCapacity);
}

void StringComparison()
{
	assert("bbb"s > "aaa"s);
	assert("xyz"s == "xyz"s);
	assert("Abc"s > "Abb"s);

	string s = "Hello";
	assert("Hello" == s);
}

void StringConcatenation()
{
	string hello("Hello");
	string world("world");

	string helloWorld = hello + " " + world;
	// "Hello world"

	string s;
	s.append(hello).append(" ").append(world);
	// "Hello world"
}

void SubstringExtraction()
{
	auto helloWorld = "Hello world"s;

	assert(helloWorld.substr(0, 5) == "Hello"s);
	assert(helloWorld.substr(6, 5) == "world"s);
	assert(helloWorld.substr(6) == "world"s);
	assert(helloWorld.substr() == "Hello world"s);

	auto s = "This is a wonderful "s;
	s.append(helloWorld, 0, 4);
	assert(s == "This is a wonderful Hell");

	auto helloWorld1 = helloWorld.substr(0, 6);
	helloWorld1.append(helloWorld, 6);
	assert(helloWorld1 == helloWorld);
}

void StringSearching()
{
	string s("Hello world");

	assert(s.find('w') == 6);
	assert(s.find('x') == string::npos);
	assert(s.find_first_of("aeiouy"s) == 1); // e

	assert(s.find("world"s) == 6);
	assert(s.find('o') == 4); // first 'o' letter
	assert(s.rfind('o') == 7); // last 'o' letter

	assert(s.find('o', 5) == 7);
}

void StringReplacement()
{
	auto s = "Hello world"s;
	s.replace(0, 5, "Goodbye"s);
	assert(s == "Goodbye world"s);

	auto s1 = "This is a cat"s;
	s1.replace(10, 3, s, 8, 5);
	assert(s1 == "This is a world");
}

int main()
{
	StringConstruction();
	SizeAndCapacity();
	StringComparison();
	StringConcatenation();
	SubstringExtraction();
	StringSearching();
	StringReplacement();
	Test1();

	return 0;
}