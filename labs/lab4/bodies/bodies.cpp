// bodies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sphere.h"

void AddSphere(std::vector<std::unique_ptr<CBody>>& bodies)
{
	auto s = std::make_unique<CSphere>(1000.0, 1.0);
	bodies.push_back(std::move(s));
}


int main()
{
	std::vector<std::unique_ptr<CBody>> bodies;
	AddSphere(bodies);
	std::cout << bodies.front()->ToString() << std::endl;
	return 0;
}
