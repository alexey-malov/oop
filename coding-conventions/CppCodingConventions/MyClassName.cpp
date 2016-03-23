#include "stdafx.h"
#include "MyClassName.h"


// Реализация конструктора класса
CMyClassName::CMyClassName()
	:m_memberVariable(10)// Для инициализации полей класса в конструкторе используются списки инициализации
{
}

// Реализация деструктора класса
CMyClassName::~CMyClassName()
{
}

void CMyClassName::DoSomething(int parameterName, int someAnotherMethodName)
{
	m_memberVariable += parameterName + someAnotherMethodName * 2;
}

int CMyClassName::SomeProtectedMethod(int someParameter)const
{
	return m_memberVariable + someParameter;
}
