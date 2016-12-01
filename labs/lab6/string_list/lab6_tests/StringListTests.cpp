#include "stdafx.h"
#include "../lab6/StringList.h"

using namespace std;

struct EmptyStringList
{
	CStringList list;
};

BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)
	BOOST_AUTO_TEST_SUITE(when_created)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(list.GetSize(), 0u);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_appeding_a_string)
		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.GetSize();
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			list.Append("goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "goodbye");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.Append("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(iterator)
		BOOST_AUTO_TEST_CASE(can_be_increnenting)
		{
			list.Append("first");
			list.Append("second");
			auto iter = list.begin();
			BOOST_CHECK_EQUAL(*iter, "first");
			++iter;
			BOOST_CHECK_EQUAL(*iter, "second");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()