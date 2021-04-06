//
// Created by jora on 3/12/21.
//

#ifndef SEARCH_ENGINE_PAGE_HPP
#define SEARCH_ENGINE_PAGE_HPP

#include <string>

class Page {
 private:
  std::string data;
  std::string effUrl;
  int status;

 public:
  Page(std::string effUrl, std::string data, int status);
  inline const std::string &getEffUrl() const;
  inline const std::string &getData() const;
  inline int getStatus() const;
  inline bool valid() const;
};

#endif //SEARCH_ENGINE_PAGE_HPP
