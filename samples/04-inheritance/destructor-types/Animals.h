#pragma once
#include <iostream>

class Drawable
{
public:
	virtual void Draw() const = 0;

protected:
	// Класс Drawable не предназначен для полиморфного удаления
	// своих подклассов, поэтому его деструктор — защищённый невиртуальный
	~Drawable() = default;
};

class Animal : public Drawable
{
public:
	void Eat()
	{
		std::cout << "Nom-nom" << std::endl;
	}
	virtual void Move() = 0;
	// Наследники класса Animal будут удаляться полиморфно
	virtual ~Animal() = default;
};

class Fish : public Animal
{
public:
	void Move() override
	{
		std::cout << "Swim" << std::endl;
	}
	// Реализуем метод Draw, унаследованный от Drawable.
	void Draw() const override
	{
		std::cout << "><(((*>" << std::endl;
	}
};

class Cat : public Animal
{
public:
	void Move() override
	{
		std::cout << "Run" << std::endl;
	}
	void Draw() const override
	{
		std::cout << "(^w^)" << std::endl;
	}
};

// Робота тоже можно нарисовать, хоть он и не животное.
class Robot : public Drawable
{
public:
	void Draw() const override
	{
		std::cout << "~[o_o]~" << std::endl;
	}
};
