#include <cassert>
#include <string>

// Структура Point, задающая точку на плоскости
struct Point
{
	int x;
	int y;
};

// Структуры могут выступать в качестве параметров функций
// Здесь передача осуществляется по константной ссылке, чтобы не создавать копию переданного аргумента
double CalculateDistance(const Point & pt1, const Point & pt2)
{
	return hypot(pt1.x - pt2.x, pt1.y - pt2.y);
}

// Поля глобально объявленной структуры по умолчанию инициализируются нулями
Point globalPoint;

// Структура Triangle, задающая треугольник, заданный координатами трех вершин
// В состав структуры могут входить поля, являющиеся структурами
struct Triangle
{
	Point vertex1;
	Point vertex2;
	Point vertex3;
};

// Возвращает геометрический центр треугольника
// Функция принимает параметр triangle по константной ссылке
//	Передача по ссылке означает, что функция работает с оригинальным объектом, а не его временной копией (незачем здесь тратить время на создание копии)
//	Константность ссылки означает, что внутри функции переменная не будет изменена
Point CalculateTriangleCenter(const Triangle & triangle)
{
	return {
		(triangle.vertex1.x + triangle.vertex2.x + triangle.vertex3.x) / 3,
		(triangle.vertex1.y + triangle.vertex2.y + triangle.vertex3.y) / 3,
	};
}

enum class Month
{
	January, February, March,
	April, May, June,
	July, August, September,
	October, November, December
};

// Структура "Дата"
struct Date
{
	int day;
	Month month;
	int year;
};

// Проверка двух дат на равенство
bool Equals(const Date & d1, const Date& d2)
{
	// Даты равны, если их день, месяц и год равны
	return
		(d1.day == d2.day) &&
		(d1.month == d2.month) &&
		(d1.year == d2.year);
}

// Person - пример более сложной стуктуры
struct Person
{
	std::string name;
	std::string address;
	Date birthday;
	int height;
};

// Сравнение двух людей на идентичность
bool Equals(const Person & p1, const Person & p2)
{
	return
		(p1.name == p2.name) &&
		(p1.address == p2.address) &&
		Equals(p1.birthday, p2.birthday) &&
		p1.height == p2.height;
}

void main()
{
	{
		// Объявляем переменную pt, а затем инициализируем ее поля одно за другим
		Point pt;
		pt.x = 10;
		pt.y = 20;
	}

	{
		// При объявлении переменной-структуры можно выполнить инициализацию ее полей
		Point pt0 = { 33, 24 };
		assert(pt0.x == 33 && pt0.y == 24);
		// Еще один способ инициализации структуры при ее объявлении
		Point pt1{ 14, -22 };
		assert(pt1.x == 14 && pt1.y == -22);
	}

	// Недостающие поля при инициализации заполняются нулями
	{
		Point pt2 = { 21 };
		assert(pt2.x == 21 && pt2.y == 0);
		Point pt3 = {};
		assert(pt3.x == 0 && pt3.y == 0);
	}

	// Поля глобальных и статических переменных-структур по умолчанию инициализируются нулями
	{
		static Point pt4;
		assert(pt4.x == 0 && pt4.y == 0);
		assert(globalPoint.x == 0 && globalPoint.y == 0);
	}

	// Инициализация структур, содержащих вложенные структуры
	{
		Triangle t1 = 
		{
			{0, 0}, 
			{20, 100}, 
			{30, 15}
		};
		assert(t1.vertex1.x == 0 && t1.vertex1.y == 0);
		assert(t1.vertex2.x == 20 && t1.vertex2.y == 100);
		assert(t1.vertex3.x == 30 && t1.vertex3.y == 15);

		// Структура, все поля которой будут проинициализированы нулями
		Triangle t2 = {};
		assert(t2.vertex1.x == 0 && t2.vertex1.y == 0);
		assert(t2.vertex2.x == 0 && t2.vertex2.y == 0);
		assert(t2.vertex3.x == 0 && t2.vertex3.y == 0);
	}

	// Структуры в качестве параметров функций и возвращаемых значений
	{
		Triangle t0 = {
			{ 0, 0 }, { 10, -20 }, {20, 20}
		};
		auto center = CalculateTriangleCenter(t0);
		assert(center.x == 10 && center.y == 0);

		// При передаче в функцию можно создать экземпляр структуры без объявления переменной
		// В этом случае в функцию будет передана ссылка временный объект
		center = CalculateTriangleCenter({ { 0, 0 }, { -20, 10 }, { 20, 20 } });
		assert(center.x == 0 && center.y == 10);

		Point pt0{ 1, 1 };
		Point pt1{ 4, 5 };
		double distance = CalculateDistance(pt0, pt1);
		// Проверка чисел с плавающей запятой на приблизительное равенство
		assert(abs(distance - 5.0) <= DBL_EPSILON);
	}

	// Проверка содержимого структур на равенство
	{
		Person person1 = {
			"Ivanov Ivan", 
			"Suvorova Street, 17", 
			{ 10, Month::March, 1975 }, 
			185
		};
		Person person2 = {
			"Sergeev Egor",
			"Sovetskaya Street, 24",
			{ 11, Month::February, 1990 },
			116
		};
		Person person3 = {
			"Ivanov Ivan",
			"Suvorova Street, 17",
			{ 10, Month::March, 1975 },
			185
		};
		assert(!Equals(person1, person2));
		assert(!Equals(person2, person3));
		assert(Equals(person1, person3));
	}

	// Поля структур, являющиеся строками (std::string) без явной инициализации - пустые
	{
		Person p{};
		assert(p.name.empty());
		assert(p.address == "");
		assert(p.height == 0);
		// Месяц по умолчанию равен January, т.к. ему соответствует целочисленное значение 0
		assert(Equals(p.birthday, { 0, Month::January, 0 }));
	}
}
