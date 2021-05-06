//
// Created by jora on 4/27/21.
//

#include "WebsiteRepoDb.hpp"

WebsiteRepoDb::WebsiteRepoDb(
		const std::string& dbName, const std::string& server,
		const std::string& user, const std::string& password, unsigned int port)
{
	bool success = this->connection.connect(dbName.c_str(), server.c_str(), user.c_str(), password.c_str(), port);
	if (!success) {
		this->connectionFailMsg(dbName, server, user, password, port);
		exit(1);
	}
}

void WebsiteRepoDb::connectionFailMsg(
		const std::string& dbName, const std::string& server, const std::string& user,
		const std::string& password, unsigned int port)
{
	std::cerr << "error message: " << this->connection.error() << std::endl;
	std::cerr << "Please check your database validation, current options are:\n"
			  << std::endl
			  << ""
			  << "                     database name: \"" << dbName << "\"" << std::endl
			  << " server (domain name / ip address): \"" << server << "\"" << std::endl
			  << "                          username: \"" << user << "\"" << std::endl
			  << "                          password: \"" << password << "\"" << std::endl
			  << "                              port: \"" << port << "\"" << std::endl;
}

WebsiteRepoDb::~WebsiteRepoDb() noexcept
{
	if (this->connection.connected()) {
		this->connection.disconnect();
	}
}

std::vector<Website> WebsiteRepoDb::getAll()
{
	std::vector<Website> websites{};
	mysqlpp::Query query = this->connection.query();
	auto result = query.use("SELECT * FROM websites");
	if (!result) {
		return websites;
	}

	while (mysqlpp::Row row = result.fetch_row()) {
		tm timeStruct{};
		strptime(row["crawled"].c_str(), "%Y-%m-%d %H:%M:%S", &timeStruct);

		websites.emplace_back(std::move(Website(row["id"],
				std::string(row["domain"].data()),
				std::string(row["homepage"].data()),
				time_t(std::mktime(&timeStruct)))));
	}
	return websites;
}

void WebsiteRepoDb::save(const Website& website)
{
	mysqlpp::Query query = this->connection.query();
	query << "INSERT INTO websites(domain, homepage) "
		  << "VALUES ( '" << website.getDomain().c_str() << "', '"
		  << website.getHomepage().c_str() << "' )"
		  << "ON DUPLICATE KEY UPDATE homepage='" << website.getHomepage().c_str() << "', "
		  << "crawled=default;";
	if (!query.exec()) {
		std::cout << "can't store website, domain is: " << website.getDomain() << std::endl;
		std::cout << query.error() << std::endl;
	}
}
