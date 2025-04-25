#include <vector>
#include <memory>
#include <cassert>

class Shape
{
public:
	// Публичный виртуальный деструктор позволит безопасно
	// удалять наследников, используя указатель на класс Shape.
	virtual ~Shape() = default;
	void SetColor(uint32_t color) { m_color = color; }
	uint32_t GetColor() const { return m_color; }

protected:
	Shape(uint32_t color)
		: m_color{ color }
	{
	}

private:
	uint32_t m_color = 0;
};
class Circle : public Shape
{
public:
	Circle(double r, uint32_t color)
		: Shape{ color }
		, m_radius{ r }
	{
	} // Так как деструктор родителя виртуальный,
	// он остаётся виртуальным и в Circle
private:
	double m_radius;
};

class Rectangle : public Shape
{
public:
	Rectangle(double w, double h, uint32_t color)
		: Shape{ color }
		, m_width{ w }
		, m_height{ h }
	{
	}

private:
	double m_width;
	double m_height;
};

int main()
{
	// Создаём в куче окружность
	std::unique_ptr<Circle> c = std::make_unique<Circle>(10, 0xFF00FF);
	std::unique_ptr<Rectangle> r = std::make_unique<Rectangle>(10, 20, 0xFF00FF);

	std::vector<std::unique_ptr<Shape>> shapes;
	shapes.push_back(std::move(c));
	shapes.push_back(std::move(r));

	// При разрушении векторов, все указатели на Shape будут разрушены и удалять объекты в куче
}

void SharedPtrCollection()
{
	std::vector<std::shared_ptr<Shape>> shapes;
	auto c = std::make_shared<Circle>(10, 0xFF00FF);
	auto r = std::make_shared<Rectangle>(10, 20, 0xFF00FF);
	shapes.push_back(c);
	shapes.push_back(r);

	assert(shapes[0] == c);
}