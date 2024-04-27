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
struct Slave;
struct Task
{
	int id;
};

struct Master
{
	Master()
	{
		std::cout << "Master is created" << std::endl;
	}
	~Master()
	{
		std::cout << "Master is destroyed" << std::endl;
	}

	Task GetTask()
	{
		return { m_nextTaskId++ };
	}

	std::shared_ptr<Slave> slave1;
	std::shared_ptr<Slave> slave2;

private:
	int m_nextTaskId = 0;
};

struct Slave
{
	Slave()
	{
		std::cout << "Slave is created" << std::endl;
	}
	~Slave()
	{
		std::cout << "Slave is destroyed" << std::endl;
	}

	void Work()
	{
		if (auto m = master.lock())
		{
			auto task = m->GetTask();
			std::cout << "Slave performs task #" << task.id << std::endl;
		}
		else
		{
			std::cout << "Slave has no master" << std::endl;
		}
	}

	// Slave не владеет объектом Master, а хранит слабую ссылку на него.
	std::weak_ptr<Master> master;
};

void TestWeakPtr()
{
	auto master = std::make_shared<Master>();
	auto slave1 = std::make_shared<Slave>();
	auto slave2 = std::make_shared<Slave>();

	master->slave1 = slave1;
	slave1->master = master;

	master->slave2 = slave2;
	slave2->master = master;
	
	slave1.reset();
	slave2->Work();
	slave2->Work();
	master.reset();
	slave2->Work();
	std::cout << "Exit from function" << std::endl;
}

int main()
{
	TestWeakPtr();
	std::cout << "---" << std::endl;
	CreateNewObjectAndWrapItIntoSharedPtr();
	WrapExistingObjectInHeapIntoSharedPtr();
}