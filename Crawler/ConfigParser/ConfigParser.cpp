//
// Created by jora on 5/15/21.
//

#include "ConfigParser.hpp"

ConfigParser::ConfigParser(const std::string& configFilePath)
{
	this->readFile(configFilePath);
	this->parseArguments();
}

void ConfigParser::readFile(const std::string& path)
{
	try {
		std::ifstream file(path);
		if (!file.is_open()) {
			std::cerr << "Can't open file: " << path << std::endl;
			exit(1);
		}
		file >> this->configs;
		file.close();
	}
	catch (nlohmann::detail::parse_error& err) {
		std::cerr << "Check Your configuration file validation!!\n\n";
		std::cerr << "Got an error: " << err.what() << "\n";
		exit(1);
	}
}

void ConfigParser::parseArguments()
{
	try {
		this->configs.at(DB_NAME).get_to(this->dbName);
		this->configs.at(SERVER_NAME).get_to(this->serverName);
		this->configs.at(USERNAME).get_to(this->username);
		this->configs.at(PASSWORD).get_to(this->password);
		this->configs.at(PORT).get_to(this->port);

		for (auto current : this->configs.at(WEBSITES)) {
			std::pair<std::string, std::string> website{};
			current.at(DOMAIN).get_to(website.first);
			current.at(HOMEPAGE).get_to(website.second);
			this->websites.emplace_back(website);
		}
	}
	catch (nlohmann::detail::out_of_range& err) {
		std::cerr << "Check Your configuration file validation!!\n\n";
		std::cerr << "Got an error: " << err.what() << "\n";
		exit(1);
	}
	catch (nlohmann::detail::type_error& err) {
		std::cerr << "Check Your configuration file validation!!\n\n";
		std::cerr << "Got an error: " << err.what() << "\n";
		exit(1);
	}
}
