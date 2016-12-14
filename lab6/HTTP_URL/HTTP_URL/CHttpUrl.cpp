#include "stdafx.h"
#include "CHttpUrl.h"

CHttpUrl::CHttpUrl(std::string const & url)
{
	ParseUrl(url);
}

CHttpUrl::CHttpUrl(std::string const & domain, 
	std::string const & document, 
	Protocol protocol, 
	unsigned short port)
	: m_domain(domain)
	, m_document(document)
	, m_protocol(protocol)
	, m_port(port)
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
	return Protocol::HTTP;
}

unsigned short CHttpUrl::GetPort() const
{
	return 0;
}

std::string CHttpUrl::ProtocolToStr()
{
	return (m_protocol == Protocol::HTTP) ? "http" : "https";
}

void CHttpUrl::ParseUrl(std::string const & url)
{
	std::string urlStr(url);

	auto protocolStr = ParseProtocol(urlStr);
	m_protocol = GetProtocolType(protocolStr);
	urlStr = urlStr.substr(protocolStr.size() + 3, urlStr.size() - 1);
	
	m_domain = ParseDomain(urlStr);
	urlStr = urlStr.substr(m_domain.size(), urlStr.size() - 1);

	
}



std::string CHttpUrl::ParseProtocol(std::string const & url)
{
	std::string delimiter = "://";
	auto end = url.find(delimiter);

	if (end == std::string::npos)
	{
		throw CUrlParsingError("Invalid URL protocol.");
	}

	return url.substr(0, end);
}

Protocol CHttpUrl::GetProtocolType(std::string const & protocolStr)
{
	if (protocolStr == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocolStr == "https")
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError("Invalid URL protocol.");
}

std::string CHttpUrl::ParseDomain(std::string const & url)
{
	auto start = strstr(url.c_str(), ":\\");
	auto end = std::string::npos;
	if (start != "")
	{
		end = url.find("/");
	}

	auto domain = url.substr(0, end);
	if (domain == "" || (domain.find(' ') != std::string::npos))
	{
		throw CUrlParsingError("Invalid URL domain name.");
	}
	
	return domain;
}