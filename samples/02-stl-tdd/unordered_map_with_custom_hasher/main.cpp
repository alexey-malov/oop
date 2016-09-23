#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct Point
{
	int x;
	int y;
};
// Структура с перегруженным оператором (), позволяющая вычислить хеш-значение
// для заданной структуры person
// Она необходима для использования Point в качестве ключей в unordered map
struct PointHasher
{
	size_t operator()(const Point& pt)const
	{
		return hash<int>()(pt.x) ^ hash<int>()(pt.y);
	}
};
// Оператор сравнения, позволяющий сравнивать структуры типа Point
// он необходим для использования Point в качестве ключей в unordered map
bool operator==(const Point& pt1, const Point& pt2)
{
	return pt1.x == pt2.x && pt1.y == pt2.y;
}

void main()
{
	// отображение Point в string, позволяющее узнать название объекта
	// на картинке, соответствующее точке в заданных координатах
	unordered_map<Point, string, PointHasher> pointDescriptions;
	
	pointDescriptions.emplace(Point{10, 20}, "apple");
	pointDescriptions[{11, 20}] = "apple";

	cout << pointDescriptions.at({ 10, 20 }) << endl; // apple

	auto it = pointDescriptions.find({ 11, 34 });
	if (it != pointDescriptions.end()) // вернет false
	{
		cout << it->second << endl;
	}
	else
	{
		cout << "No point description at {11, 34}" << endl;
	}
}