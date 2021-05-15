//
// Created by jora on 5/15/21.
//

#ifndef SEARCH_CONFIGPARSER_HPP
#define SEARCH_CONFIGPARSER_HPP

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

#define DB_INFO "database info"
#define DB_NAME "database name"
#define SERVER_NAME "server name"
#define USERNAME "username"
#define PASSWORD "password"
#define PORT "port"
#define SERVER_INFO "server info"
#define LIS_ADDR "listening address"
#define LIS_PORT "listening port"
#define MAX_DUR_TIME "maximal duration time(hours)"

struct DatabaseInfo {
	std::string name;
	std::string server;
	std::string username;
	std::string password;
	unsigned long port;
};

struct ServerInfo {
	std::string lisAddr;
	unsigned long port;
};

class ConfigParser {
private:
	DatabaseInfo dbInfo;
	ServerInfo serverInfo;
	long maxDurTime;

public:
	explicit ConfigParser(const std::string& configFilePath);
	[[nodiscard]] inline const DatabaseInfo& getDbInfo() const
	{
		return this->dbInfo;
	}
	[[nodiscard]] inline const ServerInfo& getServerInfo() const
	{
		return this->serverInfo;
	}
	[[nodiscard]] inline long getMaxDurationTime() const
	{
		return this->maxDurTime;
	}

private:
	void readFile(const std::string& path);
	void parseArguments();

	nlohmann::json configs;
};

#endif //SEARCH_CONFIGPARSER_HPP
