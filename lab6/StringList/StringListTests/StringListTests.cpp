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

BOOST_AUTO_TEST_SUITE_END()
