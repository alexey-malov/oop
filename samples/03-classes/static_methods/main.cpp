#include <chrono>
#include <string>

using std::chrono::milliseconds;
using namespace std::literals;
using namespace std;

class TimeRange
{
public:
	static TimeRange FromStartAndDuration(milliseconds start, milliseconds duration)
	{
		return { start, start + duration };
	}

	static TimeRange FromStartAndEnd(milliseconds start, milliseconds end)
	{
		return { start, end };
	}

	milliseconds GetStart() const { return m_start; }
	milliseconds GetEnd() const { return m_end; }
	milliseconds GetDuration() const { return m_end - m_start; }

private:
	TimeRange(milliseconds start, milliseconds end)
		: m_start(start)
		, m_end(end)
	{
	}
	milliseconds m_start;
	milliseconds m_end;
};

enum class Schema
{
	HTTP, HTTPS, FTP,
};

class URL
{
public:
	URL(string url)
	{
		size_t pos = 0;
		m_schema = ParseSchema(url, pos);
		m_domain = ParseDomain(url, pos);
		m_document = ParseDocument(url, pos);
	}

private:
	static Schema ParseSchema(const string& url, size_t& pos);
	static string ParseDomain(const string& url, size_t& pos);
	static string ParseDocument(const string& url, size_t& pos);
	Schema m_schema;
	string m_domain;
	string m_document;
};

Schema URL::ParseSchema(const string& url, size_t& pos)
{
}

std::string URL::ParseDomain(const string& domain, size_t& pos)
{
}

std::string URL::ParseDocument(const string& url, size_t& pos)
{
}

int main()
{
	auto tr1 = TimeRange::FromStartAndDuration(10s, 5s);
	auto tr2 = TimeRange::FromStartAndEnd(10s, 15s);
}
