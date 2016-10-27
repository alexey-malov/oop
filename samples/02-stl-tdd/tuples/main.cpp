#include <tuple>
#include <string>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

struct UserInfo
{
	string name;
	string surname;
	int birthYear;
	double height;
};

ostream & operator << (ostream & out, const UserInfo & userInfo)
{
	return out << userInfo.name << " " << userInfo.surname << ", " << userInfo.birthYear << ", " << userInfo.height;
}

int main()
{
	{
		typedef tuple<string, int, double> MyTuple;
		MyTuple t1("user name", 42, 3.14159265);
		MyTuple t2("ivan petrov", 35, 9.7);
		MyTuple t3("user name", 42, 3.14159265);

		assert(t1 != t2);
		assert(t1 == t3);
		assert(t1 > t2);
	}

	
	{
		auto t1 = make_tuple("hello", "world", 15);
		// можно сконструировать один tuple из другого tuple (const char*, const char*, int)
		tuple<string, string, int> t2 = t1;
	}

	{
		enum class Gender {Male, Female};
		auto t1 = make_tuple("Ivanov Ivan", 1985, Gender::Male);
		
		string userName;
		Gender userGender;
		// tie создает tuple из ссылок на переменные userName, std::ignore и userGender
		// присваивание std::ignore любого значения не имеет эффекта
		// в оператор = выполняется присваиванием элементам левого tuple
		// элементов правого (с игнорированием года рождения)
		tie(userName, std::ignore, userGender) = t1;
		assert(userName == get<0>(t1));
		assert(userGender == get<2>(t1));
	}

	{
		UserInfo users[] = {
			{ "Ivan", "Alekseev", 1980, 170.5 },
			{ "Sergey", "Dmitriev", 1931, 160 },
			{ "Alexey", "Dmitriev", 1931, 160 },
			{ "Vladimir", "Monomach", 1950, 166.6 },
			{ "Vladimir", "Vysotsky", 1950, 166.6 },
			{ "Petr", "Pervy", 1999, 183.7 },
		};

		// сортируем в порядке Фамилия, Имя, возраст, рост
		sort(begin(users), end(users), [](const UserInfo & lhs, const UserInfo & rhs) {
			if (lhs.surname < rhs.surname)
			{
				return true;
			}
			else if (lhs.surname > rhs.surname)
			{
				return false;
			}
			// lhs.surname == rhs.surname

			if (lhs.name < rhs.name)
			{
				return true;
			}
			else if (lhs.name > rhs.name)
			{
				return false;
			}
			// lhs.name == rhs.name

			if (lhs.birthYear < rhs.birthYear)
			{
				return true;
			}
			else if (lhs.birthYear > rhs.birthYear)
			{
				return false;
			}
			// lhs.birthYear == rhs.birthYear
			return lhs.height < rhs.height;
		});

		copy(begin(users), end(users), ostream_iterator<UserInfo>(cout, "\n"));
		cout << "==============" << endl;

		sort(begin(users), end(users), [](const UserInfo & lhs, const UserInfo & rhs) {
			return
				tie(lhs.surname, lhs.name, lhs.birthYear, lhs.height) <
				tie(rhs.surname, rhs.name, rhs.birthYear, rhs.height);
		});
		copy(begin(users), end(users), ostream_iterator<UserInfo>(cout, "\n"));
		cout << "==============" << endl;

		sort(begin(users), end(users), [](const UserInfo & lhs, const UserInfo & rhs) {
			return
				tie(lhs.name, lhs.surname, lhs.birthYear, lhs.height) <
				tie(rhs.name, rhs.surname, rhs.birthYear, rhs.height);
		});
		copy(begin(users), end(users), ostream_iterator<UserInfo>(cout, "\n"));
		cout << "==============" << endl;

	}

	return 0;
}