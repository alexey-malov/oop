#include <cassert>
#include <functional> // Необходим для std::function
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

using FindStringCallback = function<void(int lineIndex, const string& line, size_t foundPos)>;

bool FindStingInStream(
	istream& haystack,
	const string& needle,
	const FindStringCallback& callback = FindStringCallback())
{
	string line;
	bool found = false;
	for (int lineIndex = 1; getline(haystack, line); ++lineIndex)
	{
		auto pos = line.find(needle);
		if (pos != string::npos)
		{
			found = true;
			// Передаем в функцию обратного вызова информацию о
			// первом найденном вхождении подстроки
			if (callback)
			{
				callback(lineIndex, line, pos);
			}
		}
	}
	return found;
}

void PrintFoundLineIndex(int lineIndex, const string& /*line*/, size_t /*foundPos*/)
{
	cout << lineIndex << endl;
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

	if (!FindStingInStream(strm, "needle", PrintFoundLineIndex))
	{
		cout << "No string found" << endl;
	}

	strm.clear(); // сбросили флаг окончания потока
	strm.seekg(0, ios_base::beg); // перемотали в начало

	// можно не передавать callback и довольствоваться лишь информацией о наличии/отсутствии вхождений
	assert(FindStingInStream(strm, "needle"));
}
