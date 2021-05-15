//
// Created by jora on 3/13/21.
//

#include <filesystem>
#include "RedirectFStream.hpp"
#include "ConfigParser.hpp"
#include "Crawler.hpp"

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
	RedirectFStream redirectErr("errors.txt", stderr);
	RedirectFStream redirectLog("logs.txt", stdout);
	ConfigParser parser(getGivenFilePath(argc, argv));
	crawler::start(
			parser.getDbName(), parser.getServerName(), parser.getUsername(),
			parser.getPassword(), parser.getPort(), parser.getWebsites());

	return 0;
}
