//
// Created by jora on 3/13/21.
//

#ifndef CRAWLER_PARSER_HPP
#define CRAWLER_PARSER_HPP

#include <gumbo.h>
#include <cerrno>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Parser {
private:
	std::vector<std::string> urls;
	std::string title;
	std::string description;
	std::string content;

	std::string html;
	std::string startingUrl;
	int invalid;

public:
	Parser(std::string html, std::string startingUrl);

	[[nodiscard]] inline bool isValid() const
	{
		return this->invalid == 0;
	}
	[[nodiscard]] inline const std::vector<std::string>& getUrls() const
	{
		return this->urls;
	}
	[[nodiscard]] inline const std::string& getTitle() const
	{
		return this->title;
	}
	[[nodiscard]] inline const std::string& getDescription() const
	{
		return this->description;
	}
	[[nodiscard]] inline const std::string& getContent() const
	{
		return this->content;
	}
private:
	int parse();
	int extractUrls(GumboNode* node, const std::string& homeUrl);
	int extractTitle(GumboNode* node);
	int extractDescription(GumboNode* node);
	int extractContent(GumboNode* node);
	[[nodiscard]] static std::string getHomeUrl(const std::string& url) ;
	[[nodiscard]] std::string addPath(const std::string& homeUrl, const std::string& path) const;
};

#endif //CRAWLER_PARSER_HPP
