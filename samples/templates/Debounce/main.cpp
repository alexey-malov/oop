#pragma warning(push)
#pragma warning(disable:4996)
#include <memory>
#pragma warning(pop)
#include <functional>
#include <boost/signals2.hpp>
#include <iostream>
#include <string>
#include <boost/optional.hpp>

namespace detail {
	template <class F, class Tuple, std::size_t... I>
	constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
	{
		return std::invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t))...);
		// Note: std::invoke is a C++17 feature
	}
} // namespace detail

// Вызывает f, передавая в качестве аргументов содержимое из кортежа t
// В C++17 войдет в STL как std::apply
template <class F, class Tuple>
constexpr decltype(auto) apply(F&& f, Tuple&& t)
{
	return detail::apply_impl(std::forward<F>(f), std::forward<Tuple>(t),
		std::make_index_sequence<std::tuple_size_v<std::decay_t<Tuple>>>{});
}

// Шаблонный класс Debouncer, откладывающий вызов функции до момента вызова метода Dispatch()
// В зависимости от параметра m_callLast будет выполнен либо первый, либо последний вызов
template <bool m_callLast, typename ...Args>
struct Debouncer
{
	using Fn = std::function<void(Args...)>;
	Debouncer(const Fn& fn)
		: m_impl(std::make_shared<Impl>(fn))
	{
	}

	void operator()(Args && ...args)
	{
		(*m_impl)(std::forward<Args>(args)...);
	}

	void Dispatch()
	{
		m_impl->Dispatch();
	}
private:
	struct Impl
	{
		using ArgPack = std::tuple<Args...>;
		Impl(const Fn & fn)
			: m_fn(fn)
		{
		}
		void operator()(Args && ...args)
		{
#pragma warning(push)
#pragma warning(disable:4127) // Conditional expression is constant
			if (m_callLast || !m_args)
			{
				m_args.emplace(std::forward<Args>(args)...);
			}
#pragma warning(pop)
		}
		void Dispatch()
		{
			if (m_args)
			{
				apply(m_fn, *m_args);
				m_args.reset();
			}
		}
		boost::optional<ArgPack> m_args;
		Fn m_fn;
	};
	std::shared_ptr<Impl> m_impl;
};

template <typename ...Args>
auto DebounceLast(const std::function<void(Args...)> & fn)
{
	return Debouncer<true, Args...>(fn);
}

template <typename ...Args>
auto DebounceFirst(const std::function<void(Args...)> & fn)
{
	return Debouncer<false, Args...>(fn);
}

int main()
{
	using namespace std;
	using Signal = boost::signals2::signal<void(int, string)>;

	Signal signal;
	auto slot = [](int n, const string & s) {
		cout << n << ", " << s << endl;
	};

	auto debounceFirstSlot = DebounceFirst<int, string>(slot);
	auto debounceLastSlot = DebounceLast<int, string>(slot);

	signal.connect(debounceLastSlot);
	signal.connect(debounceFirstSlot);

	signal(1, "hello");
	signal(2, "world");
	signal(3, "test");
	
	debounceFirstSlot.Dispatch(); // will print 1, hello
	debounceLastSlot.Dispatch(); // will print 3, test

	debounceFirstSlot.Dispatch(); // will not print
	debounceLastSlot.Dispatch(); // will not print

	return 0;
}