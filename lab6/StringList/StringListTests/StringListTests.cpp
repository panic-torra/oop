#include "stdafx.h"
#include <vector>
#include <string>
#include "../StringList/CStringList.h"

struct EmptyStringList
{
	CStringList list;
};

BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)

	BOOST_AUTO_TEST_CASE(has_default_constructor)
	{
		BOOST_CHECK(list.empty());
	}
	BOOST_AUTO_TEST_SUITE(after_appending_element)
		BOOST_AUTO_TEST_CASE(increase_size)
		{
			list.append("hello");
			BOOST_CHECK_EQUAL(list.size(), 1);
			list.append("world");
			BOOST_CHECK_EQUAL(list.size(), 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
