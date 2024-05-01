// delegating_constructor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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
	String(const char* text, size_t size)
		: m_size{ size }
		, m_capacity{ m_size }
		, m_chars{ Allocate(m_capacity + 1) }
	{
		auto end = std::uninitialized_copy_n(text, m_size, m_chars);
		*end = '\0';
	}
	// Следующие конструкторы делегируют работу конструктору String(const char*, size_t size)
	String(const char* text)
		: String(text, std::strlen(text))
	{
	}
	String(const String& other)
		: String(other.m_chars, other.m_size)
	{
	}

	String& operator=(const String& other)
	{
		if (this != &other)
		{
			if (m_capacity >= other.m_size && m_chars != s_emptyString)
			{
				std::destroy_n(m_chars, m_size + 1);
				std::uninitialized_copy_n(other.m_chars, m_size + 1, m_chars);
				m_size = other.m_size;
			}
			else
			{
				// Используем идиому copy-and-swap
				String copy{ other };
				std::swap(m_size, copy.m_size);
				std::swap(m_capacity, copy.m_capacity);
				std::swap(m_chars, copy.m_chars);
			}
		}
		return *this;
	}

	~String()
	{
		if (m_chars != s_emptyString)
		{
			std::destroy_n(m_chars, m_size + 1);
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

	inline static char s_emptyString[] = { '\0' };

	size_t m_size = 0;
	size_t m_capacity = 0;
	char* m_chars;
};

int main()
{
	std::cout << "Hello World!\n";
}
