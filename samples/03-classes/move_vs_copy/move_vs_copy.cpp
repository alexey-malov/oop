#include <iostream>
#include <string>

class Student
{
public:
	explicit Student(const std::string& name)
		: m_name(name)
	{
	}

	const std::string& GetName() const
	{
		return m_name;
	}

private:
	std::string m_name;
};

class MovingStudent
{
public:
	explicit MovingStudent(const std::string& name)
		: m_name(name)
	{
		std::cout << "MovingStudent(const std::string& name)\n";
	}

	explicit MovingStudent(std::string&& name)
		: m_name(std::move(name))
	{
		std::cout << "MovingStudent(std::string&& name)\n";
	}

	const std::string& GetName() const
	{
		return m_name;
	}

private:
	std::string m_name;
};

struct Name
{
	Name(const char*)
	{
		std::cout << "Name(const char*)\n";
	}
	Name(const Name&)
	{
		std::cout << "Name(const Name&)\n";
	}
	Name(Name&&)
	{
		std::cout << "Name(Name&&)\n";
	}
};

class ByValueStudent
{
public:
	explicit ByValueStudent(Name name)
		: m_name(std::move(name))
	{
	}

private:
	Name m_name;
};

int main()
{
	// Создаст временную строку из строкового литерала string,
	// а потом в конструкторе копирования скопирует её в m_name
	Student student("Ivan");

	std::string name("Ivan");
	MovingStudent student2(name); // Будет вызвано копирование name
	MovingStudent student3("Ivan"); // Будет вызвано перемещение временного объекта
	MovingStudent student4(std::move(name)); // Будет вызвано перемещение из name

	Name n("Ivan");
	std::cout << "---\n";
	ByValueStudent student5(n); // Copy + Move
	std::cout << "---\n";
	ByValueStudent student6("Ivan"); // Create from char* + Move
	std::cout << "---\n";
	ByValueStudent student7(std::move(n)); // Move + Move
}
