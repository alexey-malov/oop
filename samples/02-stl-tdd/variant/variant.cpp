#include <iostream>
#include <variant>

template <class... Ts>
struct overloaded : Ts...
{
	using Ts::operator()...;
};

// explicit deduction guide (не требуется, начиная с C++20)
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

using Number = std::variant<int, double>;

void Print(Number x)
{
	std::visit(
		overloaded{
			[](int i) { std::cout << "Int " << i << "\n"; },
			[](double d) { std::cout << "Double " << d << "\n"; },
		},
		x);
}

Number Add(Number x, Number y)
{
	return std::visit(
		overloaded{
			[](auto x, auto y) -> Number { return x + y; },
		},
		x, y);
}

struct SpaceShip
{
};
struct Rocket
{
};
struct Asteroid
{
};

using GameObject = std::variant<SpaceShip, Rocket, Asteroid>;

namespace detail
{
struct Collider
{
	void operator()(SpaceShip& obj1, SpaceShip& obj2) { std::cout << "SpaceShip vs SpaceShip\n"; }
	void operator()(SpaceShip& obj1, Rocket& obj2) { std::cout << "SpaceShip vs Rocket\n"; }
	void operator()(SpaceShip& obj1, Asteroid& obj2) { std::cout << "SpaceShip vs Asteroid\n"; }
	void operator()(Rocket& obj1, Rocket& obj2) { std::cout << "Rocket vs Rocket\n"; }
	void operator()(Rocket& obj1, Asteroid& obj2) { std::cout << "Rocket vs Asteroid\n"; }
	void operator()(Asteroid& obj1, Asteroid& obj2) { std::cout << "Asteroid vs Asteroid\n"; }
	void operator()(auto& obj1, auto& obj2) { (*this)(obj2, obj1); }
};
} // namespace detail

void Collide(GameObject& obj1, GameObject& obj2)
{
	detail::Collider collider;
	std::visit(collider, obj1, obj2);
}

int main()
{
	Print(10); // Int 10
	Print(10.5); // Double 10.5
	Print(Add(30, 12)); // Int 42
	Print(Add(10, 12.5)); // Double 22.5

	GameObject obj1 = SpaceShip{};
	GameObject obj2 = Rocket{};
	Collide(obj1, obj2); // SpaceShip vs Rocket
	Collide(obj2, obj1); // SpaceShip vs Rocket
}
