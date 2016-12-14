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

	BOOST_AUTO_TEST_SUITE(can_parse_domain)
		BOOST_AUTO_TEST_CASE(with_mistakes)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("http://www.googl e.com/"), std::invalid_argument);
			BOOST_REQUIRE_THROW(CHttpUrl url("http:///"), std::invalid_argument);
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

	BOOST_AUTO_TEST_SUITE(can_parse_port)
		BOOST_AUTO_TEST_CASE(with_mistakes)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("http://google.com: /"), CUrlParsingError);
		}

		BOOST_AUTO_TEST_CASE(without_mistakes)
		{
			{
				CHttpUrl url("http://google.com/");
				BOOST_CHECK_EQUAL(url.GetPort(), 80);
			}
			{
				CHttpUrl url("http://google.com:120/");
				BOOST_CHECK_EQUAL(url.GetPort(), 120);
			}

			{
				CHttpUrl url("http://google.com:430/");
				BOOST_CHECK_EQUAL(url.GetPort(), 430);
			}
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_parse_document_path)
		BOOST_AUTO_TEST_CASE(with_mistakes)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("http://www.google.com/i mage"), std::invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(without_mistakes)
		{
			{
				CHttpUrl url("http://www.google.com/index.php");
				BOOST_CHECK_EQUAL(url.GetDocumentPath(), "/index.php");
			}
			{
				CHttpUrl url("https://google.com/img/bg.png");
				BOOST_CHECK_EQUAL(url.GetDocumentPath(), "/img/bg.png");
			}
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_return_full_url)
		BOOST_AUTO_TEST_CASE(by_str)
		{
			{
				CHttpUrl url("http://www.google.com/index.php");
				BOOST_CHECK_EQUAL(url.GetURL(), "http://www.google.com:80/index.php");
			}
			{
				CHttpUrl url("https://www.google.com/index.php");
				BOOST_CHECK_EQUAL(url.GetURL(), "https://www.google.com:443/index.php");
			}
			{
				CHttpUrl url("https://google.com:452/src/img/image.png");
				BOOST_CHECK_EQUAL(url.GetURL(), "https://google.com:452/src/img/image.png");
			}
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_return_full_url)
		BOOST_AUTO_TEST_SUITE(by_objects)
		
			BOOST_AUTO_TEST_CASE(with_mistakes)
			{
				BOOST_REQUIRE_THROW(CHttpUrl url("www.google. m", "src/image.png", Protocol::HTTP, 15), std::invalid_argument);
				BOOST_REQUIRE_THROW(CHttpUrl url("www.google.com", "src/ima ge.png", Protocol::HTTPS, 42), std::invalid_argument);
			}

			BOOST_AUTO_TEST_CASE(without_mistakes)
			{
				{
					CHttpUrl url("google.com", "src/img/image.png", Protocol::HTTPS, 452);
					BOOST_CHECK_EQUAL(url.GetURL(), "https://google.com:452/src/img/image.png");
				}
				{
					CHttpUrl url("google.com/", "/src/img/image.png", Protocol::HTTP, 42);
					BOOST_CHECK_EQUAL(url.GetURL(), "http://google.com:42/src/img/image.png");
				}
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()