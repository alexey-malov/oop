#include "stdafx.h"
#include "MyClassName.h"


// Реализация конструктора класса
MyClassName::MyClassName()
	:m_memberVariable(10)// Для инициализации полей класса в конструкторе используются списки инициализации
{
}

// Реализация деструктора класса
MyClassName::~MyClassName()
{
}

void MyClassName::DoSomething(int parameterName, int someAnotherMethodName)
{
	m_memberVariable += parameterName + someAnotherMethodName * 2;
}

int MyClassName::SomeProtectedMethod(int someParameter)const
{
	return m_memberVariable + someParameter;
}
