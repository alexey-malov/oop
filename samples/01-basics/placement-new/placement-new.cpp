/*
Пример достаточно сложный для начинающих. Можно пока проигнорировать.
Пример иллюстрирует процесс конструирования массива объектов в области памяти, ранее выделенной при помощи 
malloc. Для этого используется placement-версия оператора new
*/

#include <new>
#include <cassert>
#include <string>

using namespace std;

struct Point
{
	Point(int x0, int y0, const string& name = string())
		: x(x0), y(y0), name(name)
	{
	}

	string name;
	int x = 0;
	int y = 0;
};

void main()
{
	const size_t NUM_POINTS = 100;

	// Выделили массив char-ов, размером, способным вместить NUM_POINTS объектов типа Point
	Point * mem = reinterpret_cast<Point*>(malloc(sizeof(Point) * NUM_POINTS));
	if (mem != nullptr)
	{
		size_t i;

		try
		{
			for (i = 0; i < NUM_POINTS; ++i)
			{
				// Конструируем при помощи placement new объект Point по адресу mem+i, 
				// равному адресу i-го элемента массива
				// http://www.cplusplus.com/reference/new/operator%20new/
				Point * pt = new (mem + i) Point(i, i * 2, "This is a point #" + to_string(i));
				// Возвращенный указатель будет иметь тип Point* и хранить адрес (mem+i)
				assert(pt == (mem + i));
			}

			// Вызываем деструкторы элементов массива в порядке от последнего к самому первому
			// В С++ порядок разрушения объектов в массиве обратен порядку конструирования
			for (; i-- != 0;)
			{
				mem[i].~Point();
			}

		}
		catch (...)
		{
			// Вызываем деструкторы элементов массива, для которых успели отработать конструкторы
			// в порядке от последнего к самому первому
			// В С++ порядок разрушения объектов в массиве обратен порядку конструирования
			for (; i-- != 0;)
			{
				mem[i].~Point();
			}
		}
	}
	// Освобождаем память, занимаемую элементами массива
	// Вывать free с нулевым указателем безопасно (никаких эффектов не будет)
	free(mem);

}
