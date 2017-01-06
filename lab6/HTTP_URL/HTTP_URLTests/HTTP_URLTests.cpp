#include "stdafx.h"
#include "../HTTP_URL/CHttpUrl.h"
#include "../HTTP_URL/CUrlParsingError.h"

BOOST_AUTO_TEST_SUITE(CHttpUrl_)
	BOOST_AUTO_TEST_CASE(can_handle_url_with_errors_in_protocol)
	{
		BOOST_REQUIRE_THROW(CHttpUrl url("htp://www.google.com/"), CUrlParsingError);
		BOOST_REQUIRE_THROW(CHttpUrl url("krya/www.goose.com/"), CUrlParsingError);
	}
		
	BOOST_AUTO_TEST_CASE(can_parse_protocol)
	{
		{
			CHttpUrl urlHttp("http://www.google.com");
			BOOST_CHECK_EQUAL(ProtocolToStr(urlHttp.GetProtocol()), "http");

			CHttpUrl urlHttps("https://www.google.com");
			BOOST_CHECK_EQUAL(ProtocolToStr(urlHttps.GetProtocol()), "https");
		}
		{
			CHttpUrl urlHttp("http://www.google.com");
			BOOST_CHECK(urlHttp.GetProtocol() == Protocol::HTTP);

			CHttpUrl urlHttps("https://www.google.com");
			BOOST_CHECK(urlHttps.GetProtocol() == Protocol::HTTPS);
		}
	}

	BOOST_AUTO_TEST_CASE(can_handle_url_with_errors)
	{
		BOOST_REQUIRE_THROW(CHttpUrl url("http://www.googl e.com/"), std::invalid_argument);
		BOOST_REQUIRE_THROW(CHttpUrl url("http:///"), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(can_parse_domain)
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

	BOOST_AUTO_TEST_CASE(can_handle_url_with_errors_in_port)
	{
		BOOST_REQUIRE_THROW(CHttpUrl url("http://google.com: "), CUrlParsingError);
		BOOST_REQUIRE_THROW(CHttpUrl url("http://google.com:-8/"), CUrlParsingError);
		BOOST_REQUIRE_THROW(CHttpUrl url("http://google.com:0"), CUrlParsingError);
		BOOST_REQUIRE_THROW(CHttpUrl url("http://google.com:65536"), CUrlParsingError);
		BOOST_REQUIRE_THROW(CHttpUrl url("http://google.com:75536"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(can_parse_port)
	{
		{
			CHttpUrl url("http://google.com");
			BOOST_CHECK_EQUAL(url.GetPort(), 80);
		}

		{
			CHttpUrl url("http://google.com:65535");
			BOOST_CHECK_EQUAL(url.GetPort(), 65535);
		}
		{
			CHttpUrl url("http://google.com:120");
			BOOST_CHECK_EQUAL(url.GetPort(), 120);
		}

		{
			CHttpUrl url("http://google.com:430");
			BOOST_CHECK_EQUAL(url.GetPort(), 430);
		}
	}

	BOOST_AUTO_TEST_CASE(can_handle_url_with_errors_in_document_path)
	{
		BOOST_REQUIRE_THROW(CHttpUrl url("http://www.google.com/i mage"), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(can_parse_document_path)
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

	BOOST_AUTO_TEST_SUITE(can_return_full_url_by)
		BOOST_AUTO_TEST_CASE(str)
		{
			{
				CHttpUrl url("http://www.google.com/index.php");
				BOOST_CHECK_EQUAL(url.GetURL(), "http://www.google.com/index.php");
			}
			{
				CHttpUrl url("https://www.google.com/index.php");
				BOOST_CHECK_EQUAL(url.GetURL(), "https://www.google.com/index.php");
			}
			{
				CHttpUrl url("https://google.com:452/src/img/image.png");
				BOOST_CHECK_EQUAL(url.GetURL(), "https://google.com:452/src/img/image.png");
			}
		}

		BOOST_AUTO_TEST_CASE(objects_with_errors)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("www.google. m", "src/image.png", Protocol::HTTP, 15), std::invalid_argument);
			BOOST_REQUIRE_THROW(CHttpUrl url("www.google.com", "src/ima ge.png", Protocol::HTTPS, 42), std::invalid_argument);
		}

		BOOST_AUTO_TEST_SUITE(objects_without_errors)
			BOOST_AUTO_TEST_CASE(all_objects_get_by_constructor)
			{
				{
					CHttpUrl url("google.com", "src/img/image.png", Protocol::HTTPS, 443);
					BOOST_CHECK_EQUAL(url.GetURL(), "https://google.com/src/img/image.png");
				}
				{
					CHttpUrl url("google.com", "src/img/image.png", Protocol::HTTP, 443);
					BOOST_CHECK_EQUAL(url.GetURL(), "http://google.com:443/src/img/image.png");
				}

				{
					CHttpUrl url("google.com", "src/img/image.png", Protocol::HTTPS, 80);
					BOOST_CHECK_EQUAL(url.GetURL(), "https://google.com:80/src/img/image.png");
				}

				{
					CHttpUrl url("google.com", "src/img/image.png", Protocol::HTTP, 80);
					BOOST_CHECK_EQUAL(url.GetURL(), "http://google.com/src/img/image.png");
				}
			}

			BOOST_AUTO_TEST_CASE(port_can_be_init_by_default_value_for_current_protocol)
			{
				{
					CHttpUrl url("google.com", "src/img/image.png", Protocol::HTTPS);
					BOOST_CHECK_EQUAL(url.GetURL(), "https://google.com/src/img/image.png");
					BOOST_CHECK_EQUAL(url.GetPort(), 443);
				}
				{
					CHttpUrl url("google.com", "src/img/image.png", Protocol::HTTP);
					BOOST_CHECK_EQUAL(url.GetURL(), "http://google.com/src/img/image.png");
					BOOST_CHECK_EQUAL(url.GetPort(), 80);
				}
			}

			BOOST_AUTO_TEST_CASE(port_can_be_init_by_default_value_HTTP)
			{
				{
					CHttpUrl url("google.com", "src/img/image.png", 73);
					BOOST_CHECK_EQUAL(url.GetURL(), "http://google.com:73/src/img/image.png");
				}
				{
					CHttpUrl url("google.com", "src/img/image.png", 443);
					BOOST_CHECK_EQUAL(url.GetURL(), "http://google.com:443/src/img/image.png");
				}
			}

			BOOST_AUTO_TEST_CASE(port_and_protocol_can_be_init_by_default_values_HTTP_and_80)
			{
				{
					CHttpUrl url("google.com", "src/img/image.png");
					BOOST_CHECK_EQUAL(url.GetURL(), "http://google.com/src/img/image.png");
					BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
					BOOST_CHECK_EQUAL(url.GetPort(), 80);
				}

				{
					CHttpUrl url("google.com", "");
					BOOST_CHECK_EQUAL(url.GetURL(), "http://google.com/");
					BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
					BOOST_CHECK_EQUAL(url.GetPort(), 80);
				}
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()