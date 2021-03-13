//
// Created by jora on 3/13/21.
//

#ifndef SEARCH_ENGINE_PARSER_HPP
#define SEARCH_ENGINE_PARSER_HPP

#include <gumbo.h>
#include <iostream>
#include <string>
#include <vector>

class Parser {
private:
    std::vector<std::string> urls;
    std::string title;
    std::string description;
    std::string content;

    std::string html;
    std::string rootUrl;
    std::string domain;

public:
    Parser(const std::string& html, const std::string& rootUrl);

    void parse();
    const std::vector<std::string>& getUrls() const;
    const std::string& getTitle() const;
    const std::string& getDescription() const;
    const std::string& getContent() const;

private:
    std::string getDomain(const std::string& url);
    void extractUrls(GumboNode* node);
    bool isAbsUrl(const std::string& url) const;
};


#endif //SEARCH_ENGINE_PARSER_HPP
