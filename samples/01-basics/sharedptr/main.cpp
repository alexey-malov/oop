#include <memory>
#include <iostream>

using namespace std;

struct Obj
{
	Obj()
	{
		cout << "Obj was constructed" << endl;
	}

	void DoSomething()
	{

	}

	~Obj()
	{
		cout << "Obj was deleted" << endl;
	}
};

void CreateNewObjectAndWrapItIntoSharedPtr()
{
	auto sp = make_shared<Obj>();
	auto sp1 = sp;
	(void)&sp;
}

void WrapExistingObjectInHeapIntoSharedPtr()
{
	Obj *obj = new Obj();
	shared_ptr<Obj> sp(obj);
	// при выходе sp из области видимости объект будет удален shared_pointer-ом
	// delete obj явно вызывать не нужно и нельзя
}

void WrapExistingObjectOnStackIntoSharedPtr()
{
	shared_ptr<Obj> outerSp;
	{
		Obj obj;
		shared_ptr<Obj> sp(&obj, [](Obj * /*o*/) {
			// пустая функция для удаления объекта o
			// (ничего не делает, т.к. объект на стеке и будет удален при выходе
			// из блока, в котором объявлен)
		});
		outerSp = sp;
		sp->DoSomething(); // так можно
		outerSp->DoSomething(); // и так можно
	}
	// Пользоваться объектом outerSp здесь нельзя, т.к. объект Obj
	// уже не существует, а shared_ptr хранит адрес того места на стеке,
	// в котором объект был когда-то
	// outerSp->DoSomething();
}


int main()
{
	CreateNewObjectAndWrapItIntoSharedPtr();
	WrapExistingObjectInHeapIntoSharedPtr();
}