#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <boost/range/algorithm/remove.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm/copy.hpp>

using namespace std;
int main()
{
	auto Quote = [](const string& s) {
		return "\"" + s + "\"";
	};

	{
		vector<string> animals = {"cat", "dog", "mouse", "dog", "whale", "bee", "ant"};
		cout << "Animals: ";
		transform(animals.begin(), animals.end(), ostream_iterator<string>(cout, ", "), Quote);
		cout << endl;

		cout << "Animals after removing all dogs: ";
		// алгоритм remove не удаляет элементы физически (т.к. не знает ничего о контейнере), 
		// а лишь перемещает на место убранных следующие за ними
		// возвращается итератор, указывающий на последний не убранный элемент
		auto newEnd = remove(animals.begin(), animals.end(), "dog");
		transform(animals.begin(), animals.end(), ostream_iterator<string>(cout, ", "), Quote);
		cout << endl;

		// Для фактического удаления нужно вызвать метод erase у контейнера
		animals.erase(newEnd, animals.end());

		cout << "Animals after erase: ";
		transform(animals.begin(), animals.end(), ostream_iterator<string>(cout, ", "), Quote);
		cout << endl;

		// Идиома erase-remove
		animals.erase(remove(animals.begin(), animals.end(), "whale"), animals.end());
		cout << "Animals after erase-removing a whale: ";
		transform(animals.begin(), animals.end(), ostream_iterator<string>(cout, ", "), Quote);
		cout << endl;
	}

	{
		vector<int> numbers = {3, 8, -4, 2, 15, -16, 7, 4, 0, 5};
		cout << "Numbers: ";
		copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, ", "));
		cout << endl;

		// Удаление всех отрицательных чисел
		numbers.erase(remove_if(numbers.begin(), numbers.end(), [](int x){ return x < 0; }), numbers.end());
		cout << "Numbers after erase-removing all negatives: ";
		copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, ", "));
		cout << endl;
	}

	{
		cout << endl << "Erase-remove using boost" << endl;
		vector<string> animals = { "cat", "dog", "mouse", "dog", "whale", "bee", "ant" };
		cout << "Animals: ";
		boost::transform(animals, ostream_iterator<string>(cout, ", "), Quote);
		cout << endl;

		cout << "Animals after erase-removing all dogs: ";
		animals.erase(boost::remove(animals, "dog"), animals.end());
		boost::transform(animals, ostream_iterator<string>(cout, ", "), Quote);
		cout << endl;
	}
	return 0;
}