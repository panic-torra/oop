#pragma once
#include "stdafx.h"

enum Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:

	CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = HTTP,
		unsigned short port = 80);

	~CHttpUrl() = default;

	std::string GetURL()const;
	std::string GetDomain()const;
	std::string GetDocument()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;

private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	void ParseUrl(std::string const & url);
};