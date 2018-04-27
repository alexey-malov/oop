#pragma warning(disable : 4996)
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;
using namespace std::placeholders;

int Subtract(int a, int b)
{
	return a - b;
}

void Subtract7FromEachNumber()
{
	int numbers[] = { 1, 3, 8, 7, 4, 5 };
	for (auto& number : numbers)
	{
		number -= 7;
	}
	copy(begin(numbers), end(numbers), ostream_iterator<int>(cout, ", "));
	cout << endl;
}

int Subtract7(int x)
{
	return x - 7;
}

void Subtract7FromEachNumberUsingTransformWithGlobalFunction()
{
	int numbers[] = { 1, 3, 8, 7, 4, 5 };
	transform(begin(numbers), end(numbers), begin(numbers), Subtract7);

	copy(begin(numbers), end(numbers), ostream_iterator<int>(cout, ", "));
	cout << endl;
}

void SubtractVariableFromEachNumberUsingTransformWithLambda()
{
	int numbers[] = { 1, 3, 8, 7, 4, 5 };
	int subtrahend = 7;
	transform(begin(numbers), end(numbers), begin(numbers),
		[=](int x) { return x - subtrahend; });

	copy(begin(numbers), end(numbers), ostream_iterator<int>(cout, ", "));
	cout << endl;
}

// Возвращает функцию, вычитающую n
function<int(int arg)> MakeSubtractN(int n)
{
	return [=](int x) { return Subtract(x, n); };
}

function<int(int arg)> MakeSubtractFromN(int n)
{
	return [=](int x) { return Subtract(n, x); };
}

void SubtractVariableFromEachNumberUsingTransformWithManualBinding()
{
	int numbers[] = { 1, 3, 8, 7, 4, 5 };
	int subtrahend = 7;
	transform(begin(numbers), end(numbers), begin(numbers),
		MakeSubtractN(subtrahend));

	copy(begin(numbers), end(numbers), ostream_iterator<int>(cout, ", "));
	cout << endl;
}

void SubtractVariableFromEachNumberUsingTransformWithSTLBinding()
{
	int numbers[] = { 1, 3, 8, 7, 4, 5 };
	int subtrahend = 7;
	transform(begin(numbers), end(numbers), begin(numbers),
		bind2nd(minus<int>(), subtrahend));

	copy(begin(numbers), end(numbers), ostream_iterator<int>(cout, ", "));
	cout << endl;
}

void SubtractVariableFromEachNumberUsingTransformWithSTLBinding2()
{
	int numbers[] = { 1, 3, 8, 7, 4, 5 };
	int subtrahend = 7;
	transform(begin(numbers), end(numbers), begin(numbers),
		bind(minus<int>(), _1, subtrahend));

	copy(begin(numbers), end(numbers), ostream_iterator<int>(cout, ", "));
	cout << endl;
}

class Dog
{
public:
	explicit Dog(string name)
		: m_name(name)
	{
	}
	void Bark(int times) const
	{
		cout << m_name << " barks: ";
		for (int i = 0; i < times; ++i)
		{
			cout << "woof! ";
		}
		cout << "\n";
	}

private:
	string m_name;
};

void PlayWithDogs()
{
	Dog dogs[]{
		Dog{ "Goofy" }, Dog{ "Beethoven" }, Dog{ "Hatiko" }
	};
	int n = 5;
	for (auto& dog : dogs)
	{
		dog.Bark(n);
	}
	cout << "=====Dog will bark using lambdas===\n";
	for_each(begin(dogs), end(dogs), [n](Dog& dog) {
		dog.Bark(n);
	});
	cout << "=====Dog will bark using bound function ===\n";
	for_each(begin(dogs), end(dogs), bind(&Dog::Bark, _1, n));
}

int main()
{
	Subtract7FromEachNumber();
	Subtract7FromEachNumberUsingTransformWithGlobalFunction();
	SubtractVariableFromEachNumberUsingTransformWithLambda();
	SubtractVariableFromEachNumberUsingTransformWithManualBinding();
	cout << Subtract(7, 3) << endl;
	cout << MakeSubtractN(3)(7) << endl;
	cout << MakeSubtractFromN(7)(3) << endl;
	cout << bind(Subtract, 7, 3)() << endl;
	cout << bind(Subtract, 7, std::placeholders::_1)(3) << endl;
	cout << bind(Subtract, std::placeholders::_1, 3)(7) << endl;
	cout << bind(Subtract, std::placeholders::_1, 3)(7) << endl;
	cout << bind(Subtract, std::placeholders::_1, std::placeholders::_2)(7, 3) << endl;
	cout << bind(Subtract, std::placeholders::_2, std::placeholders::_1)(3, 7) << endl;
	SubtractVariableFromEachNumberUsingTransformWithSTLBinding();
	SubtractVariableFromEachNumberUsingTransformWithSTLBinding2();
	PlayWithDogs();
	return 0;
}
