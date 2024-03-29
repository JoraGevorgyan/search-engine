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
		std::cout << "Config parser: start reading from '" << path << "' file." << std::endl;
		std::ifstream file(path);
		if (!file.is_open()) {
			std::cerr << "Can't open file: " << path << std::endl;
			exit(1);
		}
		file >> this->configs;
		file.close();
	}
	catch (nlohmann::detail::parse_error& err) {
		ConfigParser::showErr(err.what());
	}
}

void ConfigParser::parseArguments()
{
	try {
		std::cout << "Config parser: start parsing arguments" << std::endl;
		const auto database = this->configs.at(DB_INFO)[0];
		database.at(DB_NAME).get_to(this->dbInfo.name);
		database.at(SERVER_NAME).get_to(this->dbInfo.server);
		database.at(USERNAME).get_to(this->dbInfo.username);
		database.at(PASSWORD).get_to(this->dbInfo.password);
		database.at(PORT).get_to(this->dbInfo.port);

		const auto server = this->configs.at(SERVER_INFO)[0];
		server.at(LIS_PORT).get_to(this->serverInfo.lisPort);
		server.at(MAX_COUNT).get_to(this->serverInfo.maxResultCount);
	}
	catch (nlohmann::detail::out_of_range& err) {
		ConfigParser::showErr(err.what());
	}
	catch (nlohmann::detail::type_error& err) {
		ConfigParser::showErr(err.what());
	}
}

void ConfigParser::showErr(const char* message)
{
	std::cerr << "Check Your configuration file validation!!\n\n";
	std::cerr << "Got an error: " << message << "\n";
	exit(1);
}
