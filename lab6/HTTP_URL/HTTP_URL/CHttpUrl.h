#pragma once
#include "stdafx.h"
#include "CUrlParsingError.h"

class CHttpUrl
{
public:

	CHttpUrl(std::string const & url);
	CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port);

	~CHttpUrl() = default;

	std::string GetURL()const;
	std::string GetDomain()const;
	std::string GetDocumentPath()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;

	std::string ProtocolToStr()const;

private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	void ParseUrl(std::string const & url);
	std::string ParseProtocol(std::string const & url);
	std::string ParseDomain(std::string const & url);
	std::string ParsePort(std::string const & url);
	std::string ParseDocumentPath(std::string const & url);

	Protocol StrToProtocol(std::string const & protocolStr);
};