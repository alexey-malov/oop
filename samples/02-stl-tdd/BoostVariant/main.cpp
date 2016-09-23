#pragma warning(push)
#pragma warning(disable:4702) // unreachable code 
#include <boost/variant.hpp>
#pragma warning(pop)
#include <utility>
#include <array>
#include <iostream>

typedef std::pair<double, double> TwoRoos;
// С т.з. C++ структуры NoRealRoots и NotAQuadraticEquation являются разными типами
// поэтому мы можем их использовать для того, чтобы отличить отсутствие корней от 
// неквадратичности уравнения
struct NoRealRoots{};
struct NotAQuadraticEquation{};

// Допустимые значения, которые может принимать решение квадратного уравнения
// Хранится лишь одно из данных типов значений
typedef boost::variant<NoRealRoots, double, TwoRoos, NotAQuadraticEquation> QuadraticEquationSolution;

// Структура-наследник boost::static_visitor, выполняющая печать решения квадратного уравнения
struct QuadraticEquationSolutionPrinter : public boost::static_visitor<void>
{
	// Сохраняем ссылку на поток вывода, что даст возможность вывода
	// в произвольный поток-наследник ostream (ofstream, ostringstream и т.п.)
	QuadraticEquationSolutionPrinter(std::ostream & strm)
		:m_strm(strm)
	{}

	// Печать одного корня
	void operator() (double x)
	{
		m_strm << x << std::endl;
	}

	// Печать двух корней
	void operator() (TwoRoos roots)
	{
		m_strm << roots.first << "; " << roots.second << std::endl;
	}

	// Вывод результата "нет корней"
	void operator() (NoRealRoots)
	{
		m_strm << "No real roots" << std::endl;
	}

	// Вывод ошибки (не квадратное уравнение)
	void operator() (NotAQuadraticEquation)
	{
		m_strm << "Not a quadratic equation" << std::endl;
	}
private:
	std::ostream & m_strm;
};

// Решатель квадратного уравнения
QuadraticEquationSolution SolveQuadraticEquation(double a, double b, double c)
{
	(void)&a; (void)&b; (void)&c;
	// Напишите реализацию самостоятельно, возвращая одни из следующих результатов

	return NotAQuadraticEquation();
	//return NoRealRoots();
	//return std::make_pair(3.17, 17.8); // Two roots
	//return 42.0; // one root
}


int main()
{
	auto result = SolveQuadraticEquation(1, 2, 3);

	// Создаем объект, выполняющий печать в cout
	QuadraticEquationSolutionPrinter printer(std::cout);
	// Просим result вызвать оператор(), передав хранимое значение
	result.apply_visitor(printer);


	return 0;
}
