#pragma once
#include <compare>

namespace util
{

/**
 * Вспомогательный шаблонный класс "Маркированный тип".
 * С его помощью можно описать строгий тип на основе другого типа.
 * Пример:
 *
 *  struct AddressTag{}; // метка типа для строки, хранящей адрес
 *  using Address = util::Tagged<std::string, AddressTag>;
 *
 *  struct NameTag{}; // метка типа для строки, хранящей имя
 *  using Name = util::Tagged<std::string, NameTag>;
 *
 *  struct Person {
 *      Name name;
 *      Address address;
 *  };
 *
 *  Name name{"Harry Potter"s};
 *  Address address{"4 Privet Drive, Little Whinging, Surrey, England"s};
 *
 * Person p1{name, address}; // OK
 * Person p2{address, name}; // Ошибка, Address и Name - разные типы
 */
template <typename Value, typename Tag>
class Tagged
{
public:
	using ValueType = Value;
	using TagType = Tag;

	explicit Tagged(Value&& v) noexcept(std::is_nothrow_move_constructible_v<Value>)
		: value_(std::move(v))
	{
	}
	explicit Tagged(const Value& v) noexcept(std::is_nothrow_copy_constructible_v<Value>)
		: value_(v)
	{
	}

	const Value& operator*() const noexcept
	{
		return value_;
	}

	Value& operator*() noexcept
	{
		return value_;
	}

	const ValueType* operator->() const noexcept { return value_; }
	ValueType* operator->() noexcept { return value_; }

	// Так в C++20 можно объявить оператор сравнения Tagged-типов
	// Будет просто вызван соответствующий оператор для поля value_
	friend auto operator<=>(const Tagged&, const Tagged&) = default;

private:
	Value value_;
};

#if 1
// Хешер для Tagged-типа, чтобы Tagged-объекты можно было хранить в unordered-контейнерах
template <typename TaggedValue>
struct TaggedHasher
{
	size_t operator()(const TaggedValue& value) const
	{
		// Возвращает хеш значения, хранящегося внутри value
		return std::hash<typename TaggedValue::ValueType>{}(*value);
	}
};
#endif

} // namespace util
