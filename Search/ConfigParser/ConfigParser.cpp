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
		auto database = this->configs.at(DB_INFO)[0];
		database.at(DB_NAME).get_to(this->dbInfo.name);
		database.at(SERVER_NAME).get_to(this->dbInfo.server);
		database.at(USERNAME).get_to(this->dbInfo.username);
		database.at(PASSWORD).get_to(this->dbInfo.password);
		database.at(PORT).get_to(this->dbInfo.port);

		auto server = this->configs.at(SERVER_INFO)[0];
		server.at(LIS_ADDR).get_to(this->serverInfo.lisAddr);
		server.at(LIS_PORT).get_to(this->serverInfo.port);

		this->configs.at(MAX_DUR_TIME).get_to(this->maxDurTime);
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