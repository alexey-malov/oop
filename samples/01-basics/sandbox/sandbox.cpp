#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

void SortWithIterators()
{
	int array[5] = { 3, 5, 1, 7, 9 };

	// Сортируем масссив по возрастанию
	std::sort(std::begin(array), std::end(array));

	// Сортируем по убыванию
	std::sort(std::begin(array), std::end(array), std::greater<int>());
}

void SortUsingRanges()
{
	int array[5] = { 3, 5, 1, 7, 9 };

	std::ranges::sort(array);
	std::ranges::sort(array, std::greater<int>());
}

int main1()
{
	int array[5] = { 3, 5, 1, 7, 9 };

	// Сортируем масссив по возрастанию
	std::sort(std::begin(array), std::end(array));

	// Сортируем по убыванию
	std::sort(std::begin(array), std::end(array), std::greater<int>());

	return 0;
}

#include <algorithm>
#include <functional>
#include <string>

struct Student
{
	std::string name;
	int age;
};

int main() {
	Student students[] = {
		{ "Ivan", 20 },
		{ "Alexey", 21 },
		{ "Sergey", 19 },
	};

	std::ranges::sort(students, {}, &Student::name); // Alexey, Ivan, Sergey
	std::ranges::sort(students, {}, &Student::age); // Sergey, Ivan, Alexey
	std::ranges::sort(students, std::greater<>(), &Student::age); // Alexey, Ivan, Sergey

	return 0;
}
