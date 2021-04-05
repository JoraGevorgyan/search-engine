//
// Created by jora on 3/12/21.
//

#include "Page.hpp"

Page::Page(std::string effUrl, std::string data, int status)
    : effUrl{std::move(effUrl)}, data{std::move(data)}, status{status} {
}

const std::string &Page::getEffUrl() const {
  return this->effUrl;
}

const std::string &Page::getData() const {
  return this->data;
}

int Page::getStatus() const {
  return this->status;
}