// move_ctor_and_assignment.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

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
	String(String&& other) noexcept
		: m_size{ std::exchange(other.m_size, 0) }
		, m_capacity{ std::exchange(other.m_capacity, 0) }
		, m_chars{ std::exchange(other.m_chars, s_emptyString) }
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

	String& operator=(String&& other) noexcept
	{
		if (this != &other)
		{
			std::swap(m_size, other.m_size);
			std::swap(m_capacity, other.m_capacity);
			std::swap(m_chars, other.m_chars);
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

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
