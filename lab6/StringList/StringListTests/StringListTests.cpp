#include "stdafx.h"
#include <vector>
#include <string>
#include "../StringList/CStringList.h"

struct StringList
{
	CStringList list;
	CStringList baseList;

	StringList()
	{
		baseList.Append("hello");
		baseList.Append("world");
	}
};

BOOST_FIXTURE_TEST_SUITE(String_list, StringList)

	BOOST_AUTO_TEST_CASE(has_default_constructor)
	{
		BOOST_CHECK(list.IsEmpty());
	}
	
	BOOST_AUTO_TEST_CASE(has_copy_constructor)
	{
		auto copyList(baseList);
		BOOST_CHECK_EQUAL(copyList.GetSize(), 1);
		BOOST_CHECK(copyList == baseList);
	}

	BOOST_AUTO_TEST_CASE(has_move_constructor)
	{
		auto moveList = std::move(baseList);
		BOOST_CHECK_EQUAL(moveList.GetSize(), 2);
		BOOST_CHECK(moveList.GetBackElement == "world");
		BOOST_CHECK(baseList.IsEmpty());
		BOOST_CHECK(baseList == CStringList());
	}

	BOOST_AUTO_TEST_SUITE(after_appending_element)
		BOOST_AUTO_TEST_CASE(increase_size)
		{
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), 1);
			list.Append("world");
			BOOST_CHECK_EQUAL(list.GetSize(), 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
