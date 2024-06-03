#include "Animals.h"
#include "HttpRequest.h"
#include "Shapes.h"
#include <memory>
#include <span>
#include <vector>

std::vector<std::unique_ptr<Shape>> CreateShapes()
{
	std::vector<std::unique_ptr<Shape>> shapes;

	shapes.push_back(std::make_unique<Circle>(20.0, 0xff0000));
	shapes.push_back(std::make_unique<Rectangle>(20.0, 30.0, 0xff00ff));

	return shapes;
}

void DrawPicture(const std::vector<const Drawable*>& picture)
{
	for (const auto* drawable : picture)
	{
		drawable->Draw();
	}
}

void PlayWithDrawables()
{
	// Вектор animals владеет животными. При его разрушении будут удалены животные.
	std::vector<std::unique_ptr<Animal>> animals;

	animals.push_back(std::make_unique<Cat>());
	animals.push_back(std::make_unique<Fish>());

	// Вектор picture не владеет своими drawable-объектами, так как хранит обычные указатели.
	// При разрушении picture не будут удалены drawable-объекты
	std::vector<const Drawable*> picture;
	for (auto& animal : animals)
	{
		// Animal* можно преобразовывать в const Drawable*, так как Animal — наследник Drawable.
		picture.push_back(animal.get());
	}

	const Robot robot;

	// Робот унаследован от Drawable, поэтому указатель const Robot* конвертируется в const Drawable*.
	picture.push_back(&robot);
	DrawPicture(picture);

	// Деструктор вектора animals удалит животных, а robot удалится сам.
}

void TestShapes()
{
	std::vector<std::unique_ptr<Shape>> shapes = CreateShapes();

	/* ... */

	// Деструктор класса vector безопасно удалит хранящиеся в нём
	// указатели unique_ptr, а каждый из указателей — свою фигуру.
	// Виртуальный деструктор класса Shape позволит безопасно
	// разрушить наследников Shape по указателю на базовый класс
}

int main()
{
	Print(PostRequest{
			  "/log_in",
			  {
				  { "Host", "example.com" },
				  { "Content-Type", "application/json" },
			  },
			  R"({"login": "john.doe", "password": "12345"})",
		  },
		std::cout);

	TestShapes();

	PlayWithDrawables();
}
