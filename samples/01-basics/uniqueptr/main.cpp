#include <memory>
#include <cassert>
#include <memory.h>

using namespace std;

// Структура с конструктором
struct Point
{
	Point(int x0, int y0)
		: x(x0), y(y0)
	{
	}

	int x = 0;
	int y = 0;
};

void main()
{
	// создание одиночного объекта в куче
	{
		// создание целого числа 42 в куче с оборачиванием в unique_ptr
		unique_ptr<int> i(new int(42));
		*i = 55;

		// Полностью аналогично вышенаписанному коду
		auto j = make_unique<int>(42);
		*j = 55;

		// В конструктор Point функция make_unique параметры x и y
		auto pt = make_unique<Point>(10, 20);
		assert(pt->x == 10 && pt->y == 20);
	}

	// Создание массива в куче
	{
		// Создали массив из 10 элементов и обернули в unique_ptr, хранящий адрес массива
		unique_ptr<int[]> arr0(new int[10]);
		arr0[3] = 42; // Можно осуществлять индексированный доступ к элементам
		int *arr0End = &arr0[10]; // Вычислили адрес ячейки памяти, следующей за последним элементом массива
		assert(arr0End - arr0.get() == 10);

		// Аналогично предыдущему примеру
		auto arr1 = make_unique<int[]>(10);
		arr1[3] = 42;
		auto arr1End = &arr1[10];
		assert(arr1End - arr1.get() == 10);
	}

	// Пример с пользовательским deleter-ом
	{
		// пользовательский объект, выполняющий удаление при помощи функции free
		struct FreeDeleter
		{
			void operator()(void * p)const
			{
				free(p);
			}
		};

		unique_ptr < void, FreeDeleter > p(malloc(100));
	}
}
