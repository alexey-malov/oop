#pragma once
#include <memory>

class Foo
{
public:
	Foo(int size);
	~Foo();
	int DoSomething(int arg);
private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};