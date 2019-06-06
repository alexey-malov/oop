#pragma once

#include <algorithm>
#include <new>

template <typename T>
class CMyArray
{
	template <typename T, typename OutputT, typename IterT>
	class IteratorBase
	{
	public:
		using reference = OutputT&;
		using pointer = OutputT*;
		using difference_type = ptrdiff_t;
		using value_type = OutputT;
		using iterator_category = std::random_access_iterator_tag;

		OutputT& operator*() const
		{
			return *m_item;
		}

		IterT& operator+=(difference_type offset)
		{
			m_item += offset;
			return static_cast<IterT&>(*this);
		}

		IterT operator+(difference_type offset) const
		{
			IterT self(m_item);
			return self += offset;
		}

		friend IterT operator+(difference_type offset, const IterT& it)
		{
			return it + offset;
		}

	protected:
		IteratorBase() = default;
		IteratorBase(T* item)
			: m_item(item)
		{
		}

	protected:
		T* m_item = nullptr;
	};

public:
	CMyArray() = default;

	CMyArray(const CMyArray& arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}

	void Append(const T& value)
	{
		if (m_end == m_endOfCapacity) // no free space
		{
			size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T* newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				// Конструируем копию value по адресу newItemLocation
				new (newEnd) T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			// Переключаемся на использование нового хранилища элементов
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else // has free space
		{
			new (m_end) T(value);
			++m_end;
		}
	}

	T& GetBack()
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	const T& GetBack() const
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	size_t GetSize() const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity() const
	{
		return m_endOfCapacity - m_begin;
	}
	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}

	class Iterator : public IteratorBase<T, T, Iterator>
	{
		friend class CMyArray<T>;

	public:
		Iterator() = default;

	private:
		Iterator(T* pos)
			: IteratorBase(pos)
		{
		}
	};

	class ConstIterator : public IteratorBase<T, const T, ConstIterator>
	{
		friend class CMyArray<T>;

	public:
		ConstIterator() = default;
		ConstIterator(const Iterator other)
			: IteratorBase(other.m_item)
		{
		}

	private:
		ConstIterator(T* pos)
			: IteratorBase(pos)
		{
		}
	};

	using iterator = Iterator;
	using const_iterator = ConstIterator;

	iterator begin()
	{
		return { m_begin };
	}

	const_iterator begin() const
	{
		return { m_begin };
	}

	const_iterator cbegin() const
	{
		return { m_begin };
	}

private:
	static void DeleteItems(T* begin, T* end)
	{
		// Разрушаем старые элементы
		DestroyItems(begin, end);
		// Освобождаем область памяти для их хранения
		RawDealloc(begin);
	}

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T* srcBegin, T* srcEnd, T* const dstBegin, T*& dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			new (dstEnd) T(*srcBegin);
		}
	}

	static void DestroyItems(T* from, T* to)
	{
		// dst - адрес объект, при конструирование которого было выброшено исключение
		// to - первый скорнструированный объект
		while (to != from)
		{
			--to;
			// явно вызываем деструктор для шаблонного типа T
			to->~T();
		}
	}

	static T* RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T* p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T* p)
	{
		free(p);
	}

private:
	T* m_begin = nullptr;
	T* m_end = nullptr;
	T* m_endOfCapacity = nullptr;
};
