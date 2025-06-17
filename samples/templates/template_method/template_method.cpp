// template_method.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class SomeClass
{
public:
	template <typename T>
	void DoSomething(T value)
	{
		std::cout << "Value: " << value << "\n";
	}
};

template <typename T>
class SomeTemplateClass
{
public:
	explicit SomeTemplateClass(T data)
		: m_data(data)
	{
	}

	template <typename U>
	void DoSomething(U value)
	{
		std::cout << "Data: " << m_data
				  << ", value: " << value << "\n";
	}

private:
	T m_data;
};

struct AnyLess
{
	template <typename T>
	bool operator()(const T& lhs, const T& rhs) const
	{
		return lhs < rhs;
	}
};

template <typename T>
struct S
{
	void NonTemplateMethod();
	template <typename U>
	void TemplateMethod(U u);

	template <typename U>
	void TemplateMethod2();
};

template <typename T>
void S<T>::NonTemplateMethod()
{
}

template <typename T>
template <typename U>
void S<T>::TemplateMethod(U u)
{
	std::cout << u << std::endl;
}

template <typename T>
template <typename U>
void S<T>::TemplateMethod2()
{
	U u{};
	std::cout << u << std::endl;
}

int main()
{
	S<int> s;
	s.NonTemplateMethod();
	s.TemplateMethod(3.5);
	s.TemplateMethod2<int>();

	std::string text = "a quick brown fox jumps over the lazy dog";
	std::sort(text.begin(), text.end(), AnyLess());
	std::cout << text << std::endl;

	auto ss = std::make_shared<std::string>(10, 'A');
	std::cout << *ss << "\n";

	SomeTemplateClass<int> cls{ 42 };
	cls.DoSomething('A');
}
