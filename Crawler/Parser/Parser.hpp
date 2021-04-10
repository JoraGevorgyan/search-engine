//
// Created by jora on 3/13/21.
//

#ifndef SEARCH_ENGINE_PARSER_HPP
#define SEARCH_ENGINE_PARSER_HPP

#include <gumbo.h>
#include <cerrno>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

class Parser {
 private:
  std::vector<std::string> urls;
  std::string title;
  std::string description;
  std::string content;
  std::string domain;

  std::string html;
  std::string startingUrl;

 public:
  Parser(std::string html, std::string startingUrl);

  int parse();
  inline const std::vector<std::string> &getUrls() const;
  inline const std::string &getTitle() const;
  inline const std::string &getDescription() const;
  inline const std::string &getContent() const;
  inline const std::string &getDomain() const;

 private:
  int extractUrls(GumboNode *node, const std::string &homeUrl);
  int extractTitle(GumboNode *node);
  int extractDscrpt(GumboNode *node);
  int extractContent(GumboNode *node);
  void setDomain();
  std::string getHomeUrl(const std::string &url) const;
  std::string addPath(const std::string &homeUrl, const std::string &path) const;
};

#endif //SEARCH_ENGINE_PARSER_HPP
