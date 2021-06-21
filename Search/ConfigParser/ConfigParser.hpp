//
// Created by jora on 5/15/21.
//

#ifndef SEARCH_CONFIGPARSER_HPP
#define SEARCH_CONFIGPARSER_HPP

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

#define DB_INFO "databaseInfo"
#define DB_NAME "databaseName"
#define SERVER_NAME "serverName"
#define USERNAME "username"
#define PASSWORD "password"
#define PORT "port"

#define SERVER_INFO "serverInfo"
#define LIS_PORT "listeningPort"

struct DatabaseInfo {
	std::string name;
	std::string server;
	std::string username;
	std::string password;
	unsigned long port;
};

class ConfigParser {
private:
	DatabaseInfo dbInfo;
    unsigned long serverLisPort;

public:
	explicit ConfigParser(const std::string& configFilePath);
	[[nodiscard]] inline const DatabaseInfo& getDbInfo() const
	{
		return this->dbInfo;
	}
	[[nodiscard]] inline const unsigned long& getServerLisPort() const
	{
		return this->serverLisPort;
	}

private:
	void readFile(const std::string& path);
	void parseArguments();
	static void showErr(const char* message);

	nlohmann::json configs;
};

#endif //SEARCH_CONFIGPARSER_HPP
