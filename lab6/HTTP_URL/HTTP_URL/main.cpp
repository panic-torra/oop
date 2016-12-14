#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

int main(int argc, char *argv[])
{
	std::string input;
	while (std::getline(std::cin, input))
	{
		try
		{
			CHttpUrl url(input);

			std::cout << "URL: " << url.GetURL() << std::endl
				<< "Protocol: ";
			auto protocol = url.GetProtocol();
			if (url.GetProtocol() == Protocol::HTTP)
			{
				std::cout << "http";
			}
			else
			{
				std::cout << "https";
			}
			std::cout << std::endl
				<< "Domain name: " << url.GetDomain() << std::endl
				<< "Document: " << url.GetDocumentPath() << std::endl
				<< "Port: " << url.GetPort() << std::endl;
		}
		catch (std::invalid_argument const & err)
		{
			std::cout << err.what() << std::endl;
		}
	}
	return 0;
}