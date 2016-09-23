#include <vector>
#include <iostream>
#include <string>

using namespace std;

void Test1()
{
	vector<int> numbers;
	numbers.push_back(42);
	numbers.push_back(99);
	numbers.insert(numbers.begin(), 7);

	for (size_t i = 0; i < numbers.size(); ++i)
	{
		cout << numbers[i] << ", ";
	}
	cout << endl;

	for (int x : numbers)
	{
		cout << x << ", ";
	}
	cout << endl;

	cout << "----------" << endl;

	for (int & x : numbers)
	{
		x = x + 1;
	}
	for (int x : numbers)
	{
		cout << x << ", ";
	}
	cout << endl;

	cout << "----------" << endl;

	numbers.resize(10);
	for (int x : numbers)
	{
		cout << x << ", ";
	}
	cout << endl;
}

struct Point
{
	int x, y;
};

struct PointDbl
{
	double x, y;
};

void main()
{
	Test1();

	vector<Point> points = { 
		{0, 0}, {20, 10}, {30, 30} 
	};

	for (auto & pt : points)
	{
		cout << pt.x << ", " << pt.y << endl;
	}

	PointDbl center = {0, 0};
	for (auto & pt : points)
	{
		center.x += pt.x;
		center.y += pt.y;
	}
	center.x /= points.size();
	center.y /= points.size();

	cout << center.x << ", " << center.y << endl;
}