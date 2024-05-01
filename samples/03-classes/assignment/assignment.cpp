// assignment.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <cassert>

class PostCard
{
public:
	PostCard(const std::string& text)
		: m_text{ text }
	{
		std::cout << "Post card was created: " << m_text << std::endl;
	}
	// Копирующий конструктор
	PostCard(const PostCard& other)
		: m_text{ other.m_text }
	{
		std::cout << "Post card is copied: " << m_text << std::endl;
	}

	PostCard& operator=(const PostCard& other)
	{
		std::cout << "Post card " << m_text << " is assigned value " << other.m_text << std::endl;
		m_text = other.m_text;
		return *this;
	}

	~PostCard() { std::cout << "Post card was destroyed: " << m_text << std::endl; }

	const std::string& GetText() const { return m_text; }

	void SetText(const std::string& text) { m_text = text; }

private:
	std::string m_text;
};

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
	String(const String& other)
		: m_size{ other.m_size }
		, m_capacity{ other.m_capacity }
		, m_chars{ Allocate(m_capacity + 1) }
	{
		std::uninitialized_copy_n(other.m_chars, m_size + 1, m_chars);
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

struct Envelope
{
	PostCard postCard;
};

int main()
{
	Envelope env1{ .postCard = "Hello" };
	Envelope env2{ .postCard = "world" };
	env1 = env2;
	std::cout << env1.postCard.GetText() << std::endl;
}
