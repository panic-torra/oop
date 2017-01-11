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

void VerifyStringList(CStringList const & list, std::vector<std::string> const & expectedStrings)
{
	BOOST_CHECK_EQUAL(list.GetSize(), expectedStrings.size());

	size_t expectedStringPos = 0;
	for (auto it = list.cbegin(); it != list.cend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedStrings[expectedStringPos]);
		expectedStringPos++;
	}
}

BOOST_FIXTURE_TEST_SUITE(String_list, StringList)
	BOOST_AUTO_TEST_CASE(has_default_constructor)
	{
		BOOST_CHECK(list.IsEmpty());
	}
	
	BOOST_AUTO_TEST_CASE(has_copy_constructor)
	{
		auto copyList(baseList);
		BOOST_CHECK_EQUAL(copyList.GetSize(), 2);
		VerifyStringList(copyList, { "hello", "world" });
	}

	BOOST_AUTO_TEST_CASE(has_move_constructor)
	{
		auto moveList = std::move(baseList);
		BOOST_CHECK_EQUAL(moveList.GetSize(), 2);
		//BOOST_CHECK(moveList.GetBackElement == "world");
		BOOST_CHECK(baseList.IsEmpty());
		VerifyStringList(baseList, {});
	}

	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK(list.IsEmpty());
			BOOST_CHECK_EQUAL(list.GetSize(), 0);
		}

		BOOST_AUTO_TEST_CASE(all_iterators_point_at_nullptr)
		{
			BOOST_CHECK(list.begin() == CStringList::CIterator(nullptr));
			BOOST_CHECK(list.end() == CStringList::CIterator(nullptr));
			BOOST_CHECK(list.cbegin() == CStringList::CIterator(nullptr));
			BOOST_CHECK(list.cend() == CStringList::CIterator(nullptr));
			BOOST_CHECK(list.rbegin() == CStringList::CIterator(nullptr));
			BOOST_CHECK(list.rend() == CStringList::CIterator(nullptr));
			BOOST_CHECK(list.crbegin() == CStringList::CIterator(nullptr));
			BOOST_CHECK(list.crend() == CStringList::CIterator(nullptr));
		}
	
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_appending_element)
		BOOST_AUTO_TEST_CASE(increase_size)
		{
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), 1);
			list.Append("world");
			BOOST_CHECK_EQUAL(list.GetSize(), 2);
			list.PushFront("first");
			BOOST_CHECK_EQUAL(list.GetSize(), 3);
		}

		BOOST_AUTO_TEST_CASE(element_can_be_taken_by_get_methods)
		{
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			list.Append("world");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "world");
			list.PushFront("first");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "first");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "world");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
