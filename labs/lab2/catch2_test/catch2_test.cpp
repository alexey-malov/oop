// catch2_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include <iostream>
#include <vector>

TEST_CASE("vector comparison")
{
	using namespace Catch::literals;
	std::vector<double> v1{1, 0.3, 3.5};	
	std::vector<double> v2{ 1, 0.2 + 0.1, 3.5 };
	CHECK_THAT(v1, Catch::Approx(v1));
}
