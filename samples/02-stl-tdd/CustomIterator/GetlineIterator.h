#pragma once
#include <iterator>
#include <string>

// Пользовательский итератор для построчного считывания строк из входного потока
// при помощи getline
// При разработке руководствовался поведением класса istream_iterator
class CGetlineIterator : public std::iterator < std::input_iterator_tag, std::string >
{
public:
	// Конструирует итератор, ассоциированный с концом потока (m_strm == nullptr)
	CGetlineIterator() :m_strm(nullptr)
	{}

	// Конструирует итератор, ассоциированный с заданным потоком
	CGetlineIterator(std::istream & strm)
		:m_strm(&strm)
	{
		GetNextLine();
	}

	// Оператор доступа к данным
	const std::string& operator*()const
	{
		return m_str;
	}

	// Оператор для доступа к полям структур
	const std::string* operator->()const
	{
		return &m_str;
	}

	// Префиксная форма оператора ++
	CGetlineIterator & operator++()
	{
		GetNextLine();

		return *this; // Оператор ++ возвращает ссылку на сам объект
	}

	// Постфиксная форма оператора ++
	const CGetlineIterator operator++(int)
	{
		auto tmp(*this);
		++ *this;
		return tmp; // Возвращается прежнее значение итератора
	}

	/*
	Операторы сравнения итераторов
	Выдержка из спецификации: http://www.cplusplus.com/reference/iterator/istream_iterator/operators/
		Two end-of-stream iterators are always equal (no matter the particular stream each is associated).
		Two non-end-of-stream iterators are equal when they are constructed from the same stream, or one is a copy of the other.
		An end-of-stream iterator is never equal to a non-end-of-stream iterator.
	*/
	bool operator==(const CGetlineIterator & rhs)const
	{
		return m_strm == rhs.m_strm;
	}
	bool operator!=(const CGetlineIterator & rhs)const
	{
		return !(*this == rhs);
	}
private:

	void GetNextLine()
	{
		if (m_strm && !std::getline(*m_strm, m_str))
		{
			// Поток закончился или произошла ошибка - сбрасываем указатель
			m_strm = nullptr;
		}
	}

	std::istream * m_strm = nullptr;
	std::string m_str;
};


