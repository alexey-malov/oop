#include "stdafx.h"
#include "Utils.h"


/*
Год високосный
	если он делится на 4
	если при этом он не делится на 100
	но делится на 400
*/

BOOST_AUTO_TEST_SUITE(Leap_year)
	BOOST_AUTO_TEST_CASE(is_divisible_by_4)
	{
		BOOST_CHECK(IsLeapYear(2004));
		BOOST_CHECK(!IsLeapYear(2005));
		BOOST_CHECK(!IsLeapYear(2006));
		BOOST_CHECK(!IsLeapYear(2007));
	}
	BOOST_AUTO_TEST_CASE(if_it_is_not_divisible_by_100)
	{
		BOOST_CHECK(!IsLeapYear(1900));
	}
	BOOST_AUTO_TEST_CASE(is_divisible_by_400)
	{
		BOOST_CHECK(IsLeapYear(2000));
	}
BOOST_AUTO_TEST_SUITE_END()
