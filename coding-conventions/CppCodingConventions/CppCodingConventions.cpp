﻿#include "stdafx.h"

// Анонимный неймспейс
namespace
{

}

// Неймспейс с названием `hidden_details`
namespace hidden_details
{

}

// Вложенный неймспейс
namespace details::keys
{

}

// Именование структур
struct SomeStructName
{
	// Именование полей использует верблюжьюНотацию
	int fieldName;
};

// Свободная (т.е. не являющаяся членом класса) функция
// Имя функции использует ВерблюжьюНотацию с заглавной буквы
// Параметры функции используют верблюжьюНотацию с маленькой буквы
// Между именем функции и открывающей скобочкой пробел не ставится
void FreeFunction(int someParam1)
{
	// локальные переменные используют верблюжьюНотацию
	int someLocalVariable = someParam1 * 3;

	// Между ключевым словом и открывающей скобкой ставится пробел
	if (someParam1 > 0)
	{ // Скобочки открывающие располагаются в строке ниже
	}
	else
	{
	}
}

// Константы используют UNDERSCORE_SYNTAX
const int NUMBER_OF_USERS = 100500;

int main(int argc, char* argv[])
{
	// Между именем вызываемой функции и списком ее параметров пробел не ставится
	FreeFunction(42);
	SomeStructName s;
	s.fieldName = 5;
	return 0;
}
