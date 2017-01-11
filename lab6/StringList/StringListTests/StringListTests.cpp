#include "stdafx.h"
#include "../StringList/CStringList.h"

struct StringList
{
	CStringList list;
	CStringList baseList;
	std::vector<std::string> expectedStringVector;

	StringList()
	{
		baseList.Append("hello");
		baseList.Append("world");
		baseList.Append("!");
		expectedStringVector.push_back("hello");
		expectedStringVector.push_back("world");
		expectedStringVector.push_back("!");
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
		BOOST_CHECK_EQUAL(copyList.GetSize(), 3);
		VerifyStringList(copyList, expectedStringVector);
	}

	BOOST_AUTO_TEST_CASE(has_move_constructor)
	{
		auto moveList = std::move(baseList);
		BOOST_CHECK_EQUAL(moveList.GetSize(), 3);
		BOOST_CHECK_EQUAL(moveList.GetBackElement(), "!");
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
			BOOST_CHECK(list.rbegin() == CStringList::CIterator(nullptr, true));
			BOOST_CHECK(list.rend() == CStringList::CIterator(nullptr, true));
			BOOST_CHECK(list.crbegin() == CStringList::CIterator(nullptr, true));
			BOOST_CHECK(list.crend() == CStringList::CIterator(nullptr, true));
		}
	
	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_CASE(can_push_back)
	{
		list.Append("hello");
		BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
		list.Append("world");
		BOOST_CHECK_EQUAL(list.GetBackElement(), "world");
	}

	BOOST_AUTO_TEST_CASE(can_push_front)
	{
		list.PushFront("hello");
		BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
		list.PushFront("world");
		BOOST_CHECK_EQUAL(list.GetFrontElement(), "world");
	}

	BOOST_AUTO_TEST_CASE(can_insert_element_by_iterator)
	{
		auto it = ++baseList.begin();
		baseList.Insert(it, "surprise");
		BOOST_CHECK_EQUAL(*++baseList.begin(), "surprise");

		it = baseList.begin()++;
		baseList.Insert(it, "first_surprise");
		BOOST_CHECK_EQUAL(*baseList.begin()++, "first_surprise");

		baseList.Insert(baseList.end(), "bye-bye");

		std::vector<std::string> expectedStrings = { "first_surprise", "hello", "surprise", "world", "!", "bye-bye" };
		size_t i = 0;
		for (auto str : baseList)
		{
			BOOST_CHECK_EQUAL(str, expectedStrings[i]);
			i++;
		}
	}

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

		BOOST_AUTO_TEST_CASE(can_use_GetBackElement_and_GetFrontElement_methods)
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

		BOOST_AUTO_TEST_CASE(can_get_access_to_elements_from_range_based_for)
		{
			size_t counter = 0;
			for (auto str : baseList)
			{
				BOOST_CHECK_EQUAL(str, expectedStringVector[counter]);
				counter++;
			}
		}

		BOOST_AUTO_TEST_CASE(can_erase_element_by_iterator)
		{
			{
				BOOST_REQUIRE_THROW(list.Erase(list.begin()), std::out_of_range);
				auto it = ++baseList.begin();
				baseList.Erase(it);
				VerifyStringList(baseList, { "hello", "!" });
				baseList.Erase(baseList.end());
				VerifyStringList(baseList, { "hello" });
				baseList.Erase(baseList.begin());
				BOOST_CHECK(baseList.IsEmpty());
			}
		}

		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			baseList.Clear();
			VerifyStringList(baseList, {});
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
