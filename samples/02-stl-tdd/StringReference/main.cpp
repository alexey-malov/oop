#include <boost/utility/string_ref.hpp>
#include <iostream>
#include <cassert>
#include <chrono>

using namespace std;
using boost::string_ref;

int main()
{
	const string url = "http://long.domain.name.at.google.com/long.document.path.txt";
	// Решение с использованием substr

	{
		auto t = chrono::steady_clock().now().time_since_epoch();
		for (auto i = 0; i < 10000000; ++i)
		{
			const string schemeDelimiter = "://";

			auto schemeEnd = url.find(schemeDelimiter);
			assert(schemeEnd != string::npos);
			auto scheme = url.substr(0, schemeEnd);
			assert(scheme == "http");

			auto domainStart = schemeEnd + schemeDelimiter.length();
			auto domainEnd = url.find("/", domainStart);
			assert(domainEnd != string::npos);
			auto domain = url.substr(domainStart, domainEnd - domainStart);
			assert(domain == "long.domain.name.at.google.com");

			auto document = url.substr(domainEnd);
			assert(document == "/long.document.path.txt");
		}
		t = chrono::steady_clock().now().time_since_epoch() - t;
		cout << "string operations duration " << t.count() << endl;
	}
	// аналогичный код, использующий string_ref
	{
		auto t = chrono::steady_clock().now().time_since_epoch();
		for (auto i = 0; i < 10000000; ++i)
		{
			string_ref urlRef(url); // string_ref, ссылающийся на всю строку

			const string schemeDelimiter = "://";
			auto schemeEnd = urlRef.find(schemeDelimiter);
			assert(schemeEnd != string::npos);
			auto scheme = urlRef.substr(0, schemeEnd);
			assert(scheme == "http");

			urlRef = urlRef.substr(schemeEnd + scheme.length() - 1); // отбросили схему с разделителем
			auto domainEnd = urlRef.find('/');
			assert(domainEnd != string_ref::npos);
			auto domain = urlRef.substr(0, domainEnd);
			assert(domain == "long.domain.name.at.google.com");

			auto document = urlRef.substr(domainEnd);
			assert(document == "/long.document.path.txt");
		}
		t = chrono::steady_clock().now().time_since_epoch() - t;
		cout << "string_ref operations duration " << t.count() << endl;
	}

	return 0;
}