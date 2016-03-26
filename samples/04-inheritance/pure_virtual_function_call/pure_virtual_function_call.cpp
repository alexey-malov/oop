// pure_virtual_function_call.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;
class Base
{
public:
	~Base()
	{
		Close();
	}
	virtual void DoSomething() = 0;
	virtual string ToString()const = 0;
private:
	void Close()
	{
		string result = ToString();
		cout << result << endl;
		DoSomething();
	}
};

class Derived : public Base
{
public:
	string ToString()const override
	{
		return "hello";
	}
	void DoSomething() override
	{
		cout << "Do something! " << x << endl;
	}
	int x = 42;
};


int _tmain(int argc, _TCHAR* argv[])
{
	{
		Derived derived;
		derived.DoSomething();
	}
	cout << "Good bye!" << endl;
	return 0;
}

