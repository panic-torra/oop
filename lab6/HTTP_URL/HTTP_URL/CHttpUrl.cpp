#include "stdafx.h"
#include "CHttpUrl.h"

CHttpUrl::CHttpUrl(std::string const & url)
{
	ParseUrl(url);
}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port)
	: m_domain(ParseDomain(domain))
	, m_document(ParseDocumentPath(document))
	, m_protocol(protocol)
	, m_port(port)
{
}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol)
	: m_domain(ParseDomain(domain))
	, m_document(ParseDocumentPath(document))
	, m_protocol(protocol)
{
	m_port = (m_protocol == Protocol::HTTP) ? 80 : 443;
}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, unsigned short port )
	: m_domain(ParseDomain(domain))
	, m_document(ParseDocumentPath(document))
	, m_port(port)
{
}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document)
	: m_domain(ParseDomain(domain))
	, m_document(ParseDocumentPath(document))
{
}

std::string CHttpUrl::GetURL() const
{
	auto url = ProtocolToStr(m_protocol) + "://" + m_domain;

	if (!(m_port == 80 && m_protocol == Protocol::HTTP)  && !(m_port == 443 && m_protocol == Protocol::HTTPS))
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

unsigned CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::ParseUrl(std::string const & url)
{
	boost::string_ref urlStr(url);

	auto protocolStr = ParseProtocol(urlStr.to_string());
	m_protocol = StrToProtocol(protocolStr);
	urlStr.remove_prefix(protocolStr.size() + 3);
	
	m_domain = ParseDomain(urlStr.to_string());
	urlStr.remove_prefix(m_domain.size());

	if (urlStr[0] == ':')
	{
		try
		{
			m_port = std::stoi(ParsePort(urlStr.to_string()));
		}
		catch (...)
		{
			throw CUrlParsingError("Invalid URL port.");
		}
		urlStr.remove_prefix(std::to_string(m_port).size() + 1);
	}
	else
	{
		m_port = (m_protocol == Protocol::HTTP) ? 80 : 443;
	}
	
	m_document = ParseDocumentPath(urlStr.to_string());
}


 std::string ParseProtocol(std::string const & url)
{
	auto end = url.find("://");

	if (end == std::string::npos)
	{
		throw CUrlParsingError("Invalid URL protocol.");
	}

	return url.substr(0, end);
}

 std::string ParseDomain( std::string const & url)
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

 std::string ParsePort( std::string const & url)
{
	auto end = url.find("/");
	auto port = url.substr(1, end);

	return (port.empty() || (port.find(' ') != std::string::npos || std::stoi(port) <= 0 || std::stoi(port) >= 65536)) ?
		throw CUrlParsingError("Invalid URL port.") : port;
}

 std::string ParseDocumentPath( std::string const & url)
{
	auto document = (url[0] != '/') ? '/' + url : url;
	return ((document.find(' ') != std::string::npos)) ?
		throw std::invalid_argument("Invalid URL document path.") : document;
}

Protocol StrToProtocol( std::string const & protocolStr)
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

std::string ProtocolToStr(Protocol protocol)
{
	return ((protocol == Protocol::HTTP) ? "http" : "https");
}