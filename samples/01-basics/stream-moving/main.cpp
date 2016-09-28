#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream OpenFileForReading(const string & fileName)
{
	ifstream strm(fileName);
	return move(strm); // Нельзя вернуть копию потока, но можно переместить объект потока
}

int main()
{
	if (auto strm = OpenFileForReading("Text.txt"))
	{
		string line;
		while (getline(strm, line))
		{
			cout << line << endl;
		}
	}
	else
	{
		cout << "Failed to open Text.txt" << endl;
	}
}