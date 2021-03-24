//
// Created by jora on 3/13/21.
//

#ifndef SEARCH_ENGINE_PARSER_HPP
#define SEARCH_ENGINE_PARSER_HPP

#include <gumbo.h>
#include <cerrno>
#include <string>
#include <vector>

class Parser {
private:
    std::vector<std::string> urls;
    std::string title;
    std::string description;
    std::string content;

    std::string html;
    std::string startingUrl;

public:
    Parser(std::string html, std::string startingUrl);

    int parse();
    const std::vector<std::string>& getUrls() const;
    const std::string& getTitle() const;
    const std::string& getDescription() const;
    const std::string& getContent() const;

private:
    int extractUrls(GumboNode* node, const std::string& homeUrl);
    int extractTitle(GumboNode* node);
    int extractDscrpt(GumboNode* node);
    std::string getHomeUrl(const std::string& url) const;
    std::string addPath(const std::string& homeUrl, const std::string& path) const;
};

#endif //SEARCH_ENGINE_PARSER_HPP
