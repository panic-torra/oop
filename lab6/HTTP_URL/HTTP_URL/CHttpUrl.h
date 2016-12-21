#pragma once
#include "stdafx.h"
#include "CUrlParsingError.h"

class CHttpUrl
{
public:

	CHttpUrl(std::string const & url);
	CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port);
	CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol);
	CHttpUrl(std::string const & domain, std::string const & document, unsigned short port);
	CHttpUrl(std::string const & domain, std::string const & document);

	std::string GetURL()const;
	std::string GetDomain()const;
	std::string GetDocumentPath()const;
	Protocol GetProtocol()const;
	unsigned GetPort()const;


private:
	std::string m_domain;
	std::string m_document = "\\";
	Protocol m_protocol = Protocol::HTTP;
	unsigned m_port = 80;

	void ParseUrl(std::string const & url);
};

static std::string ParseProtocol(std::string const & url);
static std::string ParseDomain(std::string const & url);
static std::string ParsePort(std::string const & url);
static std::string ParseDocumentPath(std::string const & url);

static Protocol StrToProtocol(std::string const & protocolStr);
std::string ProtocolToStr(Protocol protocol);