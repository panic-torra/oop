#include "stdafx.h"
#include "../HTTP_URL/CHttpUrl.h"
#include "../HTTP_URL/CUrlParsingError.h"

BOOST_AUTO_TEST_SUITE(CHttpUrl_)
	BOOST_AUTO_TEST_SUITE(can_parse_protocol)
		BOOST_AUTO_TEST_CASE(with_mistakes)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("htp://www.google.com/"), CUrlParsingError);
			BOOST_REQUIRE_THROW(CHttpUrl url("krya/www.goole.com/"), CUrlParsingError);
		}
		
		BOOST_AUTO_TEST_CASE(without_mistakes)
		{
			CHttpUrl urlHttp("http://www.google.com/");
			BOOST_CHECK_EQUAL(urlHttp.ProtocolToStr(), "http");

			CHttpUrl urlHttps("https://www.google.com/");
			BOOST_CHECK_EQUAL(urlHttps.ProtocolToStr(), "https");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_parse_domain_name)
		BOOST_AUTO_TEST_CASE(with_mistakes)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("http://www.googl e.com/"), CUrlParsingError);
			BOOST_REQUIRE_THROW(CHttpUrl url("http:///"), CUrlParsingError);
		}

		BOOST_AUTO_TEST_CASE(without_mistakes)
		{
			{
				CHttpUrl url("http://www.google.com/index.php");
				BOOST_CHECK_EQUAL(url.GetDomain(), "www.google.com");
			}
			{			
				CHttpUrl url("https://google.com/");
				BOOST_CHECK_EQUAL(url.GetDomain(), "google.com");
			}
			{
				CHttpUrl url("https://domain");
				BOOST_CHECK_EQUAL(url.GetDomain(), "domain");
			}

		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()