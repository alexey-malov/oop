// Countable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template <typename T>
class Countable
{
public:
	static size_t GetInstanceCount() noexcept { return m_instanceCount; }

	Countable& operator=(const Countable&) = default;
	Countable& operator=(Countable&&) = default;

protected:
	Countable() noexcept { ++m_instanceCount; }
	Countable(const Countable&) noexcept
		: Countable()
	{
	}
	Countable(Countable&&) noexcept
		: Countable()
	{
	}
	~Countable() { --m_instanceCount; }

private:
	inline static size_t m_instanceCount = 0;
};

class Cat : public Countable<Cat>
{
};

class Dog : public Countable<Dog>
{
};

int main()
{
	std::cout << "Cats: " << Cat::GetInstanceCount() << "\n";
	std::cout << "Dogs: " << Dog::GetInstanceCount() << "\n";
	{
		Cat cat1, cat2;
		Dog dog;

		std::cout << "Cats: " << Cat::GetInstanceCount() << "\n";
		std::cout << "Dogs: " << Dog::GetInstanceCount() << "\n";

		{
			Dog anotherDog(dog); // Copy dog into anotherDog
			std::cout << "Dogs: " << Dog::GetInstanceCount() << "\n";
		}
	}
	std::cout << "Cats: " << Cat::GetInstanceCount() << "\n";
	std::cout << "Dogs: " << Dog::GetInstanceCount() << "\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
