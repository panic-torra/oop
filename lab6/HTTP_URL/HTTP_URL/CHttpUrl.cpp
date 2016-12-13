#include "stdafx.h"
#include "CHttpUrl.h"

CHttpUrl::CHttpUrl(std::string const& url)
{
	ParseUrl(url);
}

CHttpUrl::CHttpUrl(const std::string & domain, const std::string & document, Protocol protocol, unsigned short port)
{
}


std::string CHttpUrl::GetURL() const
{
	return "";
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return HTTP;
}

unsigned short CHttpUrl::GetPort() const
{
	return 0;
}

void CHttpUrl::ParseUrl(std::string const & url)
{
	std::string urlStr(url);

	auto protocolStr = ParseProtocol(urlStr);

}

std::string CHttpUrl::ParseProtocol(std::string const & url)
{
	std::string delimiter = "://";
	auto end = url.find(delimiter);

	if (end == std::string::npos)
	{
		//throw CUrlParsingError("Invalid URL protocol.");
	}

	return url.substr(0, end);
}
