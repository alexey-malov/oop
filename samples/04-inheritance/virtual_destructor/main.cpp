#include <iostream>
#pragma warning (push)
#pragma warning (disable:4996)
#include <memory>
#pragma warning (pop)
#include <boost/signals2.hpp>
#include <vector>

using namespace std;

struct BaseWithNonVirtualDestructor
{
	~BaseWithNonVirtualDestructor()
	{
		cout << "~BaseWithNonVirtualDestructor()" << endl;
	}
};

struct DerivedWithNonVirtualDestructor : BaseWithNonVirtualDestructor
{
	~DerivedWithNonVirtualDestructor()
	{
		cout << "~DerivedWithNonVirtualDestructor()" << endl;
	}
};

void ObjectCreatedOnStack()
{
	cout << "Object creation on stack" << endl;
	DerivedWithNonVirtualDestructor derived;
}

void ObjectOnHeapIsDestroyedNonPolymorphically()
{
	cout << "Object created on heap is destroyed non polymorphically" << endl;
	auto derived = make_unique<DerivedWithNonVirtualDestructor>();
}

void ObjectOnHeapIsDestroyedPolymorphically()
{
	cout << "Object created on heap is destroyed polymorphically" << endl;
	unique_ptr<BaseWithNonVirtualDestructor> derived = make_unique<DerivedWithNonVirtualDestructor>();
}

void ObjectOnHeapIsDestroyedPolymorphicallyWithSharedPtr()
{
	cout << "Object created on heap is destroyed polymorphically with shared_ptr" << endl;
	shared_ptr<BaseWithNonVirtualDestructor> derived = make_shared<DerivedWithNonVirtualDestructor>();
}

void ObjectOnHeapIsPartiallyDestroyedPolymorphicallyWithSharedPtr()
{
	cout << "Object created on heap is partially destroyed polymorphically with shared_ptr" << endl;
	BaseWithNonVirtualDestructor * base = new DerivedWithNonVirtualDestructor();
	shared_ptr<BaseWithNonVirtualDestructor> derived(base);
}

struct BaseWithVirtualDestructor
{
	virtual ~BaseWithVirtualDestructor()
	{
		cout << "~BaseWithVirtualDestructor" << endl;
	}
};

struct DerivedWithVirtualDestructor : BaseWithVirtualDestructor
{
	~DerivedWithVirtualDestructor()
	{
		cout << "~DerivedWithVirtualDestructor" << endl;
	}
};

void ObjectWithVirtualDestructorDestruction()
{
	{
		cout << "Object with virtual destructor created on a stack" << endl;
		DerivedWithVirtualDestructor derived;
	}

	{
		cout << "Object with virtual destructor created on a heap" << endl;
		auto derived = make_unique<DerivedWithVirtualDestructor>();
	}

	{
		cout << "Object with virtual destructor created on a heap is destroyed polymorphically" << endl;
		unique_ptr<BaseWithVirtualDestructor> derived = make_unique<DerivedWithVirtualDestructor>();
	}
}

struct Base
{
	~Base()
	{
		cout << "~Base()" << endl;
	}
};

struct Derived : Base
{
	// Сигнал, шлющий пары значений x и y (например, перемещение какого-то объекта)
	typedef boost::signals2::signal<void(int x, int y)> MovementSignal;

	Derived(MovementSignal & signal)
	{
		connection = signal.connect(MovementSignal::slot_type(&Derived::HandleSignal, this, _1, _2));
	}

	~Derived()
	{
		cout << "~Derived()" << endl;
	}
private:
	void HandleSignal(int x, int y)
	{
		cout << "x:" << x << ", y:" << y << endl;
		recordedSignal.emplace_back(x, y);
	}
	vector<pair<int, int>> recordedSignal;
	boost::signals2::scoped_connection connection;
};

void SignalHandling()
{
	{
		cout << "Signalling to object that was created on stack" << endl;
		Derived::MovementSignal signal;
		{
			Derived derived(signal);
			signal(1, 2);
			signal(42, 15);
		} // при разрушении derived вызовется деструктор scoped_connection, который отсоединится от сигнала
		// Этот сигнал уйдет в никуда, т.к. объект derived, который его слушал, 
		// отсоединился перед своим разрушением от этого сигнала.
		signal(33, 21);
	}

	{
		cout << "Signalling to object that was created on stack, but not destroyed" << endl;
		Derived::MovementSignal signal;
		{
			unique_ptr<Base> derived = make_unique<Derived>(signal);
			signal(1, 2);
			signal(42, 15);
		}
		// Если раскомментировать следующую строку, программа упадет, т.к.
		// деструктор Derived вызван не был и не произошло отписывание от сигнала,
		// который теперь будет отправляться разрушенному объекту
		// signal(33, 21);
	}
}

int main()
{
	ObjectCreatedOnStack();
	ObjectOnHeapIsDestroyedNonPolymorphically();
	ObjectOnHeapIsDestroyedPolymorphically();
	ObjectOnHeapIsDestroyedPolymorphicallyWithSharedPtr();
	ObjectOnHeapIsPartiallyDestroyedPolymorphicallyWithSharedPtr();
	ObjectWithVirtualDestructorDestruction();

	SignalHandling();
	return 0;
}