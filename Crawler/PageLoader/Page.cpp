//
// Created by jora on 3/12/21.
//

#include "Page.hpp"

Page::Page(std::string effUrl, std::string data, int status)
    : effUrl{std::move(effUrl)}, data{std::move(data)}, status{status} {
}

inline const std::string &Page::getEffUrl() const {
  return this->effUrl;
}

inline const std::string &Page::getData() const {
  return this->data;
}

inline int Page::getStatus() const {
  return this->status;
}

inline bool Page::valid() const {
  return this->status >= 200 && this->status <= 300;
}