//
// Created by jora on 5/18/21.
//

#include "Request.hpp"

Request::Request(const std::string& messageContent)
		: got(messageContent.empty())
{
	try {
		json content << messageContent;

	}
	catch (const json::parse_error& err) {
		std::cerr << "Server got non JSON format message!!\n\n";
		std::cerr << "Got an error: " << err.what() << "\n";
	}
}
