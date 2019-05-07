// VirtualDestructor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <memory>

using namespace std;

class Bad
{
	// Тут не объявлен деструктор, компилятор сгенерирует его
	// за нас, при этом он будет невиртуальный
};

class BadChild : public Bad
{
public:
	~BadChild()
	{
		cout << "BadChild is destroyed\n";
	}
};

class Good
{
public:
	virtual ~Good() = default;
};

class GoodChild : public Good
{
public:
	// Тут нет необходимости объявлять деструктор вируальным,
	// т.к. он уже объявлен виртуальным в базовом классе
	~GoodChild()
	{
		cout << "GoodChild is destroyed\n";
	}
};

class GoodChild1 : public Good
{
	// Хоть тут и нет деструктора явно заданного, 
	// компилятор сгенерирует его за нас, при этом он будет
	// виртуальным (т.к. деструктор класса Good виртуальный)
};

class NotSoGood : public Good
{
public:
	// Мы не разрешаем переопределять деструктор своим наследникам
	// А это равноценно запрету наследования от нашего класса
	~NotSoGood() final
	{

	}
};


// Не скомпилируется, т.к. компилятор не сможет
// переопределить финальный деструктор базового класса
/*
class NotSoGoodChild : public NotSoGood
{

};
*/



class IDrawable
{
public:
	virtual void Draw() const = 0;

protected:
	~IDrawable() = default;
};

class Cat : public IDrawable
{
public:
	void Draw() const override
	{
		cout << "Cat is drawn\n";
	}
};

void DrawSomething(IDrawable* drawable)
{
	drawable->Draw();
	
	// Won't compile
	//delete drawable;
}

class NonInheritable final
{

};

// Won't compile because NonInheritable is final
/* 
class CantInheritFromNonInheritable : public NonInheritable
{

};
*/

int main()
{
	unique_ptr<Bad> bad(new BadChild());
	cout << "----\n";
	unique_ptr<Good> good(new GoodChild());

	Cat cat;
	DrawSomething(&cat);
}
