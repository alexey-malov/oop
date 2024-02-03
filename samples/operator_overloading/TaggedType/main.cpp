// ood.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "tagged.h"
#include <algorithm>
#include <format>
#include <iostream>
#include <map>
#include <numbers>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

using namespace std::literals;

template <typename Value, typename Tag>
std::ostream& operator<<(std::ostream& out, const util::Tagged<Value, Tag>& taggedValue)
{
	// Делегируем вывод значения вложенному типу.
	return out << *taggedValue;
}

// Пример 1
//
// Эта структура-маркер нужна, чтобы иметь некоторый уникальный тип данных.
struct UserIdTag
{
};
using UserId = util::Tagged<std::string, UserIdTag>;

UserId operator""_UserId(const char* s, size_t len)
{
	return UserId{ { s, len } };
}

struct User
{
	User(UserId id, std::string name)
		: id{ std::move(id) }
		, name{ std::move(name) }
	{
	}

	UserId id;
	std::string name;
};

std::ostream& operator<<(std::ostream& out, const User& user)
{
	return out << "{ id: \""sv << user.id << "\", name: \""sv << user.name << "\" }"sv;
}

// Пример 2
//
// Пользуемся тем, что лямбда-выражение создаёт новый уникальный тип данных
// и объявляем тип BookId без объявления структуры-маркера.
using BookId = util::Tagged<std::string, decltype([] {})>;

struct Book
{
	BookId id;
	std::string title;
	std::string author;
};

std::ostream& operator<<(std::ostream& out, const Book& book)
{
	return out << std::format(R"({{ id: "{}", title: "{}", author: "{}" }})",
			   *book.id, book.title, book.author);
#if 0 // Можно и так вывести
	return out << "{ id: \""sv << book.id << "\", title: \""sv << book.title
			   << "\", author: \""sv << book.author << "\"}"sv;
#endif
}

// Валюта (в качестве единиц используется int64_t)
using CurrencyValue = int64_t;
template <typename Tag>
using Currency = util::Tagged<CurrencyValue, Tag>;

// Бинарные + и -
template <typename Tag>
Currency<Tag> operator+(Currency<Tag> lhs, Currency<Tag> rhs)
{
	return Currency<Tag>{ *lhs + *rhs };
}
template <typename Tag>
Currency<Tag> operator-(Currency<Tag> lhs, Currency<Tag> rhs)
{
	return Currency<Tag>{ *lhs - *rhs };
}

// Унарные + и -
template <typename Tag>
Currency<Tag> operator-(Currency<Tag> arg)
{
	return Currency<Tag>{ -*arg };
}
template <typename Tag>
Currency<Tag> operator+(Currency<Tag> arg)
{
	return arg;
}

// Объявляем валюты
using Roubles = Currency<decltype([] {})>;
using Dollars = Currency<decltype([] {})>;
using Euros = Currency<decltype([] {})>;
// Аналогично можно объявить и другие валюты

std::ostream& operator<<(std::ostream& out, Roubles r) { return out << *r << "RUR"sv; }
std::ostream& operator<<(std::ostream& out, Dollars d) { return out << *d << "USD"sv; }
std::ostream& operator<<(std::ostream& out, Euros e) { return out << *e << "EUR"sv; }

// Создаёт валюту нужного типа + проверяет диапазон
template <typename CurrencyType>
CurrencyType MakeCurrency(unsigned long long amount)
{
	auto signedAmount = static_cast<typename CurrencyType::ValueType>(amount);
	if (!std::cmp_equal(signedAmount, amount))
	{
		throw std::out_of_range("Value is out of range");
	}
	return CurrencyType{ signedAmount };
}

Roubles operator""_rur(unsigned long long n)
{
	return MakeCurrency<Roubles>(n);
}
Dollars operator""_usd(std::make_unsigned_t<Dollars::ValueType> n)
{
	return MakeCurrency<Dollars>(n);
}
Euros operator""_eur(std::make_unsigned_t<Euros::ValueType> n)
{
	return MakeCurrency<Euros>(n);
}

// В качестве денег можем использовать одну из нескольких валют.
using Money = std::variant<Roubles, Dollars, Euros>;

std::ostream& operator<<(std::ostream& out, Money m)
{
	auto printer = [&out](auto currency) -> std::ostream& {
		return out << currency;
	};
	return std::visit(printer, m);
}

struct AddSameTypes
{
	template <typename T>
	Money operator()(T lhs, T rhs) const
	{
		return lhs + rhs;
	}

	template <typename T, typename U>
	Money operator()(T lhs, U rhs) const
	{
		std::ostringstream err;
		err << "Can't add "sv << lhs << " and " << rhs;
		throw std::invalid_argument(err.str());
	}
};

template <typename R, typename T>
R AddIfSameTypes(T lhs, T rhs) { return lhs + rhs; }

template <typename R, typename T, typename U>
R AddIfSameTypes(T lhs, U rhs)
{
	std::ostringstream err;
	err << "Can't add "sv << lhs << " and " << rhs;
	throw std::invalid_argument(err.str());
}

Money operator+(Money lhs, Money rhs)
{
	return std::visit(
		[](auto lhs, auto rhs) { return AddIfSameTypes<Money>(lhs, rhs); },
		lhs, rhs);
}

