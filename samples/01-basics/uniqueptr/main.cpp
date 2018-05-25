#include <cassert>
#include <iostream>
#include <memory.h>
#include <memory>
#include <vector>
#include <string>

using namespace std;

// Структура с конструктором
struct Point
{
	Point(int x0, int y0)
		: x(x0)
		, y(y0)
	{
	}

	int x = 0;
	int y = 0;
};

void TestArrayOfUniquePtrs();

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
		int* arr0End = &arr0[10]; // Вычислили адрес ячейки памяти, следующей за последним элементом массива
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
			void operator()(void* p) const
			{
				free(p);
			}
		};

		unique_ptr<void, FreeDeleter> p(malloc(100));
	}

	{
		// массив unique_ptr-ов
		vector<unique_ptr<Point>> points;

		points.push_back(make_unique<Point>(10, 20));

		auto p = make_unique<Point>(1, 5);

		// Так не сработает (нельзя скопировать unique_ptr),
		// т.к. только один unique_ptr может указывать на объект
		// points.push_back(p);

		// Зато можно переместить
		// std::move() превращает p из l-value ссылки в r-value ссылку
		// И тогда сработает конструктор перемещения unique_ptr-а, который
		// переместит указатель из p в ячейку массива
		points.push_back(move(p));

		// p после перемещения будет обнулён
		assert(p == nullptr);
	}

	TestArrayOfUniquePtrs();
}

vector<unique_ptr<Point>> GetPoints()
{
	vector<unique_ptr<Point>> points;

	points.emplace_back(make_unique<Point>(1, 2));
	points.emplace_back(make_unique<Point>(3, 4));

	// return переместит содержимое массива из массива points
	// в приёмник, который примет результат функции
	return points;
}

struct Logger
{
	string m_name;
	Logger(string name)
		: m_name(move(name))
	{
		cout << "Logger::Logger(string name) with name " << m_name << "\n";
	}
	Logger(const Logger& l)
		: m_name(l.m_name)
	{
		cout << "Logger::Logger(const Logger&) with name " << m_name << "\n";
	}
	Logger(Logger&& l)
		: m_name(move(l.m_name))
	{
		cout << "Logger::Logger(Logger&&) with name " << m_name << "\n";
	}
	~Logger()
	{
		cout << "Logger::~Logger() with name " << m_name << "\n";
	}
	Logger& operator=(const Logger& l)
	{
		m_name = l.m_name;
		cout << "Logger::operator=(const Logger&) with name " << m_name << "\n";
		return *this;
	}
	Logger& operator=(Logger&& l)
	{
		m_name = move(l.m_name);
		cout << "Logger::operator=(Logger&&) with name " << m_name << "\n";
	}
};

void TestArrayOfUniquePtrs()
{
	{
		vector<unique_ptr<Point>> points;
		// Массив уникальных указателей будет перемещён изнутри GetPoints() в пер
		points = GetPoints();

		for (auto&& pt : points)
		{
			cout << "(" << pt->x << ", " << pt->y << ")\n";
		}
	}

	{
		vector<unique_ptr<Logger>> outerLoggers;
		unique_ptr<Logger> outerLogger;
		{
			vector<unique_ptr<Logger>> innerLoggers;
			innerLoggers.emplace_back(make_unique<Logger>("logger A"));
			innerLoggers.emplace_back(make_unique<Logger>("logger B"));
			auto loggerC = make_unique<Logger>("logger C");
			auto loggerD = make_unique<Logger>("logger D");

			cout << "Moving content of innerLoggers to outerLoggers\n";
			outerLoggers = move(innerLoggers);
			assert(innerLoggers.empty());

			cout << "Moving content of logger C to outerLogger\n";
			outerLogger = move(loggerC);
			assert(!loggerC);

			cout << "Leaving inner scope\n";
		}

		assert(!outerLoggers.empty());
		assert(outerLogger);

		cout << "Leaving outer scope";
	}
}
