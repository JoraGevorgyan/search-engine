//
// Created by jora on 5/11/21.
//

#include <iostream>
#include <filesystem>
#include "RedirectFStream.hpp"
#include "ConfigParser.hpp"
#include "Server.hpp"

std::string getGivenFilePath(int argc, char** argv);

int main(int argc, char** argv)
{
	try {
		std::cout << "Look the program  output in 'errors.txt' and 'logs.txt' files." << std::endl;
		RedirectFStream redirectErr("errors.txt", stderr);
		RedirectFStream redirectLog("logs.txt", stdout);

		ConfigParser parser(getGivenFilePath(argc, argv));
		const auto& serverInfo = parser.getServerInfo();
		const auto& dbInfo = parser.getDbInfo();
		Server server(dbInfo.name, dbInfo.server, dbInfo.username, dbInfo.password, dbInfo.port,
				serverInfo.lisPort, serverInfo.maxResultCount);
		std::cout << "Server: start listening ..." << std::endl;
		server.start();
		std::cout << "Server: stop listening!" << std::endl;
		return 0;
	}
	catch (const mysqlpp::ConnectionFailed& failed) {
		std::cerr << "Please check your database validation, see parameters in config file" << std::endl;
		std::cerr << failed.what() << std::endl;
	}
	catch (const mysqlpp::UseQueryError& failed) {
		std::cerr <<" Got an error: " << failed.what() << std::endl;
	}
	catch (const std::exception& err) {
		std::cerr << "Got an error: " << err.what() << std::endl;
	}
}

std::string getGivenFilePath(int argc, char** argv)
{
	if (argc != 2) {
		std::cerr << "Wrong count of arguments!!\n";
		std::cerr << "We only need the path of the configuration file!\n";
		exit(1);
	}
	std::string pathToFile(argv[1]);
	std::cout << "Checking existence and type of the file '" << pathToFile << "' ..." << std::endl;
	auto path = std::filesystem::path(pathToFile);
	if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path)) {
		std::cerr << "The file doesn't exist or isn't a regular file!!\n";
		exit(1);
	}
	std::cout << "Checking permissions ..." << std::endl;
	std::filesystem::permissions(path, std::filesystem::perms::owner_read, std::filesystem::perm_options::add);
	return pathToFile;
}
