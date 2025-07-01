module;
#include <string>

module person;

Person::Person(std::string name, int age)
	: m_name(std::move(name))
	, m_age(age)
{
}

const std::string& Person::GetName() const
{
	return m_name;
}

int Person::GetAge() const
{
	return m_age;
}
