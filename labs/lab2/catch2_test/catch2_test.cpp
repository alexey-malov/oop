// catch2_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

TEST_CASE("vector comparison")
{
	using namespace Catch::literals;
	std::vector<double> v1{ 1, 0.3, 3.5 };
	std::vector<double> v2{ 1, 0.2 + 0.1, 3.5 };
	CHECK_THAT(v1, Catch::Approx(v1));
}

class Student
{
public:
	explicit Student(const std::string& name)
		: m_name(name)
	{
	}

	const std::string& GetName() const { return m_name; }
	const std::string& GetCourse() const { return m_course; }

	void SetCourse(const std::string& course)
	{
		m_course = course;
	}

	std::optional<int> TryGetMark() const
	{
		return m_course.empty() ? std::optional<int>{} : m_mark;
	}

private:
	std::string m_name;
	std::string m_course;
	int m_mark = 0;
};

struct StudentFixture
{
	Student student1{ "Vasily" };
	Student student2{ "Peter" };
};

TEST_CASE_METHOD(StudentFixture, "student has name")
{
	// Внутри этого тест-кейса мне доступны переменные из структуры StudentFixture
	CHECK(student1.GetName() == "Vasily");
	CHECK(student2.GetName() == "Peter");
}

TEST_CASE_METHOD(StudentFixture, "student has no course by default")
{
	CHECK(student1.GetCourse().empty());
}

TEST_CASE_METHOD(StudentFixture, "student can attend courses")
{
	WHEN("student attends cours")
	{
		student1.SetCourse("math");

		THEN("its GetCourseMethod returns attended course")
		{
			CHECK(student1.GetCourse() == "math");
		}
	}
}

TEST_CASE_METHOD(StudentFixture, "students who dont attend course have no mark")
{
	REQUIRE(student1.GetCourse().empty());
	CHECK_FALSE(student1.TryGetMark().has_value());
}

struct StudentWithCourseFixture : public StudentFixture
{
	// Сперва отработает конструктор StudentFixture,
	// а потом, в конструкторе StudentWithCourseFixture мы донастроим объекты
	StudentWithCourseFixture()
	{
		student1.SetCourse("math");
	}
};

TEST_CASE_METHOD(StudentWithCourseFixture, "student attending a course has a mark")
{
	REQUIRE(!student1.GetCourse().empty());
	CHECK(student1.TryGetMark() == 0);
}