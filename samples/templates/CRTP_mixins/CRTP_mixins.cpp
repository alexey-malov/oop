#include <iostream>

// Миксин для вывода отладочной информации
template <typename Derived>
class DebugMixin
{
public:
	void DebugPrint() const
	{
		std::cout << "Debug info: ";
		static_cast<const Derived*>(this)->PrintDetails();
	}
};

// Базовый класс
class Widget
{
public:
	void Draw() const
	{
		std::cout << "Drawing Widget\n";
	}
};

// Класс с миксином DebugMixin
class DebugWidget 
	: public Widget
	, public DebugMixin<DebugWidget>
{
public:
	void PrintDetails() const
	{
		std::cout << "Widget details here\n";
	}
};

int main()
{
	DebugWidget w;
	w.Draw();
	w.DebugPrint(); // Используем метод миксина
}
