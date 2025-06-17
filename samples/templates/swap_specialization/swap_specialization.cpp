// swap_specialization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <map>
#include <type_traits>
#include <vector>

struct Logger
{
	Logger() noexcept { std::cout << "DefaultCtor\n"; };
	Logger(const Logger&) noexcept { std::cout << "Copy Ctor\n"; }
	Logger& operator=(const Logger&) noexcept
	{
		std::cout << "Copy assignment\n";
		return *this;
	}
	Logger(Logger&&) noexcept { 
		std::cout << "Move Ctor\n";
	}
	Logger& operator=(Logger&&) noexcept
	{
		std::cout << "Move assignment\n";
		return *this;
	}
	~Logger() { std::cout << "Destructor\n"; }
};

class HeavyObj
{
public:
	bool operator<(const HeavyObj& rhs) const
	{
		return m_data < rhs.m_data;
	}

	void swap(HeavyObj& other) noexcept
	{
		std::cout << "Swap\n";
		if (this == &other)
			m_data.swap(other.m_data);
	}

private:
	Logger logger;
	std::map<int, int> m_data;
};

static_assert(std::is_nothrow_move_assignable_v<HeavyObj>);
static_assert(!std::is_nothrow_move_constructible_v<HeavyObj>);
static_assert(std::is_nothrow_swappable_v<std::map<int, int>>);


#if 0
static_assert(!std::is_nothrow_swappable_v<HeavyObj>);

#else


void swap(HeavyObj& lhs, HeavyObj& rhs) noexcept
{
	lhs.swap(rhs);
}


// А вот теперь HeavyObj будет использовать свой swap
static_assert(std::is_nothrow_swappable_v<HeavyObj>);

#endif

int main()
{
	std::vector<HeavyObj> vec(5);
	std::sort(vec.begin(), vec.end());
}
