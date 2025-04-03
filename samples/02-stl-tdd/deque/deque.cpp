#include <deque>
#include <string>
#include <iostream>


int main()
{
	std::deque<std::string> tasks;

	tasks.push_back("Eat");
	tasks.push_back("Love");
	tasks.push_back("Pray");

	while (!tasks.empty())
	{
		std::cout << "Executing task: " << tasks.front() << "\n";
		tasks.pop_front();
	}
}
