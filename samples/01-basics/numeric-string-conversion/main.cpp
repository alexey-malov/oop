#include <string>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <cfloat>

void main()
{
	{
		assert(std::to_string(10) == "10");
		// Не умеет отбрасывать незначащие нули
		assert(std::to_string(10.7) == "10.700000");
	}

	{
		// создали поток связанный с выводом внутрь строки
		std::ostringstream strm;
		strm << 10.5;
		assert(strm.str() == "10.5");
	}
	{
		std::ostringstream strm;
		strm << std::setprecision(4) << 102.12345678;
		assert(strm.str() == "102.1");
	}
	{
		std::ostringstream strm;
		strm << std::fixed << std::setprecision(4) << 102.12345678;
		assert(strm.str() == "102.1235");
	}

	{
		assert(std::stoi("42") == 42);
		size_t stoppedAt;
		assert(std::stoi("123456blablabla", &stoppedAt) == 123456);
		assert(stoppedAt == 6);
		assert(std::stoi("f3eblablabla", &stoppedAt, 16) == 0xf3eb);
		assert(stoppedAt == 4);
	}

	{
		try
		{
			// Эта версия stoi выбросит исключение, если не сможет сконвертировать
			std::stoi("not a number");
			// сюда мы не попадем
			assert(false);
		}
		catch (const std::invalid_argument & err)
		{
			// попадем сюда
			std::cout << err.what();
		}

		try
		{
			int i = std::stoi("123not a number");
			assert(i == 123);
		}
		catch (const std::invalid_argument & /*err*/)
		{
			// сюда не попадем, т.к. удалось сконвертировать хоть что-то
			assert(false);
		}

		try
		{
			std::stoi("5555555555not a number");
			// сюда мы не попадем
			assert(false);
		}
		catch (const std::out_of_range & err)
		{
			// попадем сюда, т.к. 5555555555 не помещается в int
			std::cout << err.what();
		}

	}

	{
		// Создаем строковый поток, связанный со строкой "123.78"
		std::istringstream strm("123.78");
		double value;
		strm >> value; // считываем значение типа double
		assert(strm);  // проверяем на наличие ошибки
		assert(abs(value - 123.78) < DBL_EPSILON);
	}

	{
		// Создаем строковый поток, связанный со строкой "not-a-string"
		std::istringstream strm("not-a-string");
		double value;
		strm >> value; // считываем значение типа double
		assert(!strm);  // ожидаем, что поток находится в состоянии ошибки, т.к. считать double не вышло
	}

}