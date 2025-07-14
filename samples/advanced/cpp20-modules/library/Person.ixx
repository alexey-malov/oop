// Это начало global module fragment, в котором можно разместить
// директивы #include, для которых недоступно импортирование заголовков.
module;

// Здесь подключаем те заголовки, которые нужны для компиляции содержимого .ixx файла.
#include <iostream>
#include <string>

// Это начало module interface unit модуля person.
export module person;

export enum class Gender
{
	Male,
	Female
};

export inline std::ostream& operator<<(std::ostream& out, Gender g)
{
	return out << ((g == Gender::Male) ? "male" : "female");
}

// Класс Person будет экспортирован из модуля person.
export class Person
{
public:
	Person(std::string name, int age);

	const std::string& GetName() const;

	int GetAge() const;

	Gender GetGender() const { return m_gender; }

private:
	std::string m_name;
	Gender m_gender = Gender::Male;
	int m_age;
};