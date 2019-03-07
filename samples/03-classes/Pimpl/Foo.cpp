#include "Foo.h"

struct Foo::Impl
{
	Impl(int size)
		: m_size(size)
	{
	}

	int DoSomething(int arg)
	{
		m_size += arg;
		return m_size;
	}
	int m_size;
};

Foo::Foo(int size)
	: m_impl(std::make_unique<Impl>(size))
{
}

 Foo::~Foo() = default;

int Foo::DoSomething(int arg)
{
	return m_impl->DoSomething(arg);
}
