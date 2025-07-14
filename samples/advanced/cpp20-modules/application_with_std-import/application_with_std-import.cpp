import std;
import person;
import library;

int main()
{
	Person person{ "John Doe", 30 };
	Book book("Book title", person.GetName());

	auto gender = person.GetGender();
	std::cout << gender << std::endl;
}
