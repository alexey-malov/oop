#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <string.h>
#include <type_traits>

class String
{
public:
	String(const char* str)
		: String(str, std::strlen(str))
	{
	}

	String(const char* str, size_t length)
		: m_chars(static_cast<char*>(operator new(length + 1)))
		, m_length(length)
		, m_capacity(length)
	{
		std::uninitialized_copy_n(str, length, m_chars);
		m_chars[length] = 0;
	}

	char& operator[](size_t index)
	{
		assert(index < m_length);
		return m_chars[index];
	}

	const char& operator[](size_t index) const
	{
		assert(index < m_length);
		return m_chars[index];
	}

private:
	char* m_chars = nullptr;
	size_t m_length = 0;
	size_t m_capacity = 0;
};

#ifdef __cpp_multidimensional_subscript
#define USE_MULTI_DIMENSIONAL_SUBSCRIPT
#endif

template <typename T, size_t NumRows, size_t NumColumns>
class Matrix
{
	using Row = std::array<T, NumColumns>;

public:
	Matrix()
		: m_items{}
	{
	}
	explicit Matrix(T initVal)
	{
		for (size_t r = 0; r < NumRows; ++r)
		{
			for (size_t c = 0; c < NumColumns; ++c)
			{
				m_items[r][c] = (r == c) ? initVal : T{};
			}
		}
	}

#ifdef USE_MULTI_DIMENSIONAL_SUBSCRIPT
	T& operator[](size_t row, size_t column)
	{
		assert(row < NumRows && column < NumColumns);
		return m_items[row][column];
	}

	const T& operator[](size_t row, size_t column) const
	{
		assert(row < NumRows && column < NumColumns);
		return m_items[row][column];
	}
#else
	template <bool IsConst>
	class RowProxy
	{
	public:
		using RowReference = std::conditional_t<IsConst, const Row&, Row&>;
		using Reference = std::conditional_t<IsConst, const T&, T&>;

		explicit RowProxy(RowReference items)
			: m_items(items)
		{
		}

		Reference operator[](size_t index) const
		{
			assert(index < m_items.size());
			return m_items[index];
		}

	private:
		RowReference m_items;
	};

	RowProxy<false> operator[](size_t row)
	{
		assert(row < NumRows);
		return m_items[row];
	}

	RowProxy<true> operator[](size_t row) const
	{
		assert(row < NumRows);
		return m_items[row];
	}
#endif

private:
	std::array<Row, NumRows> m_items;
};

int main()
{
	String s("hello");
	s[0] = 'H';
	assert(s[1] == 'e');

	Matrix<double, 3, 3> m;
#ifdef USE_MULTI_DIMENSIONAL_SUBSCRIPT
	m[1, 2] = 1.5;
	std::cout << m[1, 2] << "\n";
#else
	m[1][2] = 1.5;
	std::cout << m[1][2] << "\n";
#endif
}