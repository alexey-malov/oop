// constructors.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

class Student
{
public:
	explicit Student(string name)
		: m_name(move(name))
	{
	}

	Student(const Student& other) = delete;

	Student(Student&& other) = delete;

	void AddFriend(weak_ptr<Student> student)
	{
		m_friends.push_back(move(student));
	}

private:
	string m_name;
	vector<weak_ptr<Student>> m_friends;
};

int main()
{
	Student student("Ivan");
}

