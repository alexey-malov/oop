#include <cassert>
#include <iostream>
#include <iterator>
#include <type_traits>

template <typename T>
class List
{
	struct Node
	{
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
	};

	template <bool IsConst>
	class Iterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = std::conditional_t<IsConst, const T, T>;
		using reference = std::add_lvalue_reference_t<value_type>;
		using pointer = std::add_pointer_t<value_type>;
		using difference_type = std::ptrdiff_t;
		
		Iterator() = default;

		Iterator& operator++() // Префиксный инкремент
		{
			assert(m_node != nullptr);
			m_node = m_node->next;
			return *this;
		}

		Iterator operator++(int) // Постфиксный инкремент
		{
			assert(m_node != nullptr);
			auto copy(*this); // Сохраняем прежнее значение
			++(*this); // Выполняем инкремент
			return copy; // Возвращаем прежнее значение
		}

	private:
		explicit Iterator(Node* node)
			: m_node(node)
		{
		}
		Node* m_node = nullptr;
	};

public:

	using iterator = Iterator<false>;
	using const_iterator = Iterator<true>;
};

int main()
{
	List<int> l;
	List<int>::iterator it;
	++it;
	it++;
}
