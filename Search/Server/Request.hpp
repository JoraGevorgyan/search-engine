//
// Created by jora on 5/18/21.
//

#ifndef SEARCH_REQUEST_HPP
#define SEARCH_REQUEST_HPP

#include <string>
#include <sstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Request {
private:
	std::string requiredOffer;
	int requiredCount;

public:
	explicit Request(const std::string& messageContent);
	[[nodiscard]] inline const std::string& getRequiredOffer() const
	{
		return this->requiredOffer;
	}
	[[nodiscard]] inline int getRequiredCount() const
	{
		return this->requiredCount;
	}
};

#endif //SEARCH_REQUEST_HPP
