#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <cassert>

using namespace std;

void CaptureByValue()
{
	cout << "Capture by value" << endl;
	int x = 42;
	auto fn = [=] {
		// x захватывается по значению
		cout << " x = " << x << endl;
	};
	fn();
	x = 55;
	fn();
}

void CaptureByValueEmulation()
{
	cout << "Capture by value emulation" << endl;
	int x = 42;

	// В предыдущей функции вместо lambda-выражения компилятор сгенерировал
	// код, семантически эквивалентный следующему:
	struct Fn
	{
		Fn(int x):x(x){}

		void operator()()const
		{
			cout << " x = " << x << endl;
		}
	private:
		int x;
	};

	Fn fn(x);
	fn();
	x = 55;
	fn();
}

void CaptureByReference()
{
	cout << "Capture by reference" << endl;
	int x = 42;
	auto fn = [&] {
		// x захватывается по ссылке
		cout << " x = " << x << endl;
	};
	fn();
	x = 55;
	fn();
}

void CaptureByReferenceEmulation()
{
	cout << "Capture by reference emulation" << endl;
	int x = 42;

	// В предыдущей функции вместо lambda-выражения компилятор сгенерировал
	// код, семантически эквивалентный следующему:
	struct Fn
	{
		Fn(int & x) :x(x) {}

		void operator()()const
		{
			cout << " x = " << x << endl;
		}
	private:
		int & x;
	};

	Fn fn(x);
	fn();
	x = 55;
	fn();
}

void CaptureByValueInMutableLambda()
{
	cout << "Capture by value in mutable lambda" << endl;
	int x = 42;
	auto fn = [=] () mutable {
		// x захватывается по значению (которое можно менять внутри лямбды)
		x += 5;
		cout << " x = " << x << endl;
	};
	fn();
	x = 55; // внутри лямбды значение не изменится
	fn();
}

void CaptureByValueInMutableLambdaEmulation()
{
	cout << "Capture by value in mutable lambda emulation" << endl;
	int x = 42;

	// В предыдущей функции вместо lambda-выражения компилятор сгенерировал
	// код, семантически эквивалентный следующему:
	struct Fn
	{
		Fn(int x) :x(x) {}

		void operator()() // в mutable-lambda оператор () не является константым
		{
			x += 5;
			cout << " x = " << x << endl;
		}
		int x;
	};

	Fn fn(x);
	fn();
	x = 55;
	fn();
}

void WrongCaptureByReference()
{
	cout << "Wrong capture by reference" << endl;
	function<void()> fn;

	{
		string msg = "A long string that should not be optimized";
		auto lambda = [&] {
			msg += msg + "\n!";
			cout << " msg = " << msg << endl;
		};
		fn = lambda;
		fn(); // еще нормально
		msg += "\n:)\n";
		lambda();
	}
	// если раскомментировать следующую строчку, то будет неопр. поведение
	//fn(); 
}

void CaptureBySharedValue()
{
	cout << "Сapture by shared reference" << endl;
	function<void()> fn;

	{
		auto msg = make_shared<string>("A long string that should not be optimized");
		auto lambda = [=] {
			*msg += *msg + "\n!";
			cout << " msg = " << *msg << endl;
		};
		fn = lambda;
		fn(); // еще нормально
		*msg += "\n:)\n";
		lambda();
	} // строка при выходе из блока будет жить, т.к. на нее есть еще ссылка из лямбды
	cout << "\nmsg is still alive" << endl;
	// А вот так можно вызывать функцию, т.к. msg находится в куче и 
	// управляется shared-указателем, захваченным в лямбде по значению
	fn(); 
}

void CaptureWithMoving()
{
	cout << "Capture with moving value into lambda" << endl;
	auto str = make_unique<string>("Hello");
	
	// В лямбда-выражение перемещается содержимое str, причем внутри
	// лямбды к нему мы обращаемся по имени xyz
	auto addSuffix = [xyz = move(str)] (const string& suffix) {
		*xyz += suffix;
		cout << *xyz << endl;
	};

	// в str пусто (значение было перемещено в лямбду)
	assert(!str);

	addSuffix("!");
	addSuffix("?");
}

void BorrowingLambda()
{
	cout << "Lambda that borrows a value and then gives it back" << endl;
	auto msg = make_unique<string>("Hello");

	auto giveMeMyMessageBack = [msg = move(msg)] () mutable {
		if (msg)
		{
			cout << "I have your string: '" << *msg << "'" << endl;
		}
		else
		{
			cout << "I am empty, sorry" << endl;
		}
		// возвращает значение из msg наружу
		return move(msg);
	};

	// у нас нет сообщения, т.к. оно находится в lambda
	assert(!msg);

	msg = giveMeMyMessageBack();
	
	assert(msg);

	cout << "Hey, a got my message back: '" << *msg << "', thanks!" << endl;

	// пытаемся забрать у лямбды значение, которым она уже не владеет
	auto oneMoreMessage = giveMeMyMessageBack();

	// Нам ничего она больше не отдала
	assert(!oneMoreMessage);
}

void MutableLambdaExample()
{
	unsigned seed = 42;
	auto rnd = [seed]() mutable {
		seed = seed * 43 + 47;
		return seed % 10;
	};
	for (int i = 0; i < 10; ++i)
	{
		cout << rnd() << " ";
	}
	cout << endl;
}

void RecursiveLambda()
{
	function<unsigned(unsigned)> factorial = [&](unsigned x) {
		return (x == 0) ? 1 : x * factorial(x - 1);
	};
	cout << "4! = " << factorial(4) << endl;
}

int main()
{
	MutableLambdaExample();
	CaptureByValue();
	CaptureByValueEmulation();
	CaptureByReference();
	CaptureByReferenceEmulation();
	CaptureByValueInMutableLambda();
	CaptureByValueInMutableLambdaEmulation();
	WrongCaptureByReference();
	CaptureBySharedValue();
	CaptureWithMoving();
	BorrowingLambda();
	RecursiveLambda();
	return 0;
}