#if 1
#include <cassert>
#include <fstream>
#include <iostream>
#include <latch>
#include <mutex>
#include <numbers>
#include <sstream>
#include <string>

struct Point
{
	int x = 0;
	int y = 0;
};

Point ReadPoint(std::istream& input)
{
	Point p;
	input >> p.x >> p.y;
	return p;
}

void WritePoint(std::ostream& output, Point p)
{
	output << p.x << " " << p.y;
}
namespace ver1
{

class Time
{
	int m_hours = 0;
	int m_minutes = 0;
	int m_seconds = 0;
};

} // namespace ver1

namespace ver2
{

class Time
{
	int m_secondsSinceMidnight = 0;
};

#if 0
void Test()
{
	Time t;
	t.m_secondsSinceMidnight = 42;
	// error: cannot access private member declared in class 'Time'
}
#endif

} // namespace ver2

namespace ver3
{
// Структура глазами компилятора
struct Time
{
	// Этот спецификатор public неявно подразумевается внутри struct.
public:
	// Всё, что ниже public:, доступно для внешнего кода.
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
};
} // namespace ver3

namespace ver4
{
// Класс глазами компилятора
class Time
{
	// Этот спецификатор private неявно подразумевается внутри class.
private:
	// Всё, что ниже private:, скрыто от внешнего мира.
	int m_hours = 0;
	int m_minutes = 0;
	int m_seconds = 0;
};
} // namespace ver4

namespace ver5
{
class Time
{
public:
	int GetHours() { return m_secondsSinceMidnight / 3600; }
	int GetMinutes() { return (m_secondsSinceMidnight / 60) % 60; }
	int GetSeconds() { return m_secondsSinceMidnight % 60; }

	bool SetTime(int hours, int minutes, int seconds)
	{
		if (hours < 0 || hours >= 24 || minutes < 0 || minutes >= 60 || seconds < 0 || seconds >= 60)
		{
			return false;
		}

		m_secondsSinceMidnight = hours * 60 * 60 + minutes * 60 + seconds;

		return true;
	}

private:
	int m_secondsSinceMidnight = 0;
};
} // namespace ver5

namespace
{
class SomeClass
{
public:
	// Это метод класса. Выглядит как функция, описанная внутри класса.
	int GetData()
	{
		// К приватным данным можно обращаться только внутри методов класса.
		return m_data;
	}

private:
	// Данные надёжно спрятаны от внешнего мира.
	// Никто, кроме самого класса, не имеет к ним доступа.
	int m_data = 42;
};
} // namespace

namespace geom2
{

class Circle
{
public:
	void SetRadius(double r)
	{
		m_radius = r;
	}
	double GetRadius() const { return m_radius; }
	double GetArea() const { return std::numbers::pi * m_radius * m_radius; }

private:
	double m_radius;
};

void PrintCircle(const Circle& c)
{
	std::cout << "radius=" << c.GetRadius() << ", area=" << c.GetArea() << std::endl;
}

void main()
{
	Circle c;
	c.SetRadius(10);
	PrintCircle(c);
}
} // namespace geom2

namespace mutmut
{
class ThreadsafeCounter {
public:
	int Get() const {
		std::lock_guard lk(m_mutex);
		return m_data;
	}
	void Inc() {
		std::lock_guard lk(m_mutex);
		++m_data;
	}
private:
	// The "M&M rule": mutable and mutex go together
	mutable std::mutex m_mutex;
	int m_data = 0;
};

class NonThreadsafeCounter
{
public:
	int Get() const
	{
		return m_data;
	}
	void Inc()
	{
		++m_data;
	}

private:
	int m_data = 0;
};
} // namespace mutmut

int main()
{
	using namespace mutmut;

	ThreadsafeCounter counter;

	{
		// Триггер, который разблокируется, когда трижды вызовут arrive_and_wait
		std::latch l(3);
		std::jthread t1([&counter, &l] {
			l.arrive_and_wait();
			for (int i = 0; i < 1'000'000; ++i)
			{
				counter.Inc();
			}
		});
		std::jthread t2([&counter, &l] {
			l.arrive_and_wait();
			for (int i = 0; i < 1'000'000; ++i)
			{
				counter.Inc();
			}
		});
		std::jthread t3([&counter, &l] {
			l.arrive_and_wait();
			for (int i = 0; i < 100; ++i)
			{
				std::cout << counter.Get() << std::endl;
			}
		});
	} // Все потоки завершат работу при выходе из блока
	std::cout << "---" << std::endl;
	std::cout << counter.Get() << std::endl;
}

#else
#include <iostream>

class Mutable
{
public:
	int GetValue() const
	{
		if (m_value == -1)
		{
			m_value = 42;
		}
		return m_value;
	}
	int GetCounter() const { return m_counter; }
	void Change()
	{
		std::cout << "Enter Immutable::Change" << std::endl;
		++m_counter;
		std::cout << "Exit Immutable::Change" << std::endl;
	}

private:
	mutable int m_value = -1;
	int m_counter = 0;
};

class Immutable
{
public:
	int GetValue() const
	{
		return m_value;
	}
	int GetCounter() const { return m_counter; }
	void Change()
	{
		std::cout << "Enter Immutable::Change" << std::endl;
		++m_counter;
		std::cout << "Exit Immutable::Change" << std::endl;
	}

private:
	int m_value = 42;
	int m_counter = 0;
};

const Mutable mut;
const Immutable immut;

int main()
{
	std::cout << "Immutable: " << &immut << " - " << immut.GetValue() << std::endl;
	std::cout << "  Mutable: " << &mut << " - " << mut.GetValue() << std::endl;

	const_cast<Mutable&>(mut).Change();
	std::cout << mut.GetCounter() << std::endl;

	const_cast<Immutable&>(immut).Change();
	std::cout << immut.GetCounter() << std::endl;
}
#endif

struct Vector {
    double x = 0, y = 0;
};

struct Point {
    double x = 0, y = 0;

    void Set(double x, double y) {
        // Область видимости параметров x и y ограничена 
        // методом Point::Set. Поэтому внутри метода Set 
        // имена x и y относятся к параметрам, а не к полям.

        // Когда мы пишем this->x и this->y, то явно сообщаем 
        // компилятору, что обращаемся к полям текущего объекта.
        this->x = x;
        this->y = y;

        // Если напишем x = x, то присвоим параметру x его собственное значение.
    }
};
int main() {
    Point p1, p2;

    // Для вызова метода указываем объект.
    p1.MoveBy({1, 2.5});
    p2.MovePoint({-1, -1});
}