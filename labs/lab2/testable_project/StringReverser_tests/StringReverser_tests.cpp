// StringReverser_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"

#include "Reverse.h"

int MaxOf3(int a, int b, int c)
{
	if (a > b)
	{
		if (c > a)
		{
			return c;
		}
		return a;
	}
	else // b >= a
	{
		if (c > b)
		{
			return c;
		}
		return b;
	}
}

TEST_CASE("MaxOf3")
{
	CHECK(MaxOf3(1, 3, 8) == 8);
	CHECK(MaxOf3(3, 1, 8) == 8);
	CHECK(MaxOf3(8, 3, 5) == 8);
	CHECK(MaxOf3(3, 5, 4) == 5);
}

SCENARIO("Reversing of empty string gives an empty string")
{
	REQUIRE(Reverse("").empty());
}

SCENARIO("Reverse of string of 1 character is the string itself")
{
	REQUIRE(Reverse("a") == "a");
}

SCENARIO("Reverse of string longer than 1 character")
{
	REQUIRE(Reverse("1234") == "4321");
}

SCENARIO("ReverseLines")
{
	std::ostringstream output;
	WHEN("input stream is empty")
	{
		std::istringstream input("");
		THEN("output stream is also empty")
		{
			ReverseLines(input, output);
			CHECK(output.str().empty());
			CHECK(input.eof());
		}
	}

	WHEN("input stream contains one line")
	{
		std::istringstream input("1 line");
		THEN("output stream contains the line reversed")
		{
			ReverseLines(input, output);
			CHECK(output.str() == "enil 1");
			CHECK(input.eof());
		}
	}

	WHEN("input stream contains several lines")
	{
		std::istringstream input("1 line\n2 line");
		THEN("output stream contains the line reversed")
		{
			ReverseLines(input, output);
			CHECK(output.str() == "enil 1\nenil 2");
			CHECK(input.eof());
		}
	}

	WHEN("input stream contains EOL in the end")
	{
		std::istringstream input("1 line\n2 line\n");
		THEN("output stream contains EOL is the end as well")
		{
			ReverseLines(input, output);
			CHECK(output.str() == "enil 1\nenil 2\n");
			CHECK(input.eof());
		}
	}

	WHEN("input stream contains empty lines")
	{
		std::istringstream input("1 line\n\nlast line");
		THEN("output stream contains empty lines as well")
		{
			ReverseLines(input, output);
			CHECK(output.str() == "enil 1\n\nenil tsal");
			CHECK(input.eof());
		}
	}
}
