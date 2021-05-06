//
// Created by jora on 4/27/21.
//

#ifndef CRAWLER_WEBSITEREPODB_HPP
#define CRAWLER_WEBSITEREPODB_HPP

#include "mysql++/mysql++.h"
#include "WebsiteRepo.hpp"

class WebsiteRepoDb : public WebsiteRepo {
private:
	mysqlpp::Connection connection = false;
	mysqlpp::Query query{ nullptr };

public:
	WebsiteRepoDb(
			const std::string& dbName, const std::string& server,
			const std::string& user, const std::string& password, unsigned int port);
	~WebsiteRepoDb() noexcept override;
	std::vector<Website> getAll() override;
	void save(const Website& website) override;

private:
	void connectionFailMsg(
			const std::string& dbName, const std::string& server, const std::string& user,
			const std::string& password, unsigned int port);
	static std::unique_ptr<Website> getSiteFromDbRow(const mysqlpp::Row& row);
	mysqlpp::UseQueryResult runSqlCommand(const std::string& command);
};

#endif //CRAWLER_WEBSITEREPODB_HPP
