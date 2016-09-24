#include <string>
#include <sstream>
#include <iostream>
#include <functional> // Необходим для std::function

using namespace std;


using FindStringCallback = function<void(int lineIndex, const string& line, size_t foundPos)>;
// using позволяет сделать то же, что и typedef, но даже больше.
//typedef function<void(int lineIndex, const string& line, size_t foundPos)> FindStringCallback;

bool FindStingInStream(istream & haystack, 
	const string& needle, 
	const FindStringCallback & callback)
{
	string line;
	for (int lineIndex = 1; getline(haystack, line); ++lineIndex)
	{
		auto pos = line.find(needle);
		if (pos != string::npos)
		{
			// Передаем в функцию обратного вызова информацию о первом найденном вхождении подстроки
			callback(lineIndex, line, pos);
		}
	}
	return true;
}

int main()
{
	string hayStack = R"(Hello,
this is a haystack with a needle.
Some lines of this haystack contain needle,
while some other lines does not.
Let's find all needles in
this haystack.
)";
	istringstream strm(hayStack);
	if (!FindStingInStream(strm, 
			"needle", 
			[](int lineIndex, const string& /*line*/, size_t /*foundPos*/) {
				cout << lineIndex << endl;
			}))
	{
		cout << "No string found" << endl;
	}
}