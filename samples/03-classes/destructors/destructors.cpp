#include <cstring>
#include <iostream>
#include <memory>

class String
{
public:
	String() noexcept
		: m_chars{ s_emptyString }
	{
	}
	String(const char* text)
		: m_size{ std::strlen(text) }
		, m_capacity{ m_size }
		, m_chars{ Allocate(m_capacity + 1) }
	{
		std::uninitialized_copy_n(text, m_size + 1, m_chars);
	}
	~String()
	{
		if (m_chars != s_emptyString)
		{
			Deallocate(m_chars);
		}
	}

private:
	static char* Allocate(size_t size)
	{
		return static_cast<char*>(operator new(size));
	}
	static void Deallocate(char* buffer) noexcept
	{
		operator delete(buffer);
	}

	inline static char* s_emptyString = { '\0' };

	size_t m_size = 0;
	size_t m_capacity = 0;
	char* m_chars;
};

int main()
{
	String hello{ "Hello, world" };
}
