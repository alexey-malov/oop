#include <math.h>
#include <string>
#include <assert.h> // или <cassert>
#include "variables.h"
#include <iostream>

/*
 Объявление переменных в C++
*/

int GetNextCounter();

// Переменная, объявленная вне функции является глобальной. Ее область видимости - вся программа
int someGlobalVariable = 38;
// По умолчанию глобальные переменные инициализируются нулями
int someZeroInitializedGlobaleVariable;

// Статическая глобальная переменная. Ее область видимости - текущий .cpp файл
static int staticVariable = 42;

int GetRandomNumber();

int main()
{
	// Локальные переменные и константы
	{
		// Объявление переменной carSpeed типа double
		double carSpeed;
		carSpeed = 45.8;

		// Объявление переменной можно совместить с ее инициализацией
		int userAge = 20;
		float x = 12.6f;

		// Объявление константной переменной - переменной, 
		// значение которой не может быть изменено после инициализации
		// Константа при объявлении всегда должна быть проинициализирована
		const double SPEED_OF_LIGHT = 299792458.0;
		const int SECONDS_IN_HOUR = 3600;
		const int HOURS_IN_DAY = 24;

		// Константа может быть также проинициализирована в результате выражения
		const int SECONDS_IN_DAY = SECONDS_IN_HOUR * HOURS_IN_DAY;
	}

	// Автоматический вывод типа переменной при ее объявлении
	{
		// double
		auto PI = 3.14159265;

		// const float
		const auto E = 2.71828f;

		// float
		auto e2 = E * 2;

		// const double
		const auto halfPI = PI / 2;

		// long double
		auto sqrtPi = sqrt(PI);
	}

	// Область видимости переменных
	{
		// Область видимости переменной ограничена блоком, внутри которого она объявлена
		std::string userName = "Ivan Petrov";
		int age = 10;

		{
			// Переменная из внутренноего блока может иметь имя, совпадающее с именем из внешнего блока
			// При этом внутри этого блока она замещает собой одноименную переменную из внешнего блока
			std::string userName = "Sergey Ivanov";
			assert(userName == "Sergey Ivanov");

			// Тип переменной из вложенного блока может быть другим
			double age = 7.7;

			// Лучше, все-же отказаться от разных переменных в одном блоке
		}
		// При возврате во внешний блок видимой снова становится внешняя переменная
		assert(userName == "Ivan Petrov");
	}

	// Глобальные переменные
	{
		assert(someZeroInitializedGlobaleVariable == 0);

		// Локальная переменная замещает собой одноименные глобальные переменные
		int someGlobalVariable = 22;
		assert(someGlobalVariable == 22);
		// К глобальной переменной все же можно обратиться по ее полному имени
		assert(::someGlobalVariable == 38);
	}

	// Глобальные переменные, объявленные в других cpp-файлах
	{
		// Переменная globalVariableDeclaredInVariablesCpp объявлена в файле variables.cpp
		// Чтобы обратиться к ней из других файлов, нужно предварительно объявить ее внешней при помощи ключевого слова extern
		extern int globalVariableDeclaredInVariablesCpp;
		assert(globalVariableDeclaredInVariablesCpp == 12345);

		// А эта переменная была объявлена внешней в подключенном нами заголовочном файле variables.h
		assert(someOtherGlobalVariableDeclaredInVariablesCpp == 54321);
	}

	// Статические переменные функций
	{
		// Функция GetNextCounter() запоминает значение статической локальное переменонй currentValue между вызовами

		auto counter = GetNextCounter();
		assert(counter == 1);
		counter = GetNextCounter();
		assert(counter == 2);
		counter = GetNextCounter();
		assert(counter == 3);
	}

	std::cout << GetRandomNumber() << std::endl;
	std::cout << GetRandomNumber() << std::endl;
	std::cout << GetRandomNumber() << std::endl;
	std::cout << GetRandomNumber() << std::endl;

	// В военное время значение числа Пи может достигать четырех
	{
		const double PI = 3.14159265;

		const_cast<double&>(PI) = 4;

		std::cout << "Now pi is " << PI << std::endl;
	}

	int moonPhase = GetRandomNumber();
	enum class State
	{
		Ok,
		Wounded,
		Dead,
	};

	return 0;
}

int GetRandomNumber()
{
	static int seed = 0;
	seed = (seed * 17 + 13) % 100;
	return seed;
}

int GetNextCounter()
{
	// Статическая переменная сохраняет свое значение между вызовами функции
	// При самом первом входе в блок, где она объявлена, происходит ее инициализация
	static int currentValue = 0;

	currentValue += 1;

	return currentValue;
}
