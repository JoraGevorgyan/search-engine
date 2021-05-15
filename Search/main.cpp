//
// Created by jora on 5/11/21.
//

#include <iostream>
#include <filesystem>
#include <chrono>
#include "RedirectFStream.hpp"
#include "ConfigParser.hpp"
#include "Server.hpp"
#include "Search.hpp"

std::string getGivenFilePath(int argc, char** argv)
{
	if (argc != 2) {
		std::cerr << "Wrong count of arguments!!\n";
		std::cerr << "We only need the path of the configuration file!\n";
		exit(1);
	}
	std::string pathToFile(argv[1]);
	auto path = std::filesystem::path(pathToFile);
	if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path)) {
		std::cerr << "The file doesn't exist or isn't a regular file!!\n";
		exit(1);
	}
	std::filesystem::permissions(path, std::filesystem::perms::owner_read, std::filesystem::perm_options::add);
	return pathToFile;
}

int main(int argc, char** argv)
{
//	RedirectFStream redirectErr("errors.txt", stderr);
//	RedirectFStream redirectLog("logs.txt", stdout);

	ConfigParser parser(getGivenFilePath(argc, argv));
	const auto& serverInfo = parser.getServerInfo();
	const auto& dbInfo = parser.getDbInfo();
	Server server(serverInfo.lisAddr, serverInfo.port);
	Search search(dbInfo.name, dbInfo.server, dbInfo.username, dbInfo.password, dbInfo.port);

	auto start = std::chrono::steady_clock::now();
	const long maxDurationTime = parser.getMaxDurationTime();
	while (true) {
		auto duration =
				std::chrono::duration_cast<std::chrono::hours>(std::chrono::steady_clock::now() - start).count();
		if (duration > maxDurationTime) {
			break;
		}
		auto request = server.getRequest();
		if (request.got) {
			server.sendAnswer(search.find(request.requiredOffer, request.requiredCount));
		}
	}
	return 0;
}