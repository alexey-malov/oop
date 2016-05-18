#include "stdafx.h"
#include "MyArray.h"

using namespace std;

struct ArrayItem
{

};

struct EmptyStringArray
{
	CMyArray<ArrayItem> arr;
};

BOOST_FIXTURE_TEST_SUITE(MyArray, EmptyStringArray)
	BOOST_AUTO_TEST_CASE(is_empty_by_default)
	{
		BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
	}
	BOOST_AUTO_TEST_CASE(has_0_capacity)
	{
		BOOST_CHECK_EQUAL(arr.GetCapacity(), 0u);
	}
BOOST_AUTO_TEST_SUITE_END()