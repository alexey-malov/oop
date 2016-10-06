#include <string>
#include <iostream>

using namespace std;

class Student
{
public:
	template <typename Name, typename Surname>
	Student(Name && name, Surname && surname)
		: m_name(forward<Name>(name))
		, m_surname(forward<Surname>(surname))
	{}

	const string & GetName()const &
	{
		return m_name;
	}

	string GetName() &&
	{
		return move(m_name);
	}

	const string & GetSurname()const &
	{
		return m_surname;
	}

	string GetSurname() &&
	{
		return move(m_surname);
	}
private:
	string m_name;
	string m_surname;
};

void PrintStudentInfo(const Student & student)
{
	cout << student.GetName() << " " << student.GetSurname() << endl;
}

Student CreateStudent()
{
	string name, surname;
	cout << "Enter student's name: ";
	cin >> name;
	cout << "Enter student's surname: ";
	cin >> surname;
	return Student(name, surname);
}

int main()
{
	string vasya = "Vasya";
	Student student(vasya, "Pupkin");
	PrintStudentInfo(student);


	auto & name0 = student.GetName();

	auto & name = CreateStudent().GetName();
	cout << "name: " << name << endl;
	cout << "name: " << name << endl;
	return 0;
}