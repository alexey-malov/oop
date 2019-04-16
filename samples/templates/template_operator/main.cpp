#include <iostream>
#include <sstream>

class CCounter
{
public:
	explicit CCounter(unsigned maxValue, unsigned counter = 0)
		: m_maxValue(maxValue)
		, m_counter(counter)
	{
	}
	unsigned GetValue() const { return m_counter; }
	unsigned GetMaxValue() const { return m_maxValue; }

	CCounter& operator++()
	{
		++m_counter;
		if (m_counter >= m_maxValue)
		{
			m_counter = 0;
		}
		return *this;
	}
	CCounter const operator++(int) // постфиксная форма инкремента
	{
		// создаем копию, выполняем предынкремент и возвращаем копию
		CCounter tmpCopy(*this);
		++*this;
		return tmpCopy;
	}

private:
	unsigned m_maxValue, m_counter;
};

template <class T>
std::basic_ostream<T>& operator<<(
	std::basic_ostream<T>& stream, CCounter const& counter)
{
	stream.put('[');
	stream << counter.GetValue();
	stream.put('/');
	stream << counter.GetMaxValue();
	stream.put(']');
	return stream;
}

int main()
{
	std::ostringstream os;
	std::wostringstream wos;

	CCounter cnt(10);

	os << cnt;
	++cnt;
	wos << cnt;

	std::cout << os.str() << "\n";
	std::wcout << wos.str() << L"\n";

	return 0;
}
