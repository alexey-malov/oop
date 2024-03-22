// constructors.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <memory>
#include <string>
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

class TV
{
public:
	void TurnOn() { /* ... */ }
};

class RemoteControl
{
public:
	RemoteControl(TV& tv, std::istream& input, std::ostream& output)
		: m_tv{ tv }
		, m_input{input}
		, m_output{output}
	{
	}

	bool ExecuteCommand() const
	{
		std::string command;
		std::getline(m_input, command);
		if (command == "TurnOn")
		{
			m_tv.TurnOn();
			m_output << "TV is turned on" << std::endl;
			return true;
		}
		return false; // Команда не найдена
	}

private:
	TV& m_tv;
	std::istream& m_input;
	std::ostream& m_output;
};

int main()
{
	TV tv;
	RemoteControl remoteControl{ tv, std::cin, std::cout };
	remoteControl.ExecuteCommand();
}
