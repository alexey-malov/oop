// Transformer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <cassert>

using namespace std;


vector<int> Crypt(const vector<int> & data, const function<int(int)> & transformer)
{
	vector<int> output;
	transform(data.begin(), data.end(), back_inserter(output), transformer);
	return output;
}

void Crypt(basic_istream<char> & input, basic_ostream<char> & output, const function<int(int)> & transformer)
{
	transform(
		istream_iterator<int>(input), istream_iterator<int>(),  // input range
		ostream_iterator<int>(output, ", "), // output iterator
		transformer  // transformation function
		);
}

int Encode(int x)
{
	return x + 1;
}

int Decode(int x)
{
	return x - 1;
}

int main()
{
	vector<int> data = {11, 21, 31, 41};

	string mode = "decrypt";
	auto fn =
		(mode == "crypt") ? &Encode :
		(mode == "decrypt") ? &Decode : throw logic_error("oops");

	auto output = Crypt(data, fn);
	copy(output.begin(), output.end(), ostream_iterator<int>(cout, ", "));
	cout << endl;

	cout << "----------------" << endl;

	{
		istringstream input("10 20 30 40");
		Crypt(input, cout, &Encode);
		cout << endl;
	}

	{
		istringstream input("11 21 31 41");
		Crypt(input, cout, &Decode);
		cout << endl;
	}

	//ofstream outputFile("output.txt");
	//Crypt(cin, outputFile, Encode);

	vector<int> cryptKey = {1, 2, 3, 4};
	size_t pos = 0;
	Crypt(cin, cout, [&](int x){
		assert(!cryptKey.empty());

		int y = x * cryptKey[pos++];
		pos %= cryptKey.size();
		return y;
	});
	cout << endl;

	/*
	Вышеописанный код (с lambda-функцией) аналогичен следующему:
	class Transformer
	{
		vector<int> & cryptKey;
		size_t pos = 0;
	public:
		Transformer(vector<int> & key)
			:cryptKey(key)
		{
		}
		int operator()(int x)
		{
			assert(!cryptKey.empty());

			int y = x * cryptKey[pos++];
			pos %= cryptKey.size();
			return y;
		}
	};
	Crypt(cin, cout, Transformer(cryptKey));
	*/

	return 0;
}

