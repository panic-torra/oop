#include "stdafx.h"
#include "../HTTP_URL/CHttpUrl.h"

BOOST_AUTO_TEST_SUITE(CHttpUrl_)
	BOOST_AUTO_TEST_CASE(can_assign_url_by_string_method)
	{
		CHttpUrl googleUrl("http://www.google./index.html");
		BOOST_REQUIRE_THROW(googleUrl, std::invalid_argument);

	}
BOOST_AUTO_TEST_SUITE_END()