// Пример 3
// Используем охватывающий класс или структуру в качестве маркера типа
struct Order
{
	// В качестве значения используется uint64_t
	using Id = util::Tagged<uint64_t, Order>;

	Id id;
	Money cost;
};

std::ostream& operator<<(std::ostream& out, Order order)
{
	return out << "{ id: "sv << order.id << ", cost: "sv << order.cost << " }"sv;
};

void Problem()
{
	int roubles = 10;
	int dollars = 20;
	std::cout << roubles << "RUR + "sv << dollars << "USD = "sv
			  << (roubles + dollars) << "???"sv << std::endl;

	struct User
	{
		std::string id;
		std::string name;
	};
	struct Book
	{
		std::string id;
		std::string name;
	};

	User user;
	Book book;

	user.id = book.id; // Oops
}

long double operator""_deg_to_rad(long double deg)
{
	return deg * std::numbers::pi_v<long double> / 180;
}

struct Cat
{
	std::string name;
};

Cat operator""_Cat(const char* str, std::size_t length)
{
	return Cat{ .name{ str, length } };
}

// Вызывает функцию заданное количество раз
class Repeater
{
public:
	explicit Repeater(unsigned long long repeatCount)
		: m_repeatCount{ repeatCount }
	{
	}

	template <typename Fn>
	void Do(Fn fn) const
	{
		for (unsigned long long i = 0; i < m_repeatCount; ++i)
		{
			fn();
		}
	}

private:
	unsigned long long m_repeatCount;
};

Repeater operator""_Times(unsigned long long repeatCount)
{
	return Repeater{ repeatCount };
}

namespace std
{
template <typename Value, typename Tag>
struct hash<::util::Tagged<Value, Tag>>
{
	[[nodiscard]] size_t operator()(const ::util::Tagged<Value, Tag>& value) const
	{
		return ::util::TaggedHasher<Value, Tag>{}(value);
	}
};
} // namespace std

int main()
{
	Problem();

	User user1{ UserId{ "user-1"s }, "Ivan"s };
	// Не скомпилируется: user1.id = "Some userId"s;
	std::cout << user1 << std::endl;

	std::vector<Book> books = {
		{ .id = BookId{ "book-1"s }, .title = "Moby Dick"s, .author = "Herman Melville"s },
		{ .id = BookId{ "book-2"s }, .title = "A Christmas Carol"s, .author = "Charles Dickens"s },
	};
	if (auto it = std::ranges::find(books, BookId{ "book-2"s }, &Book::id); it != books.end())
	{
		std::cout << *it << std::endl;
	}

	Roubles r1{ 10 };
	Roubles r2{ 20 };
	std::cout << r1 << " + "sv << r2 << " = "sv << (r1 + r2) << std::endl;

	Dollars d1{ 8 };
	Dollars d2{ 5 };
	std::cout << d1 << " + "sv << d2 << " = "sv << (d1 + d2) << std::endl;

	// binary '=': no operator found which takes a right-hand operand of type 'Roubles'
	// (or there is no acceptable conversion)
	// d1 = r1;

	Money m1 = Dollars{ 15 };
	Money m2 = Dollars{ 5 };
	std::cout << m1 << " + "sv << m2 << " = "sv << (m1 + m2) << std::endl;

	try
	{
		// Этот код компилируется, хотя операция сложения рублей и долларов не определена.
		// Работает за счёт неявного преобразования Roubles и Dollars к типу Money.
		//
		// Money{ Roubles{50} } + Money{ Dollars{70} }
		std::cout << (Roubles{ 50 } + Dollars{ 70 }) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << 180.0_deg_to_rad << std::endl; // Выведет 3.14159

	// Классические способы создать котика
	Cat cat0{ "Leopold"s };
	auto cat1 = Cat{ "Leopold"s };
	auto cat2 = Cat{ .name = "Leopold"s };
	auto cat3 = Cat{ .name = { "Leopold", 7 } };

	auto cat4 = "Leopold"_Cat; // Создаём котика при помощи суффикса _Cat.
	static_assert(std::is_same_v<decltype(cat4), Cat>); // Это точно котик!

	// Можно у созданного объекта сразу обращаться к полям и методам
	std::cout << "Basil"_Cat.name << std::endl; // Напечатает строку Basil

	// Напечатает 5 раз строку Hello
	Repeater(5).Do([] { std::cout << "Hello" << std::endl; });

	// Тоже напечатает 5 раз строку Hello
	5_Times.Do([] { std::cout << "Hello" << std::endl; });

	Order order1{
		.id = Order::Id{ 42 },
		.cost = 20_eur + 70_eur
	};
	Order order2{
		.id = Order::Id{ 42 },
		.cost = 500_rur + 17_rur
	};

	std::map<UserId, Money> salaries;

	salaries.emplace(UserId{ "user-0" }, Dollars{ 100 });

	salaries.emplace("user-2"_UserId, 100_usd);

	{
		// Указали хешер явно
		std::unordered_map<UserId, Money, util::TaggedHasher<UserId>> salariesUMap;
		salaries.emplace("user-2"_UserId, 200'000_usd);
	}

	{
		// Так работает, так как выше определили специализацию шаблона std::hash для Tagged
		std::unordered_map<UserId, Money> salariesUMap;
		salaries.emplace("user-2"_UserId, 200'000_usd);
	}
}
