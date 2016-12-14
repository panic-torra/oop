#include "stdafx.h"
#include "CHttpUrl.h"

CHttpUrl::CHttpUrl(std::string const & url)
{
	ParseUrl(url);
}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol = Protocol::HTTP, unsigned short port = 80)
	: m_domain(ParseDomain(domain))
	, m_document(ParseDocumentPath(document))
	, m_protocol(protocol)
	, m_port(port)
{
}

std::string CHttpUrl::GetURL() const
{
	auto url = ProtocolToStr() + "://" + m_domain;
	if (m_port != 80 && m_port != 443)
	{
		url += ":" + std::to_string(m_port);
	}
	return  url + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocumentPath() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::ParseUrl(std::string const & url)
{
	std::string urlStr(url);

	auto protocolStr = ParseProtocol(urlStr);
	m_protocol = StrToProtocol(protocolStr);
	urlStr = urlStr.substr(protocolStr.size() + 3);
	
	m_domain = ParseDomain(urlStr);
	urlStr = urlStr.substr(m_domain.size());

	if (urlStr[0] == ':')
	{
		m_port = std::stoi(ParsePort(urlStr));
		urlStr = urlStr.substr(std::to_string(m_port).size() + 1);
	}
	else
	{
		m_port = (m_protocol == Protocol::HTTP) ? 80 : 443;
	}
	
	m_document = ParseDocumentPath(urlStr);
}


std::string CHttpUrl::ParseProtocol(std::string const & url)
{
	auto end = url.find("://");

	if (end == std::string::npos)
	{
		throw CUrlParsingError("Invalid URL protocol.");
	}

	return url.substr(0, end);
}

std::string CHttpUrl::ParseDomain(std::string const & url)
{
	auto end = url.find(':');
	if (end == std::string::npos)
	{
		end = url.find("/");
	}
	auto domain = url.substr(0, end);
	return (domain == "" || (domain.find(' ') != std::string::npos)) ?	
		throw std::invalid_argument("Invalid URL domain.") : domain;
}

std::string CHttpUrl::ParsePort(std::string const & url)
{
	auto end = url.find("/");
	auto port = url.substr(1, end);

	return (port.empty() || (port.find(' ') != std::string::npos)) ?  
		throw CUrlParsingError("Invalid URL port.") : port;
}

std::string CHttpUrl::ParseDocumentPath(std::string const & url)
{
	auto document = (url[0] != '/') ? '/' + url : url;
	return ((document.find(' ') != std::string::npos)) ?
		throw std::invalid_argument("Invalid URL document path.") : document;
}

Protocol CHttpUrl::StrToProtocol(std::string const & protocolStr)
{
	if (protocolStr == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocolStr == "https")
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError("Invalid protocol type");
}

std::string CHttpUrl::ProtocolToStr()const
{
	return (m_protocol == Protocol::HTTP) ? "http" : "https";
}