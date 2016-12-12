// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma warning(push)
#pragma warning(disable:4996)
#include <memory>
#pragma warning(pop)
#include <functional>
#include <boost/signals2.hpp>
#include <iostream>
#include <string>
#include <boost/optional.hpp>
#include <deque>

namespace detail {
	template <class F, class Tuple, std::size_t... I>
	constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
	{
		(void)&t;
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

	template <typename ...Args>
	void operator()(Args && ...args)
	{
		(*m_impl)(std::forward<Args>(args)...);
	}

	bool IsEmpty()const
	{
		return m_impl->IsEmpty();
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
		template <typename ...Args>
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
		bool IsEmpty()const
		{
			return !m_args.is_initialized();
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

auto DebounceFirst(const std::function<void()> & fn)
{
	return Debouncer<false>(fn);
}

template <typename Debouncer>
struct ScheduledDebouncer
{
	using Task = std::function<void()>;
	using Scheduler = std::function<void(const Task&)>;
	ScheduledDebouncer(const Debouncer &debouncer, const Scheduler& scheduler)
		: m_scheduler(scheduler)
		, m_debouncer(debouncer)
	{
	}

	template <typename ...Args>
	void operator()(Args && ...args)
	{
		bool needSchedule = m_debouncer.IsEmpty();
		m_debouncer(std::forward<Args>(args)...);
		if (needSchedule)
		{
			auto debouncer = m_debouncer;
			m_scheduler([debouncer]() mutable{
				debouncer.Dispatch();
			});
		}
	}
private:
	Scheduler m_scheduler;
	Debouncer m_debouncer;
};

template <typename Debouncer, typename Scheduler>
auto ScheduledDebounce(const Debouncer & debouncer, Scheduler && scheduler)
{
	return ScheduledDebouncer<Debouncer>(debouncer, std::forward<Scheduler>(scheduler));
}


int main()
{
	using namespace std;
	using MouseMoveSignal = boost::signals2::signal<void(int x, int y)>;
	using ScopedConnection = boost::signals2::scoped_connection;

	MouseMoveSignal signal;

	auto mousePosPrinter = [](int x, int y) {
		cout << "x: " << x << ", y: " << y << endl;
	};

	{
		ScopedConnection con = signal.connect(mousePosPrinter);
		signal(1, 2);
		signal(3, 4);
		signal(5, 6);
		cout << "---------" << endl;
	}

	auto lastMousePosPrinter = DebounceLast<int, int>(mousePosPrinter);
	{
		ScopedConnection con = signal.connect(lastMousePosPrinter);
		signal(1, 2);
		signal(3, 4);
		signal(5, 6);
		lastMousePosPrinter.Dispatch();
		signal(7, 8);
		signal(9, 10);
		signal(11, 12);
		lastMousePosPrinter.Dispatch();

		cout << "---------" << endl;
	}

	{
		deque<function<void()>> queuedCalls;
		auto scheduler = [&](auto && fn)
		{
			queuedCalls.push_back(fn);
		};

		auto processQueuedCalls = [&]()
		{
			while (!queuedCalls.empty())
			{
				queuedCalls.front()();
				queuedCalls.pop_front();
			}
		};

		auto scheduledLastMousePosPrinter = ScheduledDebounce(lastMousePosPrinter, scheduler);
		ScopedConnection con = signal.connect(scheduledLastMousePosPrinter);
		signal(1, 2);
		signal(3, 4);
		signal(5, 6);

		processQueuedCalls(); // 5, 6
		signal(7, 8);
		signal(9, 10);
		signal(11, 12);
		processQueuedCalls(); // 11, 12
	}
	return 0;
}